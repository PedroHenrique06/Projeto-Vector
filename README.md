# Introduction

In this repo you'll find the support code for the development of the Project `sc::vector`.
The description of the assignment may be found [**here**](docs/projeto_TAD_vector.pdf).

# Organization

The folders and files of this project are the following:

- `source/tests/include/tm`: This is the library that provides supports for the unit tests. Do not change or delete this folder.
- `source/tests`: This folder has the file `main.cpp` and `iterator_tests.cpp` that contains all the tests. You might want to change this file and comment out some of the tests while you have not finished all the `sc::vector`'s methods.
- `source/include`: This is the folder in which you should add the `vector.h` file with your solution (i.e. the implementation of the class `sc::vector`).
- `source/CMakeLists.txt: The cmake script file.
- `README.md`: This file.
- `docs`: This folder has a [pdf file](docs/projeto_TAD_vector.pdf) describing the vector project.

# Compiling

This project may be compiled with [CMake](https://cmake.org). CMake is an open-source, cross-platform family of tools designed to build, test and package software. Basically, cmake reads a script (`CMakeLists.txt`) with meta-information on the project and **creates a Makefile automatically**, tailored to your system configuration.
After that, you may run the `make` command, as usual.
Alternatively, the same script might be used to create Xcode projects, Ninja, or Microsoft Visual Studio projects, for instance.

CMake supports **out-of-source** build. This means the _source code_ is stored in **one** folder and the _generated executable files_ should be stored in **another** folder: project should never mix-up the source tree with the build tree.

In particular, this project creates a single **target** (executable), called `run_tests`.

But don't worry, they are already set up in the `CMakeLists.txt` script.

To compile this project with [cmake](https://cmake.org) follow these steps (from the root folder):

1. `cmake -S source -B build`: asks cmake to create the build directory and generate the Unix Makefile based on the script found in `source/CMakeLists.txt`, on the current level.
2. `cmake --build build`: triggers the compiling process that creates both targets (executable).D inside `build`.

The executable is created inside the `build` directory.

For further details, please refer to the [cmake documentation website](https://cmake.org/cmake/help/v3.14/manual/cmake.1.html).

We have in this project two batches of tests: 31 unit tests for the `sc::vector` class, and 16 unit tests for the `sc::vector::iterator` class. You should try to get passed all these tests.

All tests begin **deactivated** by default, via a [_conditional preprocessing block_](https://en.cppreference.com/w/cpp/preprocessor/conditional) marked with a `#ifdef SOMETHING` ... `#endif`.
To activate a test you need to turn on the test by changing the test indicator from `NO` to `YES` inside the files `vector_tests.h` (to control the vector tests), and `iterator_test.cpp` (to control the iterator tests).
For example, to active the default constructor test the code will become this:

```c++
// Test default ctro's size and capacity initial values.
#define DEFAULT_CTRO YES  // Change it to YES to activate the test.
```

## Compiling without cmake

If you wish to compile this project without the cmake, create the `build` folder manually (`mkdir build`), then try to run the command below from the source folder:

```
g++ -Wall -std=c++11 -I source/include -I source/tests/include/tm/ source/tests/main.cpp source/tests/include/tm/test_manager.cpp source/tests/iterator_tests.cpp -o build/run_tests
```

# Running

From the project's root folder, run as usual (assuming `$` is the terminal prompt):

```
$ ./build/run_tests
```

# Authorship

Program developed by Selan (<selan.santos@ufrn.br>), 2022.2

&copy; DIMAp/UFRN 2016-2022.

# Implementation authors

+ Pedro Henrique Sales dos Santos
+ Igor Rauan Soares da Silva
