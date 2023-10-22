#include "xetwl.h"
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>

xetwl::Window::Window(int sx, int sy, bool fs) {
    if (sx<1 || sy<5) {
        printf("WINDOW CREATION FAILED, WINDOW TOO SMALL");
//        exit(-1); // doesnt work???
    }

    autoupdate = 0;
    fullscreen = fs; sizex = sx; sizey = sy;
    clear();
}

int xetwl::Window::getScreenLen() { if (fullscreen) { return sizex*sizey; }; return sizex*(sizey-4); };

void xetwl::Window::clear(xetwl::pixel px) {
    int screenlen = getScreenLen();

    pixelsp = new xetwl::pixel[screenlen];
    for (int i = 0; i<screenlen; i++) {
        pixelsp[i] = px;
    }
}

void xetwl::Window::clear() {
    xetwl::pixel px;
    px.bg = 0;
    px.fg = 255;
    px.letter = ' ';
    px.transparent = false;
    xetwl::Window::clear(px);
}

xetwl::pixel xetwl::Window::getPixel(int x, int y) {
    return pixelsp[y*sizex+x];
}

void xetwl::Window::setPixel(int x, int y, xetwl::pixel px) { pixelsp[y*sizex + x] = px; };
void xetwl::Window::setPixel(int x, int y, unsigned char bg, unsigned char fg, char letter, bool tr) { pixelsp[y*sizex + x].bg = bg; pixelsp[y*sizex + x].fg = fg; pixelsp[y*sizex + x].letter = letter; pixelsp[y*sizex + x].transparent = tr;};

void xetwl::Window::renderTitle() {
    int lp = (sizex/2)-6;
    int rp = sizex-lp-12;
    for (int i = 0; i<lp; i++) { printf(" "); }
    printf("THIS_IS_TEST");
    for (int i = 0; i<rp; i++) { printf(" "); }
}

void xetwl::Window::renderInput() {
    printf("\033[0m");
    for (int i = 0; i<sizex; i++) { printf("~"); }
}

void xetwl::Window::renderFrame() {
    for (int i = 0; i<sizey-(4*!fullscreen); i++) {
        for (int j = 0; j<sizex; j++) {
            if (pixelsp[j + i*sizex].transparent) {
                printf("\033[0m ");
            } else {
                printf("\033[38;5;%dm\033[48;5;%dm%c", pixelsp[j + i*sizex].fg, pixelsp[j + i*sizex].bg, pixelsp[j + i*sizex].letter);
            }
        }
    }
}

float xetwl::Window::render() {
    printf("\033[3J\033[2J\033[0;0H\033[0m"); // clear screen
    if (!fullscreen) {
        renderTitle();
    }

    renderFrame();
    if (fullscreen) {
        printf("\033[0;0H");
    }

    if (!fullscreen) {
        printf("\n\r");
        renderInput();
        renderInput();
        printf("\033[1F"); // move cursor to input0
    }
    fflush(stdout);
    return 0.0; // TODO RETURN TIME IT TOOK TO RENDER IT
}

xetwl::Window xetwl::getMaxWindow(bool fs) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return xetwl::Window(w.ws_col, w.ws_row, fs);
}
