#!/bin/sh

boy_presents=("toy cars" "baseball cards")
girl_presents=("barbies" "princess paraphernalia")
neutral_presents=("LEGOs" "books") # legos are the best :D

# not a standard locale, but who knows!? :p
if [[ "$LANG" = "en_SOUTHERN_US"* ]]; then
	boy_presents+=("toy soldiers" "actual guns")
fi

presents=()

if [ -n "$NO_GENDER_STERIOTYPES" ]; then
	presents+=("${boy_presents[@]}" "${girl_presents[@]}" "${neutral_presents[@]}")
else
	if [ "$1" = boy ]; then
		presents+=("${boy_presents[@]}")
	elif [ "$1" = girl ]; then
		presents+=("${girl_presents[@]}")
	elif [ "$1" = neutral ]; then
		presents+=("${neutral_presents[@]}")
	else
		echo "usage: $(basename "$0") <gender>" > /dev/stderr
		echo "  please select a gender (boy, girl, neutral)" > /dev/stderr
		echo "  or set \$NO_GENDER_STERIOTYPES in your environment" > /dev/stderr
		exit 1
	fi
fi

present=${presents[$RANDOM % ${#presents[*]}]}

echo "$present"
