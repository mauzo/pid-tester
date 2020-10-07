/*
 * PIDTester.cc
 * The main window.
 */

#include <iostream>
#include <random>

#include <gtkmm.h>

#include "PIDTester.h"

namespace mauzo::pid {

using std::cerr;

static std::random_device                  _random_device;
static std::mt19937                        _prng_gen(_random_device());
static std::uniform_real_distribution<>    _prng_dist(25.0, 200.0);

static float
prng() {
    double d    = _prng_dist(_prng_gen);
    return float(d);
}

PIDTester::PIDTester() {
    init_samples();
    init_window();
}

bool
PIDTester::add_new_sample() {
    static int i = 0;
    std::cerr << "Adding sample #" << i << "\n";
    graph.add_sample(float(i), prng());
    i++;
    return true;
}

void
PIDTester::init_samples() {
    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &PIDTester::add_new_sample),
        500
    );
}

void
PIDTester::init_window() {
    set_title("PID tester");
    add(graph);
    show_all_children();
}

}
