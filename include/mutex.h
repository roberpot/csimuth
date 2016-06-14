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

#ifndef __CSIMUTH_MUTEX_H
#define __CSIMUTH_MUTEX_H

#include "defines.h"

namespace csimuth {
    class Mutex {
    public:
        /** @name Constructors, Destructor, Asign operator:
        */
        ///@{
        Mutex();
        ~Mutex();
    private:
        // Copy not allowed.
        Mutex(const Mutex& copy);
        Mutex& operator=(const Mutex& other);
        ///@}

    public:
        /** @name Interaction:
        */
        ///@{
        /**
        * @brief Locks the mutex.
        *
        * Waits for ownership of the mutex. The function returns when the calling
        * thread is granted ownership.
        */
        void lock();
        /**
        * @brief Tries to lock the mutex.
        *
        * Attempts to locks the mutex withouth blocking. If the call is
        * successful, the calling thread takes ownership of the critical section.
        * @return True If the mutex is successfully entered or the current
        * thread already owns the mutex, false otherwise.
        */
        bool trylock();
        /**
        * @brief Unlocks the mutex.
        *
        * Releases ownership of the mutex.
        */
        void unlock();
        ///@}

    private:
        #ifdef __CSIMUTH_WINAPI
                CRITICAL_SECTION _mutex;   ///< Windows API specific mutex.
        #endif
        #ifdef __CSIMUTH_PTHREAD
                pthread_mutex_t _mutex;   ///< Unix API specific mutex.
                pthread_mutexattr_t _mutex_attr;   ///< Unix API mutex attr.
        #endif
    };
}

#endif //__CSIMUTH_MUTEX_H
