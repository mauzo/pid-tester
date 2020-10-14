#ifndef _mauzo_pid_Graph_h
#define _mauzo_pid_Graph_h

#include <array>
#include <vector>
#include <gtkmm/drawingarea.h>

namespace mauzo::pid {

#define LINES 3

class Graph : public Gtk::DrawingArea {
  public:
    typedef const Cairo::RefPtr<Cairo::Context>     &CC;
    typedef std::array<float, LINES>                sample;
    typedef std::array<float, 3>                    colour;
    typedef float                                   time;

    typedef std::vector<std::pair<float, sample>>   points_t;
    typedef std::array<colour, LINES>               colours_t;

    static colours_t    colours;

    points_t            points;

    Graph() { }

    void    add_sample(time t, sample s);
    size_t  lines() { return LINES; }

    bool    on_draw(CC ctx);
    void    draw_graphs(CC ctx, float xfac);
    float   set_scale(CC ctx);
};

}

#endif
