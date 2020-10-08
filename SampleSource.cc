#include <iostream>
#include <random>

#include <glibmm/main.h>

#include "SampleSource.h"

namespace mauzo::pid {

static std::random_device                  _random_device;
static std::mt19937                        _prng_gen(_random_device());
static std::uniform_real_distribution<>    _prng_dist(-1.0, 1.0);

float
SampleSource::prng() {
    double d    = _prng_dist(_prng_gen);
    return float(d);
}

SampleSource::SampleSource(Graph &gr) :
    time(0.0), current_value({100.0, 200.0}), graph(gr)
{
    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &SampleSource::add_new_sample),
        20
    );
}

bool
SampleSource::add_new_sample() {
    //std::cerr << "Adding sample at " << time << "\n";
    graph.add_sample(time, current_value);

    time    += 0.1;

    for (int i = 0; i < graph.lines(); i++)
        current_value[i]    += prng();

    return true;
}

}
