# Traceroute
Simple ICMP traceroute

## About
Traceroute shows a path through the Internet from your computer to a specified address. This implementation uses ICMP packages and raw sockets.

### Output format
When there are replies for *any* of the requests sent, then reply addresses are displayed with 
average reply time with count of responses.
```
<step>. <reply addresses> -- <average time> (<responses count>)
```

When there are no replies, then a single asterisk character is displayed.
```
<step>. *
```

-----

## Dependencies

### Standard build & run
> *versions last used by the author are in double parentheses and italic*

Build process:
+ Linux-based operating system *((Debian testing))*
+ [CMake](https://cmake.org/) *((3.13.4))*
+ C++ 14 compiler *((g++ 9.2.1))*
+ [GNU Make](https://www.gnu.org/software/make) *((4.2.1))*

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
**Make sure you've got ``sudo`` priviledges so as to use raw sockets! Otherwise traceroute won't work.**

Traceroute can be run directly using the executable file in the `bin` root directory:
```sh
$ sudo /path-to-project-directory/bin/traceroute
```
