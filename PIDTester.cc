/*
 * PIDTester.cc
 * The main window.
 */

#include <iostream>

#include <gtkmm.h>

#include "PIDTester.h"

namespace mauzo::pid {

using std::cerr;

PIDTester::PIDTester() :
    ssource(graph)
{
    init_window();
}

void
PIDTester::init_window() {
    set_title("PID tester");
    add(graph);
    show_all_children();
}

}
