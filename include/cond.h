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

#ifndef __CSIMUTH_COND_H
#define __CSIMUTH_COND_H

#include "defines.h"

namespace csimuth {
    class ConditionVariable {
    public:
        /** @name Constructors, Destructor, Asign operator:
        */
        ///@{
        ConditionVariable();
        ~ConditionVariable();
    private:
        ConditionVariable(const ConditionVariable& copy);
        ConditionVariable& operator=(const ConditionVariable& other);
        ///@}
    public:
        /** @name Interaction:
        */
        ///@{
        void lock();
        void unlock();
        void wait();
        void signal();
    private:
        #ifdef __CSIMUTH_WINAPI
            CRITICAL_SECTION _mutex;   ///< Windows API specific mutex.
            CONDITION_VARIABLE _condvar;   ///< Windows API specific condition variable.
        #endif
        #ifdef __CSIMUTH_PTHREAD
            pthread_cond_t _condvar;   ///< Unix API specific condition variable.
            pthread_mutex_t _mutex;   ///< Unix API specific mutex.
            pthread_mutexattr_t _mutex_attr;   ///< Unix API mutex attr.
        #endif
    };
}

#endif //__CSIMUTH_COND_H
