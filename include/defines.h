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

#ifndef __CSIMUTH_DEFINES_H
#define __CSIMUTH_DEFINES_H

#ifdef _WIN32
    #ifdef _MSVC
        #define __CSIMUTH_WINAPI
    #endif
    #ifdef __MINGW32__
        #define __CSIMUTH_PTHREAD
    #endif
#else
    #define __CSIMUTH_PTHREAD
#endif

#ifdef __CSIMUTH_WINAPI
#include <windows.h>
#endif
#ifdef __CSIMUTH_PTHREAD
#include <pthread.h>
#endif

#endif //__CSIMUTH_DEFINES_H
