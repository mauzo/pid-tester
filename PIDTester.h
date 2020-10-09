#ifndef _mauzo_pid_Window_h
#define _mauzo_pid_Window_h

#include <gtkmm/applicationwindow.h>

#include "Graph.h"
#include "SampleSource.h"

namespace mauzo::pid {

class PIDTester : public Gtk::ApplicationWindow {
  public:
    Graph           graph;
    SampleSource    ssource;

    PIDTester();

  private:
    void    init_actions();
    void    init_window();
};

}

#endif
