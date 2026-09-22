#!/bin/sh
# Hashes stdin, ignoring comments, spaces and newlines (tabs are kept).
# Usage: ./hash.sh < Makefile        (or: cat Makefile | ./hash.sh)
sed 's/#.*//' | tr -d ' \n\r' | md5sum | cut -c-6