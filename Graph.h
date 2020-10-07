#ifndef _mauzo_pid_Graph_h
#define _mauzo_pid_Graph_h

#include <vector>
#include <gtkmm/drawingarea.h>

namespace mauzo::pid {

class Graph : public Gtk::DrawingArea {
  public:
    typedef const Cairo::RefPtr<Cairo::Context>     &CC;
    typedef float                                   sample;
    typedef float                                   time;
    typedef std::vector<std::pair<float, sample>>   points_t;

    points_t    points;

    Graph() { }

    void    add_sample(time t, sample s);

    bool    on_draw(CC ctx);
    void    set_scale(CC ctx);
};

}

#endif
