// This has been adapted from the Vulkan tutorial
#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"

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
  {"models/park_002.mgcg", "textures/Textures_City.png", glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
  {"models/beach_tile_1x1_003.mgcg", "textures/Textures_City.png", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)}
};

class ComputerGraphicsProject2024 : public BaseProject {
protected:

  float Ar;

  DescriptorSetLayout DSL;
  Pipeline Pip;
  VertexDescriptor VDVertex;
  TextMaker txt;

  glm::vec3 CamPos = glm::vec3(0.0, 0.1, 5.0);
  glm::mat4 ViewMatrix;


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
    DPSZs.uniformBlocksInPool = 2;
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
    for (int i = 0; i < ComponentVector.size(); i++) {
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

    float deltaT;
    glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
    bool fire = false;
    getSixAxis(deltaT, m, r, fire);

    const float ROT_SPEED = glm::radians(120.0f);
    const float MOVE_SPEED = 2.0f;

    // The Fly model update proc.
    ViewMatrix = glm::rotate(glm::mat4(1), ROT_SPEED * r.x * deltaT,
      glm::vec3(1, 0, 0)) * ViewMatrix;
    ViewMatrix = glm::rotate(glm::mat4(1), ROT_SPEED * r.y * deltaT,
      glm::vec3(0, 1, 0)) * ViewMatrix;
    ViewMatrix = glm::rotate(glm::mat4(1), -ROT_SPEED * r.z * deltaT,
      glm::vec3(0, 0, 1)) * ViewMatrix;
    ViewMatrix = glm::translate(glm::mat4(1), -glm::vec3(
      MOVE_SPEED * m.x * deltaT, MOVE_SPEED * m.y * deltaT, MOVE_SPEED * m.z * deltaT))
      * ViewMatrix;

    // Standard procedure to quit when the ESC key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Here is where you actually update your uniforms
    glm::mat4 M = glm::perspective(glm::radians(45.0f), Ar, 0.1f, 160.0f);
    M[1][1] *= -1;

    glm::mat4 Mv = ViewMatrix;

    glm::mat4 ViewPrj = M * Mv;
    glm::mat4 baseTr = glm::mat4(1.0f);

    // objects
    UniformBufferObject Ubo{};
    for (int i = 0; i < ComponentVector.size(); i++) {
      glm::mat4 Transform = glm::translate(glm::mat4(1), ComponentVector[i].pos);
      Transform = glm::scale(Transform, ComponentVector[i].scale);
      Ubo.mMat = Transform;
      Ubo.mvpMat = ViewPrj * Ubo.mMat;
      Ubo.nMat = glm::inverse(glm::transpose(Ubo.mMat));

      ComponentVector[i].DS.map(currentImage, &Ubo, 0);
    }
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