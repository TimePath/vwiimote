#pragma once

#include <cereal/cereal.hpp>

namespace vwiimote {
    struct config_t {
        bool bluetooth = true;

        template<class Archive>
        void serialize(Archive &ar) {
            ar(CEREAL_NVP(bluetooth));
        }
    };

    extern config_t config;

    void configure();
}
