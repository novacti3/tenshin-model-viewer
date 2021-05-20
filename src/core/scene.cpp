#include "scene.hpp"

Scene::Scene()
{
    SceneObject *camObject = new SceneObject(new TransformComponent(glm::vec3(0.0f, 0.0f, 3.0f)));
    camObject->AddComponent<CameraComponent>(new CameraComponent(*(camObject->GetComponent<TransformComponent>()), 60.0f, 1600.0f/1200.0f, 0.01f, 100.0f));      

    _sceneObjects.push_back(camObject);  
}
Scene::Scene(SceneObject *camera) 
{ 
    _sceneObjects.push_back(camera);   
}
Scene::~Scene()
{
    for(SceneObject *obj: _sceneObjects)
    {
        delete obj;
        obj = nullptr;
    }
}

// Copy
Scene::Scene(const Scene& other)
{
    this->_sceneObjects = other._sceneObjects;
}
Scene& Scene::operator=(Scene other)
{
    this->_sceneObjects = other._sceneObjects;
    return *this;
}

// Move
Scene::Scene(Scene&& other)
{
    this->_sceneObjects = std::move(other._sceneObjects);
}
Scene& Scene::operator=(Scene&& other)
{
    this->_sceneObjects = std::move(other._sceneObjects);
    return *this;
}

// NOTE: Find object by name func?
void Scene::AddObject(SceneObject *obj)
{
    _sceneObjects.push_back(obj);
}
void Scene::RemoveObject(SceneObject *obj)
{
    // NOTE: Doing this is probably inefficient because to get the object pointer, you must loop through the scene objects already and now loop through them again to get the iterator
    // Making the SceneObjects vector changeable directly might be better?
    for (auto i = _sceneObjects.begin(); i < _sceneObjects.end(); i++)
    {
        if(obj == *i)
        {
            _sceneObjects.erase(i);
        }
    }
}