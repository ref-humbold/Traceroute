# Traceroute

[![GitHub Actions](https://github.com/ref-humbold/Traceroute/actions/workflows/build-and-test.yml/badge.svg)](https://github.com/ref-humbold/Traceroute/actions/workflows/build-and-test.yml)

[![Release](https://img.shields.io/github/v/release/ref-humbold/Traceroute?style=plastic)](https://github.com/ref-humbold/Traceroute/releases)
[![License](https://img.shields.io/github/license/ref-humbold/Traceroute?style=plastic)](./LICENSE)

Simple ICMP traceroute

-----

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

## System requirements

> versions used by the author are in italics

+ Linux-based operating system \
  *Debian testing*
+ C++ compiler \
  *APT package `g++`, 15.2.+*
+ CMake \
  *APT package `cmake`, 4.2.+*
+ GNU Make \
  *APT package `make`, 4.4.+*

## Automated formatting
+ Clang-format \
  *APT package `clang-format`, 21.1.+*

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

> **Make sure you've got `sudo` privileges to use raw sockets! Otherwise, traceroute app won't work.**

Traceroute can be run directly using the executable file in the `buildOut/bin` root directory:

```sh
$ sudo /path-to-project-directory/buildOut/bin/traceroute OPTIONS ARGUMENTS
```

-----

## Synopsis

**traceroute** \[**-L** *limit*\] *ADDRESS*

### Description

Track the route of Internet packages on their path to IPv4 *ADDRESS*. Only paths of length up to *limit* are being tracked.

### Options

**-L** *limit* \
&emsp;&emsp; Declare maximal path length to track, default is 32.
