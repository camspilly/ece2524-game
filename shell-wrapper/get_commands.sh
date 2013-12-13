#!/usr/bin/env bash

# There are plenty of ways around this, but if somebody is determined to cheat,
# then they're going to do so, and this won't stop them no matter how accurate
# it is.

if [ $# -ne 1 ]; then
	echo "usage: $(basename "$0") \"command --line\"" > /dev/stderr
	exit 1
fi

sed="$(command -v gsed || command -v sed)"

cmd="$1"

real_path="$PATH"
tmp_path="$(mktemp -dt XXXXXX)"

used=()

worked=false
while ! $worked; do
	worked=true

	# Add missing binaries to our empty path until we aren't missing any
	# more commands, keeping track of what we had to add.

	export PATH="$tmp_path"
	missing="$(eval "$cmd" 2>&1)"
	export PATH="$real_path"

	for bin in $(echo "$missing" \
	| grep -F "command not found" \
	| $sed -E 's/^.*: (\w+): command not found$/\1/g'); do
		used+=("$bin")
		ln -sf /usr/bin/true "$tmp_path/$bin"
		worked=false
	done
done

rm -r "$tmp_path"

printf '%s\n' "${used[@]}"
