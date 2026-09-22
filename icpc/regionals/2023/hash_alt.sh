#!/bin/sh
sed 's/#.*//' | tr -d ' \n\r' | md5sum | cut -c-6