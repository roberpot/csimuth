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

#include "../include/mutex.h"

namespace csimuth {

    // Mutex:: Constructors, Destructor, Asign operator.

    Mutex::Mutex() {
        #ifdef __CSIMUTH_WINAPI
            InitializeCriticalSectionAndSpinCount(&_mutex, 0x80000020);
        #endif
        #ifdef __CSIMUTH_PTHREAD
            // Initialize pthread mutex attr.
            pthread_mutexattr_init(&_mutex_attr);
            // Set pthread mutex attr to allow multiple unlocks (no relocking deadlock).
            pthread_mutexattr_settype(&_mutex_attr, PTHREAD_MUTEX_RECURSIVE_NP);
            // Initialize pthread mutex.
            pthread_mutex_init(&_mutex, &_mutex_attr);
        #endif
    }

    Mutex::~Mutex() {
        #ifdef __CSIMUTH_WINAPI
            DeleteCriticalSection(&_mutex);
        #endif
        #ifdef __CSIMUTH_PTHREAD
            pthread_mutexattr_destroy(&_mutex_attr);
            pthread_mutex_destroy(&_mutex);
        #endif
    }

    // Mutex:: Interaction.

    void Mutex::lock() {
        #ifdef __CSIMUTH_WINAPI
            EnterCriticalSection(&_mutex);
        #endif
        #ifdef __CSIMUTH_PTHREAD
            pthread_mutex_lock(&_mutex);
        #endif
    }

    bool Mutex::trylock() {
        #ifdef __CSIMUTH_WINAPI
            return TryEnterCriticalSection(&_mutex) == TRUE;
        #endif
        #ifdef __CSIMUTH_PTHREAD
            return pthread_mutex_trylock(&_mutex) == 0;
        #endif
    }

    void Mutex::unlock() {
        #ifdef __CSIMUTH_WINAPI
            LeaveCriticalSection(&_mutex);
        #endif
        #ifdef __CSIMUTH_PTHREAD
            pthread_mutex_unlock(&_mutex);
        #endif
    }
}
