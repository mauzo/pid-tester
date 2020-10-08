/*
 * Graph.cc
 * A DrawingArea that draws the graphs.
 */

#include <algorithm>

#include "Graph.h"

namespace mauzo::pid {

void
Graph::add_sample(time t, sample s) {
    points.push_back({t, s});
    if (is_visible())
        queue_draw();
}

bool
Graph::on_draw (CC ctx) {
    if (points.empty())
        return true;

    float   xfac    = set_scale(ctx);
    ctx->set_line_width(1.0);
    ctx->set_source_rgb(0.8, 0.0, 0.0);

    for (int i = 0; i < lines(); i++) {
        ctx->move_to(points[0].first, points[0].second[i]);
        for (auto &p: points) {
            ctx->line_to(p.first * xfac, p.second[i]);
        }
        ctx->stroke();
    }

    return true;
}

/* Returns the X scale factor to use. We can't scale anamorphically
 * because it messes up the lines. */
float
Graph::set_scale(CC ctx) {
    auto    alloc   = get_allocation();
    int     w       = alloc.get_width();
    int     h       = alloc.get_height();

    float   s       = float(h) / 256.0;
    ctx->scale(s, s);

    float   xw      = float(w) / s;
    time    xm      = points.back().first;
    time    xs      = std::max(xm, 60.0f);
    float   xf      = xw / float(xs);
    return xf;
}

}
