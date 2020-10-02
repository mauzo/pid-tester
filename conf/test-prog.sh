write_file () {
    local file="$1"

    log_msg "Creating file '$file':"
    cat >"$file"
    cat "$file" >&3
    log_msg "----------------------"
}

try_test_program () {
    local cmd="$1"
    local want="$2"
    local out err

    out="$(log_capture $cmd)"
    err=$?

    if [ "$out" != "$want" ] || [ "$err" -ne 0 ]
    then
        return 1
    fi

    return 0
}
