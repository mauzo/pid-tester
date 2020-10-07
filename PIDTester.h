#ifndef _mauzo_pid_Window_h
#define _mauzo_pid_Window_h

#include <gtkmm/window.h>

#include "Graph.h"

namespace mauzo::pid {

class PIDTester : public Gtk::Window {
  public:
    Graph   graph;

    PIDTester();

  private:
    bool    add_new_sample();
    void    init_samples();
    void    init_window();
};

}

#endif
