/////////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2024 Walrus Ted Sloth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
/////////////////////////////////////////////////////////////////////////////////

// wrslog.h - WellRestedSloth logger
// Header-only C logging utility.

#ifndef __WRSLOG_H__
#define __WRSLOG_H__

#include <stdio.h>
#include <time.h>

///////////////////////////////////////////////////////////
// Customize the values in this section below. (Start)
///////////////////////////////////////////////////////////

// Enable the logger unless __WRSLOG_DISABLE is defined
#if defined(__WRSLOG_DISABLE)
#define __WRSLOG_ENABLE 0
#else
#define __WRSLOG_ENABLE 1
#endif

// Set the logging target:
#define __WRSLOG_TARGET stderr

// Set the module name:
#define __WRSLOG_MODULE "APP"

// Set the logging level:
// Any log message with levels less than this (that is, of higher priority)
// will be printed to the target.
#define __WRSLOG_LEVEL __WRSLOG_LEVEL_DEBUG

// Set the config for logging colors:
//     0 for no terminal colors
//     1 for terminal ANSI colors
#define __WRSLOG_COLOR 1

// Set the time format:
//     0 for custom format
//     1 for ISO 8601 local time format
//         Example for PDT:
//         [YYYY-MM-DDThh:mm:ss.msec-0700]
#define __WRSLOG_ISO8601 1

// Set __WRSLOG_PRETAG, __WRSLOG_TAG, __WRSLOG_POSTTAG to be passed into fprintf():
//     __WRSLOG_PRETAG;
//     fprintf(target, __WRSLOG_TAG, __WRSLOG_POSTTAG);
// Please refer to actual logging functions below to see how these are used.

#if __WRSLOG_ISO8601

// ISO 8601 time format
#define __WRSLOG_PRETAG \
    struct timespec _ts; \
    struct tm _tm; \
    clock_gettime(CLOCK_REALTIME, &_ts); \
    localtime_r(&_ts.tv_sec, &_tm); \

#define __WRSLOG_TAG "[%04d-%02d-%02dT%02d:%02d:%02d.%03ld%+03ld%02ld][%s-%d-%s](%s:%s:%d) "

#define __WRSLOG_POSTTAG(lvlnum, lvlstr) \
    _tm.tm_year+1900, _tm.tm_mon+1, _tm.tm_mday, \
    _tm.tm_hour, _tm.tm_min, _tm.tm_sec, _ts.tv_nsec/(1000*1000), \
    (-1*_tm.tm_gmtoff)/3600, (_tm.tm_gmtoff<0?((-1*_tm.tm_gmtoff)%3600)/60:(_tm.tm_gmtoff%3600)/60), \
    __WRSLOG_MODULE, lvlnum, lvlstr, \
    __FILE__, __func__, __LINE__

#else // __WRSLOG_ISO8601

// Custom time format
#define __WRSLOG_PRETAG \
    struct timespec _ts; \
    struct tm _tm; \
    clock_gettime(CLOCK_REALTIME, &_ts); \
    localtime_r(&_ts.tv_sec, &_tm);

#define __WRSLOG_TAG "[%02d:%02d:%02d.%03ld][%d][%s:%s:%d] "

#define __WRSLOG_POSTTAG(lvlnum, lvlstr) \
    _tm.tm_hour, _tm.tm_min, _tm.tm_sec, _ts.tv_nsec/(1000*1000), \
    lvlnum, \
    __FILE__, __func__, __LINE__

#endif // __WRSLOG_ISO8601

///////////////////////////////////////////////////////////
// Customize the values in this section above. (End)
///////////////////////////////////////////////////////////


// log levels the same as Linux kernel log levels:
#define __WRSLOG_LEVEL_EMERG    0
#define __WRSLOG_LEVEL_ALERT    1
#define __WRSLOG_LEVEL_CRIT     2
#define __WRSLOG_LEVEL_ERR      3
#define __WRSLOG_LEVEL_WARNING  4
#define __WRSLOG_LEVEL_NOTICE   5
#define __WRSLOG_LEVEL_INFO     6
#define __WRSLOG_LEVEL_DEBUG    7

#define __WRSLOG_LEVEL_EMERG_STR    "EMERG"
#define __WRSLOG_LEVEL_ALERT_STR    "ALERT"
#define __WRSLOG_LEVEL_CRIT_STR     "CRIT"
#define __WRSLOG_LEVEL_ERR_STR      "ERR"
#define __WRSLOG_LEVEL_WARNING_STR  "WARNING"
#define __WRSLOG_LEVEL_NOTICE_STR   "NOTICE"
#define __WRSLOG_LEVEL_INFO_STR     "INFO"
#define __WRSLOG_LEVEL_DEBUG_STR    "DEBUG"

