#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include "Executor.hh"
#include "../scene_elements/fixed_size_vectors/Vector3D.hh"
#include "../scene_elements/Polygon.hh"
#include "../parser/ObjectFileParser.hh"
#include "../scene_elements/serialized/camera/Camera.hh"
#include "../parser/SaveManager.hh"
#include "../factory/SceneFactory.hh"

Vector3D<float> centerGravityPolygons(std::vector<Polygon> polygons) {
    Vector3D<float> gravityCenter = Vector3D<float>();
    for (size_t i = 0; i < polygons.size(); ++i) {
        gravityCenter += polygons[i].meanVertices();
        std::cout << "center of gravity of " << i << " is " << polygons[i].meanVertices() << "\n";
    }
    gravityCenter /= polygons.size();
    return gravityCenter;
}

void cameraHit() {
    auto list = ObjectFileParser::fromPathToObjStruct("cube.obj");
    Camera c = Camera(1.f, Vector2D(512, 512), Vector3D(1.5f, .7f, -1.f), Vector3D(-0.5f, 0.f, 1.f), 90);
    std::cout << "started compute" << std::endl;
    c.computeImage(list);
    std::cout << "end compute" << std::endl;
    c.dumpImageToPpm("test.ppm");
}

void cameraHit2() {
    auto list = ObjectFileParser::fromPathToObjStruct("cube.obj");
    Camera c = Camera(1.f, Vector2D(512, 512), Vector3D(0.f, 0.0f, -2.f), Vector3D(0.f, 0.f, 1.f), 60);
    std::cout << "started compute" << std::endl;
    c.computeImage(list);
    std::cout << "end compute" << std::endl;
    c.dumpImageToPpm("test2.ppm");
}

void Executor::load(const std::string &path) {
    SaveManager::Load(path, sceneSave_);
    loaded_ = true;
}

void Executor::save(const std::string &path) {
    SaveManager::Save(path, sceneSave_);
}

void Executor::setType(Executor::jobType type) {
    type_ = type;
}

void Executor::run() {
    map_actions[type_](*this);
}


Executor::Executor() {
    map_actions[jobType::none] = [](Executor &executor) {};
    map_actions[jobType::binaryTest] = [](Executor &executor) { cameraHit(); };
    map_actions[jobType::binaryTest2] = [](Executor &executor) { cameraHit2(); };
    map_actions[jobType::buildscene] = [](Executor &executor) { executor.sceneSave_ = SceneFactory::BuildScene(); };
    map_actions[jobType::executeScene] = [](Executor &executor) { executor.renderScene(); };
}

void Executor::renderScene() {
    auto list = ObjectFileParser::fromAllObjsToObjStruct(sceneSave_.getObjects());
    sceneSave_.getCamera().computeImage(list);
    sceneSave_.getCamera().dumpImageToPpm(save_path);
}

void Executor::setSavePath(const std::string &path) {
    save_path = path;
}





