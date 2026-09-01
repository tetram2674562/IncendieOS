#ifndef ARCTICFOX_OS_VGATEXTMODE_H
#define ARCTICFOX_OS_VGATEXTMODE_H
#include "VgaDriver.h"


namespace kernel {
    namespace driver {
        namespace vga {
            class VgaTextMode {
                // TODO USE TEMPLATE CUZ VIRTUAL DOES NOT EXIST
            public:
                enum VgaColor {
                    VGA_COLOR_BLACK = 0,
                    VGA_COLOR_BLUE = 1,
                    VGA_COLOR_GREEN = 2,
                    VGA_COLOR_CYAN = 3,
                    VGA_COLOR_RED = 4,
                    VGA_COLOR_MAGENTA = 5,
                    VGA_COLOR_BROWN = 6,
                    VGA_COLOR_LIGHT_GREY = 7,
                    VGA_COLOR_DARK_GREY = 8,
                    VGA_COLOR_LIGHT_BLUE = 9,
                    VGA_COLOR_LIGHT_GREEN = 10,
                    VGA_COLOR_LIGHT_CYAN = 11,
                    VGA_COLOR_LIGHT_RED = 12,
                    VGA_COLOR_LIGHT_MAGENTA = 13,
                    VGA_COLOR_LIGHT_BROWN = 14,
                    VGA_COLOR_WHITE = 15,
                };
                VgaTextMode(uint16_t width = 80, uint16_t height = 25);
                void load();
                void setForeground(VgaColor foreground);
                void setBackground(VgaColor background);
                void writeString(const char* string,int size);
                void writeChar(char character);
                void writeChar(char character, int x, int y) const;


            private:
                void recalculateColor();
                uint16_t calculateCharacter(unsigned char character) const;

                int row;
                int column;
                uint8_t terminalColor;
                VgaColor foreground;
                VgaColor background;
                uint16_t* addr;
                const uint16_t width;
                const uint16_t height;
            };
        }
    }
}

#endif //ARCTICFOX_OS_VGATEXTMODE_H