// colors
#if __WRSLOG_COLOR
#define __WRSLOG_COLOR_RESET        "\x1b[0m"
#define __WRSLOG_COLOR_RED          "\x1b[0;31m"
#define __WRSLOG_COLOR_BOLD_RED     "\x1b[1;31m"
#define __WRSLOG_COLOR_GREEN        "\x1b[0;32m"
#define __WRSLOG_COLOR_BOLD_GREEN   "\x1b[1;32m"
#define __WRSLOG_COLOR_YELLOW       "\x1b[0;33m"
#define __WRSLOG_COLOR_BOLD_YELLOW  "\x1b[1;33m"
#define __WRSLOG_COLOR_BLUE         "\x1b[0;34m"
#define __WRSLOG_COLOR_BOLD_BLUE    "\x1b[1;34m"
#define __WRSLOG_COLOR_MAGENTA      "\x1b[0;35m"
#define __WRSLOG_COLOR_BOLD_MAGENTA "\x1b[1;35m"
#define __WRSLOG_COLOR_CYAN         "\x1b[0;36m"
#define __WRSLOG_COLOR_BOLD_CYAN    "\x1b[1;36m"
#define __WRSLOG_COLOR_WHITE        "\x1b[0;37m"
#define __WRSLOG_COLOR_BOLD_WHITE   "\x1b[1;37m"
#else // __WRSLOG_COLOR
#define __WRSLOG_COLOR_RESET        ""
#define __WRSLOG_COLOR_RED          ""
#define __WRSLOG_COLOR_BOLD_RED     ""
#define __WRSLOG_COLOR_GREEN        ""
#define __WRSLOG_COLOR_BOLD_GREEN   ""
#define __WRSLOG_COLOR_YELLOW       ""
#define __WRSLOG_COLOR_BOLD_YELLOW  ""
#define __WRSLOG_COLOR_BLUE         ""
#define __WRSLOG_COLOR_BOLD_BLUE    ""
#define __WRSLOG_COLOR_MAGENTA      ""
#define __WRSLOG_COLOR_BOLD_MAGENTA ""
#define __WRSLOG_COLOR_CYAN         ""
#define __WRSLOG_COLOR_BOLD_CYAN    ""
#define __WRSLOG_COLOR_WHITE        ""
#define __WRSLOG_COLOR_BOLD_WHITE   ""
#endif // __WRSLOG_COLOR

// Actual logging below.

// Emergency level __WRSLOG_LEVEL_EMERG (0)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_EMERG)
#define WRSLOG_EMERG(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_BOLD_YELLOW __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
        __WRSLOG_POSTTAG(__WRSLOG_LEVEL_EMERG,__WRSLOG_LEVEL_EMERG_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_EMERG(fmt, ...) do {} while(0)
#endif

// Alert level __WRSLOG_LEVEL_ALERT (1)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_ALERT)
#define WRSLOG_ALERT(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_BOLD_MAGENTA __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
        __WRSLOG_POSTTAG(__WRSLOG_LEVEL_ALERT,__WRSLOG_LEVEL_ALERT_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_ALERT(fmt, ...) do {} while(0)
#endif

// Critical level __WRSLOG_LEVEL_CRIT (2)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_CRIT)
#define WRSLOG_CRIT(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_BOLD_CYAN __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
        __WRSLOG_POSTTAG(__WRSLOG_LEVEL_CRIT,__WRSLOG_LEVEL_CRIT_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_CRIT(fmt, ...) do {} while(0)
#endif

// Error level __WRSLOG_LEVEL_ERR (3)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_ERR)
#define WRSLOG_ERR(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_BOLD_RED __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
        __WRSLOG_POSTTAG(__WRSLOG_LEVEL_ERR,__WRSLOG_LEVEL_ERR_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_ERR(fmt, ...) do {} while(0)
#endif

// Warning level __WRSLOG_LEVEL_WARNING (4)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_WARNING)
#define WRSLOG_WARNING(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_MAGENTA __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
        __WRSLOG_POSTTAG(__WRSLOG_LEVEL_WARNING,__WRSLOG_LEVEL_WARNING_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_WARNING(fmt, ...) do {} while(0)
#endif

// Notice level __WRSLOG_LEVEL_NOTICE (5)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_NOTICE)
#define WRSLOG_NOTICE(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_CYAN __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
        __WRSLOG_POSTTAG(__WRSLOG_LEVEL_NOTICE,__WRSLOG_LEVEL_NOTICE_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_NOTICE(fmt, ...) do {} while(0)
#endif

// Informational level __WRSLOG_LEVEL_INFO (6)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_INFO)
#define WRSLOG_INFO(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_GREEN __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
        __WRSLOG_POSTTAG(__WRSLOG_LEVEL_INFO,__WRSLOG_LEVEL_INFO_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_INFO(fmt, ...) do {} while(0)
#endif

// Debug level __WRSLOG_LEVEL_DEBUG (7)
#if (__WRSLOG_ENABLE) && (__WRSLOG_LEVEL >= __WRSLOG_LEVEL_DEBUG)
#define WRSLOG_DEBUG(fmt, ...) do { \
    __WRSLOG_PRETAG \
    fprintf(__WRSLOG_TARGET, __WRSLOG_COLOR_WHITE __WRSLOG_TAG fmt __WRSLOG_COLOR_RESET "\n", \
         __WRSLOG_POSTTAG(__WRSLOG_LEVEL_DEBUG,__WRSLOG_LEVEL_DEBUG_STR), ##__VA_ARGS__);\
    } while(0)
#else
#define WRSLOG_DEBUG(fmt, ...) do {} while(0)
#endif

#endif // __WRSLOG_H__
