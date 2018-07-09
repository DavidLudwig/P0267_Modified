
#include <io2d.h>

using namespace std::experimental::io2d;

int main(int argc, const char *argv[]) {
    run([](auto &surface) {
        brush mainColor{rgba_color::green};
        surface.paint(mainColor);
    });
    return 0;
}
