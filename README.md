# Traceroute
![Release](https://img.shields.io/github/v/release/ref-humbold/Traceroute?style=plastic)
![License](https://img.shields.io/github/license/ref-humbold/Traceroute?style=plastic)

Simple ICMP traceroute

## About
Traceroute shows a path through the Internet from your computer to a specified address. This implementation uses ICMP packages and raw sockets.

### Output format
When there are replies for *any* of the requests sent, then reply addresses are displayed with average reply time and count of responses:
```
<step>. <reply addresses> -- <average time> (<responses count>)
```

When there are no replies, then a single asterisk character is displayed:
```
<step>. *
```

-----

## Dependencies

### Standard build & run
> *versions last used by the author are in double parentheses and italic*

General:
+ Linux-based operating system \
  *((Debian testing))*
+ C++ compiler \
  *((APT package `g++`, 10.2.+))*
+ [CMake](https://cmake.org/) \
  *((APT package `cmake`, 3.18.+))*
+ [GNU Make](https://www.gnu.org/software/make) \
  *((APT package `make`, 4.3.+))*

### Automated formatting
+ [Clang-format](https://releases.llvm.org/11.0.0/tools/clang/docs/ClangFormat.html) \
  *((APT package `clang-format`, 11.+))*

-----

## How to build?
Traceroute can be built using **CMake** that generates **GNU Make** Makefile.

Follow these steps to build:
```sh
$ cd /path-to-project-directory/
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## How to run?
> **Make sure you've got `sudo` privileges, so as to use raw sockets! Otherwise the traceroute won't work.**

Traceroute can be run directly using the executable file in the `bin` root directory:
```sh
$ sudo /path-to-project-directory/bin/traceroute
```
