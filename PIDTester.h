#ifndef _mauzo_pid_Window_h
#define _mauzo_pid_Window_h

#include <gtkmm/window.h>

#include "Graph.h"

namespace mauzo::pid {

class PIDTester : public Gtk::Window {
  public:
    Graph   graph;

    PIDTester() {
        set_title("PID tester");
        add(graph);
        show_all_children();
    }
};

}

#endif
