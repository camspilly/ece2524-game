#!/bin/sh

shuf="$(command -v gshuf || command -v shuf)"

grep -vE '^#' cookie_types.txt | $shuf | head -n 1
