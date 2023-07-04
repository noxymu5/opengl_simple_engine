
#include <yaml-cpp/yaml.h>
#include <glm/vec3.hpp>

#include "scene/light.h"

namespace YAML {

    template<>
    struct convert<glm::vec3> {
        static Node encode(const glm::vec3& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        static bool decode(const Node& node, glm::vec3& rhs) {
            if(!node.IsSequence() || node.size() != 3) {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<LIGHT_TYPE> {
        static Node encode(const LIGHT_TYPE& rhs) {
            Node node;
            node.push_back((int)rhs);

            return node;
        }

        static bool decode(const Node& node, LIGHT_TYPE& rhs) {
            rhs = (LIGHT_TYPE)node.as<int>();
            
            return true;
        }
    };

}