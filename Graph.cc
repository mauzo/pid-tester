#include "Graph.h"

namespace mauzo::pid {

void
Graph::add_sample(time t, sample s) {
    points.push_back({t, s});
}

bool 
Graph::on_draw (CC ctx) {
    set_scale(ctx);

    ctx->set_source_rgb(0.8, 0.0, 0.0);
    ctx->set_line_width(0.1);

    ctx->move_to(points[0].first, points[0].second);
    for (auto &p: points) {
        ctx->line_to(p.first, p.second);
    }
    ctx->stroke();

    return true;
}

void
Graph::set_scale(CC ctx) {
    auto    alloc   = get_allocation();
    int     w       = alloc.get_width();
    int     h       = alloc.get_height();

    ctx->scale(float(w)/100.0f, float(h)/255.0f);
}

}
