// This has been adapted from the Vulkan tutorial
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

enum Scene { CITY, SHOP };

//SHOP
vector<Component> Shop = {
    //PAVIMENTO
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{100.0f, -1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{104.0f, -1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{100.0f, -1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", "textures/Textures.png", MGCG,{104.0f, -1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},

    //MURI
    //ALTO SINISTRA
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{98.0f, 1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{100.0f, 1.0f, 106.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0f,0.0f}}, {90.0f}},
    //ALTO DESTRA
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{106.0f, 1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{104.0f, 1.0f, 106.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0f,0.0f}}, {90.0f}},
    //BASSO DESTRA
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{104.0f, 1.0f, 98.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0f,0.0f}}, {90.0f}},
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{106.0f, 1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    //BASSO SINISTRA
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{98.0f, 1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
    {"models/Shop/wall_013_Mesh.290.mgcg", "textures/Wall_Shop.png", MGCG,{100.0f, 1.0f, 98.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0f,0.0f}}, {90.0f}},

    //TETTO
    {"models/Shop/floor_013_Mesh.331.mgcg", "textures/Textures.png", MGCG,{100.0f, 3.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_013_Mesh.331.mgcg", "textures/Textures.png", MGCG,{104.0f, 3.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_013_Mesh.331.mgcg", "textures/Textures.png", MGCG,{100.0f, 3.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_013_Mesh.331.mgcg", "textures/Textures.png", MGCG,{104.0f, 3.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},

    //ACCESSORI
    {"models/Shop/shop_003_Mesh.4875.mgcg", "textures/Textures.png", MGCG,{105.0f, -1.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_003_Mesh.4875.mgcg", "textures/Textures.png", MGCG,{103.0f, -1.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_004_Mesh.4923.mgcg", "textures/Textures.png", MGCG,{100.0f, 0.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_002_Mesh.5167.mgcg", "textures/Textures.png", MGCG,{104.0f, 0.0f, 105.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
    {"models/Shop/door_011_Mesh.116.mgcg", "textures/Textures.png",MGCG, {101.0f, -1.0f, 106.0f}, {1.3f, 1.3f, 1.3f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
    {"models/Shop/window_006_Mesh.654.mgcg", "textures/Textures.png", MGCG,{106.0f, 1.0f, 102.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Shop/window_006_Mesh.654.mgcg", "textures/Textures.png", MGCG,{98.0f, 1.0f, 102.0f}, {1.3f, 1.3f, 1.3f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},

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
    {"models/apartment_1_004.mgcg", "textures/Textures_City.png",MGCG, {4+3*8.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/apartment_1_003.mgcg", "textures/Textures_City.png",MGCG, {5+5*8.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}}, //001 or 003;

    
    {"models/park_002.mgcg", "textures/Textures_City.png", MGCG,{2+3*8.0f, 0.0f, -4-8*8.0f}, {1.0f, 1.0f, 1.0f}}
    

};
//    {"models/dwelling_004.mgcg", "textures/Textures_City.png", {0.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}}


struct spotLightUBO {
    alignas(16) vec3 lightDir[4];
    alignas(16) vec3 lightPos[4];
    alignas(16) vec3 lightColor[4];
    alignas(4) float cosIn;
    alignas(4) float cosOut;
    alignas(16) vec3 eyePos;
};

struct EmissionUniformBufferObject {
    alignas(16) mat4 mvpMat;
};

struct EmissionVertex {
    glm::vec3 pos;
    glm::vec2 UV;
};

class ComputerGraphicsProject2024 : public BaseProject {
protected:

    Scene currentScene = CITY;

  float Ar;

  DescriptorSetLayout DSL;
  Pipeline Pip;
  VertexDescriptor VDVertex;
  TextMaker txt;

  //SHOP
  DescriptorSetLayout DSLshop;
  Pipeline Pipshop;
  VertexDescriptor VDshop;

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
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(UniformBufferObject), 1},
          {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1} });
      DSLshop.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(UniformBufferObject), 1},
          {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
          {2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(spotLightUBO), 1} });
      DSLemission.init(this, {
            {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(EmissionUniformBufferObject), 1},
            {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1}
          });


      VDVertex.init(this, { {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX} }, {
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


      Pip.init(this, &VDVertex, "shaders/Vert.spv", "shaders/Frag.spv", { &DSL });
      Pipshop.init(this, &VDshop, "shaders/Shop/Vert.spv", "shaders/Shop/SpotLight.spv", { &DSLshop });
      PipEmission.init(this, &VDemission, "shaders/generalEmissionVert.spv", "shaders/generalEmissionFrag.spv", { &DSLemission });

      //METODO CHE INIZIALIZZA TUTTI I MODELLI E TEXTURE DELL'ARRAY DI ASSET
      for (int i = 0; i < ComponentVector.size(); i++) {
          ComponentVector[i].model.init(this, &VDVertex, ComponentVector[i].ObjPath, ComponentVector[i].type);
          ComponentVector[i].texture.init(this, ComponentVector[i].TexturePath);
      }
      
      //SHOP
      int j;
      for (j = 0; j < Shop.size()-4; j++) {
          Shop[j].model.init(this, &VDVertex, Shop[j].ObjPath, Shop[j].type);
          Shop[j].texture.init(this, Shop[j].TexturePath);
      }
      for (; j < Shop.size(); j++) {
          Shop[j].model.init(this, &VDemission, Shop[j].ObjPath, Shop[j].type);
          Shop[j].texture.init(this, Shop[j].TexturePath);
      }


      //DA CAMBIARE
  //    DPSZs.uniformBlocksInPool = 3;
      DPSZs.uniformBlocksInPool = ComponentVector.size() + Shop.size()*2;
      DPSZs.texturesInPool = ComponentVector.size() + Shop.size();
      DPSZs.setsInPool = ComponentVector.size() + Shop.size();

      cout << "Initializing text\n";
      //txt.init(this, &outText);

      cout << "Initialization completed!\n";
      cout << "Uniform Blocks in the Pool  : " << DPSZs.uniformBlocksInPool << "\n";
      cout << "Textures in the Pool        : " << DPSZs.texturesInPool << "\n";
      cout << "Descriptor Sets in the Pool : " << DPSZs.setsInPool << "\n";

      ViewMatrix = translate(mat4(1), -CamPos);
  }

  void pipelinesAndDescriptorSetsInit() {

    Pip.create();
    Pipshop.create();
    PipEmission.create();

    //METODO CHE INIZIALIZZA TUTTI I DESCRIPTOR SET
    int sizeCV = ComponentVector.size();
    for (int i = 0; i < sizeCV; i++) {
      ComponentVector[i].DS.init(this, &DSL, {&ComponentVector[i].texture});
    }
    int sizeSHOP, j;
    for (j = 0; j < Shop.size()-4; j++) {
        Shop[j].DS.init(this, &DSLshop, { &Shop[j].texture });
    }
    for (; j < Shop.size(); j++) {
        Shop[j].DS.init(this, &DSLemission, { &Shop[j].texture });
    }
  }

  void pipelinesAndDescriptorSetsCleanup() {

    Pip.cleanup();
    Pipshop.cleanup();
    PipEmission.cleanup();

    //CLEAN UP DI TUTTI I DESCRIPTOR SET
    for (int i = 0; i < ComponentVector.size(); i++) {
      ComponentVector[i].DS.cleanup();
    }
    for (int i = 0; i < Shop.size(); i++) {
        Shop[i].DS.cleanup();
    }

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

    DSLemission.cleanup();
    DSLshop.cleanup();
    DSL.cleanup();

    PipEmission.destroy();
    Pip.destroy();
    Pipshop.destroy();
  }

  void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {

    Pip.bind(commandBuffer);
    
    for (int i = 0; i < ComponentVector.size(); i++) {

      ComponentVector[i].model.bind(commandBuffer);
      ComponentVector[i].DS.bind(commandBuffer, Pip, 0, currentImage);

      // The actual draw call.
      vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(ComponentVector[i].model.indices.size()), 1, 0, 0, 0);
    }

    int j;
    Pipshop.bind(commandBuffer);
    for (j= 0; j < Shop.size()-4; j++) {
        Shop[j].model.bind(commandBuffer);
        Shop[j].DS.bind(commandBuffer, Pipshop, 0, currentImage);
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
    }
    PipEmission.bind(commandBuffer);
    for (; j < Shop.size(); j++) {
        Shop[j].model.bind(commandBuffer);
        Shop[j].DS.bind(commandBuffer, PipEmission, 0, currentImage);
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
    }
  }

  void updateUniformBuffer(uint32_t currentImage) {

    
    float deltaT, cameraAngle = 0.0, movX, movZ;
    vec3 m = vec3(0.0f), r = vec3(0.0f), cameraPosition = { 0.0,0.0,0.0 }, CamPosOld;
    bool fire = false;

    getSixAxis(deltaT, m, r, fire);

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
        subo.lightPos[i].y = 1.7f;
        subo.lightDir[i] = vec3(0.0, -1.0, 0.0);
        subo.lightColor[i] = vec3(0.6f, 0.6f, 0.6f);
    }
    subo.cosIn = 0.45;
    subo.cosOut = 0.50;
    subo.eyePos = CamPos;
    int j=0;
    
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
        Shop[j].DS.map(currentImage, &subo, 2);
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
      //DA CAMBIARE IN UN FOR O QUALCOSA DI SIMILE SE DIVENTANO TANTI OGGETTI

      //Check porta negozio 
      if (checkSingleDoor(cameraPosition, cameraAngle, 7.5, 8.8, -12.8404, true))
          goToShop();
      if (checkSingleDoor(cameraPosition, cameraAngle, 99.63, 100.86, 105, false))
          exitShop();
  }

  void goToShop() {
      CamPos = { 100.0, 1.0, 104.0 };
      currentScene = SHOP;
  }

  void exitShop() {
      CamPos = { 7.0, 1.0, -12.0 };
      currentScene = CITY;
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
      if (distance < minDistance && cameraPosition.x >= x1 && cameraPosition.x <= x2 && Zmin < Zmax) {
          alpha = 60 - (Zmax - Zmin) / minDistance * 60;
          cout << "ALPHA: " << alpha <<'\n';
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
          cout << "ANGOLO VA TRA: " << left << " - " << 360 - right << ", Angolo attuale: " << cameraAngle << '\n';
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