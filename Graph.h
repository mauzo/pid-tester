#ifndef _mauzo_pid_Graph_h
#define _mauzo_pid_Graph_h

#include <array>
#include <vector>
#include <gtkmm/drawingarea.h>

namespace mauzo::pid {

class Graph : public Gtk::DrawingArea {
  public:
    typedef const Cairo::RefPtr<Cairo::Context>     &CC;
    typedef std::array<float, 2>                    sample;
    typedef float                                   time;
    typedef std::vector<std::pair<float, sample>>   points_t;

    points_t    points;

    Graph() { }

    void    add_sample(time t, sample s);
    size_t  lines() { return 2; }

    bool    on_draw(CC ctx);
    float   set_scale(CC ctx);
};

}

#endif
