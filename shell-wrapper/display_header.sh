#!/usr/bin/env bash

if [ $# -ne 1 ]; then
	echo "usage: $0 level" > /dev/stderr
	exit 1
fi

sed="$(command -v gsed || command -v sed)"

cd "$1"

len="$(awk '{if(length>x){x=length}}END{print x}' CHARACTER)"
len=$((len + 3))

declare -a character=(); while IFS= read -r line; do character+=("$line"); done < CHARACTER
declare -a challenge=(); while IFS= read -r line; do challenge+=("$line"); done < CHALLENGE

[ ${#character[@]} -gt ${#challenge[@]} ] \
&& lines=${#character[@]} \
|| lines=${#challenge[@]}

for ((i = 0; $i < $lines; i++)); do
	challenge_line="$(echo "${challenge[$i]}" \
	| $sed -e 's/{{{command:\([^}]*\)}}}/\x1b[31m\1\x1b[0m/g' \
	       -e 's/{{{file:\([^}]*\)}}}/\x1b[32m\1\x1b[0m/g')"
	[ $i -gt ${#character[@]} ] && len=0
	printf "%-${len}s%s\n" "${character[$i]}" "$challenge_line"
done

echo ""
echo -n "Allowed commands: "
tr '\n' ' ' < COMMANDS | sed 's/ *$//; s/ /, /g'

echo -n "Recommended man pages: "
$sed -E 's/^(\w*):(\w*)$/\2(\1)/' < MANPAGES | tr '\n' ' ' | sed 's/ *$//; s/ /, /g'
echo ""
