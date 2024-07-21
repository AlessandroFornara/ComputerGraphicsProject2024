// This has been adapted from the Vulkan tutorial
#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"
using namespace std;
using namespace glm;

vector<SingleText> outText = {
  {1, {"Press H to see the command list"}, 0, 0},
  {6, {"Press L to print coordinates", 
  "Press P to enter spectator mode", 
  "Press O to exit spectator mode", 
  "Press K to check doors / enter car", 
  "Press J to exit car",
  "Press G to close this text"}, 
  0, 0},
  };

struct MatricesUniformBufferObject {
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


struct EmissionColorUniformBuffer {
    alignas(16) vec4 color;
};


struct EmissionVertex {
    alignas(16) vec3 pos;
    alignas(16) vec2 UV;
};

struct BlinnUniformBufferObject {
    alignas(16) vec3 lightDir;
    alignas(16) vec4 lightColor;
    alignas(16) vec3 eyePos;
};

struct BlinnMatParUniformBufferObject {
    alignas(4)  float Power;
};

struct ApartmentUniBuffer {
    alignas(16) vec3 lightDir;
    alignas(16) vec3 lightColor;
    alignas(16) vec3 lightPos;
    alignas(16) vec3 eyePos;
};

struct Component {
  const string ObjPath;
  const string TexturePath;
  ModelType type;
  vec3 pos;
  const vec3 scale;
  const std::vector<vec3> rot;
  std::vector<float> angle;
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
/*   //PAVIMENTO
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
*/
    {"models/Apartment/tv_wall_003_Mesh.184.mgcg", "textures/Textures.png", MGCG,{203.0f, -1.0f, 198.5f}, {1.2f, 1.2f, 1.2f}, {}, {}},
    {"models/Apartment/flower_010_Mesh.287.mgcg", "textures/Textures.png", MGCG,{200.f, -1.0f, 203.0f}, {1.2f, 1.2f, 1.2f}, {}, {}},
    {"models/Apartment/lamp_018_Mesh.6631.mgcg", "textures/Textures.png", MGCG,{202.0f, 3.0f, 202.0f}, {2.0f, 2.0f, 2.0f}, {}, {}},
    {"models/Apartment/Sphere.obj", "textures/Lamp.png", OBJ, {202.0f, 2.0f, 202.0f}, {0.15f, 0.15f, 0.15f}, {}, {}},
       
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


std::vector<Component> CityComponents = {
    {"models/apecar.obj", "textures/apecar.png",OBJ, {0.0f, 0.6f, -3 * 8.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}}, // DRIVEABLE CAR MODEL;
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
    {"models/transport_sport_001_transport_sport_001.001.mgcg", "textures/Textures_City.png",MGCG, {-8.0f, 0.0f, -3 * 8.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/landscape_entertainments_007.mgcg", "textures/Textures_City.png",MGCG, {4 + 5 * 8.0f, 0.0f, 4.0f}, {1.0f, 1.0f, 1.0f}}, //tennis
    {"models/landscape_entertainments_003.mgcg", "textures/Textures_City.png", MGCG,{4+5*8.0f, 0.0f, -20.0f}, {1.0f, 1.0f, 1.0f}}, //gym
    {"models/landscape_entertainments_008.mgcg", "textures/Textures_City.png", MGCG,{20+5*8.0f, 0.0f, 4.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {-90.0f}}, //football
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
/*
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
    {"models/park_006.mgcg", "textures/Textures_City.png", MGCG, { 20 + 3 * 8.0f, 0.0f, -4 - 8 * 8.0f }, { 1.0f, 1.0f, 1.0f }},
*/
    {"models/Shop/Sphere.obj", "textures/Lamp.png", OBJ,{0.0f, 20.0f, 0.0f}, {3.0f, 3.0f, 3.0f}, {}, {} }
    
};

class ComputerGraphicsProject2024 : public BaseProject {
protected:

  Scene currentScene = CITY;

  float Ar;
  TextMaker outTxt;

  DescriptorSetLayout DSLMatricesAndTextures;
  VertexDescriptor VDWorld;

  //CITY
  DescriptorSetLayout DSLSunLight;
  DescriptorSet DSSunLight;
  Pipeline PipCity;

  //SHOP
  DescriptorSetLayout DSLShopLight;
  DescriptorSet DSlight;
  Pipeline PipShop;

  //APARTMENT
  DescriptorSetLayout DSLApartmentLight;
  DescriptorSet DSApartmentLight;
  Pipeline PipApartment;

  //ONLY EMISSION
  DescriptorSetLayout DSLemission;
  Pipeline PipEmission;
  VertexDescriptor VDemission;

  vec3 CamPos = vec3(0.0, 1.0, -8.0);
  vec3 Cam1Pos;
  float CamAlpha = 0.0f, CamBeta = 0.0f;
  float CamRoll = 0.0f;
  mat4 ViewMatrix;

  bool spectatorMode = false;
  bool cityWithLimits = false;
  bool thirdViewCar = true;

  //car set up
  vec3 CarPos = vec3(0.0f, 0.6f, -24.0f);
  bool isInsideCar = false;
  const float CAR_SPEED = 1.0f;
  const float MAX_CAR_SPEED = 15.0f;

  bool autoTime = true;
  const float ROT_SPEED = radians(120.0f);
  const float WALK_SPEED = 2.5f;
  float sunAng = 0.0f;
  const float sunRotSpeed = 3.3333f;
  float moveSpeed;
  float Yaw = radians(0.0f);
  float CamPitch = radians(20.0f);
  float CamYaw = M_PI;
  bool showCommands = false;

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

      DSLMatricesAndTextures.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(MatricesUniformBufferObject), 1},
          {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1} });
      DSLSunLight.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS, sizeof(BlinnUniformBufferObject), 1},
          {1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(BlinnMatParUniformBufferObject), 1}
          });
      DSLShopLight.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL, sizeof(spotLightUBO), 1 } }
      );
      DSLApartmentLight.init(this, {
          {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL, sizeof(ApartmentUniBuffer), 1 }
      });

      DSLemission.init(this, {
            {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL, sizeof(EmissionUniformBufferObject), 1},
            {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
            {2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(EmissionColorUniformBuffer), 1}
          });


      VDWorld.init(this, { {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX} }, {
             {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),sizeof(vec3), POSITION},
             {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),sizeof(vec3), NORMAL},
             {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(vec2), UV}
          });
      VDemission.init(this, { {0, sizeof(EmissionVertex),VK_VERTEX_INPUT_RATE_VERTEX} }, {
          { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(EmissionVertex, pos),sizeof(vec3), POSITION },
          { 0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(EmissionVertex, UV), sizeof(vec2), UV } }
          );


      PipCity.init(this, &VDWorld, "shaders/Vert.spv", "shaders/Frag.spv", { &DSLSunLight, &DSLMatricesAndTextures });
      PipShop.init(this, &VDWorld, "shaders/Shop/Vert.spv", "shaders/Shop/SpotLight.spv", { &DSLShopLight, &DSLMatricesAndTextures });
      PipEmission.init(this, &VDemission, "shaders/generalEmissionVert.spv", "shaders/generalEmissionFrag.spv", { &DSLemission });
      PipApartment.init(this, &VDWorld, "shaders/Apartment/Vert.spv", "shaders/Apartment/Frag.spv", { &DSLApartmentLight, &DSLMatricesAndTextures });

      //City
      int i = 0;
      for (; i < CityComponents.size() - 1; i++) {
          CityComponents[i].model.init(this, &VDWorld, CityComponents[i].ObjPath, CityComponents[i].type);
          CityComponents[i].texture.init(this, CityComponents[i].TexturePath);
      }
      CityComponents[i].model.init(this, &VDemission, CityComponents[i].ObjPath, CityComponents[i].type);
      CityComponents[i].texture.init(this, CityComponents[i].TexturePath);
      
      //SHOP
      int j;
      for (j = 0; j < Shop.size()-4; j++) {
          Shop[j].model.init(this, &VDWorld, Shop[j].ObjPath, Shop[j].type);
          Shop[j].texture.init(this, Shop[j].TexturePath);
      }
      for (; j < Shop.size(); j++) {
          Shop[j].model.init(this, &VDemission, Shop[j].ObjPath, Shop[j].type);
          Shop[j].texture.init(this, Shop[j].TexturePath);
      }

      //APARTMENT
      for (j = 0; j < Apartment.size()-1; j++) {
          Apartment[j].model.init(this, &VDWorld, Apartment[j].ObjPath, Apartment[j].type);
          Apartment[j].texture.init(this, Apartment[j].TexturePath);
      }
      Apartment[j].model.init(this, &VDemission, Apartment[j].ObjPath, Apartment[j].type);
      Apartment[j].texture.init(this, Apartment[j].TexturePath);

      //DA CAMBIARE
      DPSZs.uniformBlocksInPool = CityComponents.size() * 2 + Shop.size() + 2 + Apartment.size() + 1;
      DPSZs.texturesInPool = CityComponents.size() + Shop.size() + Apartment.size();
      DPSZs.setsInPool = CityComponents.size() + Shop.size() + 3 + Apartment.size() + 1;

      cout << "Initializing text\n";
      outTxt.init(this, &outText);

      cout << "Initialization completed!\n";
      cout << "Uniform Blocks in the Pool  : " << DPSZs.uniformBlocksInPool << "\n";
      cout << "Textures in the Pool        : " << DPSZs.texturesInPool << "\n";
      cout << "Descriptor Sets in the Pool : " << DPSZs.setsInPool << "\n";

      ViewMatrix = translate(mat4(1), -CamPos);
  }

  void pipelinesAndDescriptorSetsInit() {

    PipCity.create();
    PipShop.create();
    PipEmission.create();
    PipApartment.create();

    //CITY
    DSSunLight.init(this, &DSLSunLight, {});
    int sizeCV = CityComponents.size();
    for (int i = 0; i < sizeCV - 1; i++) {
      CityComponents[i].DS.init(this, &DSLMatricesAndTextures, {&CityComponents[i].texture});
    }
    CityComponents[sizeCV - 1].DS.init(this, &DSLemission, { &CityComponents[sizeCV - 1].texture });

    //SHOP
    int sizeSHOP, j;
    for (j = 0; j < Shop.size() - 4; j++) {
        Shop[j].DS.init(this, &DSLMatricesAndTextures, { &Shop[j].texture });
    }
    for (; j < Shop.size(); j++) {
        Shop[j].DS.init(this, &DSLemission, { &Shop[j].texture });
    }
    DSlight.init(this, &DSLShopLight, {});

    //APARTMENT
    for (j = 0; j < Apartment.size()-1; j++) {
        Apartment[j].DS.init(this, &DSLMatricesAndTextures, { &Apartment[j].texture });
    }
    Apartment[j].DS.init(this, &DSLemission, { &Apartment[j].texture });
    DSApartmentLight.init(this, &DSLApartmentLight, {});

    outTxt.pipelinesAndDescriptorSetsInit();
  }

  void pipelinesAndDescriptorSetsCleanup() {

    PipCity.cleanup();
    PipShop.cleanup();
    PipEmission.cleanup();
    PipApartment.cleanup();

    //CITY
    for (int i = 0; i < CityComponents.size(); i++) {
      CityComponents[i].DS.cleanup();
    }
    DSSunLight.cleanup();

    //SHOP
    for (int i = 0; i < Shop.size(); i++) {
        Shop[i].DS.cleanup();
    }
    DSlight.cleanup();

    //APARTMENT
    for (int i = 0; i < Apartment.size(); i++) {
        Apartment[i].DS.cleanup();
    }
    DSApartmentLight.cleanup();

    outTxt.pipelinesAndDescriptorSetsCleanup();
  }

  void localCleanup() {

    //CITY
    for (int i = 0; i < CityComponents.size(); i++) {
      CityComponents[i].model.cleanup();
      CityComponents[i].texture.cleanup();
    }

    //SHOP
    for (int i = 0; i < Shop.size(); i++) {
        Shop[i].model.cleanup();
        Shop[i].texture.cleanup();
    }

    //APARTMENT
    for (int i = 0; i < Apartment.size(); i++) {
        Apartment[i].model.cleanup();
        Apartment[i].texture.cleanup();
    }

    DSLSunLight.cleanup();
    DSLemission.cleanup();
    DSLMatricesAndTextures.cleanup();
    DSLShopLight.cleanup();
    DSLApartmentLight.cleanup();

    PipEmission.destroy();
    PipCity.destroy();
    PipShop.destroy();
    PipApartment.destroy();

    outTxt.localCleanup();
  }

  void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
      //CITY
      if (currentScene == CITY) {
          PipCity.bind(commandBuffer);

          DSSunLight.bind(commandBuffer, PipCity, 0, currentImage);
          int i = 0;
          for (; i < CityComponents.size() - 1; i++) {

              CityComponents[i].model.bind(commandBuffer);
              CityComponents[i].DS.bind(commandBuffer, PipCity, 1, currentImage);

              // The actual draw call.
              vkCmdDrawIndexed(commandBuffer,
                  static_cast<uint32_t>(CityComponents[i].model.indices.size()), 1, 0, 0, 0);
          }
          PipEmission.bind(commandBuffer);
          CityComponents[i].model.bind(commandBuffer);
          CityComponents[i].DS.bind(commandBuffer, PipEmission, 0, currentImage);
          vkCmdDrawIndexed(commandBuffer,
              static_cast<uint32_t>(CityComponents[i].model.indices.size()), 1, 0, 0, 0);
      }//SHOP
      else if (currentScene == SHOP) {
          int j;
          PipShop.bind(commandBuffer);
          DSlight.bind(commandBuffer, PipShop, 0, currentImage);
          for (j = 0; j < Shop.size() - 4; j++) {
              Shop[j].model.bind(commandBuffer);
              Shop[j].DS.bind(commandBuffer, PipShop, 1, currentImage);
              vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
          }
          PipEmission.bind(commandBuffer);
          for (; j < Shop.size(); j++) {
              Shop[j].model.bind(commandBuffer);
              Shop[j].DS.bind(commandBuffer, PipEmission, 0, currentImage);
              vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
          }
      }//APARTMENT
      else if (currentScene == APARTMENT) {
          int j;
          PipApartment.bind(commandBuffer);
          DSApartmentLight.bind(commandBuffer, PipApartment, 0, currentImage);
          for (j = 0; j < Apartment.size() - 1; j++) {
              Apartment[j].model.bind(commandBuffer);
              Apartment[j].DS.bind(commandBuffer, PipApartment, 1, currentImage);
              vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Apartment[j].model.indices.size()), 1, 0, 0, 0);
          }
          PipEmission.bind(commandBuffer);
          Apartment[j].model.bind(commandBuffer);
          Apartment[j].DS.bind(commandBuffer, PipEmission, 0, currentImage);
          vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Apartment[j].model.indices.size()), 1, 0, 0, 0);
      }

      if (!showCommands)
          outTxt.populateCommandBuffer(commandBuffer, currentImage, 0);
      else
          outTxt.populateCommandBuffer(commandBuffer, currentImage, 1);
  }

  void updateUniformBuffer(uint32_t currentImage) {
    float deltaT, cameraAngle = 0.0;
    float rotAngleCar = 0.0f;
    float rotSpeed = ROT_SPEED;

    vec3 m = vec3(0.0f);
    vec3 r = vec3(0.0f);
    vec3 cameraPosition = { 0.0,0.0,0.0 };
    vec3 CarPosOld, tmpCarPos;
    vec3 CamPosOld, tmpCamPos;
    bool fire = false;

    getSixAxis(deltaT, m, r, fire);

    //CamPitch = radians(20.0f);
    //CamYaw = M_PI;
    static float CamDist = 10.0f;
    static float CamRoll = 0.0f;
    const vec3 CamTargetDelta = vec3(0, 2, 0);
    static float dampedVel = 0.0f;
    vec3 Cam1stPos = vec3(0.0f, 1.0f, -0.4f);

    if (!isInsideCar)
        moveSpeed = WALK_SPEED;

    if(!isInsideCar){
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
            moveSpeed = moveSpeed * 2;
    }
    else {
        moveSpeed = accelerateCar(moveSpeed, m.z);
    }

    mat4 Mv;

    CamAlpha = CamAlpha - rotSpeed * deltaT * r.y;
    CamBeta = CamBeta - rotSpeed * deltaT * r.x;
    CamBeta = CamBeta < radians(-90.0f) ? radians(-90.0f) : (CamBeta > radians(90.0f) ? radians(90.0f) : CamBeta);

    vec3 ux = rotate(mat4(1.0f), CamAlpha, vec3(0, 1, 0)) * vec4(1, 0, 0, 1);
    vec3 uz = rotate(mat4(1.0f), CamAlpha, vec3(0, 1, 0)) * vec4(0, 0, -1, 1);
    vec3 uy = rotate(mat4(1.0f), CamBeta, vec3(1, 0, 1)) * vec4(0, 1, 0, 1);
    
    tmpCamPos = CamPos + moveSpeed * m.x * ux * deltaT;
    tmpCamPos = tmpCamPos - moveSpeed * m.z * uz * deltaT;

    if (checkLimits(tmpCamPos)) {
        CamPos = tmpCamPos;
    }

    if (spectatorMode && currentScene == CITY) {
        CamPos = CamPos + moveSpeed * m.y * uy * deltaT;
    }
    else if(!isInsideCar) {
        CamPos.y = vec3(0, 1, 0).y;
    }
    else if(isInsideCar) {
        float carCurrAngle = CityComponents[0].angle[0];
        m.z = -m.z;
        tmpCarPos = CarPos - moveSpeed * m.z * vec3(sin(radians(carCurrAngle)), 0, cos(radians(carCurrAngle))) * deltaT;
        rotAngleCar = -m.x;

        if (m.z < 0.0f)
            rotAngleCar = -rotAngleCar;
        
        if (checkLimits(tmpCarPos)) {
            CarPos = tmpCarPos;
        }

        CityComponents[0].pos.x = CarPos.x;
        CityComponents[0].pos.y = CarPos.y;
        CityComponents[0].pos.z = CarPos.z;
        CityComponents[0].angle[0] += rotAngleCar;

        if (thirdViewCar) {
            CamYaw += rotSpeed * deltaT * r.y;
            CamPitch -= rotSpeed * deltaT * r.x;
            CamRoll -= rotSpeed * deltaT * r.z;
            CamDist -= moveSpeed * deltaT * m.y;

            CamYaw = (CamYaw < 0.0f ? 0.0f : (CamYaw > 2 * M_PI ? 2 * M_PI : CamYaw));
            CamPitch = (CamPitch < 0.0f ? 0.0f : (CamPitch > M_PI_2 - 0.01f ? M_PI_2 - 0.01f : CamPitch));
            CamRoll = (CamRoll < -M_PI ? -M_PI : (CamRoll > M_PI ? M_PI : CamRoll));
            CamDist = (CamDist < 7.0f ? 7.0f : (CamDist > 15.0f ? 15.0f : CamDist));

            vec3 CamTarget = CarPos;
            //Yaw is useless;
            CamPos = CamTarget + vec3(rotate(mat4(1), Yaw + CamYaw, vec3(0, 1, 0)) * rotate(mat4(1), -CamPitch, vec3(1, 0, 0)) * vec4(0, 0, CamDist, 1));
        }
        else {
            CamYaw -= rotSpeed * deltaT * r.y;
            CamPitch -= rotSpeed * deltaT * r.x;
            CamRoll -= rotSpeed * deltaT * r.z;

            // -180° <= CamYaw <= 540°;
            CamYaw = (CamYaw < -M_PI ? -M_PI : (CamYaw > 2.5f * M_PI ? 2.5f * M_PI : CamYaw));
            CamPitch = (CamPitch < -0.25 * M_PI ? -0.25 * M_PI : (CamPitch > 0.25 * M_PI ? 0.25 * M_PI : CamPitch));
            CamRoll = (CamRoll < -M_PI ? -M_PI : (CamRoll > M_PI ? M_PI : CamRoll));
            CamPos = CarPos + vec3(rotate(mat4(1.0f), radians(CityComponents[0].angle[0]), vec3(0.0f, 1.0f, 0.0f)) * vec4(Cam1stPos, 1.0f));
        }

    }

    cameraPosition = CamPos;
    cameraAngle = cameraAngle + (360.0 * (CamAlpha)) / (2*M_PI);

    // Standard procedure to quit when the ESC key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_H)) {
        showCommands = true;
        RebuildPipeline();
    }
    if (glfwGetKey(window, GLFW_KEY_G)) {
        showCommands = false;
        RebuildPipeline();
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
        if (cameraAngle > 0 && !isInsideCar) {
            checkDoors(cameraPosition, cameraAngle - 360.0 * floor(cameraAngle / 360.0));
        }
        else {
            if(!isInsideCar){
                tmp = cameraAngle - 360.0 * (floor(cameraAngle / 360.0) + 1);
                checkDoors(cameraPosition, 360.0 + tmp);
            }
        }
        if (isInsideCar == false) {
            if (isNearCar()) {
                enterCar();
                moveSpeed = CAR_SPEED;
                cityWithLimits = true;
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_J)) {
        if (isInsideCar == true) {
            exitCar();
            moveSpeed = WALK_SPEED;
            cityWithLimits = false;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_V)) {
        thirdViewCar = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_B)) {
        thirdViewCar = false;
    }


    Mv = rotate(mat4(1.0), -CamBeta, vec3(1, 0, 0)) * rotate(mat4(1.0), -CamAlpha, vec3(0, 1, 0)) * translate(mat4(1.0), -CamPos);
    ViewMatrix = Mv;
    // Here is where you actually update your uniforms
    mat4 M = perspective(radians(45.0f), Ar, 0.1f, 160.0f);
    M[1][1] *= -1;
    mat4 ViewPrj;
    
    if (!isInsideCar) {
        ViewPrj = M * Mv;
    }
    else {
        ViewPrj = updateViewMatrix();
        //ViewPrj = MakeViewProjectionLookInDirection(CamPos, Yaw + CamYaw, CamPitch, CamRoll, radians(90.0f), Ar, 0.1f, 500.0f);
    }
    mat4 baseTr = mat4(1.0f);

    if (currentScene == CITY) {
        buildCity(currentImage, ViewPrj, deltaT);
    }
    else if (currentScene == SHOP) {
        buildShop(currentImage, ViewPrj);
    }
    else if (currentScene == APARTMENT) {
        buildApartment(currentImage, ViewPrj);
    }
  }

  float accelerateCar(float speed, float acc) {
      float speed2;
      if (acc < 0)
          acc = -acc;
      if (acc != 0) {
        speed2 = speed + acc * 0.1f;
        if (speed2 > MAX_CAR_SPEED)
            speed2 = MAX_CAR_SPEED;
        else if(speed2 < CAR_SPEED)
            speed2 = CAR_SPEED;
      }
      else {
          speed2 = speed - 0.3f;
          if (speed2 < CAR_SPEED)
              speed2 = CAR_SPEED;
      }
      return speed2;
  }

  void exitCar() {
      isInsideCar = false;
      thirdViewCar = true;
      CamPos = CarPos + (-2.0f, 0.0f, -2.0f);
      CamPos.y = 1.0f;
  }

  bool isNearCar() {
      float dist;
      dist = distance(CamPos, CarPos);
      return dist < 2.0f;
  }

  void enterCar() {
      isInsideCar = true;
//      CamPos = CarPos + vec3(0.0f, 2.0f, -5.0f);
  }

  mat4 updateViewMatrix() {
      if (isInsideCar) {
          if (thirdViewCar)
              return MakeViewProjectionLookAt(CamPos, CarPos, vec3(0, 1, 0), CamRoll, radians(90.0f), Ar, 0.1f, 500.0f);
          else
              return MakeViewProjectionLookInDirection(CamPos, Yaw + CamYaw, CamPitch, CamRoll, radians(90.0f), Ar, 0.1f, 500.0f);
      }
  }

  mat4 MakeViewProjectionLookAt(vec3 Pos, vec3 Target, vec3 Up, float Roll, float FOVy, float Ar, float nearPlane, float farPlane) {

      mat4 M = perspective(FOVy, Ar, nearPlane, farPlane);
      M[1][1] *= -1;

      M = M *
          rotate(mat4(1.0), -Roll, vec3(0, 0, 1)) *
          lookAt(Pos, Target, Up);
      return M;
  }

  mat4 MakeViewProjectionLookInDirection(vec3 Pos, float Yaw, float Pitch, float Roll, float FOVy, float Ar, float nearPlane, float farPlane) {

      // Mvp = Mprj * Mv
      mat4 M = perspective(FOVy, Ar, nearPlane, farPlane);
      M[1][1] *= -1;

      M = M *
          rotate(mat4(1.0), -Roll, vec3(0, 0, 1)) *
          rotate(mat4(1.0), -Pitch, vec3(1, 0, 0)) *
          rotate(mat4(1.0), -Yaw, vec3(0, 1, 0)) *
          translate(mat4(1.0), -Pos) *
          mat4(1.0f);

      return M;
  }

  bool checkLimits(vec3 newPos) {
      bool result;
      if (currentScene == SHOP) {
          result = (newPos.z > 100.1 && newPos.z <= 105.5 && newPos.x < 105 && newPos.x >= 98.60);
          result = result && !(newPos.x > 102 && newPos.x < 105 && newPos.z > 104 && newPos.z < 105.5);
          return result;
      }
      else if (currentScene == APARTMENT) {
         result = (newPos.z > 197 && newPos.z <= 205 && newPos.x > 198 && newPos.x <= 205);
         result = result && !(newPos.x > 200 && newPos.x < 205 && newPos.z > 197 && newPos.z < 198);
         return result;
      }
      else if (currentScene == CITY && cityWithLimits) {
          result = (newPos.x >= -1.77 && newPos.x <= 65.75 && newPos.z <= -6.24 && newPos.z >= -9.71) //1
              || (newPos.x >= 13.50 && newPos.x <= 17.8 && newPos.z <= -9.71 && newPos.z >= -30.3)//2
              || (newPos.x >= -17.5 && newPos.x <= 65.8 && newPos.z <= -30.3 && newPos.z >= -41.7) //3
              || (newPos.x >= 15 && newPos.x <= 18 && newPos.z <= -41.7 && newPos.z >= -78.0) //4
              || (newPos.x >= 54.10 && newPos.x <= 65.8 && newPos.z <= -41.7 && newPos.z >= -78.0) //6
              || (newPos.x >= -17.5 && newPos.x <= -6.2 && newPos.z <= -41.7 && newPos.z >= -78.0) //5
              || (newPos.x >= -17.5 && newPos.x <= 65.8 && newPos.z <= -78.0 && newPos.z >= -89.95) //7
              || (newPos.x >= -2.0f && newPos.x <= 2.0f && newPos.z >= -78.0 && newPos.z < -77.0) //8
              || (newPos.x >= -3.6f && newPos.x <= 11.6f && newPos.z >= -77.0f && newPos.z <= -61.58f) //9
              || (newPos.x >= 12.5f && newPos.x <= 13.5f && newPos.z >= -27.0f && newPos.z <= -21.0f) //10
              || (newPos.x >= -16.0f && newPos.x < 12.5f && newPos.z >= -28.0f && newPos.z <= -21.0f); //11
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
      vec3 tmpcam;
      tmpcam = invertXZ(cameraPosition);
      if (checkSingleDoor(tmpcam, (cameraAngle-90.0 > 0.0) ? (cameraAngle-90.0) : 360.0 +(cameraAngle-90.0), -15.0f, -12.0f, 23.0f, true)) {
          goTo(APARTMENT, { 198.5, 1.0f, 198.5f });
      }
      if (checkSingleDoor(tmpcam, (cameraAngle - 90.0 > 0.0) ? (cameraAngle - 90.0) : 360.0 + (cameraAngle - 90.0), 196.70f, 197.90f, 198.2f, true))
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
      cout << "X: " << cameraPosition.x << '\n';
      cout << "Zmin: " << Zmin << '\n';
      cout << "Zmax: " << Zmax << '\n';
      cout << "distance: " << distance << '\n';
      */
      if (distance < minDistance && cameraPosition.x >= x1 && cameraPosition.x <= x2 && Zmin < Zmax) {
          alpha = 60 - (Zmax - Zmin) / minDistance * 60;
          //cout << "ALPHA: " << alpha <<'\n';
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

  void fillUniformBuffer(int start, int end, vector<Component> vec, mat4 ViewPrj, int currentImage, vec3 traslation) {
      MatricesUniformBufferObject ubo{};
      for (int i = start; i < end; i++) {
          mat4 transform = translate(mat4(1), vec[i].pos + traslation);
          transform = scale(transform, vec[i].scale);
          if (!vec[i].rot.empty()) {
              for (int k = 0; k < vec[i].rot.size(); k++) {
                  transform = rotate(transform, radians(vec[i].angle[k]), vec[i].rot[k]);
              }
          }
          ubo.mMat = transform;
          ubo.mvpMat = ViewPrj * ubo.mMat;
          ubo.nMat = inverse(transpose(ubo.mMat));
          vec[i].DS.map(currentImage, &ubo, 0);
      }
  }

  void fillEmissionBuffer(int start, int end, vector<Component> vec, mat4 ViewPrj, int currentImage, vec3 traslation, bool flag, vec4 colorLight) {
      EmissionUniformBufferObject eubo{};
      EmissionColorUniformBuffer ecubo{};
      for (int j = start; j < end; j++) {
          mat4 transform = translate(mat4(1), vec[j].pos + traslation);
          transform = scale(transform, vec[j].scale);
          if (!vec[j].rot.empty()) {
              for (int k = 0; k < vec[j].rot.size(); k++) {
                  transform = rotate(transform, radians(vec[j].angle[k]), vec[j].rot[k]);
              }
          }
          eubo.mvpMat = ViewPrj * transform;
          if (flag) {
              ecubo.color = colorLight;
              ecubo.color.w = 1.0f;
          }
          else
              ecubo.color = vec4(1.0);

          vec[j].DS.map(currentImage, &eubo, 0);
          vec[j].DS.map(currentImage, &ecubo, 2);
      }
  }


  void buildApartment(int currentImage, mat4 ViewPrj) {
      ApartmentUniBuffer tubo{};

      tubo.lightColor = vec3(0.5f, 0.5f, 0.5f);
      tubo.lightDir = vec3(0.0f, -1.0f, 0.0f);
      tubo.lightPos = vec3(202.0f, 2.0f, 202.0f);
      tubo.eyePos = CamPos;
      DSApartmentLight.map(currentImage, &tubo, 0);

      fillUniformBuffer(0, Apartment.size() - 1, Apartment, ViewPrj, currentImage, vec3(0.0f));

      fillEmissionBuffer(Apartment.size() - 1, Apartment.size(), Apartment, ViewPrj, currentImage, vec3(0.0f), false, vec4(0.0));
  }

  void buildShop(int currentImage, mat4 ViewPrj) {
      //SHOP 
      spotLightUBO subo{};
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

      fillUniformBuffer(0, Shop.size() - 4, Shop, ViewPrj, currentImage, vec3(0.0f));

      fillEmissionBuffer(Shop.size() - 4, Shop.size(), Shop, ViewPrj, currentImage, vec3(0.0f), false, vec4(0.0));
  }

  void buildCity(int currentImage, mat4 ViewPrj, float deltaT) {
      BlinnUniformBufferObject BlinnUbo{};

      if (autoTime) {
          sunAng = fmod(sunAng + deltaT * sunRotSpeed, 360.0f);
      }

      float x, y, z;
      float r = 100.0f;
      x = 26.5852f + r * cos(radians(sunAng)) * cos(radians(45.0f)); // Inclinazione di 45 gradi per simulare un percorso ellittico
      y = r * sin(radians(sunAng)) * sin(radians(45.0f)); // La componente y varia tra -r/2 e r/2
      z = -35.3748f + r * cos(radians(sunAng)) * sin(radians(45.0f)); // Inclinazione di 45 gradi per simulare un percorso ellittico
      BlinnUbo.lightDir = vec3(x, y, z);

      vec4 dawnColor = vec4(1.0f, 0.5f, 0.0f, 1.0f); // Alba
      vec4 dayColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); // Giorno
      vec4 duskColor = vec4(1.0f, 0.2f, 0.0f, 1.0f); // Tramonto
      vec4 nightColor = vec4(0.0f, 0.0f, 0.1f, 1.0f); // Notte

      float normalizedTime = sunAng;
      vec4 interpolatedColor;

      if (normalizedTime < 15.0f) {
          float t = normalizedTime / 15.0f;
          interpolatedColor = mix(nightColor, dawnColor, t);
      }
      else if (normalizedTime < 40.0f) {
          float t = (normalizedTime - 15.0f) / 25.0f;
          interpolatedColor = mix(dawnColor, dayColor, t);
      }
      else if (normalizedTime < 165.0f) {
          float t = (normalizedTime - 40.0f) / 125.0f;
          interpolatedColor = mix(dayColor, duskColor, t);
      }
      else if (normalizedTime < 180.0f) {
          float t = (normalizedTime - 165.0f) / 25.0f;
          interpolatedColor = mix(duskColor, nightColor, t);
      }
      else {
          interpolatedColor = nightColor;
      }

      BlinnUbo.lightColor = interpolatedColor;
      BlinnUbo.eyePos = vec3(inverse(ViewMatrix) * vec4(0, 0, 0, 1));
      DSSunLight.map(currentImage, &BlinnUbo, 0);

      BlinnMatParUniformBufferObject blinnMatParUbo{};
      blinnMatParUbo.Power = 100.0;
      DSSunLight.map(currentImage, &blinnMatParUbo, 1);

      fillUniformBuffer(0, CityComponents.size() - 1, CityComponents, ViewPrj, currentImage, vec3(0.0f));
      fillEmissionBuffer(CityComponents.size() - 1, CityComponents.size(), CityComponents, ViewPrj, currentImage, vec3(x, y, z), true, interpolatedColor);
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