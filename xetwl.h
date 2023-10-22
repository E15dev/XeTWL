#ifndef XETWL_H
#define XETWL_H

#include <cstdint>

namespace xetwl {
    #pragma pack(1)
    struct pixel {
        uint8_t bg;
        uint8_t fg;
        char letter;
        bool transparent;
    }; // 4 bytes

    class Window {
        public:
            Window(int, int, bool);
            bool autoupdate;
            int getScreenLen();
            float render();
            void clear();
            void clear(pixel);
            pixel getPixel(int, int);
            void setPixel(int, int, pixel);
            void setPixel(int, int, uint8_t, uint8_t, char, bool); // x y background textcolor transparent
        private:
            bool fullscreen;
            int sizex;
            int sizey;
            pixel* pixelsp;
            void renderTitle();
            void renderInput();
            void renderFrame();
    };

    Window getMaxWindow(bool);
}

#endif
