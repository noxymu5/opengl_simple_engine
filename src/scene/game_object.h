#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <string>
#include <map>

#include "math/transform.h"
#include "core/asserts.h"

class GameComponent;

class GameObject {
public:
    void Init();
    void Update(float dt);
    
    void GetTransform(Transform& trf) { trf = transform; }
    Transform& GetTransform() {return transform; }
    void SetTransform(Transform trf) { transform = trf; }
    void SetTransform(glm::mat4 trf) { transform.SetMatrix(trf); }

    void GetPos(glm::vec3* pos) { *pos = transform.GetPosition(); }
    glm::vec3 GetPos() { return transform.GetPosition(); }
    
    void SetPos(glm::vec3 pos) { transform.SetPosition(pos); }
    void SetScale(glm::vec3 pos) { transform.Scale(pos); }

    void SetName(std::string newName) { name = newName; }

    template<class CompT>
    CompT* AddComponent() {
        CompT* component = new CompT(this);
        components[CompT::Name()] = component;
        return component;
    }

    template<class CompT>
    CompT* TryGet() {
        auto it = components.find(CompT::Name());
        if (it == components.end()) {
            return nullptr;
        } else {
            return static_cast<CompT*>(it->second);
        }
    }

    template<class CompT>
    CompT* Get() {
        CompT* comp = TryGet<CompT>();
        ASSERT(comp != nullptr, "Can not get component %s", CompT::Name().c_str())
    }

protected:
    virtual void UpdateImpl(float dt) {}
    Transform transform;

private:
    std::string name;

    std::map<std::string, GameComponent*> components;
};

#endif