// This has been adapted from the Vulkan tutorial
#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"
using namespace std;
using namespace glm;

/*std::vector<SingleText> outText = {
  {2, {"City", "","",""}, 0, 0} };*/

struct UniformBufferObject {
  alignas(16) glm::mat4 mvpMat;
  alignas(16) glm::mat4 mMat;
  alignas(16) glm::mat4 nMat;
};

struct Component {
  const std::string ObjPath;
  const std::string TexturePath;
  const glm::vec3 pos;
  const glm::vec3 scale;
  const glm::vec3 rot;
  const float angle;
  Model model;
  Texture texture;
  DescriptorSet DS;
};

struct Vertex {
  glm::vec3 pos;
  glm::vec3 norm;
  glm::vec2 UV;
};

std::vector<Component> ComponentVector = {
//  {"models/park_002.mgcg", "textures/Textures_City.png", glm::vec3(20.0f, 0.0f, -20.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
  {"models/beach_tile_1x1_001.mgcg", "textures/Textures_City.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  { "models/beach_tile_1x1_003.mgcg", "textures/Textures_City.png", glm::vec3(1*8.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  { "models/beach_tile_1x1_004.mgcg", "textures/Textures_City.png", glm::vec3(2*8.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  { "models/beach_tile_1x1_006.mgcg", "textures/Textures_City.png", glm::vec3(3*8.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/beach_tile_1x1_002.mgcg", "textures/Textures_City.png", glm::vec3(4*8.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/landscape_entertainments_006.mgcg", "textures/Textures_City.png", glm::vec3(-12.0f, 0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_008.mgcg", "textures/Textures_City.png", glm::vec3(16.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", glm::vec3(8.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", glm::vec3(24.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", glm::vec3(32.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", glm::vec3(40.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_001.mgcg", "textures/Textures_City.png", glm::vec3(48.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_004.mgcg", "textures/Textures_City.png", glm::vec3(56.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f},
  {"models/road_tile_1x1_004.mgcg", "textures/Textures_City.png", glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f},
  {"models/store_003.mgcg", "textures/Textures_City.png", glm::vec3(8.0f, 0.0f, -16.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/transport_bus_005_transport_bus_005.001.mgcg", "textures/Textures_City.png", glm::vec3(0.0f, 0.0f, -16.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/landscape_entertainments_007.mgcg", "textures/Textures_City.png", glm::vec3(4+5*8.0f, 0.0f, 3.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/landscape_entertainments_003.mgcg", "textures/Textures_City.png", glm::vec3(4+5*8.0f, 0.0f, -18.0f), glm::vec3(0.9f, 1.0f, 0.9f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/landscape_entertainments_008.mgcg", "textures/Textures_City.png", glm::vec3(18+5*8.0f, 0.0f, 1.5f), glm::vec3(0.9f, 1.0f, 0.9f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f},
  {"models/landscape_entertainments_010.mgcg", "textures/Textures_City.png", glm::vec3(18+5*8.0f, 0.0f, -18.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f},
  {"models/apartment_008.mgcg", "textures/Textures_City.png", glm::vec3(24.0f, 0.0f, -16.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/apartment_012.mgcg", "textures/Textures_City.png", glm::vec3(32.0f, 0.0f, -16.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_1x1_010.mgcg", "textures/Textures_City.png", glm::vec3(2*8.0f, 0.0f, -2*8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f},
  {"models/road_tile_2x2_006.mgcg", "textures/Textures_City.png", glm::vec3(4+2*8.0f, 0.0f, -4-3*8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
  {"models/road_tile_2x2_005.mgcg", "textures/Textures_City.png", glm::vec3(4.0f, 0.0f, -4-3*8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f}
};
//TODO: add tile_river;

class ComputerGraphicsProject2024 : public BaseProject {
protected:

  float Ar;

  DescriptorSetLayout DSL;
  Pipeline Pip;
  VertexDescriptor VDVertex;
  TextMaker txt;

  glm::vec3 CamPos = glm::vec3(0.0, 1.0, -8.0);
  float CamAlpha = 0.0f, CamBeta = 0.0f;
  glm::mat4 ViewMatrix;

  bool spectatorMode = false;


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
    std::cout << "Window resized to: " << w << " x " << h << "\n";
    Ar = (float)w / (float)h;
  }

  void localInit() {

    DSL.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(UniformBufferObject), 1},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1} });

    VDVertex.init(this, { {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX} }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),sizeof(glm::vec3), NORMAL},
        {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(glm::vec2), UV}
      });

    Pip.init(this, &VDVertex, "shaders/Vert.spv", "shaders/Frag.spv", { &DSL });

    //METODO CHE INIZIALIZZA TUTTI I MODELLI E TEXTURE DELL'ARRAY DI ASSET
    for (int i = 0; i < ComponentVector.size(); i++) {
      ComponentVector[i].model.init(this, &VDVertex, ComponentVector[i].ObjPath, MGCG);
      ComponentVector[i].texture.init(this, ComponentVector[i].TexturePath);
    }
    

    //DA CAMBIARE
//    DPSZs.uniformBlocksInPool = 3;
    DPSZs.uniformBlocksInPool = ComponentVector.size();
    DPSZs.texturesInPool = ComponentVector.size();
    DPSZs.setsInPool = ComponentVector.size();

    std::cout << "Initializing text\n";
    //txt.init(this, &outText);

    std::cout << "Initialization completed!\n";
    std::cout << "Uniform Blocks in the Pool  : " << DPSZs.uniformBlocksInPool << "\n";
    std::cout << "Textures in the Pool        : " << DPSZs.texturesInPool << "\n";
    std::cout << "Descriptor Sets in the Pool : " << DPSZs.setsInPool << "\n";

    ViewMatrix = glm::translate(glm::mat4(1), -CamPos);
  }

  void pipelinesAndDescriptorSetsInit() {

    Pip.create();

    //METODO CHE INIZIALIZZA TUTTI I DESCRIPTOR SET
    int sizeCV = ComponentVector.size();
    for (int i = 0; i < sizeCV; i++) {
      ComponentVector[i].DS.init(this, &DSL, {&ComponentVector[i].texture});
    }

  }

  void pipelinesAndDescriptorSetsCleanup() {

    Pip.cleanup();

    //CLEAN UP DI TUTTI I DESCRIPTOR SET
    for (int i = 0; i < ComponentVector.size(); i++) {
      ComponentVector[i].DS.cleanup();
    }

  }

  void localCleanup() {

    //CLEAN UP DI TUTTI I MODEL E TEXTURES
    for (int i = 0; i < ComponentVector.size(); i++) {
      ComponentVector[i].model.cleanup();
      ComponentVector[i].texture.cleanup();
    }

    DSL.cleanup();
    Pip.destroy();
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

  }

  void updateUniformBuffer(uint32_t currentImage) {

    
    float deltaT, cameraAngle = 0.0;;
    glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f), cameraPosition = {0.0,0.0,0.0};
    bool fire = false;

    getSixAxis(deltaT, m, r, fire);

    const float ROT_SPEED = glm::radians(120.0f);
    const float MOVE_SPEED = 5.0f;

    glm::mat4 Mv;

    CamAlpha = CamAlpha - ROT_SPEED * deltaT * r.y;
    CamBeta = CamBeta - ROT_SPEED * deltaT * r.x;
    CamBeta = CamBeta < radians(-90.0f) ? radians(-90.0f) : (CamBeta > radians(90.0f) ? radians(90.0f) : CamBeta);


    vec3 ux = rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1);
    vec3 uz = rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
    vec3 uy = rotate(mat4(1.0f), CamBeta, vec3(1, 0, 1)) * vec4(0, 1, 0, 1);
    CamPos = CamPos + MOVE_SPEED * m.x * ux * deltaT;
    CamPos = CamPos - MOVE_SPEED * m.z * uz * deltaT;
    if (spectatorMode) {
        CamPos = CamPos - MOVE_SPEED * m.y * uy * deltaT;
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

    if (glfwGetKey(window, GLFW_KEY_L)) {
        printCordinates(cameraAngle - 360.0 * floor(cameraAngle / 360.0));
    }

    if (glfwGetKey(window, GLFW_KEY_P)) {
        spectatorMode = true;
    }

    if (glfwGetKey(window, GLFW_KEY_O)) {
        spectatorMode = false;
    }

    // Here is where you actually update your uniforms
    glm::mat4 M = glm::perspective(glm::radians(45.0f), Ar, 0.1f, 160.0f);
    M[1][1] *= -1;

    glm::mat4 ViewPrj = M * Mv;
    glm::mat4 baseTr = glm::mat4(1.0f);

    // objects
    UniformBufferObject Ubo{};
    for (int i = 0; i < ComponentVector.size(); i++) {
     
      //TODO: do we perform the rotation before or after the other movement? leggi le slide

      glm::mat4 Transform = glm::translate(glm::mat4(1), ComponentVector[i].pos);
      Transform = glm::scale(Transform, ComponentVector[i].scale);
      if (ComponentVector[i].angle != 0.0f) {
        Transform = glm::rotate(Transform, glm::radians(ComponentVector[i].angle), ComponentVector[i].rot);
      }
      
      Ubo.mMat = Transform;
      Ubo.mvpMat = ViewPrj * Ubo.mMat;
      Ubo.nMat = glm::inverse(glm::transpose(Ubo.mMat));

      ComponentVector[i].DS.map(currentImage, &Ubo, 0);

    }
  }

  /*
    * Deve essere passato in ingresso la variabile "cameraPosition" e "cameraAngle" che sono presenti nella funzione updateUniformBuffer.
    * Le variabili x1,x2,z invece sono rispettivamente la coordinita più a sinistra dell'oggetto, più a destra (dimensioni del modello) e la sua profondità (posizione 
    * in cui è rispetto asse Z).
    * Per avviare questo metodo devi immaginarti l'oggetto dritto, senza alcuna rotazione, prima di effettuare effettivamente il check infatti raddrizzo tutto.
    * Ecco spiegato il motivo di "modelRotation", mi serve per raddrizzare
    */
  bool checkInteraction(vec3 cameraPosition, float cameraAngle, float x1, float x2, float z, vec3 modelRotation) {
      //makeRight(cameraPosition, modelRotation, z); //CI STO LAVORANDO
      const float minDistance = 5;
      float distance, alpha, center, beta, halfSide, left, right;
      center = (x2 + x1) / 2;
      halfSide = (x2 - x1) / 2;
      distance = sqrt(pow(((x2 - x1) - cameraPosition.x), 2) + pow(z - cameraPosition.z, 2));
      if (distance < minDistance && cameraPosition.x >= x1 && cameraPosition.x <= x2 && z < cameraPosition.z) {
          alpha = 60 - (cameraPosition.z - z) / minDistance * 60;
          if (center < cameraPosition.x) {
              beta = alpha * (cameraPosition.x - center) / halfSide; //Zero se sono pefettamente al centro
              left = alpha + beta;
              right = alpha - beta;
          }
          else {
              beta = alpha * (-cameraPosition.x + center) / halfSide;
              left = alpha - beta;
              right = alpha + beta;
          }
          /*
          cout << "Camera angle must be between: " << left << " - " << 360.0 - right << '\n';
          cout << "Camera angle: " << cameraAngle << '\n';
          */
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
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}