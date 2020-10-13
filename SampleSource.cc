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
    time(0.0), graph(gr)
{
    Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &SampleSource::add_new_sample),
        20
    );
}

bool
SampleSource::add_new_sample() {
    Graph::sample   s;

    s[0]    = float(motor.get_pwm());
    s[1]    = motor.get_speed() / 100;
    std::cout << "Sample [" << s[0] << ", " << s[1] << "]\n";
    graph.add_sample(time, s);

    float   dt  = 0.1;
    time    += dt;

    motor.sim_step(dt);

    return true;
}

}
