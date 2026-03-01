#! /bin/sh

set -e

sudo -i -- sh -c \
"cd /usr/src/googletest/googletest && \
mkdir build && \
cd build && \
cmake .. && \
make && \
find . -name \"*.a\" -exec cp {} /usr/local/lib/ \;"
