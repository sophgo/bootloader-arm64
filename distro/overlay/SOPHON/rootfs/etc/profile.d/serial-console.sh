case "$(tty)" in
/dev/ttyS*|/dev/ttyAMA*|/dev/ttyUSB*)
    if [ -n "${BASH_VERSION:-}" ]; then
        bind 'set horizontal-scroll-mode on' 2>/dev/null
        export TERM=xterm
        stty -F "$(tty)" sane -ixon -ixoff cols 80 rows 24 2>/dev/null
    fi
    ;;
esac
