#include "xetws.h"
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>

xetws::Window::Window(int sx, int sy) {
    if (sx<1 || sy<5) {
        printf("WINDOW CREATION FAILED, WINDOW TOO SMALL");
//        exit(-1); // doesnt work???
    }

    auto_update = 0;
    sizex = sx;
    sizey = sy;
    xetws::pixel bgpx; bgpx.bg = 0; bgpx.fg = 28; bgpx.letter = ' ';
    clear(bgpx);
}

void xetws::Window::clear(xetws::pixel px) {
    pixelsp = new xetws::pixel[sizex*sizey];
    for (int i = 0; i<sizex*sizey; i++) {
        px.letter = 65 + i%32; // TEST
        pixelsp[i] = px;
    }
}

void xetws::Window::render_title() {
    int lp = (sizex/2)-6;
    int rp = sizex-lp-12;
    for (int i = 0; i<lp; i++) { printf(" "); }
    printf("THIS_IS_TEST");
    for (int i = 0; i<rp; i++) { printf(" "); }
}

void xetws::Window::render_input() {
    printf("\033[0m");
    for (int i = 0; i<sizex; i++) { printf("~"); }
}

float xetws::Window::render() {
    printf("\033[3J\033[2J\033[0;0H\033[0m");
    render_title();

    for (int i = 0; i<sizey-4; i++) {
        for (int j = 0; j<sizex; j++) {
            printf("\033[38;5;%dm\033[48;5;%dm%c", pixelsp[j + i*sizex].fg, pixelsp[j + i*sizex].bg, pixelsp[j + i*sizex].letter);
        }
        printf("\n\r");
    }

    printf("\n\r");
    render_input();
    render_input();
    printf("\033[1F"); // move cursor to input0
    fflush(stdout);
    return 0.0; // TODO RETURN TIME IT TOOK TO RENDER IT
}

xetws::Window xetws::getMaxWindow() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    xetws::Window win = xetws::Window(w.ws_col, w.ws_row);
    return win;
}
