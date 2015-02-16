#include "config.hpp"
#include <fstream>
#include <cereal/archives/json.hpp>

namespace vwiimote {

    config_t config;

    void configure() {
        char const *file = "config.json";
        try {
            std::ifstream is(file, std::ios::binary);
            cereal::JSONInputArchive r(is);
            config.serialize(r);
        } catch (std::exception e) {
            std::ofstream os(file, std::ios::binary);
            cereal::JSONOutputArchive w(os);
            config.serialize(w);
        }
        std::cout << config.bluetooth << std::endl;
    }
}
