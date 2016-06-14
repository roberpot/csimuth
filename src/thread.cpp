/*
 * Copyright 2016 Roberto García Carvajal
 *
 * This file is part of CSimuth.
 * CSimuth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * CSimuth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with CSimuth. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/thread.h"

namespace csimuth {
    Thread::Thread() {
        _running = false;
        #ifdef __CSIMUTH_WINAPI
        #endif
        #ifdef __CSIMUTH_PTHREAD
            // Initialize and set thread detached attribute.
            pthread_attr_init(&_attr);
            pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_JOINABLE);
        #endif
    }

    Thread::~Thread() {
        _mutex.lock();
        if (_running) {
            _mutex.unlock();
            stop();
        }
        #ifdef __CSIMUTH_WINAPI
        #endif
        #ifdef __CSIMUTH_PTHREAD
        pthread_attr_destroy(&_attr);
        #endif
    }

    int Thread::start() {
        _mutex.lock();
        if (_running) {
            _mutex.unlock();
            return 1;
        }
        #ifdef __CSIMUTH_WINAPI
            _thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Thread::_run, this, 0, NULL);
            if (_thread == NULL)  {
                _mutex.unlock();
                return 2;
            }
        #endif
        #ifdef __CSIMUTH_PTHREAD
            int rc;
            rc = pthread_create(&_thread, &_attr, &Thread::_run, this);
            if (rc) {
                _mutex.unlock();
                return 2;
            }
        #endif
        _running = true;
        _mutex.unlock();
        return 0;
    }

    int Thread::stop() {
        _mutex.lock();
        if (!_running) {
            _mutex.unlock();
            return 1;
        }
        #ifdef __CSIMUTH_WINAPI
            TerminateThread(_thread, 0);
        #endif
        #ifdef __CSIMUTH_PTHREAD
            int rc = pthread_cancel(_thread);
            if (rc) {
                _mutex.unlock();
                return 2;
            }
        #endif
        _mutex.unlock();
        return 0;
    }

    int Thread::join() {
        _mutex.lock();
        if (!_running) {
            _mutex.unlock();
            return 1;
        }
        #ifdef __CSIMUTH_WINAPI
            WaitForSingleObject(_thread, INFINITE);
        #endif
        #ifdef __CSIMUTH_PTHREAD
            void * status;
            int rc;
            rc = pthread_join(_thread, &status);
            if (rc) {
                _mutex.unlock();
                return 2;
            }
        #endif
        _running = false;
        _mutex.unlock();
        return 0;
    }

    void * Thread::_run(void * c) {
        ((Thread *)c)->run();
        #ifdef __CSIMUTH_WINAPI
            ExitThread(0);
        #endif
        #ifdef __CSIMUTH_PTHREAD
            pthread_exit(NULL);
        #endif
        return NULL;
    }

}