#include <iostream>
#include <gtkmm/application.h>

#include "PIDTester.h"

int
main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "");

    mauzo::pid::PIDTester window;
    window.set_default_size(800, 400);

    app->set_accel_for_action("win.quit",   "q");
    app->set_accel_for_action("win.pause",  "space");

    return app->run(window);
}
