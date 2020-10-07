/*
 * PIDTester.cc
 * The main window.
 */

#include <random>

#include "PIDTester.h"

namespace mauzo::pid {

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

void
PIDTester::init_samples() {
    for (int i = 0; i < 100; i++) {
        graph.add_sample(float(i), prng());
    }
}

void
PIDTester::init_window() {
    set_title("PID tester");
    add(graph);
    show_all_children();
}

}
