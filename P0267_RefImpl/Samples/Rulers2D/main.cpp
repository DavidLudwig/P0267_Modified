
#include <io2d.h>

using namespace std::experimental::io2d;
using namespace std;

static output_surface & display() {
    static auto surface = output_surface {512, 512, format::argb32, scaling::none, refresh_style::fixed, 60.f};
    return surface;
}

// Include header with 'add_rulers_for_surface' function:
//
// (Some IDEs will allow this header to be opened, quickly, by right-clicking
// on the file-name, below (after the #include).
#include "io2d_rulers.h"

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

            // Draw rulers
            path_builder pb;
            add_rulers_for_surface(pb, surface);    // this function is found in the included file, io2d_guides.h
            const brush ruler_color {rgba_color::white};
            surface.stroke(ruler_color, pb);
        });
        d.begin_show();
    } catch (const std::exception &ex) {
        printf("std::exception caught, what=\"%s\"\n", ex.what());
    } catch (...) {
        printf("unknown exception caught\n");
    }
    return 0;
}
