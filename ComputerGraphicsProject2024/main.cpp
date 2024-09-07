// This has been adapted from the Vulkan tutorial
#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"
using namespace std;
using namespace glm;

vector<SingleText> outText = {
  {5, {
      "City Simulator",
      "",
      "Alessandro Fornara",
      "Donato Fiore",
      "Riccardo Figini"
  }, 0, 0, 0, 0, 0},
  {2, {
      "Press H (Keyboard) / START (Gamepad)", 
      "to see the command list"
  }, 0, 0, 0, 0, 1},
  {13, {
      "Press SHIFT to run",
      "Press SPACE to jump",
      "Press L to print coordinates",
      "Press P to enter spectator mode",
      "Press O to exit spectator mode",
      "Press K to check doors / enter car",
      "Press J to exit car",
      "In the car:",
      "Press B to switch to first-person view",
      "Press V to switch to third-person view",
      "Press 1/2/3 to switch to isometric/dimetric/trimetric view",
      "Press G to close this text",
      "Press ESC to exit"
  }, 0, 0, 0, 0, 1},
  {13, {
      "Press RIGHT BUMPER to run",
      "Press LEFT BUMPER to jump",
      "Press D-PAD UP to enter spectator mode",
      "Press D-PAD DOWN to exit spectator mode",
      "Press A to interact check doors / enter car",
      "Press B to exit car", 
      "Press BACK to close this text",
      "In the car:",
      "Press D-PAD LEFT to switch to first-person view",
      "Press D-PAD RIGHT to switch to third-person view",
      "Press X to switch to isometric view",
      "Press Y to switch to dimetric view",
      "Press RIGHT-THUMB to switch to dimetric view"
  }, 0, 0, 0, 0, 1}
};

struct MatricesUniformBufferObject {
    alignas(16) mat4 mvpMat;
    alignas(16) mat4 mMat;
    alignas(16) mat4 nMat;
};

struct SpotLightUBO {
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
    alignas(4) float Power;
    alignas(16) vec3 lightDir;
    alignas(16) vec4 lightColor;
    alignas(16) vec3 eyePos;
    
};

struct ApartmentLightBuffer {
    alignas(16) vec3 lightPos;
    alignas(16) vec3 lightColor;
    alignas(16) vec3 eyePos;
    alignas(16) vec3 sigmaGammaBeta;
};

enum Scene { CITY, SHOP, APARTMENT };
enum TextureIndex {
    APARTMENT_SHOP_TEXTURE, LAMP_TEXTURE, WALL_SHOP_TEXTURE, APECAR_TEXTURE, CITY_TEXTURE
};

