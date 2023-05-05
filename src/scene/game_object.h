#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <vector>

#include "math/transform.h"

class GameComponent;

class GameObject {
public:
    void Update(float dt);
    
    void GetTransform(Transform* trf) { trf = &transform; }
    Transform GetTransform() {return transform; }
    void SetTransform(Transform trf) { transform = trf; }
    void SetTransform(glm::mat4 trf) { transform.SetMatrix(trf); }

    void GetPos(glm::vec3* pos) { *pos = transform.GetPosition(); }
    glm::vec3 GetPos() { return transform.GetPosition(); }
    
    void SetPos(glm::vec3 pos) { transform.SetPosition(pos); }

    template<class CompT>
    CompT* AddComponent() {
        CompT* component = new CompT(this);
        components.push_back(component);
        return component;
    }

protected:
    virtual void UpdateImpl(float dt) {}

private:
    Transform transform;

    std::vector<GameComponent*> components;
};

#endif