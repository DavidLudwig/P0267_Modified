
#include <io2d.h>

using namespace std::experimental::io2d;
using namespace std;

static output_surface & display() {
    static auto surface = output_surface {512, 512, format::argb32, scaling::none, refresh_style::fixed, 60.f};
    return surface;
}

template <typename Surface>
void add_guides(path_builder & pb, Surface & surface) {
    // Configure-ables
    const float small_tick_size = 5.f;
    const int   small_tick_increment = 50;
    const float big_tick_size = 15.f;
    // big ticks are 2x the size of small ticks

    // Make note of the surface's dimension
    const float w = (float) surface.dimensions().x();
    const float h = (float) surface.dimensions().y();

    // Add (visible) edges on the left and top
    pb.new_figure({0, h});
    pb.rel_line({0, -h});
    pb.rel_line({w, 0});

    // Add tick-marks along the x axis
    for (int x = 0; x < w; x += small_tick_increment) {
        pb.new_figure({(float)x, 0});
        if ((x % (small_tick_increment * 2)) == 0) {
            pb.rel_line({0, big_tick_size});
        } else {
            pb.rel_line({0, small_tick_size});
        }
    }

    // Add tick-marks along the y axis
    for (int y = 0; y < w; y += small_tick_increment) {
        pb.new_figure({0, (float)y});
        if ((y % (small_tick_increment * 2)) == 0) {
            pb.rel_line({big_tick_size, 0});
        } else {
            pb.rel_line({small_tick_size, 0});
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
