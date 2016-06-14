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

#ifndef __CSIMUTH_THREAD_H
#define __CSIMUTH_THREAD_H

#include "defines.h"
#include "mutex.h"

namespace csimuth {
    class Thread {
    public:
        /** @name Constructors, Destructor, Asign operator:
        */
        ///@{
        Thread();
        ~Thread();
    private:
        Thread(const Thread& copy);
        Thread& operator=(const Thread& other);
        ///@}
    public:
        /** @name Interaction:
        */
        ///@{
        int start();
        virtual void * run() = 0;
        int stop();
        int join();
        ///@}
    private:
        static void * _run(void * c);
        bool _running;
        Mutex _mutex;
        #ifdef __CSIMUTH_WINAPI
            HANDLE _thread;
        #endif
        #ifdef __CSIMUTH_PTHREAD
            pthread_t _thread;
            pthread_attr_t _attr;
        #endif
    };
}

#endif //__CSIMUTH_THREAD_H
