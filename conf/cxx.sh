CXX=NONE
CXXFLAGS=

config_add_vars CXX CXXFLAGS

try_cxx () {
    local $1
    local out

    [ "$CXX" = "NONE" ] && step_fail "I don't have a C++ compiler"

    log_cmd ${CXX} ${CXXFLAGS} ${INCLUDES} -c -o test.o test.cc || return 1
    log_cmd ${CXX} -o test ${LDFLAGS} test.o ${LIBS} || return 1

    return 0
}

find_cxx () {
    local tries out

    step_start "Looking for a C++ compiler"

    write_file "test.cc" <<TEST
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "ok";
}
TEST

    CXX=NONE
    tries="c++ g++"
    for p in $tries
    do
        if try_cxx CXX="$p" && try_test_program "./test" "ok"
        then
            CXX="$p"
            break
        fi
    done

    rm -f test.cc test.o test
    if [ "$CXX" = "NONE" ]
    then
        step_fail "I cannot find a working C++ compiler." \
            "I tried: $tries."
    fi

    step_finish "$CXX"
}
