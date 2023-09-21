# Traceroute

![Release](https://img.shields.io/github/v/release/ref-humbold/Traceroute?style=plastic)
![License](https://img.shields.io/github/license/ref-humbold/Traceroute?style=plastic)

Simple ICMP traceroute

## About
Traceroute shows a path through the Internet from your computer to a specified address. This implementation uses ICMP packages and raw sockets. Only paths up to specified limit of steps (32 by default) are recognized.

### Output format
When there are replies for *any* of the requests sent, then reply addresses are displayed with their reply times and average reply time at the end:
```
<step>. <reply address> -- <reply times> [/ <reply address> -- <reply times>...] (avg <average reply time>)
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
  *((APT package `g++`, 12.3.+))*
+ [CMake](https://cmake.org/) \
  *((APT package `cmake`, 3.26.+))*
+ [GNU Make](https://www.gnu.org/software/make) \
  *((APT package `make`, 4.3.+))*

### Automated formatting
+ [Clang-format](https://releases.llvm.org/14.0.0/tools/clang/docs/ClangFormat.html) \
  *((APT package `clang-format`, 14.+))*

-----

## How to build?
Traceroute can be built using **CMake** that generates **GNU Make** Makefile.

Follow these steps to build:
```sh
$ cd /path/to/project/directory/
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## How to run?
> **Make sure you've got `sudo` privileges, so as to use raw sockets! Otherwise traceroute app won't work.**

Traceroute can be run directly using the executable file in the `buildOut/bin` root directory:
```sh
$ sudo /path-to-project-directory/buildOut/bin/traceroute OPTIONS ARGUMENTS
```

### Synopsis
**traceroute** \[**-L** *limit*\] *ADDRESS*

### Description
Track the route of Internet packages on their path to IPv4 address *ADDRESS*. Only paths of length up to *limit* are being tracked.

### Options
**-L** *limit*
> Declare maximal path length to track, default is 32.
