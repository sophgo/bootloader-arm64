# |login info|cur user info|pid info|pwd info|cmd info|cmd ret info|

export PROMPT_COMMAND='RETRN_VAL=$?;logger -p local0.debug "|login: $(who)| |user: $(whoami)| |pid: $$| |pwd: $(pwd)| |cmd: $(history 1 | sed "s/^[ ]*[0-9]\+[ ]*//")| |ret: $RETRN_VAL|"'
readonly PROMPT_COMMAND
