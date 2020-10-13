#ifndef _mauzo_pid_Window_h
#define _mauzo_pid_Window_h

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/scale.h>

#include "Graph.h"
#include "SampleSource.h"

namespace mauzo::pid {

class PIDTester : public Gtk::ApplicationWindow {
  public:
    Graph           graph;
    SampleSource    ssource;

    PIDTester();

  private:
    Gtk::Box        hbox;
    Gtk::Scale      pwm_slider;

    void    init_actions();
    void    init_window();

    void    on_pwm_changed();
};

}

#endif
