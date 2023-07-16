#include <assimp/matrix4x4.h>
#include <assimp/vector3.h>

namespace Assimp {
    namespace Math {
        aiVector3D TransformVector(aiMatrix4x4 matrix, aiVector3D vec);
        aiVector3D TransformVectorNoTranslate(aiMatrix4x4 matrix, aiVector3D vec);
    }
}