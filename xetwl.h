#ifndef XETWL_H
#define XETWL_H

#include <cstdint>

namespace xetwl {
    #pragma pack(1)
    struct pixel {
        uint8_t bg;
        uint8_t fg;
        char letter;
        char NOTHING; // so it will be 4 bytes
    }; // 4 bytes

    class Window {
        public:
            Window(int, int, bool);
            bool auto_update;
            int get_screen_len();
            float render();
            void clear(pixel);
        private:
            bool fullscreen;
            int sizex;
            int sizey;
            pixel* pixelsp;
            void render_title();
            void render_input();
            void render_frame();
    };

    Window getMaxWindow();
}

#endif
