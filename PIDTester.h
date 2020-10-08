#ifndef _mauzo_pid_Window_h
#define _mauzo_pid_Window_h

#include <gtkmm/window.h>

#include "Graph.h"
#include "SampleSource.h"

namespace mauzo::pid {

class PIDTester : public Gtk::Window {
  public:
    Graph           graph;
    SampleSource    ssource;

    PIDTester();

  private:
    void    init_window();
};

}

#endif
