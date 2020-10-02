PKGCONF=NONE

find_pkgconf () {
    local out

    step_start "Looking for pkgconf"

    PKGCONF=NONE
    tries="pkgconf pkg-config"
    for p in $tries
    do
        if log_cmd $p --version
        then
            PKGCONF="$p"
            break
        fi
    done

    if [ "$PKGCONF" = "NONE" ]
    then
        step_fail "I cannot find a working pkgconf." \
            "I tried: $tries."
    fi

    step_finish "$PKGCONF"
}

pkgconf_modver () {
    local pkg="$1"
    local ver

    [ "$PKGCONF" = "NONE" ] && step_fail "I don't have pkg-config"

    ver="$(log_capture $PKGCONF --modversion "$pkg")" \
        || step_fail "I cannot find $pkg"
    echo "$ver"
}

pkgconf_configure () {
    local pkg="$1"

    [ "$PKGCONF" = "NONE" ] && step_fail "I don't have pkg-config"

    out="$(log_capture $PKGCONF --cflags "$pkg")" \
        || step_fail "I cannot find $pkg"
    INCLUDES="$INCLUDES $out"

    out="$(log_capture $PKGCONF --libs "$pkg")" \
        || step_fail "I cannot find $pkg"
    LIBS="$LIBS $out"
}
