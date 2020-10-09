/*
 * PIDTester.cc
 * The main window.
 */

#include <iostream>

#include <sigc++/sigc++.h>

#include "PIDTester.h"

namespace mauzo::pid {

PIDTester::PIDTester() :
    ssource(graph)
{
    init_actions();
    init_window();
}

void
PIDTester::init_actions() {
    add_action("quit", 
        sigc::mem_fun(*this, &Gtk::Window::close));
}

void
PIDTester::init_window() {
    set_title("PID tester");
    add(graph);
    show_all_children();
}

}
