case "$(tty)" in
/dev/ttyS*|/dev/ttyAMA*|/dev/ttyUSB*)
    if [ -n "${BASH_VERSION:-}" ]; then
        bind 'set horizontal-scroll-mode on' 2>/dev/null
    fi
    ;;
esac
