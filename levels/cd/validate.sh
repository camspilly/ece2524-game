#!/usr/bin/env bash

if [[ "$(basename "$PWD")" != "a_directory" ]]; then
	echo "You didn't cd into a_directory"
	exit 1
fi
