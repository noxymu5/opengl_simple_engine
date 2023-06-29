#include "math.h"

namespace Assimp {
    namespace Math {

        aiVector3D TransformVector(aiMatrix4x4 matrix, aiVector3D vec) {
            aiVector3D result;

            result.x = matrix.a1 * vec.x + matrix.a2 * vec.y + matrix.a3 * vec.z + matrix.a4;
            result.y = matrix.b1 * vec.x + matrix.b2 * vec.y + matrix.b3 * vec.z + matrix.b4;
            result.z = matrix.c1 * vec.x + matrix.c2 * vec.y + matrix.c3 * vec.z + matrix.c4;

            return result;
        }

    }
}