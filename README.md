# c-header-logger

WellRestedSloth's (WRS) logger:
A lightweight and customizable header file logger written in C.

![github_logger](https://github.com/user-attachments/assets/428c443a-6378-4903-af49-8cc21f5cbfcb)


## Features

- Date/timestamp (with millisecond granularity) format
- Supports 8 different logging levels (based on Linux kernel log levels)
- Supports debug/non-debug build profiles
- Easily customizable:
  - Select log output format (supports ISO 8601 time format)
	- Select log output destination (stdout or stderr)
	- Change ANSI terminal color for each log level
- Lightweight:
  - Logger is implemented using the preprocessor in a single header file
  - No additional buffers allocated on the stack
	- For non-debug builds, logging macros are compiled out
- Can be used in C and C++ programs
- MIT license, so you can freely modify the source code to your liking!

All development was done using Github Codespaces, using VS Code editor, compiled with gcc 9.4.


## Known Limitations

- No logging to file (future work)
- No multithreaded support (future work)


## Using c-header-logger

1. Simply include the `wrslog.h` header file:

   ```c
   #include "wrslog.h"
   ```

2. In your source code, add the logging macros.  Examples:

   No arguments:

   ```c
   WRSLOG_DEBUG( "This is a debug log!" );
   ```

   Several arguments:

   ```c
   int a = 42;
   WRSLOG_INFO( "This is an info log, count = %d, %d, %d", a, a+1, a+2 );
   ```

3. Enable logging in a debug build, or disable logging in a non-debug build.

   To enable logging, set either variable `DEBUG` or `_DEBUG` to `1`:

   1. In `wrslog.h` header file:

      ```c
      #define _DEBUG 1
      ```

   2. Or, add the variable during compilation:

      ```shell
      gcc -o myprog main.c -D_DEBUG=1
      ```

   If `DEBUG` or `_DEBUG` is not set to `1`, then the logging macros are "compiled out".


## Documentation

List of logging macros:

```c
WRSLOG_DEBUG( "7-Debug level" );
WRSLOG_INFO( "6-Information level" );
WRSLOG_NOTICE( "5-Notice level" );
WRSLOG_WARNING( "4-Warning level" );
WRSLOG_ERR( "3-Error level" );
WRSLOG_CRIT( "2-Critical level" );
WRSLOG_ALERT( "1-Alert level" );
WRSLOG_EMERG( "0-Emergency level" );
```


## Customization

For further customization options, please refer to `wrslog.h`.  Please look between these two sections:

```c
///////////////////////////////////////////////////////////
// Customize the values in this section below. (Start)
///////////////////////////////////////////////////////////
```

and

```c
///////////////////////////////////////////////////////////
// Customize the values in this section above. (End)
///////////////////////////////////////////////////////////
```

Below is a description of the options that can be customized.

- Enable or disable logging at compile time

  ```c
  #define _DEBUG 1
  ```

  - Set `_DEBUG` to 1 to enable logging.
  - Set `_DEBUG` to 0 to disable logging.  All debug logs are compiled out.
  - The `_DEBUG` flag can also be set during compilation.  For example, this method can be used in a Makefile to enable logging for debug builds, and disable logging for release builds.  Example:

    ```shell
    # Debug build
    gcc -o myprog main.c -D_DEBUG=1

    # Release build
    gcc -o myprog main.c -D_DEBUG=0
    # or remove the _DEBUG flag
    gcc -o myprog main.c
    ```

- Set the target for the log output

  ```c
  #define __WRSLOG_TARGET stderr
  ```

  The log output target can be set using the `__WRSLOG_TARGET` variable.  Common choices are `stderr` or `stdout`.

- Set the module name

  ```c
  #define __WRSLOG_MODULE “APP”
  ```

  The module name is a user-defined string that can appear in the log using the `__WRSLOG_MODULE` macro.  This is useful if your system has many applications using the same `wrslog.h` file to distinguish which module the log originated from.

- Set the logging level

  ```c
  #define __WRSLOG_LEVEL __WRSLOG_LEVEL_DEBUG
  ```

  The `__WRSLOG_LEVEL` setting is used to include logs that are at the `__WRSLOG_LEVEL` or higher priority (i.e. exclude logs that are at a lower priority).  For the above setting, since `__WRSLOG_LEVEL_DEBUG` is the lowest priority log level, all log levels will be included.

- Enable or disable log colors in the terminal

  ```c
  #define __WRSLOG_COLOR 1
  ```

  - Set `__WRSLOG_COLOR` to 1 to enable ANSI colors in the terminal
  - Set `__WRSLOG_COLOR` to 0 to disable ANSI colors in the terminal
  - Please refer to the definitions of the actual WRSLOG macros to modify which color each log level will display.

- Set the logging format

  ```c
  #define __WRSLOG_ISO8601 0
  ```

  - Set `__WRSLOG_ISO8601` to 1 to set the log format to ISO8601 time format
  - Set `__WRSLOG_ISO8601` to 0 to set a custom log format
  - The ISO8601 time format is as follows:

    ```
    [YYYY-MM-DDThh:mm:ss.msec+-<time offset from GMT]
    ```

  - A custom log format can be set using the `__WRSLOG_PRETAG`, `__WRSLOG_TAG`, and `__WRSLOG_POSTTAG` macros.  These will be described in the next section.  Currently, the custom log format is set as follows:

    ```
    [hh:mm:ss.msec][<log level>]
    ```

  - The log is output using `fprintf`, and the basic structure is as follows:

    ```c
    __WRSLOG_PRETAG
    fprintf( __WRSLOG_TARGET, __WRSLOG_TAG fmt, __WRSLOG_POSTTAG );
    ```

  - The macro `__WRSLOG_PRETAG` is used to set up parameters that are passed into the `fprintf` function.  For example: the msec calculation using the `localtime_r` function.
  - The macro `__WRSLOG_TAG` is the format string forming the first part of the log output.  This usually contains the timestamp, and also the log level.
  - The macro `__WRSLOG_POSTTAG` is used to specify the parameters that were used in the format string.

Again, please look at the `wrslog.h` header file to see how all of this was implemented.


## Motivation and Stuff

I wrote this WellRestedSloth logger to be used in other future projects.  I designed it to be lightweight (no additional allocations on the stack), easily used (simply include a header file), easily compiled out for non-debug builds, and easily customizable.  It is more of a learning project that turned into an actual useful project.  I hope you find this logger useful in your projects!

Now I must go back to sleep.  Good night. Zzzzzzz.....
