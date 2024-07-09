﻿// This has been adapted from the Vulkan tutorial
#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"
using namespace std;
using namespace glm;

/*vector<SingleText> outText = {
  {2, {"City", "","",""}, 0, 0} };*/

struct UniformBufferObject {
  alignas(16) mat4 mvpMat;
  alignas(16) mat4 mMat;
  alignas(16) mat4 nMat;
};

struct spotLightUBO {
    alignas(16) vec3 lightDir[4];
    alignas(16) vec3 lightPos[4];
    alignas(16) vec3 lightColor[4];
    alignas(16) vec3 eyePos;
    alignas(16) vec4 InOutDecayTarget;
};

struct EmissionUniformBufferObject {
    alignas(16) mat4 mvpMat;
};

struct EmissionVertex {
    glm::vec3 pos;
    glm::vec2 UV;
};

struct BlinnUniformBufferObject {
    alignas(16) glm::vec3 lightDir;
    alignas(16) glm::vec4 lightColor;
    alignas(16) glm::vec3 eyePos;
};

struct BlinnMatParUniformBufferObject {
    alignas(4)  float Power;
};

struct ToonUniformBufferObject {
    alignas(16) glm::vec3 lightDir;
    alignas(16) glm::vec3 lightColor;
    alignas(16) glm::vec3 eyePos;
    alignas(4) float angleDiff;
    alignas(4) float angleSpec;
};

struct Component {
  const string ObjPath;
  const string TexturePath;
  ModelType type;
  const vec3 pos;
  const vec3 scale;
  const std::vector<vec3> rot;
  const std::vector<float> angle;
  Model model;
  Texture texture;
  DescriptorSet DS;
};

struct Vertex {
  vec3 pos;
  vec3 norm;
  vec2 UV;
};

enum Scene { CITY, SHOP, APARTMENT };

