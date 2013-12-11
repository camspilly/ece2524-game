#!/bin/bash

sed="$(command -v gsed || command -v sed)"
readlink="$(command -v greadlink || command -v readlink)"

readlink="$(command -v greadlink || command -v readlink)"
if [ ! -x "$readlink" -o "$($readlink -e /)" != "/" ]; then
	echo "suitable readlink(1) not found" > /dev/stderr
	echo "please install GNU coreutils compatible readlink" > /dev/stderr
	exit 1
fi

export GAME_LEVEL_DIR="$($readlink -e "$GAME_LEVEL_DIR")"

if [ ! -d "$GAME_LEVEL_DIR" ]; then
	echo "GAME_LEVEL_DIR not set" > /dev/stderr
	exit 1
fi

export GAME_SHELL_WRAPPER_DIR="$($readlink -e "$(dirname "$0")")"
if [ ! -d "$GAME_SHELL_WRAPPER_DIR" ]; then
	echo "unable to establish canonical shell wrapper dir" > /dev/stderr
	exit 1
fi

"$GAME_SHELL_WRAPPER_DIR/display_header.sh" "$GAME_LEVEL_DIR"

rm -rf "$GAME_LEVEL_DIR/scratch"
cp -r "$GAME_LEVEL_DIR/clean" "$GAME_LEVEL_DIR/scratch"

while true; do
	bash --noprofile --rcfile "$GAME_SHELL_WRAPPER_DIR/init" -i
	result=$?
	if [ $result -eq 16 ]; then # requested help reset
		continue
	fi
	if [ $result -eq 0 ]; then # ^D exits with 0, challenge success is 32
		exit 33
	fi
	exit $result
done
