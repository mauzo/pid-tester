# XXX I don't know what to do with these
INCLUDES=
LDFLAGS=
LIBS=

config_mk_vars="INCLUDES LDFLAGS LIBS"

# XXX This is not secure against bad input.
getvar () {
    local n="$1"
    eval "echo \${$n}"
}

config_start () {
    echo "Checking your system to find what we need..."

    exec 3>config.log

    log_msg "Working in $(pwd)"
}

config_add_vars () {
    config_mk_vars="$config_mk_vars $*"
}

config_finish () {
    local n v

    echo >config.mk

    for n in $config_mk_vars
    do
        v="$(getvar "$n")"
        echo "$n=$v" >>config.mk
    done

    echo "_config_mk_included=YES" >>config.mk
}

log_msg () {
    echo "$*" >&3
}

log_capture () {
    local out err

    log_msg "Running: $*"
    out="$("$@" 2>&1)"
    err=$?

    log_msg "Output: $out"
    echo "$out"
    return $err
}

log_cmd () {
    local out err

    out="$(log_capture "$@")"
    err=$?

    return $err
}

