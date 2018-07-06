
#include <io2d.h>

using namespace std::experimental::io2d;
using namespace std;

static output_surface & display() {
    static auto surface = output_surface {512, 512, format::argb32, scaling::none, refresh_style::fixed, 60.f};
    return surface;
}

template <typename Surface>
void add_guides(
    path_builder & pb,
    Surface & surface,
    const float length_small = 5.f,     // length of small ticks
    const float length_large = 15.f,    // length of big ticks
    const int spacing = 50              // length in-between ticks
) {
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
    //   add_guides(pb, surface);
    //   const brush guide_color{rgba_color::white};
    //   surface.stroke(guide_color, pb);
}

int main(int argc, const char *argv[]) {
    try {
        auto &d = display();
        d.size_change_callback([&](output_surface &surface) {
            surface.dimensions(surface.display_dimensions());
        });
        d.draw_callback([&](auto &surface) {
            // Draw background
            brush bg_color {rgba_color::black};
            surface.paint(bg_color);

            // Draw measurement guides
            path_builder pb;
            add_guides(pb, surface);
            const brush guide_color {rgba_color::white};
            surface.stroke(guide_color, pb);
        });
        d.begin_show();
    } catch (const std::exception &ex) {
        printf("std::exception caught, what=\"%s\"\n", ex.what());
    } catch (...) {
        printf("unknown exception caught\n");
    }
    return 0;
}
