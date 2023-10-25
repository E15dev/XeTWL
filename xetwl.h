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
            Window(uint16_t, uint16_t, bool);

            bool autoupdate;
            uint16_t cursorx;
            uint16_t cursory;

            void clipCursor();
            void syncCursor();
            int getScreenLen();
            float render();
            void clear();
            void clear(pixel);
            pixel getPixel(uint16_t, uint16_t);
            void setPixel(uint16_t, uint16_t, pixel);
            void setPixel(uint16_t, uint16_t, uint8_t, uint8_t, char, bool);    // x y background textcolor transparent

        private:
            bool fullscreen;
            uint16_t sizex;
            uint16_t sizey;
            pixel* pixelsp;

            void init();                                                        // init pixelsp
            void renderTitle();
            void renderFrame();
    };

    Window getMaxWindow(bool);
}

#endif
