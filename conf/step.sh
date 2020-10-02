step_current="NONE"

step_start () {
    log_msg "$1."
    echo -n "$1..."
    step_current="$1"
}

step_finish () {
    log_msg "$step_current: $1"
    echo " $1"
    step_current="NONE"
}

step_fail () {
    local l

    log_msg "$step_current: FAILED"
    for l in "$@"
    do
        log_msg "$l"
    done

    echo
    for l in "$@"
    do
        echo "$l" >&2
        echo "See $(pwd)/config.log for more details." >&2
    done

    exit 1
}
