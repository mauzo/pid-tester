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
}

void
SampleSource::start() {
    timer = Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &SampleSource::add_new_sample),
        20
    );
}

void
SampleSource::pause() {
    if (timer)
        timer.disconnect();
}

void
SampleSource::toggle_pause() {
    if (timer) {
        std::cout << "Stopping timer\n";
        pause();
    }
    else {
        std::cout << "Timer stopped, restarting\n";
        start();
    }
    std::cout << "Timer: " << (bool)timer << "\n";
}

bool
SampleSource::add_new_sample() {
    Graph::sample   s;

    s[0]    = float(motor.get_pwm());
    s[1]    = motor.get_speed() / 200;
    s[2]    = motor.get_force() * 50;
    std::cout << "Sample [";
    for (auto &i: s) {
        std::cout << i << ", ";
    }
    std::cout << "]\n";
    graph.add_sample(time, s);

    float   dt  = 0.1;
    time    += dt;

    motor.sim_step(dt);

    return true;
}

}
