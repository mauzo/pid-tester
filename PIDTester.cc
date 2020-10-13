/*
 * PIDTester.cc
 * The main window.
 */

#include <iostream>

#include <sigc++/sigc++.h>

#include "PIDTester.h"

namespace mauzo::pid {

PIDTester::PIDTester() :
    ssource(graph),
    pwm_slider(Gtk::ORIENTATION_VERTICAL)
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

    pwm_slider.set_inverted();
    pwm_slider.set_range(0.0, 255.0);
    pwm_slider.signal_value_changed().connect(
        sigc::mem_fun(*this, &PIDTester::on_pwm_changed));

    hbox.pack_start(pwm_slider, Gtk::PACK_SHRINK,           5);
    hbox.pack_start(graph,      Gtk::PACK_EXPAND_WIDGET,    5);

    add(hbox);
    show_all_children();
}

void
PIDTester::on_pwm_changed() {
    int pwm     = pwm_slider.get_value();
    
    std::cerr << "PWM changed: " << pwm << "\n";
    ssource.set_pwm(pwm);
}
}
