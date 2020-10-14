#ifndef _SampleSource_h
#define _SampleSource_h

#include <sigc++/sigc++.h>

#include "Graph.h"
#include "MotorSimulator.h"

namespace mauzo::pid {

class SampleSource {
  public:
    SampleSource(Graph &gr);

    void    start();
    void    pause();
    void    toggle_pause();

    void    set_pwm(int pwm)    { motor.set_pwm(pwm); }

  private:
    sigc::connection    timer;
    Graph               &graph;
    MotorSimulator      motor;
    Graph::time         time;

    static float    prng();

    bool    add_new_sample();
};

}

#endif
