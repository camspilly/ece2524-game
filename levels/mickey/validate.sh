#!/usr/bin/env bash

cd "$(dirname "$0")"

if [ ! -d scratch/.git ]; then
	echo "You didn't initialize the repo!"
	exit 1
fi
