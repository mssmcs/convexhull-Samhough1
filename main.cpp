#include "graphics.h"

using namespace std;
using namespace mssm;

int main()
{
    Graphics g("Hello Graphics!", 1024, 768);

    int x = 0;

    while (g.draw()) {
        if (!g.isDrawable()) {
            continue;
        }

        g.line({100,200}, {300,400}, GREEN);

        g.ellipse({500,500}, 20, 30, YELLOW, PURPLE);

        g.text({20,40}, 20, format("HELLO!!! {}", x), GREEN);

        g.rect({600,600}, 150, 50, RED, YELLOW);

        if (g.onKeyPress(Key::Space)) {
            g.printError("Space!!!");
            x++;
        }
    }

    return 0;
}


