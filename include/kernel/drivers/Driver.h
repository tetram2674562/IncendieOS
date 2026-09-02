#ifndef ARCTICFOX_OS_DRIVER_H
#define ARCTICFOX_OS_DRIVER_H

namespace kernel {
    namespace driver {
        template <typename DriverType>
        class Driver {
        public:
            void load();
        };

        template<typename DriverType>
        void Driver<DriverType>::load() {
            static_cast<DriverType*>(this)->load();
        }
    }
}

#endif //ARCTICFOX_OS_DRIVER_H
