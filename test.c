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

// Must include WRS logger header
#include "wrslog.h"

// Sample code to use logger functions.

int main(int argc, char **argv)
{
    WRSLOG_DEBUG( "debug %s", "testString" );
    WRSLOG_INFO( "info %u, %s", __WRSLOG_LEVEL_INFO, __WRSLOG_LEVEL_INFO_STR );
    WRSLOG_NOTICE( "notice 0x%x", 0xCAFEBEEF );
    WRSLOG_WARNING( "warning %d", -12345 );
    WRSLOG_ERR( "error" );
    WRSLOG_CRIT( "critical " );
    WRSLOG_ALERT( "alert" );
    WRSLOG_EMERG( "emergency" );

    return 0;
}