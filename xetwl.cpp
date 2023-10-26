#include "xetwl.h"
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>

bool xetwl::canBeDisplayed(char ch) {
    return ch >= 32 && ch < 127;
}

xetwl::Window::Window(uint16_t sx, uint16_t sy, bool fs) {
    if (sx<1 || sy<5) {
        printf("WINDOW CREATION FAILED, WINDOW TOO SMALL");
//        exit(-1); // doesnt work???
    }

    autoupdate = 0;
    fullscreen = fs; sizex = sx; sizey = sy;
    init();
    clear();
}

int xetwl::Window::getScreenLen() { if (fullscreen) { return sizex*sizey; }; return sizex*(sizey-4); };

void xetwl::Window::init() { pixelsp = new xetwl::pixel[getScreenLen()]; }

void xetwl::Window::clipCursor() {
    if (cursorx > 32768) cursorx=0; // its unsigned so instead checking if its negative it needs to check if its above half of max
    if (cursory > 32768) cursory=0;
    if (cursorx > sizex-1) cursorx=sizex-1;
    if (cursory > sizey-(4*!fullscreen)-1) cursory=sizey-(4*!fullscreen)-1;
}

void xetwl::Window::syncCursor() {
    clipCursor();
    printf("\033[%d;%dH", 1+cursory+!fullscreen, cursorx+1);    // this is counting form 1 belive thats why i need to add 1
}

void xetwl::Window::clear(xetwl::pixel px) {
    for (int i = 0; i<getScreenLen(); i++) { pixelsp[i] = px; }
    if (autoupdate) render();
}

void xetwl::Window::clear() {
    xetwl::pixel px;
    px.bg = 0;
    px.fg = 255;
    px.letter = ' ';
    px.transparent = false;
    xetwl::Window::clear(px);
}

xetwl::pixel xetwl::Window::getPixel(uint16_t x, uint16_t y) { return pixelsp[y*sizex+x]; }

// set pixels with autoupdate works by seting cursor in position and replacing pixel
void xetwl::Window::setPixel(uint16_t x, uint16_t y, xetwl::pixel px) {
    pixelsp[y*sizex + x] = px;
    if (autoupdate) {
        printf("\033[%d;%dH", 1+y+!fullscreen, 1+x);
        printf("\033[38;5;%dm\033[48;5;%dm%c", px.fg, px.bg, px.letter);
    }
};

void xetwl::Window::setPixel(uint16_t x, uint16_t y, unsigned char bg, unsigned char fg, char lt, bool tr) {
    int i = y*sizex + x;
    pixelsp[i].bg = bg; pixelsp[i].fg = fg;
    pixelsp[i].letter = lt;
    pixelsp[i].transparent = tr;
    if (autoupdate) {
        printf("\033[%d;%dH", 1+y+!fullscreen, 1+x);
        printf("\033[38;5;%dm\033[48;5;%dm%c", fg, bg, lt);
    }
}

void xetwl::Window::renderTitle() {
    int lp = (sizex/2)-6;
    int rp = sizex-lp-12;
    for (int i = 0; i<lp; i++) { printf("-"); }
    printf("THIS_IS_TEST");
    for (int i = 0; i<rp; i++) { printf("-"); }
}

void xetwl::Window::renderFrame() {
    for (int i = 0; i<sizey-(4*!fullscreen); i++) {
        for (int j = 0; j<sizex; j++) {
            if (pixelsp[j + i*sizex].transparent) {
                printf("\033[0m ");
            } else {
                if (canBeDisplayed(pixelsp[j + i*sizex].letter)) {pixelsp[j + i*sizex].letter = ' ';} // so it wont break render
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
        for (int i = 0; i<sizex; i++) {
            printf("-");
        }
        printf("\n\r"); printf("\n\r");
    }
    syncCursor();
    fflush(stdout);
    return 0.0; // TODO RETURN TIME IT TOOK TO RENDER IT
}

xetwl::Window xetwl::getMaxWindow(bool fs) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return xetwl::Window(w.ws_col, w.ws_row, fs);
}