vector<Component> Apartment = {
    //PAVIMENTO
    {"models/Apartment/floor_016_Mesh.338.mgcg", "textures/Textures.png", MGCG,{200.0f, -1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Apartment/floor_016_Mesh.338.mgcg", "textures/Textures.png", MGCG,{204.0f, -1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Apartment/floor_016_Mesh.338.mgcg", "textures/Textures.png", MGCG,{200.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Apartment/floor_016_Mesh.338.mgcg", "textures/Textures.png", MGCG,{204.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Apartment/floor_016_Mesh.338.mgcg", "textures/Textures.png", MGCG,{199.0f, -1.0f, 197.0f}, {0.5f, 2.0f, 0.5f}, {}, {}},

    //SOFFITTO
    {"models/Apartment/Walls_009_Plane.003.mgcg", "textures/Textures.png", MGCG,{200.0f, 3.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
    {"models/Apartment/Walls_009_Plane.003.mgcg", "textures/Textures.png", MGCG,{204.0f, 3.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
    {"models/Apartment/Walls_009_Plane.003.mgcg", "textures/Textures.png", MGCG,{200.0f, 3.0f, 202.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
    {"models/Apartment/Walls_009_Plane.003.mgcg", "textures/Textures.png", MGCG,{204.0f, 3.0f, 202.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
    {"models/Apartment/Walls_009_Plane.003.mgcg", "textures/Textures.png", MGCG,{199.0f, 3.0f, 196.0f}, {0.5f, 1.0f, 0.5f}, {{1.0f, 0.0, 0.0}}, {90.0f}},

    //MURI
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{206.0f, 1.0f, 206.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{202.0f, 1.0f, 206.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{206.0f, -1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{206.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{198.0f, -1.0f, 200.0f},{1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{198.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{206.0f, 1.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{202.0f, 1.0f, 198.0f}, {0.5f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{200.0f, 1.0f, 196.0f}, {0.5f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{200.0f, -1.0f, 197.0f}, {1.0f, 1.0f, 0.5f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/Walls_116_Plane.057.mgcg", "textures/Textures.png", MGCG,{198.0f, -1.0f, 197.0f}, {1.0f, 1.0f, 0.5f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},

    //ACCESSORI
    {"models/Apartment/door_005_Mesh.119.mgcg", "textures/Textures.png", MGCG,{198.15f, -1.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/window_003_Mesh.125.mgcg", "textures/Textures.png", MGCG,{205.8f, 1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/window_003_Mesh.125.mgcg", "textures/Textures.png", MGCG,{205.8f, 1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/window_003_Mesh.125.mgcg", "textures/Textures.png", MGCG,{198.2f, 1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/window_003_Mesh.125.mgcg", "textures/Textures.png", MGCG,{198.2f, 1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Apartment/sofa_007_Mesh.158.mgcg", "textures/Textures.png", MGCG,{203.0f, -0.8f, 204.0f}, {1.2f, 1.2f, 1.2f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
    {"models/Apartment/tv_wall_003_Mesh.184.mgcg", "textures/Textures.png", MGCG,{203.0f, -1.0f, 198.5f}, {1.2f, 1.2f, 1.2f}, {}, {}},
    {"models/Apartment/flower_010_Mesh.287.mgcg", "textures/Textures.png", MGCG,{200.f, -1.0f, 203.0f}, {1.2f, 1.2f, 1.2f}, {}, {}},
    {"models/Apartment/lamp_018_Mesh.6631.mgcg", "textures/Textures.png", MGCG,{202.0f, 3.0f, 202.0f}, {2.0f, 2.0f, 2.0f}, {}, {}},
    {"models/Apartment/Sphere.obj", "textures/Lamp.png", OBJ, {202.0f, 2.2f, 202.0f}, {0.15f, 0.15f, 0.15f}, {}, {}},

    
};


//SHOP
vector<Component> Shop = {
    
    //PAVIMENTO
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{100.0f, -1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{104.0f, -1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{100.0f, -1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{104.0f, -1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    
    //MURI
    //ALTO SINISTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{98.0f, -1.0f, 104.0f}, {1.0f, 2.0f, 1.0f}, { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{100.0f, -1.0f, 106.0f}, {1.0f, 2.0f, 1.0f}},
    //ALTO DESTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{106.0f, -1.0f, 104.0f}, {1.0f, 2.0f, 1.0f}, { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{104.0f, -1.0f, 106.0f}, {1.0f, 2.0f, 1.0f}},
    //BASSO DESTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{104.0f, -1.0f, 98.0f}, {1.0f, 2.0f, 1.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{106.0f, -1.0f, 100.0f}, {1.0f, 2.0f, 1.0f},  { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    //BASSO SINISTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{98.0f, -1.0f, 100.0f}, {1.0f, 2.0f, 1.0f} , { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", "textures/Wall_Shop.png", MGCG,{100.0f, -1.0f, 98.0f}, {1.0f, 2.0f, 1.0f} },

    //TETTO
    {"models/Shop/Walls_036_Plane.019.mgcg", "textures/Textures.png", MGCG,{100.0f, 3.0f, 98.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},
    {"models/Shop/Walls_036_Plane.019.mgcg", "textures/Textures.png", MGCG,{104.0f, 3.0f, 98.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},
    {"models/Shop/Walls_036_Plane.019.mgcg", "textures/Textures.png", MGCG,{100.0f, 3.0f, 102.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},
    {"models/Shop/Walls_036_Plane.019.mgcg", "textures/Textures.png", MGCG,{104.0f, 3.0f, 102.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},

    //ACCESSORI
    {"models/Shop/shop_003_Mesh.4875.mgcg", "textures/Textures.png", MGCG,{105.0f, -1.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_003_Mesh.4875.mgcg", "textures/Textures.png", MGCG,{103.0f, -1.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_004_Mesh.4923.mgcg", "textures/Textures.png", MGCG,{100.0f, 0.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_002_Mesh.5167.mgcg", "textures/Textures.png", MGCG,{104.0f, 0.0f, 105.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
    {"models/Shop/door_011_Mesh.116.mgcg", "textures/Textures.png",MGCG, {101.0f, -1.0f, 105.7f}, {1.3f, 1.3f, 1.3f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
    {"models/Shop/window_006_Mesh.654.mgcg", "textures/Textures.png", MGCG,{105.7f, 1.0f, 102.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Shop/window_006_Mesh.654.mgcg", "textures/Textures.png", MGCG,{98.3f, 1.0f, 102.0f}, {1.3f, 1.3f, 1.3f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},

    //LAMPADE 
    {"models/Shop/lamp_026_Mesh.6700.mgcg", "textures/Textures.png", MGCG,{100.0f, 3.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/lamp_026_Mesh.6700.mgcg", "textures/Textures.png", MGCG,{104.0f, 3.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/lamp_026_Mesh.6700.mgcg", "textures/Textures.png",MGCG, {100.0f, 3.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/lamp_026_Mesh.6700.mgcg", "textures/Textures.png", MGCG,{104.0f, 3.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},

    //LAMPADINE
    {"models/Shop/Sphere.obj", "textures/Lamp.png", OBJ,{100.0f, 2.2f, 100.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    {"models/Shop/Sphere.obj", "textures/Lamp.png", OBJ, {104.0f, 2.2f, 100.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    {"models/Shop/Sphere.obj", "textures/Lamp.png", OBJ, {100.0f, 2.2f, 104.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    {"models/Shop/Sphere.obj", "textures/Lamp.png", OBJ, {104.0f, 2.2f, 104.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    
};




std::vector<Component> ComponentVector = {
    {"models/beach_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    
    {"models/beach_tile_1x1_003.mgcg", "textures/Textures_City.png", MGCG,{8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/beach_tile_1x1_004.mgcg", "textures/Textures_City.png",MGCG, {2*8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/beach_tile_1x1_006.mgcg", "textures/Textures_City.png",MGCG, {3*8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/beach_tile_1x1_002.mgcg", "textures/Textures_City.png",MGCG, {4*8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/beach_tile_1x1_007.mgcg", "textures/Textures_City.png",MGCG, {4*8.0f, 0.0f, 8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},
    {"models/beach_tile_1x1_007.mgcg", "textures/Textures_City.png",MGCG, {4*8.0f, 0.0f, 2*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},
    {"models/beach_tile_1x1_007.mgcg", "textures/Textures_City.png",MGCG, {0.0f, 0.0f, 8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/beach_tile_1x1_007.mgcg", "textures/Textures_City.png", MGCG,{0.0f, 0.0f, 2*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/landscape_entertainments_006.mgcg", "textures/Textures_City.png", MGCG,{-12.0f, 0.0f, -4.0f}, {1.0f, 1.0f, 1.0f}},
    
    {"models/tile_river_2x2_001.mgcg", "textures/Textures_City.png",MGCG, {10.0f, -1.2f, 10.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/tile_river_2x2_001.mgcg", "textures/Textures_City.png",MGCG, {20.0f, -1.2f, 10.0f}, {1.0f, 1.0f, 1.0f}},
    
    {"models/road_tile_1x1_008.mgcg", "textures/Textures_City.png",MGCG, {2*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", MGCG,{8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {3*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {4*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {5*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {6*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {7*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_1x1_004.mgcg", "textures/Textures_City.png",MGCG, {8*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f}}, {-90.0f}},
    {"models/road_tile_1x1_004.mgcg", "textures/Textures_City.png",MGCG, {0.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {90.0f}},
    
    {"models/store_003.mgcg", "textures/Textures_City.png", MGCG,{8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/tile_for_home_2x2_007.mgcg", "textures/Textures_City.png", MGCG,{4.0f, 0.0f, -2.5 * 8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/tile_for_home_2x2_007.mgcg", "textures/Textures_City.png", MGCG,{-12.0f, 0.0f, -2.5 * 8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/transport_bus_005_transport_bus_005.001.mgcg", "textures/Textures_City.png", MGCG,{0.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/transport_sport_001_transport_sport_001.001.mgcg", "textures/Textures_City.png",MGCG, {0.0f, 0.0f, -3 * 8.0f}, {1.0f, 1.0f, 1.0f}},
    
    {"models/landscape_entertainments_007.mgcg", "textures/Textures_City.png",MGCG, {4+5*8.0f, 0.0f, 4.0f}, {1.0f, 1.0f, 1.0f}}, //tennis
    {"models/landscape_entertainments_003.mgcg", "textures/Textures_City.png", MGCG,{4+5*8.0f, 0.0f, -20.0f}, {1.0f, 1.0f, 1.0f}}, //gym
    {"models/landscape_entertainments_008.mgcg", "textures/Textures_City.png", MGCG,{20+5*8.0f, 0.0f, 4.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {-90.0f}}, //foot
    {"models/landscape_entertainments_010.mgcg", "textures/Textures_City.png", MGCG,{20+5*8.0f, 0.0f, -20.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {90.0f}}, //basket
    
    {"models/apartment_008.mgcg", "textures/Textures_City.png",MGCG, {3*8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/apartment_008.mgcg", "textures/Textures_City.png",MGCG, {3*8.0f, 0.0f, -3*8.0f}, {1.0f, 1.0f, 1.0f}, { {0.0f, 1.0f, 0.0f} }, {180.0f}},
    {"models/tile_for_home_2x2_003.mgcg", "textures/Textures_City.png", MGCG,{28.0f, 0.0f, -20.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/apartment_012.mgcg", "textures/Textures_City.png",MGCG, {4*8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/apartment_012.mgcg", "textures/Textures_City.png",MGCG, {4*8.0f, 0.0f, -3*8.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {180.0f}},
    
    {"models/road_tile_1x1_010.mgcg", "textures/Textures_City.png", MGCG,{2*8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {90.0f}},
    {"models/road_tile_1x1_010.mgcg", "textures/Textures_City.png",MGCG, {2*8.0f, 0.0f, -3*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}},
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", MGCG,{2*8.0f, 0.0f, -6*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}}, //change with 011 maybe
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", MGCG,{2*8.0f, 0.0f, -7*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}}, //change with 011 maybe
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {2*8.0f, 0.0f, -8*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}}, //change with 011 maybe
    {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png",MGCG, {2*8.0f, 0.0f, -9*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}}, //change with 011 maybe

    {"models/road_tile_2x2_006.mgcg", "textures/Textures_City.png",MGCG, {4+2*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}}, // big road
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png",MGCG, {4.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png",MGCG, {4+4*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png", MGCG,{4+5*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_2x2_003.mgcg", "textures/Textures_City.png",MGCG, {4+7*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {270.0f}},
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png",MGCG, {4+7*8.0f, 0.0f, -4-6*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/road_tile_2x2_003.mgcg", "textures/Textures_City.png",MGCG, {-4-1*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {180.0f}},

    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png",MGCG, {4+7*8.0f, 0.0f, -4-8*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png",MGCG, {-4-1*8.0f, 0.0f, -4-6*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png",MGCG, {-4-1*8.0f, 0.0f, -4-8*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},

    {"models/road_tile_2x2_003.mgcg", "textures/Textures_City.png",MGCG, {-4-1*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/road_tile_2x2_003.mgcg", "textures/Textures_City.png", MGCG,{4+7*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/road_tile_2x2_002.mgcg", "textures/Textures_City.png", MGCG,{4+2*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}}, // big road
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png", MGCG,{4.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png", MGCG,{4+4*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png", MGCG,{4+5*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/apartment_1_002.mgcg", "textures/Textures_City.png", MGCG,{4.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/tile_for_home_2x2_003.mgcg", "textures/Textures_City.png", MGCG,{4.0f, 0.0f, -52.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/apartment_1_004.mgcg", "textures/Textures_City.png",MGCG, {4+3*8.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/tile_for_home_2x2_007.mgcg", "textures/Textures_City.png", MGCG,{28.0f, 0.0f, -52.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/apartment_1_003.mgcg", "textures/Textures_City.png",MGCG, {5+5*8.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}}, //001 or 003;
    {"models/tile_for_home_2x2_007.mgcg", "textures/Textures_City.png", MGCG,{44.0f, 0.0f, -52.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/parking_tile_2x2_002.mgcg", "textures/Textures_City.png", MGCG,{4.0f, 0.0f, -68.0f}, {1.0f, 1.0f, 1.0f}},
    
    {"models/park_002.mgcg", "textures/Textures_City.png", MGCG,{4+3*8.0f, 0.0f, -4-8*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/park_006.mgcg", "textures/Textures_City.png", MGCG, { 20 + 3 * 8.0f, 0.0f, -4 - 8 * 8.0f }, { 1.0f, 1.0f, 1.0f } }   
    
};
//    {"models/dwelling_004.mgcg", "textures/Textures_City.png", {0.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}}

class ComputerGraphicsProject2024 : public BaseProject {
protected:

  Scene currentScene = CITY;

  float Ar;
  TextMaker txt;

  DescriptorSet DS;

  DescriptorSetLayout DSL;

  //BLINN
  DescriptorSetLayout DSLBlinn;
  Pipeline PipBlinn;
  VertexDescriptor VDBlinnVertex;

  //SHOP
  DescriptorSetLayout DSLshop, DSLShopLight;
  DescriptorSet DSlight;
  Pipeline Pipshop;
  VertexDescriptor VDshop;

  //APARTMENT
  DescriptorSetLayout DSLapartmentLight;
  DescriptorSet DStoonLight;
  Pipeline Pipapartment;
  VertexDescriptor VDapartment;

  //ONLY EMISSION
  DescriptorSetLayout DSLemission;
  Pipeline PipEmission;
  VertexDescriptor VDemission;

  vec3 CamPos = vec3(1.0, 1.0, -8.0);
  float CamAlpha = 0.0f, CamBeta = 0.0f;
  mat4 ViewMatrix;

  bool spectatorMode = false;

  bool isInsideCar = false;
  bool firstPersonView = true;


  void setWindowParameters() {
    windowWidth = 800;
    windowHeight = 600;
    windowTitle = "ComputerGraphicsProject2024";
    windowResizable = GLFW_TRUE;
    initialBackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };

    Ar = (float)windowWidth / (float)windowHeight;
  }

  // What to do when the window changes size
  void onWindowResize(int w, int h) {
    cout << "Window resized to: " << w << " x " << h << "\n";
    Ar = (float)w / (float)h;
  }

  void localInit() {

      DSL.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS, sizeof(BlinnUniformBufferObject), 1},
          {1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(BlinnMatParUniformBufferObject), 1}
          });
      DSLBlinn.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(UniformBufferObject), 1},
          {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1} });


      /*DSLshop contiene al texture e le matrici per posizionare nei punti corretti i vari modelli, mentre DSLShopLight contiene 
      esclusivamente le informazioni per le luci. Essendo che le stesse luci colpiscono tutti gli oggetti è presente un descriptor 
      set a parte. Il primo sarà associato al set 1, mentre il secondo al set 0*/
      DSLshop.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(UniformBufferObject), 1},
          {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
          });
      DSLShopLight.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL, sizeof(spotLightUBO), 1 } }
      );
      DSLapartmentLight.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL, sizeof(ToonUniformBufferObject), 1 }
      });

      DSLemission.init(this, {
            {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(EmissionUniformBufferObject), 1},
            {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1}
          });


      VDBlinnVertex.init(this, { {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX} }, {
             {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),sizeof(vec3), POSITION},
             {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),sizeof(vec3), NORMAL},
             {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(vec2), UV}
          });
      VDshop.init(this, { {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX} }, {
          {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),sizeof(vec3), POSITION},
          {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),sizeof(vec3), NORMAL},
          {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(vec2), UV}
          });
      VDemission.init(this, { {0, sizeof(EmissionVertex),VK_VERTEX_INPUT_RATE_VERTEX} }, {
          { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(EmissionVertex, pos),sizeof(vec3), POSITION },
          { 0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(EmissionVertex, UV), sizeof(vec2), UV } }
          );
      VDapartment.init(this, { {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX} }, {
          {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),sizeof(vec3), POSITION},
          {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),sizeof(vec3), NORMAL},
          {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(vec2), UV}
      });


      PipBlinn.init(this, &VDBlinnVertex, "shaders/Vert.spv", "shaders/Frag.spv", { &DSL, &DSLBlinn });
      Pipshop.init(this, &VDshop, "shaders/Shop/Vert.spv", "shaders/Shop/SpotLight.spv", { &DSLShopLight, &DSLshop });
      PipEmission.init(this, &VDemission, "shaders/generalEmissionVert.spv", "shaders/generalEmissionFrag.spv", { &DSLemission });
      Pipapartment.init(this, &VDapartment, "shaders/Apartment/Vert.spv", "shaders/Apartment/ToonLight.spv", { &DSLapartmentLight, &DSLshop });

      //METODO CHE INIZIALIZZA TUTTI I MODELLI E TEXTURE DELL'ARRAY DI ASSET
      for (int i = 0; i < ComponentVector.size(); i++) {
          ComponentVector[i].model.init(this, &VDBlinnVertex, ComponentVector[i].ObjPath, ComponentVector[i].type);
          ComponentVector[i].texture.init(this, ComponentVector[i].TexturePath);
      }
      
      //SHOP
      int j;
      for (j = 0; j < Shop.size()-4; j++) {
          Shop[j].model.init(this, &VDshop, Shop[j].ObjPath, Shop[j].type);
          Shop[j].texture.init(this, Shop[j].TexturePath);
      }
      for (; j < Shop.size(); j++) {
          Shop[j].model.init(this, &VDemission, Shop[j].ObjPath, Shop[j].type);
          Shop[j].texture.init(this, Shop[j].TexturePath);
      }

      //APARTMENT
      for (j = 0; j < Apartment.size(); j++) {
          Apartment[j].model.init(this, &VDapartment, Apartment[j].ObjPath, Apartment[j].type);
          Apartment[j].texture.init(this, Apartment[j].TexturePath);
      }


      //DA CAMBIARE
      DPSZs.uniformBlocksInPool = ComponentVector.size() * 2 + Shop.size() + 2 + Apartment.size() + 1;
      DPSZs.texturesInPool = ComponentVector.size() + Shop.size() + Apartment.size();
      DPSZs.setsInPool = ComponentVector.size() + Shop.size() + 3 + Apartment.size() + 1;

      cout << "Initializing text\n";
      //txt.init(this, &outText);

      cout << "Initialization completed!\n";
      cout << "Uniform Blocks in the Pool  : " << DPSZs.uniformBlocksInPool << "\n";
      cout << "Textures in the Pool        : " << DPSZs.texturesInPool << "\n";
      cout << "Descriptor Sets in the Pool : " << DPSZs.setsInPool << "\n";

      ViewMatrix = translate(mat4(1), -CamPos);
  }

  void pipelinesAndDescriptorSetsInit() {

    PipBlinn.create();
    Pipshop.create();
    PipEmission.create();
    Pipapartment.create();

    DS.init(this, &DSL, {});
    //METODO CHE INIZIALIZZA TUTTI I DESCRIPTOR SET
    int sizeCV = ComponentVector.size();
    for (int i = 0; i < sizeCV; i++) {
      ComponentVector[i].DS.init(this, &DSLBlinn, {&ComponentVector[i].texture});
    }
    int sizeSHOP, j;
    for (j = 0; j < Shop.size() - 4; j++) {
        Shop[j].DS.init(this, &DSLshop, { &Shop[j].texture });
    }
    for (; j < Shop.size(); j++) {
        Shop[j].DS.init(this, &DSLemission, { &Shop[j].texture });
    }
    DSlight.init(this, &DSLShopLight, {});
    for (j = 0; j < Apartment.size(); j++) {
        Apartment[j].DS.init(this, &DSLshop, { &Apartment[j].texture });
    }
    DStoonLight.init(this, &DSLapartmentLight, {});
  }

  void pipelinesAndDescriptorSetsCleanup() {

    PipBlinn.cleanup();
    Pipshop.cleanup();
    PipEmission.cleanup();
    Pipapartment.cleanup();

    DS.cleanup();
    //CLEAN UP DI TUTTI I DESCRIPTOR SET
    for (int i = 0; i < ComponentVector.size(); i++) {
      ComponentVector[i].DS.cleanup();
    }
    //SHOP
    for (int i = 0; i < Shop.size(); i++) {
        Shop[i].DS.cleanup();
    }
    DSlight.cleanup();
    //APARTMENT
    for (int i = 0; i < Apartment.size(); i++) {
        Apartment[i].DS.cleanup();
    }
    DStoonLight.cleanup();
  }

  void localCleanup() {

    //CLEAN UP DI TUTTI I MODEL E TEXTURES
    for (int i = 0; i < ComponentVector.size(); i++) {
      ComponentVector[i].model.cleanup();
      ComponentVector[i].texture.cleanup();
    }
    for (int i = 0; i < Shop.size(); i++) {
        Shop[i].model.cleanup();
        Shop[i].texture.cleanup();
    }
    for (int i = 0; i < Apartment.size(); i++) {
        Apartment[i].model.cleanup();
        Apartment[i].texture.cleanup();
    }

    DSLemission.cleanup();
    DSLshop.cleanup();
    DSLShopLight.cleanup();
    DSLBlinn.cleanup();
    DSLapartmentLight.cleanup();

    PipEmission.destroy();
    PipBlinn.destroy();
    Pipshop.destroy();
    Pipapartment.destroy();
  }

  void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
      if (currentScene == CITY) {
          PipBlinn.bind(commandBuffer);

          DS.bind(commandBuffer, PipBlinn, 0, currentImage);
          for (int i = 0; i < ComponentVector.size(); i++) {

              ComponentVector[i].model.bind(commandBuffer);
              ComponentVector[i].DS.bind(commandBuffer, PipBlinn, 1, currentImage);

              // The actual draw call.
              vkCmdDrawIndexed(commandBuffer,
                  static_cast<uint32_t>(ComponentVector[i].model.indices.size()), 1, 0, 0, 0);
          }
      }
      else if (currentScene == SHOP) {
          int j;
          Pipshop.bind(commandBuffer);
          DSlight.bind(commandBuffer, Pipshop, 0, currentImage);
          for (j = 0; j < Shop.size() - 4; j++) {
              Shop[j].model.bind(commandBuffer);
              Shop[j].DS.bind(commandBuffer, Pipshop, 1, currentImage);
              vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
          }
          PipEmission.bind(commandBuffer);
          for (; j < Shop.size(); j++) {
              Shop[j].model.bind(commandBuffer);
              Shop[j].DS.bind(commandBuffer, PipEmission, 0, currentImage);
              vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
          }
      }
      else if (currentScene == APARTMENT) {
          int j;
          Pipapartment.bind(commandBuffer);
          DStoonLight.bind(commandBuffer, Pipapartment, 0, currentImage);
          for (j = 0; j < Apartment.size(); j++) {
              Apartment[j].model.bind(commandBuffer);
              Apartment[j].DS.bind(commandBuffer, Pipapartment, 1, currentImage);
              vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Apartment[j].model.indices.size()), 1, 0, 0, 0);
          }
      }
      
  }

  void updateUniformBuffer(uint32_t currentImage) {

    
    float deltaT, cameraAngle = 0.0, movX, movZ;
    vec3 m = vec3(0.0f), r = vec3(0.0f), cameraPosition = { 0.0,0.0,0.0 }, CamPosOld;
    bool fire = false;

    getSixAxis(deltaT, m, r, fire);

    static float autoTime = true;
	static float cTime = 0.0;
	const float turnTime = 72.0f;
	const float angTurnTimeFact = 2.0f * M_PI / turnTime;
		
	if(autoTime) {
		cTime = cTime + deltaT;
		cTime = (cTime > turnTime) ? (cTime - turnTime) : cTime;
	};

    const float ROT_SPEED = radians(120.0f);
    const float WALK_SPEED = 8.0f;
    const float RUN_SPEED = WALK_SPEED * 2;

    float MOVE_SPEED = WALK_SPEED;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        MOVE_SPEED = RUN_SPEED;
    }

    mat4 Mv;

    CamAlpha = CamAlpha - ROT_SPEED * deltaT * r.y;
    CamBeta = CamBeta - ROT_SPEED * deltaT * r.x;
    CamBeta = CamBeta < radians(-90.0f) ? radians(-90.0f) : (CamBeta > radians(90.0f) ? radians(90.0f) : CamBeta);


    vec3 ux = rotate(mat4(1.0f), CamAlpha, vec3(0, 1, 0)) * vec4(1, 0, 0, 1);
    vec3 uz = rotate(mat4(1.0f), CamAlpha, vec3(0, 1, 0)) * vec4(0, 0, -1, 1);
    vec3 uy = rotate(mat4(1.0f), CamBeta, vec3(1, 0, 1)) * vec4(0, 1, 0, 1);
    
    CamPosOld = CamPos;
    CamPos = CamPos + MOVE_SPEED * m.x * ux * deltaT;
    CamPos = CamPos - MOVE_SPEED * m.z * uz * deltaT;

    if (!checkLimits(CamPos)) {
        CamPos = CamPosOld;
    }

    if (spectatorMode) {
        CamPos = CamPos + MOVE_SPEED * m.y * uy * deltaT;
    }
    else {
        CamPos.y = vec3(0, 1, 0).y;
    }
    cameraPosition = CamPos;
    cameraAngle = cameraAngle + (360.0 * (CamAlpha)) / (2*M_PI);
    Mv = rotate(mat4(1.0), -CamBeta, vec3(1, 0, 0)) * rotate(mat4(1.0), -CamAlpha, vec3(0, 1, 0)) * translate(mat4(1.0), -CamPos);


    // Standard procedure to quit when the ESC key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    float tmp;
    if (glfwGetKey(window, GLFW_KEY_L)) {
        if (cameraAngle > 0) {
            printCordinates(cameraAngle - 360.0 * floor(cameraAngle / 360.0));
        }
        else {
            tmp = cameraAngle - 360.0 * (floor(cameraAngle / 360.0) + 1);
            printCordinates(360.0 - tmp);
        }
    }


    if (glfwGetKey(window, GLFW_KEY_P)) {
        spectatorMode = true;
    }

    if (glfwGetKey(window, GLFW_KEY_O)) {
        spectatorMode = false;
    }

    if (glfwGetKey(window, GLFW_KEY_K)) {
        if (cameraAngle > 0) {
            checkDoors(cameraPosition, cameraAngle - 360.0 * floor(cameraAngle / 360.0));
        }
        else {
            tmp = cameraAngle - 360.0 * (floor(cameraAngle / 360.0) + 1);
            checkDoors(cameraPosition, 360.0 + tmp);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_Y)) {
        isInsideCar = true;
    }

    // Here is where you actually update your uniforms
    mat4 M = perspective(radians(45.0f), Ar, 0.1f, 160.0f);
    M[1][1] *= -1;

    mat4 ViewPrj = M * Mv;
    mat4 baseTr = mat4(1.0f);

    // objects
    UniformBufferObject Ubo{};

    BlinnUniformBufferObject BlinnUbo{};

    float timeFactor = 0.040f;
    float cycleDuration = 24.0f; 
    float timeInCycle = fmod(cTime * timeFactor, cycleDuration); 
    float azimuthAngle = glm::radians((timeInCycle / cycleDuration) * 360.0f);

    float maxElevation = glm::radians(45.0f);
    float elevationAngle = maxElevation * sin((timeInCycle / cycleDuration) * glm::pi<float>());

    BlinnUbo.lightDir = glm::vec3(cos(elevationAngle) * cos(azimuthAngle), sin(elevationAngle), cos(elevationAngle) * sin(azimuthAngle));

    glm::vec4 dawnColor = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f); // Alba
    glm::vec4 dayColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Giorno
    glm::vec4 duskColor = glm::vec4(1.0f, 0.2f, 0.0f, 1.0f); // Tramonto
    glm::vec4 nightColor = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f); // Notte

    float normalizedTime = fmod(cTime * timeFactor, 1.0f);
    glm::vec4 interpolatedColor;

    if (normalizedTime < 0.15f) {
        // Da notte ad alba (15% del ciclo)
        float t = normalizedTime / 0.15f;
        interpolatedColor = glm::mix(nightColor, dawnColor, t);
    }
    else if (normalizedTime < 0.4f) {
        // Da alba a giorno (25% del ciclo)
        float t = (normalizedTime - 0.15f) / 0.25f;
        interpolatedColor = glm::mix(dawnColor, dayColor, t);
    }
    else if (normalizedTime < 0.6f) {
        // Da giorno a tramonto (20% del ciclo)
        float t = (normalizedTime - 0.4f) / 0.2f;
        interpolatedColor = glm::mix(dayColor, duskColor, t);
    }
    else if (normalizedTime < 0.85f) {
        // Da tramonto a notte (25% del ciclo)
        float t = (normalizedTime - 0.6f) / 0.25f;
        interpolatedColor = glm::mix(duskColor, nightColor, t);
    }
    else {
        // Notte (15% del ciclo)
        float t = (normalizedTime - 0.85f) / 0.15f;
        interpolatedColor = glm::mix(nightColor, nightColor, t);
    }

    BlinnUbo.lightColor = interpolatedColor;
    BlinnUbo.eyePos = glm::vec3(glm::inverse(ViewMatrix) * glm::vec4(0, 0, 0, 1));
    DS.map(currentImage, &BlinnUbo, 0);

    BlinnMatParUniformBufferObject blinnMatParUbo{};
    blinnMatParUbo.Power = 200.0;
    DS.map(currentImage, &blinnMatParUbo, 1);

    for (int i = 0; i < ComponentVector.size(); i++) {
     
      mat4 Transform = translate(mat4(1), ComponentVector[i].pos);
      Transform = scale(Transform, ComponentVector[i].scale);

      if (!ComponentVector[i].rot.empty()) {
          for (int j = 0; j < ComponentVector[i].rot.size(); j++) {
              Transform = rotate(Transform, radians(ComponentVector[i].angle[j]), ComponentVector[i].rot[j]);
          }
      }
      
      Ubo.mMat = Transform;
      Ubo.mvpMat = ViewPrj * Ubo.mMat;
      Ubo.nMat = inverse(transpose(Ubo.mMat));

      ComponentVector[i].DS.map(currentImage, &Ubo, 0);

    }



    //SHOP 
    spotLightUBO subo{};
    EmissionUniformBufferObject eubo{};
    for (int i = 0; i < 4; i++) {
        subo.lightPos[i] = Shop[23 + i].pos;
        subo.lightDir[i] = vec3(0.0, -1.0, 0.0);
        subo.lightColor[i] = vec3(0.6f, 0.6f, 0.6f);
    }
    subo.InOutDecayTarget.x = 0.90f;
    subo.InOutDecayTarget.y = 0.92f;
    subo.InOutDecayTarget.z = 2.0f;
    subo.InOutDecayTarget.w = 2.0f;
    subo.eyePos = CamPos;
    DSlight.map(currentImage, &subo, 0);

    int j = 0;
    for (; j < Shop.size() - 4; j++) {
        mat4 Transform = translate(mat4(1), Shop[j].pos);
        Transform = scale(Transform, Shop[j].scale);
        if (!Shop[j].rot.empty()) {
            for (int k = 0; k < Shop[j].rot.size(); k++) {
                Transform = rotate(Transform, radians(Shop[j].angle[k]), Shop[j].rot[k]);
            }
        }
        Ubo.mMat = Transform;
        Ubo.mvpMat = ViewPrj * Ubo.mMat;
        Ubo.nMat = inverse(transpose(Ubo.mMat));
        Shop[j].DS.map(currentImage, &Ubo, 0);
    }

    for (; j < Shop.size(); j++) {
        mat4 Transform = translate(mat4(1), Shop[j].pos);
        Transform = scale(Transform, Shop[j].scale);
        if (!Shop[j].rot.empty()) {
            for (int k = 0; k < Shop[j].rot.size(); k++) {
                Transform = rotate(Transform, radians(Shop[j].angle[k]), Shop[j].rot[k]);
            }
        }
        eubo.mvpMat = ViewPrj * Transform;
        Shop[j].DS.map(currentImage, &eubo, 0);
    }

    //APARTMENT
    ToonUniformBufferObject tubo{};
    tubo.angleDiff = 0.70f;
    tubo.angleSpec = 0.95f;
    tubo.eyePos = { 200.2, 3.0, 202.0 };
    tubo.eyePos.y = 2.2f;
    tubo.lightColor = vec3(0.5f, 0.5f, 0.5f);
    tubo.lightDir = vec3(0.0f, 1.0f, 0.0f);

    DStoonLight.map(currentImage, &tubo, 0);
    j = 0;
    for (; j < Apartment.size(); j++) {
        mat4 Transform = translate(mat4(1), Apartment[j].pos);
        Transform = scale(Transform, Apartment[j].scale);
        if (!Apartment[j].rot.empty()) {
            for (int k = 0; k < Apartment[j].rot.size(); k++) {
                Transform = rotate(Transform, radians(Apartment[j].angle[k]), Apartment[j].rot[k]);
            }
        }
        Ubo.mMat = Transform;
        Ubo.mvpMat = ViewPrj * Ubo.mMat;
        Ubo.nMat = inverse(transpose(Ubo.mMat));
        Apartment[j].DS.map(currentImage, &Ubo, 0);
    }

  }

  bool checkLimits(vec3 newCamPos) {
      bool result;
      if (currentScene == SHOP) {
          result = (newCamPos.z > 100.1 && newCamPos.z <= 105.5 && newCamPos.x < 105 && newCamPos.x >= 98.60);
          result = result && !(newCamPos.x > 102 && newCamPos.x < 105 && newCamPos.z > 104 && newCamPos.z < 105.5);
          return result;
      }
      return true;
  }

  void checkDoors(vec3 cameraPosition, float cameraAngle) {
      //Check porta negozio 
      if (checkSingleDoor(cameraPosition, cameraAngle, 7.5, 8.8, -12.8404, true))
          goTo(SHOP, { 100.0f, 1.0f, 104.0f });
      if (checkSingleDoor(cameraPosition, cameraAngle, 99.63, 100.86, 105, false))
          exit({ 7.0, 1.0, -12.0 });
      vec3 tmpcam = invertXZ(cameraPosition);
      if(checkSingleDoor(tmpcam, cameraAngle, -14.70f, -13.70f, 23.2f, true))
        goTo(APARTMENT, { 200.0f, 1.0f, 200.0f });
      if (checkSingleDoor(tmpcam, cameraAngle, 196.70f, 197.90f, 198.2f, true))
          exit({ 25.0, 1.0, -14.0 });
  }

  vec3 invertXZ(vec3 cam){
      vec3 tmp = vec3(cam.z, cam.y, cam.x);
      return tmp;
  }

  void goTo(Scene ty, vec3 cor) {
      CamPos = cor;
      currentScene = ty;
      RebuildPipeline();
  }

  void exit(vec3 c) {
      CamPos = c;
      currentScene = CITY;
      RebuildPipeline();
  }

  /*
    * Deve essere passato in ingresso la variabile "cameraPosition" e "cameraAngle" che sono presenti nella funzione updateUniformBuffer.
    * Le variabili x1,x2,z invece sono rispettivamente la coordinita più a sinistra dell'oggetto, più a destra (dimensioni del modello) e la sua profondità (posizione
    * in cui è rispetto asse Z).
    * Per avviare questo metodo devi immaginarti l'oggetto dritto, senza alcuna rotazione, prima di effettuare effettivamente il check infatti raddrizzo tutto.
    * Ecco spiegato il motivo di "modelRotation", mi serve per raddrizzare
    */
  bool checkSingleDoor(vec3 cameraPosition, float cameraAngle, float x1, float x2, float z, bool switchView) {
      //makeRight(cameraPosition, modelRotation, z); //DA FARE PIù AVANTI
      float Zmax, Zmin;
      if (switchView) {
          Zmax = cameraPosition.z;
          Zmin = z;
      }
      else {
          Zmax = z;
          Zmin = cameraPosition.z;
          if (cameraAngle > 180.0)
              cameraAngle = cameraAngle - 180.0;
          else
              cameraAngle = 360 + (cameraAngle - 180.0);
      }
      const float minDistance = 3;
      float distance, alpha, center, beta, halfSide, left, right;
      center = (x2 + x1) / 2;
      halfSide = (x2 - x1) / 2;
      distance = sqrt(pow(center - cameraPosition.x, 2) + pow(Zmin - Zmax, 2));
      /*
      cout << "Center: " << center << '\n';
      cout << ": " << cameraPosition.x << '\n';
      cout << "Zmin: " << Zmin << '\n';
      cout << "Zmax: " << Zmax << '\n';
      cout << "distance: " << distance << '\n';
      */
      if (distance < minDistance && cameraPosition.x >= x1 && cameraPosition.x <= x2 && Zmin < Zmax) {
          alpha = 60 - (Zmax - Zmin) / minDistance * 60;
         // cout << "ALPHA: " << alpha <<'\n';
          if (center < cameraPosition.x) {
              beta = alpha * (cameraPosition.x - center) / halfSide;
              left = alpha + beta;
              right = alpha - beta / 2;
          }
          else {
              beta = alpha * (-cameraPosition.x + center) / halfSide;
              left = alpha - beta;
              right = alpha + beta / 2;
          }
          //cout << "ANGOLO VA TRA: " << left << " - " << 360 - right << ", Angolo attuale: " << cameraAngle << '\n';
          return ((cameraAngle < left && cameraAngle >= 0) || (cameraAngle <= 360 && cameraAngle > (360 - right)));
      }
      return false;
  }



  void makeRight(vec3 cameraPosition, vec3 modelRotation, float z) {
      //DA FARE PIù AVANTI SE C'è TEMPO
  }

  void printCordinates(float cameraAngle){
      cout << "________________________________________________________________________________" << '\n';
      cout << "X: " << CamPos.x << ", Y: " << CamPos.y << ", Z: " << CamPos.z << ", CameraAngle: " << cameraAngle << "\n";
      cout << "________________________________________________________________________________" << '\n';
  }

};


int main() {
    ComputerGraphicsProject2024 app;

    try {
        app.run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}