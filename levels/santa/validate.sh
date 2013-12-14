#!/usr/bin/env bash

cd "$(dirname "$0")"

if [ ! -r scratch/present ]; then
	echo "You didn't make a present!"
	exit 1
fi

if [ "$(wc -l < scratch/present | awk '{print $1}')" != 1 ]; then
	echo "Your present file doesn't have exactly one line!"
	exit 1
fi

if ! grep -vF "$(cat scratch/present)" < support/valid_presents.txt > /dev/null; then
	echo "You didn't make the right present :("
	exit 1
fi
