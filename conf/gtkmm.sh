find_gtkmm () {
    local out ver
    local pkg="gtkmm-3.0"

    step_start "Looking for gtkmm 3"
    ver="$(pkgconf_modver "$pkg")"
    pkgconf_configure "$pkg"

    write_file "test.cc" <<TEST
#include <gtkmm.h>
#include <iostream>

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create("");
    std::cout << "ok";
}
TEST

    if ! try_cxx
    then
        step_fail "I cannot compile a gtkmm program."
    fi
    rm -f test.cc test.o test

    step_finish "$ver"
}
