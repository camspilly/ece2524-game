# Invocation

start by running `run.sh`


# Environment

* GAME_LEVEL_DIR - shall be set to a level directory (for example levels/santa)


# Exit codes

* 32 - user succeeded
* 33 - user gave up
* 16 - restart without header (only used internally)
anything else should be regarded as an internal error
(quite likely because of missing dependencies)


# Level Structure

* `<level_name>` - The name of the level
  * `clean/` - The virgin copy of the working directory the user gets dropped in for the level (duplicated to `scratch` for the user to actually work in)
  * `support/` - An optional directory containing whatever the challenge might need (for example support scripts that you don't want visible in the working directory, or a file of expected output to be used in validation)
  * `CHALLENGE` - A description of what you're asking the user to do
  * `CHARACTER` - ASCII art for character
  * `COMMANDS` - List of allowed commands for this level
  * `ICON` - The icon of this character as to be displayed in the map
  * `MANPAGES` - List of recommended man pages the user might want to read for this level
  * `SOLUTION` - One possible way to solve the challenge (not displayed to the user)
  * `validate.sh` - The script called after each command the user enters. Exits with 0 if they passed, non-0 if they failed.

# Notes

This is embarrassingly hacky, and horribly unportable.
