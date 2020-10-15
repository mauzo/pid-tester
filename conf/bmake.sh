MAKE=NONE
DEFAULT_JOBS=1

config_add_vars MAKE DEFAULT_JOBS

find_bmake () {
    local m

    step_start "Looking for BSD make"

    write_file "test.mk" <<TEST
.if empty(.PARSEDIR)
. error This is not a recent enough bmake
.endif

all: .PHONY
	true
TEST

    MAKE=NONE
    tries="make bmake"
    for m in $tries
    do
        if log_cmd "$m" -f "test.mk"
        then
            MAKE="$m"
            break
        fi
    done

    rm "test.mk"
    if [ "$MAKE" = "NONE" ]
    then
        step_fail "I cannot find a suitable bmake." \
            "I tried: $tries."
    fi

    step_finish "$MAKE"
}

_try_ncpu () {
    [ -n "$ncpu" ] && return

    ncpu="$(log_capture "$@")"
    [ $? -eq 0 ] || ncpu=""
}

find_default_jobs () {
    local ncpu

    step_start "Choosing a number of make jobs"

    _try_ncpu sysctl -n hw.ncpu     # FreeBSD
    _try_ncpu nproc                 # Linux

    [ -z "$ncpu" ] && ncpu=1

    DEFAULT_JOBS="$ncpu"

    step_finish "$ncpu"
}
