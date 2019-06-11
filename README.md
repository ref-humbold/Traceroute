# Traceroute
Simple ICMP traceroute

## About
Traceroute shows a path through the Internet from your computer to a specified address. This implementation uses ICMP packages and raw sockets.

-----

## Dependencies

### Standard build & run
Build process:
+ C++ 14
+ [CMake](https://cmake.org/)
+ [GNU Make](https://www.gnu.org/software/make)

-----

## How to build?
Traceroute can be built using **CMake** that generates **GNU Make** Makefile.

Follow these steps to build:
```sh
$ cd /path-to-directory/
$ mkdir build && cd build
$ cmake ..
$ make
```

## How to run?
Traceroute can be run directly using the executable file in the `bin` root directory:
```sh
$ sudo /path-to-directory/bin/traceroute
```

Make sure you've got ``sudo`` priviledges so as to use raw sockets! Otherwise traceroute won't work.
