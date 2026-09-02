#include "kernel/drivers/vga/VgaTextMode.h"


using namespace kernel::driver::vga;


VgaTextMode::VgaTextMode(const uint16_t width, const uint16_t height) : VgaDriver(0xB8000,width,height,TEXT), row(0), column(0),
                                                                        terminalColor(0),
                                                                        foreground(VGA_COLOR_LIGHT_GREY),
                                                                        background(VGA_COLOR_BLACK) {
    recalculateColor();
}

void VgaTextMode::load() {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            const int index = y * this->width + x;
            this->addr[index] = calculateCharacter(' ');
        }
    }
}

void VgaTextMode::setForeground(VgaColor foreground) {
    this->foreground = foreground;
    recalculateColor();
}

void VgaTextMode::setBackground(VgaColor background) {
    this->background = background;
    recalculateColor();
}

void VgaTextMode::writeString(const char *string, int size) {
    for (int i = 0; i < size; ++i) {
        writeChar(string[i]);
    }
}

void VgaTextMode::writeChar(char character) {
    if (character == '\n') {
        column = 0;
        if (++row == this->height)
            row = 0;
    } else if (character == '\t') {
        column = (column + 4) & ~(4 - 1);
        if (column >= this->width) {
            column = 0;
            if (++row == this->height)
                row = 0;
        }
    } else {
        writeChar(character, column, row);
        if (++column == this->width) {
            column = 0;
            if (++row == this->height)
                row = 0;
        }
    }
}

void VgaTextMode::writeChar(char character, int x, int y) const {
    const int index = y * this->width + x;
    this->addr[index] = calculateCharacter(character);
}

void VgaTextMode::recalculateColor() {
    this->terminalColor = foreground | background << 4;
}

uint16_t VgaTextMode::calculateCharacter(unsigned char character) const {
    return (uint16_t) character | (uint16_t) terminalColor << 8;
}

