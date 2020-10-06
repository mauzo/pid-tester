#ifndef _mauzo_pid_Graph_h
#define _mauzo_pid_Graph_h

#include <vector>
#include <gtkmm/drawingarea.h>

namespace mauzo::pid {

class Graph : public Gtk::DrawingArea {
  public:
    typedef const Cairo::RefPtr<Cairo::Context> &CC;
    typedef std::vector<std::pair<int, int>>    Points;

    Points  points;

    Graph() : 
        points{ {0, 120}, {1, 100} }
    { }

    bool    on_draw(CC ctx);
    void    set_scale(CC ctx);
};

inline bool 
Graph::on_draw (CC ctx) {
    set_scale(ctx);

    ctx->set_source_rgb(0.8, 0.0, 0.0);

    ctx->move_to(points[0].first, points[0].second);
    for (auto &p: points) {
        ctx->line_to(p.first, p.second);
    }
    ctx->stroke();

    return true;
}

inline void
Graph::set_scale(CC ctx) {
    auto    alloc   = get_allocation();
    int     w       = alloc.get_width();
    int     h       = alloc.get_height();

    ctx->scale(float(w)/2.0f, float(h)/255.0f);
}

}

#endif
