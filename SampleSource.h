#ifndef _SampleSource_h
#define _SampleSource_h

#include "Graph.h"

namespace mauzo::pid {

class SampleSource {
  public:
    SampleSource(Graph &gr);

  private:
    Graph           &graph;
    Graph::time     time;
    Graph::sample   current_value;

    static float    prng();

    bool    add_new_sample();
};

}

#endif
