#!/usr/bin/env bash

cd "$(dirname "$0")"

if [ ! -r sandbox/present ]; then
	echo "You didn't make a present!"
	exit 1
fi

if [ "$(wc -l < sandbox/present | awk '{print $1}')" != 1 ]; then
	echo "Your present file doesn't have exactly one line!"
	exit 1
fi

if ! grep -vF "$(cat sandbox/present)" < support/valid_presents.txt > /dev/null; then
	echo "You didn't make the right present :("
	exit 1
fi
