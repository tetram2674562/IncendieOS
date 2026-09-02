#ifndef ARCTICFOX_OS_VGADRIVER_H
#define ARCTICFOX_OS_VGADRIVER_H
#include "../Driver.h"
#include <stdint.h>


namespace kernel {
    namespace driver {
        namespace vga {

            template <typename Mode>
            class VgaDriver : public Driver<VgaDriver<Mode>> {
            public:
                enum VGA_MODE{
                    TEXT,
                    GRAPHICS
                };
                VgaDriver(int addr, uint16_t width, uint16_t height, VGA_MODE mode);

                VGA_MODE getMode() const;
                void load();
            protected:
                uint16_t* addr;
                const uint16_t width;
                const uint16_t height;
                const VGA_MODE mode;
            };

            template<typename Mode>
            VgaDriver<Mode>::VgaDriver(int addr, uint16_t width, uint16_t height, VGA_MODE mode) : addr((uint16_t*)addr) ,width(width), height(height),
                mode(mode) {
            }

            template<typename Mode>
            typename VgaDriver<Mode>::VGA_MODE VgaDriver<Mode>::getMode() const {
                return this->mode;
            }

            template<typename Mode>
            void VgaDriver<Mode>::load() {
                static_cast<Mode*>(this)->load();
            }
        }
    }
}

#endif //ARCTICFOX_OS_VGADRIVER_H