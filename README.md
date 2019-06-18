# Traceroute
Simple ICMP traceroute

## About
Traceroute shows a path through the Internet from your computer to a specified address. This implementation uses ICMP packages and raw sockets.

### Output format
When there are replies for *all* of the sent requests, then reply addresses are displayed with average reply time.
```
<step>. <reply addresses> [<average time>]
```

When there are replies for *some* of the sent requests, then reply addresses are displayed with question marks indicating unknown reply time.
```
<step>. <reply addresses> ???
```

When there are no replies, then a single asterisk is displayed.
```
<step>. *
```

-----

## Dependencies

### Standard build & run
> *versions used by the author are in double parentheses and italic*

Build process:
+ Linux-based operating system *((Debian testing))*
+ C++ 14 compiler *((g++ 8.3.0))*
+ [CMake](https://cmake.org/) *((3.13.4))*
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
Traceroute can be run directly using the executable file in the `bin` root directory:
```sh
$ sudo /path-to-project-directory/bin/traceroute
```

Make sure you've got ``sudo`` priviledges so as to use raw sockets! Otherwise traceroute won't work.
