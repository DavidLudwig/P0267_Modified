
#ifndef __io2d_rulers_h__
#define __io2d_rulers_h__

template <typename Surface>
void add_rulers_for_surface(
    std::experimental::io2d::path_builder &pb,
    Surface &surface,
    const float length_small = 5.f,  // length of small ticks
    const float length_large = 15.f, // length of big ticks
    const int spacing = 50           // length in-between ticks
)
{
    using namespace std::experimental::io2d;

    // Make note of the surface's dimension
    const float w = (float) surface.dimensions().x();
    const float h = (float) surface.dimensions().y();

    // Add (visible) edges on the left and top
    pb.new_figure({0, h});
    pb.rel_line({0, -h});
    pb.rel_line({w, 0});

    // Add tick-marks along the x axis
    for (int x = 0; x < w; x += spacing) {
        pb.new_figure({(float)x, 0});
        if ((x % (spacing * 2)) == 0) {
            pb.rel_line({0, length_large});
        } else {
            pb.rel_line({0, length_small});
        }
    }

    // Add tick-marks along the y axis
    for (int y = 0; y < w; y += spacing) {
        pb.new_figure({0, (float)y});
        if ((y % (spacing * 2)) == 0) {
            pb.rel_line({length_large, 0});
        } else {
            pb.rel_line({length_small, 0});
        }
    }

    // It is the caller's responsibility to draw the guides, using data that
    // is now in the provided path_builder, 'pb', and a brush.  For example:
    //
    //   path_builder pb;
    //   add_rulers_for_surface(pb, surface);
    //   const brush guide_color{rgba_color::white};
    //   surface.stroke(guide_color, pb);
}

#endif // __io2d_rulers_h__
