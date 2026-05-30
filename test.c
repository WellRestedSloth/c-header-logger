/////////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2025-2026 Walrus Ted Sloth
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

// Must include WRS logger header
#include "wrslog.h"

#include "test2.h"

#if defined(__WRSLOG_PTHREAD)

#include <pthread.h>

// Sample code to use logger functions.
void *thread_func(void *arg)
{
    long thr = (long)arg;

    const int NUM_LOOPS = 20;

    for (int i=0; i<NUM_LOOPS; i++)
    {
        WRSLOG_DEBUG("thread = %ld, loop %d", thr, i);
    }
    return NULL;
}

int main(void)
{
    const int THREAD_COUNT = 20;
    pthread_t tid[THREAD_COUNT];

    WRSLOG_INFO("Begin");

    for (long i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&tid[i], NULL, thread_func, (void*)i);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        if (0 == pthread_join(tid[i], NULL))
        {
            WRSLOG_INFO("joined thread %d", i);
        }
    }

    WRSLOG_INFO("Done!");

    return 0;
}

#else

int main(void)
{
    int i = 100, j = 0xcafebeef;
    float f = 3.14159;
    char szTest[10];
    snprintf( szTest, sizeof(szTest), "%s", "mystr" );

    WRSLOG_DEBUG( "no args" );
    WRSLOG_INFO( "1 arg: %d", i );
    WRSLOG_NOTICE( "2 args: %s, 0x%08X", szTest, j );
    WRSLOG_WARNING( "3 args: %f, %s, %d", f, szTest, i );

    // Update vars to avoid release build warnings about unused variables
    i += 400;
    j -= 0xcafe0000;
    f *= f;
    snprintf( szTest, sizeof(szTest), "%s", "teststr2" );

    WRSLOG_ERR( "no args" );
    WRSLOG_CRIT( "1 arg: %d", i );
    WRSLOG_ALERT( "2 args: %s, 0x%08X", szTest, j );
    WRSLOG_EMERG( "3 args: %f, %s, %d", f, szTest, i );

    another_func(55, 66);

    return 0;
}

#endif