struct Component {
    const string ObjPath;
    const TextureIndex TexturePath;
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

vector <string> TexturePaths = { "textures/Textures_Apartment_Shop.png", "textures/Lamp.png", "textures/Wall_Shop.png", "textures/ape.jpg", "textures/Textures_City.png" };

vector<Component> Apartment = {
    //PAVIMENTO
     {"models/Apartment/floor_016_Mesh.338.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{200.0f, -1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
     {"models/Apartment/floor_016_Mesh.338.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{204.0f, -1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
     {"models/Apartment/floor_016_Mesh.338.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{200.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
     {"models/Apartment/floor_016_Mesh.338.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{204.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
     {"models/Apartment/floor_016_Mesh.338.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{199.0f, -1.0f, 197.0f}, {0.5f, 2.0f, 0.5f}, {}, {}},

     //SOFFITTO
     {"models/Apartment/Walls_009_Plane.003.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{200.0f, 3.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
     {"models/Apartment/Walls_009_Plane.003.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{204.0f, 3.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
     {"models/Apartment/Walls_009_Plane.003.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{200.0f, 3.0f, 202.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
     {"models/Apartment/Walls_009_Plane.003.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{204.0f, 3.0f, 202.0f}, {1.0f, 1.0f, 1.0f}, {{1.0f, 0.0, 0.0}}, {90.0f}},
     {"models/Apartment/Walls_009_Plane.003.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{199.0f, 3.0f, 196.0f}, {0.5f, 1.0f, 0.5f}, {{1.0f, 0.0, 0.0}}, {90.0f}},

     //MURI
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{206.0f, 1.0f, 206.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{202.0f, 1.0f, 206.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{206.0f, -1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{206.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{198.0f, -1.0f, 200.0f},{1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{198.0f, -1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{206.0f, 1.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{202.0f, 1.0f, 198.0f}, {0.5f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{200.0f, 1.0f, 196.0f}, {0.5f, 1.0f, 1.0f}, {{0.0f, 0.0f, 1.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{200.0f, -1.0f, 197.0f}, {1.0f, 1.0f, 0.5f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/Walls_116_Plane.057.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{198.0f, -1.0f, 197.0f}, {1.0f, 1.0f, 0.5f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},

     //ACCESSORI
     {"models/Apartment/door_005_Mesh.119.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{198.15f, -1.0f, 198.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/window_003_Mesh.125.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{205.8f, 1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/window_003_Mesh.125.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{205.8f, 1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/window_003_Mesh.125.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{198.2f, 1.0f, 200.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/window_003_Mesh.125.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{198.2f, 1.0f, 204.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
     {"models/Apartment/sofa_007_Mesh.158.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{203.0f, -0.8f, 204.0f}, {1.2f, 1.2f, 1.2f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
     {"models/Apartment/picture_049_Mesh.465.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{202.0f, 0.75f, 205.9f}, {1.2f, 1.2f, 1.2f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
     {"models/Apartment/office_chair_021_Mesh.922.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{204, -1.0f, 201.0f}, {2.0f, 2.0f, 2.0f}, {{0.0, 1.0, 0.0}}, {-45.0f} },

     {"models/Apartment/tv_wall_003_Mesh.184.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{203.0f, -1.0f, 198.5f}, {1.2f, 1.2f, 1.2f}, {}, {}},
     {"models/Apartment/musical_instrument_012_Mesh.306.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{200.f, -1.0f, 203.0f}, {1.2f, 1.2f, 1.2f}, {{0.0f, 1.0f, 0.0f}}, {-45.0f}},
     {"models/Apartment/lamp_018_Mesh.6631.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{202.0f, 3.0f, 202.0f}, {2.0f, 2.0f, 2.0f}, {}, {}},
     {"models/Apartment/Sphere.obj", LAMP_TEXTURE, OBJ, {202.0f, 2.0f, 202.0f}, {0.15f, 0.15f, 0.15f}, {}, {}},
     
};

vector<Component> Shop = {  
    //MURI
    //ALTO SINISTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{98.0f, -1.0f, 104.0f}, {1.0f, 2.0f, 1.0f}, { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{100.0f, -1.0f, 106.0f}, {1.0f, 2.0f, 1.0f}},
    //ALTO DESTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{106.0f, -1.0f, 104.0f}, {1.0f, 2.0f, 1.0f}, { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{104.0f, -1.0f, 106.0f}, {1.0f, 2.0f, 1.0f}},
    //BASSO DESTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{104.0f, -1.0f, 98.0f}, {1.0f, 2.0f, 1.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{106.0f, -1.0f, 100.0f}, {1.0f, 2.0f, 1.0f},  { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    //BASSO SINISTRA
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{98.0f, -1.0f, 100.0f}, {1.0f, 2.0f, 1.0f} , { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/Shop/Walls_029_Plane.016.mgcg", WALL_SHOP_TEXTURE, MGCG,{100.0f, -1.0f, 98.0f}, {1.0f, 2.0f, 1.0f} },

    //PAVIMENTO
    {"models/Shop/floor_001_Mesh.640.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{100.0f, -1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{104.0f, -1.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{100.0f, -1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/floor_001_Mesh.640.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{104.0f, -1.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},

    //TETTO
    {"models/Shop/Walls_036_Plane.019.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{100.0f, 3.0f, 98.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},
    {"models/Shop/Walls_036_Plane.019.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{104.0f, 3.0f, 98.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},
    {"models/Shop/Walls_036_Plane.019.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{100.0f, 3.0f, 102.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},
    {"models/Shop/Walls_036_Plane.019.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{104.0f, 3.0f, 102.0f}, {1.0f, 1.0f, 2.0f}, {{1.0f, 0.0f, 0.0f}}, {90.0f}},

    //ACCESSORI
    {"models/Shop/shop_003_Mesh.4875.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{105.0f, -1.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_003_Mesh.4875.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{103.0f, -1.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_004_Mesh.4923.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{100.0f, 0.0f, 99.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/shop_002_Mesh.5167.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{104.0f, 0.0f, 105.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
    {"models/Shop/door_011_Mesh.116.mgcg", APARTMENT_SHOP_TEXTURE, MGCG, {101.0f, -1.0f, 105.7f}, {1.3f, 1.3f, 1.3f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}},
    {"models/Shop/window_006_Mesh.654.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{105.7f, 1.0f, 102.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    {"models/Shop/window_006_Mesh.654.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{98.3f, 1.0f, 102.0f}, {1.3f, 1.3f, 1.3f}, {{0.0f, 1.0f, 0.0f}}, {90.0f}},
    
    //LAMPADE 
    {"models/Shop/lamp_026_Mesh.6700.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{100.0f, 3.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/lamp_026_Mesh.6700.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{104.0f, 3.0f, 100.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/lamp_026_Mesh.6700.mgcg", APARTMENT_SHOP_TEXTURE, MGCG, {100.0f, 3.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    {"models/Shop/lamp_026_Mesh.6700.mgcg", APARTMENT_SHOP_TEXTURE, MGCG,{104.0f, 3.0f, 104.0f}, {1.0f, 1.0f, 1.0f}, {}, {}},
    
    //LAMPADINE
    {"models/Shop/Sphere.obj", LAMP_TEXTURE, OBJ, {100.0f, 2.2f, 100.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    {"models/Shop/Sphere.obj", LAMP_TEXTURE, OBJ, {104.0f, 2.2f, 100.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    {"models/Shop/Sphere.obj", LAMP_TEXTURE, OBJ, {100.0f, 2.2f, 104.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    {"models/Shop/Sphere.obj", LAMP_TEXTURE, OBJ, {104.0f, 2.2f, 104.0f}, {0.1f, 0.1f, 0.1f}, {}, {}},
    
};

vector<Component> CityComponents = {
    {"models/City/ape.obj", APECAR_TEXTURE,OBJ, {0.0f, 0.6f, -3 * 8.0f}, {1.0f, 1.0f, 1.0f}, {{0.0f, 1.0f, 0.0f}}, {180.0f}}, // DRIVEABLE CAR MODEL;
    
    {"models/City/beach_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/beach_tile_1x1_003.mgcg", CITY_TEXTURE, MGCG,{8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/beach_tile_1x1_004.mgcg", CITY_TEXTURE, MGCG, {2*8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/beach_tile_1x1_006.mgcg", CITY_TEXTURE, MGCG, {3*8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/beach_tile_1x1_002.mgcg", CITY_TEXTURE, MGCG, {4*8.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/beach_tile_1x1_007.mgcg", CITY_TEXTURE, MGCG, {4*8.0f, 0.0f, 8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},
    {"models/City/beach_tile_1x1_007.mgcg", CITY_TEXTURE, MGCG, {4*8.0f, 0.0f, 2*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},
    {"models/City/beach_tile_1x1_007.mgcg", CITY_TEXTURE, MGCG, {0.0f, 0.0f, 8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/City/beach_tile_1x1_007.mgcg", CITY_TEXTURE, MGCG,{0.0f, 0.0f, 2*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/City/landscape_entertainments_006.mgcg", CITY_TEXTURE, MGCG,{-12.0f, 0.0f, -4.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/City/tile_river_2x2_001.mgcg", CITY_TEXTURE, MGCG, {10.0f, -1.2f, 10.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/tile_river_2x2_001.mgcg", CITY_TEXTURE, MGCG, {20.0f, -1.2f, 10.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/City/road_tile_1x1_008.mgcg", CITY_TEXTURE, MGCG, {2*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG,{8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {3*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {4*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {5*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {6*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {7*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_1x1_004.mgcg", CITY_TEXTURE, MGCG, {8*8.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f}}, {-90.0f}},
    {"models/City/road_tile_1x1_004.mgcg", CITY_TEXTURE, MGCG, {0.0f, 0.0f, -8.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {90.0f}},

    {"models/City/store_003.mgcg", CITY_TEXTURE, MGCG,{8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/tile_for_home_2x2_007.mgcg", CITY_TEXTURE, MGCG,{4.0f, 0.0f, -2.5 * 8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/tile_for_home_2x2_007.mgcg", CITY_TEXTURE, MGCG,{-12.0f, 0.0f, -2.5 * 8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/transport_bus_005_transport_bus_005.001.mgcg", CITY_TEXTURE, MGCG,{0.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/transport_sport_001_transport_sport_001.001.mgcg", CITY_TEXTURE, MGCG, {-8.0f, 0.0f, -3 * 8.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/City/landscape_entertainments_007.mgcg", CITY_TEXTURE, MGCG, {4 + 5 * 8.0f, 0.0f, 4.0f}, {1.0f, 1.0f, 1.0f}}, //tennis
    {"models/City/landscape_entertainments_003.mgcg", CITY_TEXTURE, MGCG,{4+5*8.0f, 0.0f, -20.0f}, {1.0f, 1.0f, 1.0f}}, //gym
    {"models/City/landscape_entertainments_008.mgcg", CITY_TEXTURE, MGCG,{20+5*8.0f, 0.0f, 4.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {-90.0f}}, //football
    {"models/City/landscape_entertainments_010.mgcg", CITY_TEXTURE, MGCG,{20+5*8.0f, 0.0f, -20.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {90.0f}}, //basket

    {"models/City/apartment_008.mgcg", CITY_TEXTURE, MGCG, {3*8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/apartment_008.mgcg", CITY_TEXTURE, MGCG, {3*8.0f, 0.0f, -3*8.0f}, {1.0f, 1.0f, 1.0f}, { {0.0f, 1.0f, 0.0f} }, {180.0f}},
    {"models/City/tile_for_home_2x2_003.mgcg", CITY_TEXTURE, MGCG,{28.0f, 0.0f, -20.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/apartment_012.mgcg", CITY_TEXTURE, MGCG, {4*8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/apartment_012.mgcg", CITY_TEXTURE, MGCG, {4*8.0f, 0.0f, -3*8.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {180.0f}},

    {"models/City/road_tile_1x1_010.mgcg", CITY_TEXTURE, MGCG,{2*8.0f, 0.0f, -2*8.0f}, {1.0f, 1.0f, 1.0f},
        { {0.0f, 1.0f, 0.0f} }, {90.0f}},
    {"models/City/road_tile_1x1_010.mgcg", CITY_TEXTURE, MGCG, {2*8.0f, 0.0f, -3*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG,{2*8.0f, 0.0f, -6*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG,{2*8.0f, 0.0f, -7*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}},
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {2*8.0f, 0.0f, -8*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}}, 
    {"models/City/road_tile_1x1_001.mgcg", CITY_TEXTURE, MGCG, {2*8.0f, 0.0f, -9*8.0f}, {1.0f, 1.0f, 1.0f},
        {{0.0f, 1.0f, 0.0f} }, {90.0f}}, 

    {"models/City/road_tile_2x2_006.mgcg", CITY_TEXTURE, MGCG, {4+2*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}}, // big road
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG, {4.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG, {4+4*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG,{4+5*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_2x2_003.mgcg", CITY_TEXTURE, MGCG, {4+7*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {270.0f}},
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG, {4+7*8.0f, 0.0f, -4-6*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/City/road_tile_2x2_003.mgcg", CITY_TEXTURE, MGCG, {-4-1*8.0f, 0.0f, -4-4*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {180.0f}},

    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG, {4+7*8.0f, 0.0f, -4-8*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG, {-4-1*8.0f, 0.0f, -4-6*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG, {-4-1*8.0f, 0.0f, -4-8*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {-90.0f}},

    {"models/City/road_tile_2x2_003.mgcg", CITY_TEXTURE, MGCG, {-4-1*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f},
        { { 0.0f, 1.0f, 0.0f } }, {90.0f}},
    {"models/City/road_tile_2x2_003.mgcg", CITY_TEXTURE, MGCG,{4+7*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/City/road_tile_2x2_002.mgcg", CITY_TEXTURE, MGCG,{4+2*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}}, // big road
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG,{4.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG,{4+4*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/road_tile_2x2_005.mgcg", CITY_TEXTURE, MGCG,{4+5*8.0f, 0.0f, -4-10*8.0f}, {1.0f, 1.0f, 1.0f}},
    
    {"models/City/apartment_1_002.mgcg", CITY_TEXTURE, MGCG,{4.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/tile_for_home_2x2_003.mgcg", CITY_TEXTURE, MGCG,{4.0f, 0.0f, -52.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/apartment_1_004.mgcg", CITY_TEXTURE, MGCG, {4+3*8.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/tile_for_home_2x2_007.mgcg", CITY_TEXTURE, MGCG,{28.0f, 0.0f, -52.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/apartment_1_003.mgcg", CITY_TEXTURE, MGCG, {5+5*8.0f, 0.0f, -10-5*8.0f}, {1.0f, 1.0f, 1.0f}}, //001 or 003;
    {"models/City/tile_for_home_2x2_007.mgcg", CITY_TEXTURE, MGCG,{44.0f, 0.0f, -52.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/parking_tile_2x2_002.mgcg", CITY_TEXTURE, MGCG,{4.0f, 0.0f, -68.0f}, {1.0f, 1.0f, 1.0f}},

    {"models/City/park_002.mgcg", CITY_TEXTURE, MGCG,{4+3*8.0f, 0.0f, -4-8*8.0f}, {1.0f, 1.0f, 1.0f}},
    {"models/City/park_006.mgcg", CITY_TEXTURE, MGCG, { 20 + 3 * 8.0f, 0.0f, -4 - 8 * 8.0f }, { 1.0f, 1.0f, 1.0f }},
    
    {"models/City/Sphere.obj", LAMP_TEXTURE, OBJ,{0.0f, 20.0f, 0.0f}, {3.0f, 3.0f, 3.0f}, {}, {} }
    
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
    DescriptorSet DSShopLight;
    Pipeline PipShop;

    //APARTMENT
    DescriptorSetLayout DSLApartmentLight;
    DescriptorSet DSApartmentLight;
    Pipeline PipApartment;

    //ONLY EMISSION
    DescriptorSetLayout DSLemission;
    Pipeline PipEmission;
    VertexDescriptor VDemission;

    vector <Texture> Textures;

    int const citySize = CityComponents.size();
    int const shopSize = Shop.size();
    int const apartmentSize = Apartment.size();

    vec3 CamPos = vec3(0.0, 1.0, -8.0);
    float CamAlpha = 0.0f, CamBeta = 0.0f, CamRoll = 0.0f, CamDist = 10.0f;
    const vec3 Cam1stPos = vec3(0.0f, 1.0f, -0.4f);
    vec3 CarPos = vec3(0.0f, 0.6f, -24.0f);

    float lookAng = 0;
    float DlookAng = 0;

    bool autoTime = true;
    bool cityWithLimits = false;
    bool isInsideCar = false;
    bool isJumping = false;
    bool isometricViewCar = false;
    bool dimetricViewCar = false;
    bool trimetricViewCar = false;
    bool showCommandsGamepad = false;
    bool showCommandsKeyboard = false;
    bool spectatorMode = false;
    bool thirdViewCar = true;
    bool goAhead = false;

    const float CAR_SPEED = 1.0f;
    const float MAX_CAR_SPEED = 15.0f;
    const float ROT_SPEED = radians(120.0f);
    const float WALK_SPEED = 2.5f;
    const float SUN_ROT_SPEED = 3.3333f;
    const float UP_DIRECTION = 1.0f;
    const float DOWN_DIRECTION = -1.0f;
    const float JUMP_SPEED = 3.0f;

    float jumpDirection;    
    float sunAng = 0.0f;   
    float moveSpeed;
    float CamPitch = radians(20.0f);
    float CamYaw = M_PI;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    bool showStartText = true;

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
            {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(BlinnUniformBufferObject), 1},
            });
        DSLShopLight.init(this, {
            {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(SpotLightUBO), 1 } }
        );
        DSLApartmentLight.init(this, {
            {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(ApartmentLightBuffer), 1 }
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


        PipCity.init(this, &VDWorld, "shaders/City/CityVert.spv", "shaders/City/CityFrag.spv", { &DSLSunLight, &DSLMatricesAndTextures });
        PipShop.init(this, &VDWorld, "shaders/Shop/ShopVert.spv", "shaders/Shop/ShopSpotLight.spv", { &DSLShopLight, &DSLMatricesAndTextures });
        PipEmission.init(this, &VDemission, "shaders/Emission/generalEmissionVert.spv", "shaders/Emission/generalEmissionFrag.spv", { &DSLemission });
        PipApartment.init(this, &VDWorld, "shaders/Apartment/ApartmentVert.spv", "shaders/Apartment/ApartmentFrag.spv", { &DSLApartmentLight, &DSLMatricesAndTextures });

        //first elements are "normal" components,the second ones are light (emission components)
        
        //Texures vector
        int i = 0;
        for (; i < TexturePaths.size(); i++) {
            Texture tempTexture; 
            tempTexture.init(this, TexturePaths[i]);
            Textures.push_back(tempTexture);
        }

        //CITY
        for (i = 0; i < citySize; i++) {
            CityComponents[i].model.init(this, &VDWorld, CityComponents[i].ObjPath, CityComponents[i].type);
            CityComponents[i].texture = Textures[CityComponents[i].TexturePath];
        }

        //SHOP
        for (i = 0; i < shopSize; i++) {
            Shop[i].model.init(this, &VDWorld, Shop[i].ObjPath, Shop[i].type);
            Shop[i].texture = Textures[Shop[i].TexturePath];
        }

        //APARTMENT
        for (i = 0; i < apartmentSize; i++) {
            Apartment[i].model.init(this, &VDWorld, Apartment[i].ObjPath, Apartment[i].type);
            Apartment[i].texture = Textures[Apartment[i].TexturePath];
        }

        DPSZs.uniformBlocksInPool = citySize * 2 + shopSize + apartmentSize;
        DPSZs.texturesInPool = citySize + shopSize + apartmentSize;
        DPSZs.setsInPool = citySize +1 + shopSize + 1 + apartmentSize + 1;

        cout << "Initializing text\n";
        outTxt.init(this, &outText);

        cout << "Initialization completed!\n";
        cout << "Uniform Blocks in the Pool  : " << DPSZs.uniformBlocksInPool << "\n";
        cout << "Textures in the Pool        : " << DPSZs.texturesInPool << "\n";
        cout << "Descriptor Sets in the Pool : " << DPSZs.setsInPool << "\n";

        startTime = std::chrono::high_resolution_clock::now();
    }

    void pipelinesAndDescriptorSetsInit() {

        PipCity.create();
        PipShop.create();
        PipEmission.create();
        PipApartment.create();

        //CITY
        DSSunLight.init(this, &DSLSunLight, {});
        int i;
        for (i = 0; i < citySize - 1; i++) {
            CityComponents[i].DS.init(this, &DSLMatricesAndTextures, {&CityComponents[i].texture});
        }
        CityComponents[citySize - 1].DS.init(this, &DSLemission, { &CityComponents[citySize - 1].texture });

        //SHOP
        for (i = 0; i < shopSize - 4; i++) {
            Shop[i].DS.init(this, &DSLMatricesAndTextures, { &Shop[i].texture });
        }
        for (; i < shopSize; i++) {
            Shop[i].DS.init(this, &DSLemission, { &Shop[i].texture });
        }
        DSShopLight.init(this, &DSLShopLight, {});

        //APARTMENT
        for (i = 0; i < apartmentSize-1; i++) {
            Apartment[i].DS.init(this, &DSLMatricesAndTextures, { &Apartment[i].texture });
        }
        Apartment[i].DS.init(this, &DSLemission, { &Apartment[i].texture });
        DSApartmentLight.init(this, &DSLApartmentLight, {});

        outTxt.pipelinesAndDescriptorSetsInit();
    }

    void pipelinesAndDescriptorSetsCleanup() {
        PipCity.cleanup();
        PipShop.cleanup();
        PipEmission.cleanup();
        PipApartment.cleanup();

        //CITY
        int i;
        for (i = 0; i < citySize; i++) {
            CityComponents[i].DS.cleanup();
        }
        DSSunLight.cleanup();

        //SHOP
        for (i = 0; i < shopSize; i++) {
            Shop[i].DS.cleanup();
        }
        DSShopLight.cleanup();

        //APARTMENT
        for (i = 0; i < apartmentSize; i++) {
            Apartment[i].DS.cleanup();
        }
        DSApartmentLight.cleanup();

        outTxt.pipelinesAndDescriptorSetsCleanup();
    }

    void localCleanup() {

        //CITY
        for (int i = 0; i < citySize; i++)
            CityComponents[i].model.cleanup();

        //SHOP
        for (int i = 0; i < shopSize; i++)
            Shop[i].model.cleanup();

        //APARTMENT
        for (int i = 0; i < apartmentSize; i++)
            Apartment[i].model.cleanup();

        //Textures Vector
        for (int i = 0; i < Textures.size(); i++)
            Textures[i].cleanup();

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
            for (; i < citySize - 1; i++) {

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
            DSShopLight.bind(commandBuffer, PipShop, 0, currentImage);
            for (j = 0; j < shopSize - 4; j++) {
                Shop[j].model.bind(commandBuffer);
                Shop[j].DS.bind(commandBuffer, PipShop, 1, currentImage);
                vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
            }
            PipEmission.bind(commandBuffer);
            for (; j < shopSize; j++) {
                Shop[j].model.bind(commandBuffer);
                Shop[j].DS.bind(commandBuffer, PipEmission, 0, currentImage);
                vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Shop[j].model.indices.size()), 1, 0, 0, 0);
            }
        }//APARTMENT
        else if (currentScene == APARTMENT) {
            int j;
            PipApartment.bind(commandBuffer);
            DSApartmentLight.bind(commandBuffer, PipApartment, 0, currentImage);
            for (j = 0; j < apartmentSize - 1; j++) {
                Apartment[j].model.bind(commandBuffer);
                Apartment[j].DS.bind(commandBuffer, PipApartment, 1, currentImage);
                vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Apartment[j].model.indices.size()), 1, 0, 0, 0);
            }
            PipEmission.bind(commandBuffer);
            Apartment[j].model.bind(commandBuffer);
            Apartment[j].DS.bind(commandBuffer, PipEmission, 0, currentImage);
            vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(Apartment[j].model.indices.size()), 1, 0, 0, 0);
        }

        int txtIndex;
        if (showStartText)
            txtIndex = 0;
        else if (!showCommandsKeyboard && !showCommandsGamepad)
            txtIndex = 1;
        else if (showCommandsKeyboard)
            txtIndex = 2;
        else if (showCommandsGamepad)
            txtIndex = 3;

        outTxt.populateCommandBuffer(commandBuffer, currentImage, txtIndex);
    }

    void updateUniformBuffer(uint32_t currentImage) {
        float deltaT, cameraAngle = 0.0;
        vec3 m = vec3(0.0f), r = vec3(0.0f);
        bool fire = false;
        GLFWgamepadstate state;

        getSixAxis(deltaT, m, r, fire);
        int connected = glfwGetGamepadState(GLFW_JOYSTICK_1, &state);

        if (!isInsideCar)
            handleWalkingMovement(m, r, deltaT, state, connected);
        else
            handleCarMovement(m, r, deltaT);

        //cameraAngle is degree, CamAlpha is radiant
        cameraAngle = cameraAngle + (360.0 * (CamAlpha)) / (2 * M_PI);

        HandleUserInputs(CamPos, cameraAngle, state, connected);

        mat4 ViewPrj = updateViewMatrix();

        if (currentScene == CITY) {
            buildCity(currentImage, ViewPrj, deltaT);
        }
        else if (currentScene == SHOP) {
            buildShop(currentImage, ViewPrj);
        }
        else if (currentScene == APARTMENT) {
            buildApartment(currentImage, ViewPrj);
        }

        if (showStartText) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float elapsedTime = std::chrono::duration<float>(currentTime - startTime).count();

            if (elapsedTime > 5.0f) {
                showStartText = false;              
                RebuildPipeline();
            }
        }
    }

    /*
       Manage the player's movement when outside the vehicle
       @param m: player moviment
       @param r: player rotation
       @param deltaT: time difference since last update
       @param connected: indicates if the player is using a joystick
       @param state: handles joystick's buttons
   */
    void handleWalkingMovement(vec3 m, vec3 r, float deltaT, GLFWgamepadstate state, int connected) {
        moveSpeed = WALK_SPEED;
        bool isShiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
        bool isGamepadRunPressed = (connected && state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER] == GLFW_PRESS);

        if (isShiftPressed || isGamepadRunPressed) {
            moveSpeed *= 2;
        }

        CamAlpha = CamAlpha - ROT_SPEED * deltaT * r.y;
        CamBeta = CamBeta - ROT_SPEED * deltaT * r.x;
        CamBeta = CamBeta < radians(-90.0f) ? radians(-90.0f) : (CamBeta > radians(90.0f) ? radians(90.0f) : CamBeta);

        vec3 ux = rotate(mat4(1.0f), CamAlpha, vec3(0, 1, 0)) * vec4(1, 0, 0, 1);
        vec3 uz = rotate(mat4(1.0f), CamAlpha, vec3(0, 1, 0)) * vec4(0, 0, -1, 1);
        vec3 uy = rotate(mat4(1.0f), CamBeta, vec3(1, 0, 1)) * vec4(0, 1, 0, 1);

        vec3 tmpCamPos = CamPos + moveSpeed * m.x * ux * deltaT - moveSpeed * m.z * uz * deltaT;

        if (checkLimits(tmpCamPos))
            CamPos = tmpCamPos;

        if (spectatorMode) {
            CamPos = CamPos + moveSpeed * m.y * uy * deltaT;
        }
        else if (!isJumping) {
            CamPos.y = computeHeight(CamPos);
            bool isSpacePressed = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
            bool isGamepadJumpPressed = (connected && state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER] == GLFW_PRESS);
            if (isSpacePressed || isGamepadJumpPressed) {
                isJumping = true;
                jumpDirection = UP_DIRECTION;
            }
        }
        if (isJumping)
            jump(computeHeight(CamPos), deltaT);
    }

    /*
        Manage the player's movement when inside the vehicle
        @param m: player moviment
        @param r: player rotation
        @param deltaT: time difference since last update
    */
    void handleCarMovement(vec3 m, vec3 r, float deltaT) {
        float rotAngleCar, carCurrAngle = CityComponents[0].angle[0];
        
        moveSpeed = accelerateCar(moveSpeed, m.z);
        m.z = -m.z;
        vec3 tmpCarPos = CarPos - moveSpeed * m.z * vec3(sin(radians(carCurrAngle)), 0, cos(radians(carCurrAngle))) * deltaT;
        rotAngleCar = -m.x;

        if (m.z < 0.0f)
            rotAngleCar = -rotAngleCar;

        if (checkLimits(tmpCarPos)) {
            CarPos = tmpCarPos;
        }

        CityComponents[0].pos = CarPos;
        CityComponents[0].angle[0] += rotAngleCar;

        if (isometricViewCar || dimetricViewCar || trimetricViewCar) {
            lookAng -= r.y * radians(360.0f) * deltaT;
            lookAng = (lookAng < -M_PI) ? lookAng + 2 * M_PI : ((lookAng > M_PI) ? lookAng - 2 * M_PI : lookAng);
            DlookAng = M_PI / 2 * round(2 * lookAng / M_PI);
            CamPos = CarPos;
        }
        else if (thirdViewCar) {
            CamYaw += ROT_SPEED * deltaT * r.y;
            CamPitch -= ROT_SPEED * deltaT * r.x;
            CamDist -= moveSpeed * deltaT * m.y;

            CamYaw = (CamYaw < 0.0f ? 0.0f : (CamYaw > 2 * M_PI ? 2 * M_PI : CamYaw));
            CamPitch = (CamPitch < 0.0f ? 0.0f : (CamPitch > M_PI_2 - 0.01f ? M_PI_2 - 0.01f : CamPitch));
            CamDist = (CamDist < 7.0f ? 7.0f : (CamDist > 15.0f ? 15.0f : CamDist));

            CamPos = CarPos + vec3(rotate(mat4(1), CamYaw, vec3(0, 1, 0)) * rotate(mat4(1), -CamPitch, vec3(1, 0, 0)) * vec4(0, 0, CamDist, 1));
        }
        else {
            CamYaw -= ROT_SPEED * deltaT * r.y;
            CamPitch -= ROT_SPEED * deltaT * r.x;

            // -180° <= CamYaw <= 540°;
            CamYaw = (CamYaw < -M_PI ? -M_PI : (CamYaw > 2.5f * M_PI ? 2.5f * M_PI : CamYaw));
            CamPitch = (CamPitch < -0.25 * M_PI ? -0.25 * M_PI : (CamPitch > 0.25 * M_PI ? 0.25 * M_PI : CamPitch));

            CamPos = CarPos + vec3(rotate(mat4(1.0f), radians(CityComponents[0].angle[0]), vec3(0.0f, 1.0f, 0.0f)) * vec4(Cam1stPos, 1.0f));
        }
    }

    /*
        It handles every user input from keyboard or joystick
        @param cameraPosition: camera position
        @param cameraAngle: camera angle
        @param connected: indicates if the player is using a joystick
        @param state: handles joystick's buttons 
    */
    void HandleUserInputs(vec3 cameraPosition, float cameraAngle, GLFWgamepadstate state, int connected) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if (glfwGetKey(window, GLFW_KEY_G)) {
            showCommandsKeyboard = false;
            RebuildPipeline();
        }
        if (glfwGetKey(window, GLFW_KEY_H)) {
            showCommandsKeyboard = true;
            showCommandsGamepad = false;
            RebuildPipeline();
        }
        if (glfwGetKey(window, GLFW_KEY_J) && isInsideCar) {
            exitCar();
        }
        if (glfwGetKey(window, GLFW_KEY_K) && !isInsideCar && !spectatorMode) {
            if (distance(CamPos, CarPos) < 2.0f) {
                enterCar();
            }
            else{
                if (cameraAngle > 0)
                    checkDoors(cameraPosition, cameraAngle - 360.0 * floor(cameraAngle / 360.0));
                else {
                    float tmp = cameraAngle - 360.0 * (floor(cameraAngle / 360.0) + 1);
                    checkDoors(cameraPosition, 360.0 + tmp);
                }
            }
        }
        if (isInsideCar) {
            if (glfwGetKey(window, GLFW_KEY_1)) {
                isometricViewCar = true;
                dimetricViewCar = false;
                trimetricViewCar = false;
                thirdViewCar = false;
            }
            else if (glfwGetKey(window, GLFW_KEY_2)) {
                isometricViewCar = false;
                dimetricViewCar = true;
                trimetricViewCar = false;
                thirdViewCar = false;
            }
            else if (glfwGetKey(window, GLFW_KEY_3)) {
                isometricViewCar = false;
                dimetricViewCar = false;
                trimetricViewCar = true;
                thirdViewCar = false;
            }
            else if (glfwGetKey(window, GLFW_KEY_V)) {
                thirdViewCar = true;
                resetParallelProjections();
            }
            else if (glfwGetKey(window, GLFW_KEY_B)) {
                thirdViewCar = false;
                resetParallelProjections();
            }
        }
        if (glfwGetKey(window, GLFW_KEY_L)) {
            printCordinates(cameraAngle);
        }
        if (glfwGetKey(window, GLFW_KEY_O)) {
            spectatorMode = false;
        }
        if (glfwGetKey(window, GLFW_KEY_P) && !isInsideCar && currentScene == CITY) {
            spectatorMode = true;
        }

        if (connected) {
            if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK] == GLFW_PRESS) {
                showCommandsGamepad = false;
                RebuildPipeline();
            }
            if (state.buttons[GLFW_GAMEPAD_BUTTON_START] == GLFW_PRESS) {
                showCommandsGamepad = true;
                showCommandsKeyboard = false;
                RebuildPipeline();
            }
            if (state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_PRESS && isInsideCar) {
                exitCar();
            }
            if (state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS && !isInsideCar) {
                if (distance(CamPos, CarPos) < 2.0f) {
                    enterCar();
                }
                else {
                    if (cameraAngle > 0)
                        checkDoors(cameraPosition, cameraAngle - 360.0 * floor(cameraAngle / 360.0));
                    else {
                        float tmp = cameraAngle - 360.0 * (floor(cameraAngle / 360.0) + 1);
                        checkDoors(cameraPosition, 360.0 + tmp);
                    }
                }
            }
            if (isInsideCar) {
                if (state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_PRESS) {
                    isometricViewCar = true;
                    dimetricViewCar = false;
                    trimetricViewCar = false;
                    thirdViewCar = false;
                }
                else if (state.buttons[GLFW_GAMEPAD_BUTTON_Y] == GLFW_PRESS) {
                    isometricViewCar = false;
                    dimetricViewCar = true;
                    trimetricViewCar = false;
                    thirdViewCar = false;
                }
                else if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB] == GLFW_PRESS) {
                    isometricViewCar = false;
                    dimetricViewCar = false;
                    trimetricViewCar = true;
                    thirdViewCar = false;
                }
                else if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT] == GLFW_PRESS) {
                    thirdViewCar = true;
                    resetParallelProjections();
                }
                else if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT] == GLFW_PRESS) {
                    thirdViewCar = false;
                    resetParallelProjections();
                }
            }
            if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN] == GLFW_PRESS) {
                spectatorMode = false;
            }
            if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP] == GLFW_PRESS && !isInsideCar && currentScene == CITY) {
                spectatorMode = true;
            }    
        }
    }

    void resetParallelProjections() {
        isometricViewCar = false;
        dimetricViewCar = false;
        trimetricViewCar = false;
    }

    /*
        It handles the acceleration of the car, the speed increases up to a certain limit
        @param speed: actual speed
        @param acc: acceleration ratio
    */
    float accelerateCar(float speed, float acc) {
        float speed2;
        bool inverse = false;
        if (acc < 0) {
            if (goAhead){
                goAhead = false;
                inverse = true;
            }
            acc = -acc;
        }
        else if(acc>0) {
            if (!goAhead) {
                goAhead = true;
                inverse = true;
            }
        }
        if (acc != 0) {
            if (!inverse) {
                speed2 = speed + acc * 0.12f;
                if (speed2 >= MAX_CAR_SPEED)
                    speed2 = MAX_CAR_SPEED;
                else if(speed2 < CAR_SPEED)
                    speed2 = CAR_SPEED;
            }
            else {
                speed2 = CAR_SPEED;
            }
        }
        else {
            speed2 = speed - 0.3f;
            if (speed2 < CAR_SPEED)
                speed2 = CAR_SPEED;
        }
        return speed2;
    }

    /*
        It Allows the player to jump
        @param initialHeight: initial height of the jump
    */
    void jump(float initialHeight, float deltaT) {
        if (isJumping) {
            CamPos.y += JUMP_SPEED * jumpDirection * deltaT;

            if (CamPos.y >= initialHeight + 1.0f)
                jumpDirection = DOWN_DIRECTION;
            else if (CamPos.y <= initialHeight) {
                jumpDirection = 0;
                isJumping = false;
            }
        }
    }

    /*
        It enters the player in the car    
    */
    void enterCar() {
        isInsideCar = true;
        moveSpeed = CAR_SPEED;
        cityWithLimits = true;
        spectatorMode = false;
    }

    /*
        It exits the player from the car 
    */
    void exitCar() {
        isInsideCar = false;
        cityWithLimits = false;
        CamPos = CarPos + (-2.0f, 0.0f, -2.0f);
        CamPos.y = 1.0f;
    }

    /*
        It updates the view matrix according to the user movements 
    */
    mat4 updateViewMatrix() {
        if (isInsideCar) {
            if (isometricViewCar)
                return makeViewProjectionIsometric(CamPos, 20.0f, Ar, -500.0f, 500.0f);
            else if (dimetricViewCar)
                return makeViewProjectionDimetric(CamPos, 20.0f, Ar, -500.0f, 500.0f);
            else if (trimetricViewCar)
                return makeViewProjectionTrimetric(CamPos, 20.0f, Ar, -500.0f, 500.0f);
            else if (thirdViewCar)
                return MakeViewProjectionLookAt(CamPos, CarPos, vec3(0, 1, 0), CamRoll, radians(90.0f), Ar, 0.1f, 500.0f);
            else
                return MakeViewProjectionLookInDirection(CamPos, CamYaw, CamPitch, CamRoll, radians(90.0f), Ar, 0.1f, 500.0f);
            
        }
        else {
            mat4 ViewMatrix = rotate(mat4(1.0), -CamBeta, vec3(1, 0, 0)) * rotate(mat4(1.0), -CamAlpha, vec3(0, 1, 0)) * translate(mat4(1.0), -CamPos);
            mat4 M = perspective(radians(45.0f), Ar, 0.1f, 160.0f);
            M[1][1] *= -1;
            return M * ViewMatrix;
        }
    }

    /*
        It defines the view projection matrix with isometric
        @param Pos: camera position
        @param halfWidth: half width
        param Ar: aspect ratio
        @param nearPlane: near plane
        @param farPlane: far plane
    */
    mat4 makeViewProjectionIsometric(vec3 Pos, float halfWidth, float Ar, float nearPlane, float farPlane) {
        mat4 M = mat4(1.0f/halfWidth, 0, 0, 0, 0, -Ar/halfWidth, 0, 0, 0, 0, 1.0f /(nearPlane - farPlane), 0, 0, 0, nearPlane/(nearPlane - farPlane), 1) *
            rotate(mat4(1.0f), radians(35.26f), vec3(1.0f, 0.0f, 0.0f)) *
            rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
        mat4 Mv = inverse(
            translate(mat4(1), Pos) *
            rotate(mat4(1), DlookAng, vec3(0, 1, 0)) *
            translate(mat4(1), vec3(0, 2, 8))
        );
        return M * Mv;
    }

    mat4 makeViewProjectionDimetric(vec3 Pos, float halfWidth, float Ar, float nearPlane, float farPlane) {
        mat4 M = mat4(1.0f/halfWidth,0,0,0, 0,-Ar/halfWidth,0,0, 0,0,1.0f/(nearPlane - farPlane),0, 0,0,nearPlane/(nearPlane - farPlane),1.0f) *
            rotate(mat4(1.0f), radians(20.0f), vec3(1.0f, 0.0f, 0.0f)) *
            rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
        mat4 Mv = inverse(
            translate(mat4(1), Pos) *
            rotate(mat4(1), DlookAng, vec3(0, 1, 0)) *
            translate(mat4(1), vec3(0, 2, 8))
        );
        return M * Mv;
    }

    mat4 makeViewProjectionTrimetric(vec3 Pos, float halfWidth, float Ar, float nearPlane, float farPlane) {
        mat4 M = mat4(1.0f / halfWidth, 0, 0, 0, 0, -Ar / halfWidth, 0, 0, 0, 0, 1.0f / (nearPlane - farPlane), 0, 0, 0, nearPlane / (nearPlane - farPlane), 1.0f) *
            rotate(mat4(1.0f), radians(30.0f), vec3(1.0f, 0.0f, 0.0f)) *
            rotate(mat4(1.0f), radians(60.0f), vec3(0.0f, 1.0f, 0.0f));
        mat4 Mv = inverse(
            translate(mat4(1), Pos) *
            rotate(mat4(1), DlookAng, vec3(0, 1, 0)) *
            translate(mat4(1), vec3(0, 2, 8))
        );
        return M * Mv;
    }
    /*
        It defines the view projection matrix with look at and perspective
        @param Pos: camera position
        @param target: target on the screen (the object that "follow" the camera)
        @param Up: vertical distance from the target
        @param Roll: rotation 
        @param FOVy: field of the view, angle of the frustum 
        @param ar: aspect ration
        @param nearPlane: near plane
        @param far plane: far plane
    */
    mat4 MakeViewProjectionLookAt(vec3 Pos, vec3 Target, vec3 Up, float Roll, float FOVy, float Ar, float nearPlane, float farPlane) {

        mat4 M = perspective(FOVy, Ar, nearPlane, farPlane);
        M[1][1] *= -1;

        M = M *
            rotate(mat4(1.0), -Roll, vec3(0, 0, 1)) *
            lookAt(Pos, Target, Up);
        return M;
    }

    /*
        It defines the view - projection matrx with look in direction and perspective
        @param Pos: position of the camera
        @param Yaw: rotation on axis y
        @param Pitch: rotation on axis z
        @param Roll: rotation on axis x
        @param FOVy: field of the view, angle of the frustum 
        @param Ar: aspect ration
        @param nearPlane: near plane
        @param farPlane: far plane
    */
    mat4 MakeViewProjectionLookInDirection(vec3 Pos, float Yaw, float Pitch, float Roll, float FOVy, float Ar, float nearPlane, float farPlane) {
        // Mvp = Mprj * Mv
        mat4 M = perspective(FOVy, Ar, nearPlane, farPlane);
        M[1][1] *= -1;

        M = M *
            rotate(mat4(1.0), -Roll, vec3(0, 0, 1)) *
            rotate(mat4(1.0), -Pitch, vec3(1, 0, 0)) *
            rotate(mat4(1.0), -Yaw, vec3(0, 1, 0)) *
            translate(mat4(1.0), -Pos);
        return M;
    }

    /*
        It return true if the player enters in a valid zone of the map
        @param newPos: new position of the player
    */
    bool checkLimits(vec3 newPos) {
        if (currentScene == SHOP) {
            return (newPos.z > 100.1 && newPos.z <= 105.5 && newPos.x < 105 && newPos.x >= 98.60)
                && !(newPos.x > 102 && newPos.x < 105 && newPos.z > 104 && newPos.z < 105.5);
        }
        else if (currentScene == APARTMENT) {
            return (newPos.z > 197 && newPos.z <= 205 && newPos.x > 198 && newPos.x <= 205)
                && !(newPos.x > 200 && newPos.x < 205 && newPos.z > 197 && newPos.z < 198);
        }
        else if (currentScene == CITY && cityWithLimits) {
            return (newPos.x >= -1.77 && newPos.x <= 65.75 && newPos.z <= -6.24 && newPos.z >= -9.71) //1
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
        }
        else if (currentScene == CITY && !cityWithLimits) {
            return (newPos.x > -20.0 && newPos.x < 68.0 && newPos.z>-92.0 && newPos.z <= -4.0) //1
                || (newPos.x > 37.0 && newPos.x < 68.0 && newPos.z >= -4.0 && newPos.z < 12.0) //2
                || (newPos.x > -20.0 && newPos.x < -4.0 && newPos.z >= -4.0 && newPos.z < 4.0);//3
        }
        return true;
    }

    /*
        This method is called when the player click "k", it checks if he click on something clickable. 
        It switch x-z coordinates where necessary.
        @param cameraPosition: camera position
        @param cameraAngle: camera angle
    */
    void checkDoors(vec3 cameraPosition, float cameraAngle) {
        //Check porta negozio 
        if (checkSingleDoor(cameraPosition, cameraAngle, 7.5, 8.8, -12.8404, true))
            goTo(SHOP, { 100.0f, 1.0f, 104.0f });
        if (checkSingleDoor(cameraPosition, cameraAngle, 99.63, 100.86, 105, false))
            exit({ 7.0f, 1.0f, -12.0f });
        vec3 tmpcam = vec3(cameraPosition.z, cameraPosition.y, cameraPosition.x);
        if (checkSingleDoor(tmpcam, (cameraAngle-90.0 > 0.0) ? (cameraAngle-90.0) : 360.0 +(cameraAngle-90.0), -15.0f, -12.0f, 23.0f, true)) {
            goTo(APARTMENT, { 198.5f, 1.0f, 198.5f });
        }
        if (checkSingleDoor(tmpcam, (cameraAngle - 90.0 > 0.0) ? (cameraAngle - 90.0) : 360.0 + (cameraAngle - 90.0), 196.70f, 197.90f, 198.2f, true)) {
            exit({ 26.5f, 1.0f, -14.0f });
        }
    }

    /*
        This method allows you to enter by setting the correct scene 
        @param ty: scene
        @param cor: coordinates of the interior of buildings 
    */
    void goTo(Scene ty, vec3 cor) {
        CamPos = cor;
        currentScene = ty;
        spectatorMode = false;
        RebuildPipeline();
    }

    /*
        This method exit from apartment or shop
        @param c: city's position
    */
    void exit(vec3 c) {
        CamPos = c;
        currentScene = CITY;
        RebuildPipeline();
    }


    float computeHeight(vec3 cam) {
        if(cam.z >= -11.57 && cam.z <= 3.46) {
            if (cam.x <= -7.25159 && cam.x >= -7.60898)
                return 1.25;
            else if (cam.x <= -7.60899 && cam.x >= -7.92241)
                return 1.5;
            else if (cam.x <= -7.92241 && cam.x >= -8.15)
                return 1.75;
            else if (cam.x <= -8.16 && cam.x >= -17.35)
                return 2.0;
        }
        return 1.0;
    }

    /*
        Method for interacting with objects. Each time the "k" button is pressed, the method checks the camera’s position and angle to see if the player can interact. 
        The object with which you want to interact must be placed along the x-axis, otherwise it is necessary to invert the coordinates. 
        The method defines an angle within which the object is clickable based on its distance from it. 
        @param camera position: camera position
        @param camera angle: camera angle
        @param x1: left end point object
        @param x2: right end point object
        @param z: deep object
        @param switchView: true if z of the object is lower than camera
    */
    bool checkSingleDoor(vec3 cameraPosition, float cameraAngle, float x1, float x2, float z, bool switchView) {
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
            return ((cameraAngle < left && cameraAngle >= 0) || (cameraAngle <= 360 && cameraAngle > (360 - right)));
        }
        return false;
    }

    /* This method print the coordinates
        @param camAngle: camera's angle
    */
    void printCordinates(float camAngle) {
        float adjustedAngle;
        if (camAngle > 0) {
            adjustedAngle = camAngle - 360.0 * floor(camAngle / 360.0);
        }
        else {
            float tmp = camAngle - 360.0 * (floor(camAngle / 360.0) + 1);
            adjustedAngle = 360.0 - tmp;
        }

        cout << "________________________________________________________________________________" << '\n';
        cout << "X: " << CamPos.x << ", Y: " << CamPos.y << ", Z: " << CamPos.z << ", CameraAngle: " << adjustedAngle << "\n";
        cout << "________________________________________________________________________________" << '\n';
    }

    /*
        This method places every object in the world, generalizing the function of positioning an object
        @param start: initial index of light components
        @param end: final index of light components
        @param vec: list of component
        @param ViewPrj: view projection matrix
        @param currentImage: scene shown 
        @param traslation: translation of the luminous object if necessary
    */
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

    /*
        General method for building the lights in the various environments. 
        It is possible to change the color of the light emitted and also the position of the bulbs/ sun.
        @param start: initial index of light components
        @param end: final index of light components
        @param vec: list of component
        @param ViewPrj: view projection matrix
        @param currentImage: scene shown 
        @param traslation: translation of the luminous object if necessary
        @param flag: Signal if the light color has changed 
        @param colorLught: new light color
    */
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

    /*
     Builds the apartment. 
        Creates one light via the emission pipeline, 
        while the lighting is given by Oner-nayar and phong  
        @param currentImage: current scene
        @param ViewPrj: view projection matrix
    */
    void buildApartment(int currentImage, mat4 ViewPrj) {
        ApartmentLightBuffer aubo{};

        aubo.lightPos = vec3(202.0, 1.75, 202.0);
        aubo.lightColor = vec3(0.6f, 0.6f, 0.6f);
        aubo.eyePos = CamPos;
        aubo.sigmaGammaBeta.x = 0.2;
        aubo.sigmaGammaBeta.y = 64.0f;
        aubo.sigmaGammaBeta.z = 0.5f;

        DSApartmentLight.map(currentImage, &aubo, 0);

        fillUniformBuffer(0, apartmentSize - 1, Apartment, ViewPrj, currentImage, vec3(0.0f));

        fillEmissionBuffer(apartmentSize - 1, apartmentSize, Apartment, ViewPrj, currentImage, vec3(0.0f), false, vec4(0.0));
    }


    /*
        Builds the shop. 
        Creates the four lights via the emission pipeline, 
        while the lighting is given by spot light and lambert  
        @param currentImage: current scene
        @param ViewPrj: view projection matrix
    */
    void buildShop(int currentImage, mat4 ViewPrj) {
        SpotLightUBO subo{};
        for (int i = 0; i < 4; i++) {
            subo.lightPos[i] = Shop[23 + i].pos;
            subo.lightPos[i].y = 1.0f;
            subo.lightDir[i] = vec3(0.0, 1.0, 0.0);
            subo.lightColor[i] = vec3(0.8f, 0.8f, 0.8f);
        }
        subo.InOutDecayTarget.x = 0.9f; 
        subo.InOutDecayTarget.y = 0.7f;  
        subo.InOutDecayTarget.z = 2.0f;  
        subo.InOutDecayTarget.w = 2.5f;  

        subo.eyePos = CamPos;
        DSShopLight.map(currentImage, &subo, 0);

        fillUniformBuffer(0, shopSize - 4, Shop, ViewPrj, currentImage, vec3(0.0f));

        fillEmissionBuffer(shopSize - 4, shopSize, Shop, ViewPrj, currentImage, vec3(0.0f), false, vec4(0.0));
    }

    /*
        Builds the main city and the sun. 
        It uses two pipelines, one for the sun’s emission and one for the main components exploiting lambert and blinn. 
        @param currentImage: current scene 
        @param ViewPrj: view projection matrix
        @param deltaT: time difference from last update
    */
    void buildCity(int currentImage, mat4 ViewPrj, float deltaT) {
        BlinnUniformBufferObject BlinnUbo{};

        if (autoTime) {
            sunAng = fmod(sunAng + deltaT * SUN_ROT_SPEED, 360.0f);
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
        vec4 nightColor = vec4(0.0f, 0.0f, 0.0f, 0.0f); // Notte

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
        else if (normalizedTime < 175.0f) {
            float t = (normalizedTime - 40.0f) / 135.0f;
            interpolatedColor = mix(dayColor, duskColor, t); ;
        }
        else if (normalizedTime < 200.0f) {
            float t = (normalizedTime - 165.0f) / 35.0f;
            interpolatedColor = mix(duskColor, nightColor, t);
        }
        else {
            interpolatedColor = nightColor;
        }

        BlinnUbo.lightColor = interpolatedColor;
        if (isometricViewCar || dimetricViewCar || trimetricViewCar) {
            mat4 inverseView = inverse(ViewPrj);
            vec3 cameraPosition = vec3(inverseView[3]);
            BlinnUbo.eyePos = cameraPosition;
        }
        else
            BlinnUbo.eyePos = CamPos;

        BlinnUbo.Power = 100.0;
        DSSunLight.map(currentImage, &BlinnUbo, 0);

        fillUniformBuffer(0, citySize - 1, CityComponents, ViewPrj, currentImage, vec3(0.0f));
        fillEmissionBuffer(citySize - 1, citySize, CityComponents, ViewPrj, currentImage, vec3(x, y, z), true, interpolatedColor);
    }

};

/*
    Main
*/
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