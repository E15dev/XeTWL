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
            Window(int, int);
            bool auto_update;
            float render();
            void clear(pixel);
        private:
            int sizex;
            int sizey;
            pixel* pixelsp;
            void render_title();
            void render_input();
    };

    Window getMaxWindow();
}
