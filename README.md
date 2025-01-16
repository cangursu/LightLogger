# Light Logger (LLog)

A lightweight, flexible logging framework for C++ applications with asynchronous logging capabilities and file support.

## Features

- Asynchronous logging support
- File output support
- File compression support
- Lightweight and minimal overhead
- Flexible logging interface
- CMake-based build system
- Comprehensive test suite using Google Test
- Cross-platform support (Linux, Windows)

## Prerequisites

- C++17 compatible compiler
- CMake (minimum version 3.12)
- zlib library
- Google Test (for running tests)
- Git (for version control)

## Project Structure

```
.
├── lib/            # Core logging library
├── client/         # Example client implementation
├── test/           # Test suite
└── bin/            # Compiled binaries output
```

## Building the Project

1. Clone the repository:
   ```bash
   git clone [repository-url]
   cd llog
   ```

2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

3. Generate build files:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   cmake --build .
   ```

The compiled binaries will be available in the `bin/` directory.

## Running Tests

After building the project, you can run the test suite:

```bash
./bin/llog_test
```

## Usage

1. Add the LLog include path and link against the LLOG library in your CMake project:
   ```cmake
   target_link_libraries(your_project PRIVATE llog)
   target_include_directories(your_project PRIVATE "<llog_path>/lib/inc" )
   ```

2. Include the logger header in your source files:
   ```cpp
   #include "LLog.h"
   ```

3. A simple excample :
    ```cpp
    #include "LLog.h"
    void MainLog()
    {
        LOG_TRACE << "Loging is beautiful";
    }
    ```


For more usage and CMake samples, please refer to the ```<LLog Path>/client``` project.


## Development

The project uses several development tools and standards:

- C++17 standard
- CMake build system
- Google Test framework for testing
- Continuous Integration support
- Code coverage analysis (gcov support)

### Build Configuration

- Debug build: Includes debug symbols and no optimization
- Release build: Optimized for performance (-O3)

### IDE Support

The project includes configuration files for:
- Visual Studio Code
- Eclipse
- NetBeans

## Version

Current version: 2.0.0

## Authors

cangursu@yahoo.com

## Acknowledgments

- zlib library
- Google Test framework
