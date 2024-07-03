// This has been adapted from the Vulkan tutorial
// test 2 donato repo clone
#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"

std::vector<SingleText> outText = {
	{2, {"City", "","",""}, 0, 0} };

struct GlobalUniformBufferObject {
	alignas(16) glm::vec3 lightDir;
	alignas(16) glm::vec4 lightColor;
	alignas(16) glm::vec3 eyePos;
};

struct Asset {
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

class ComputerGraphicsProject2024 : public BaseProject {
protected:

	float Ar;

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

	}

	void pipelinesAndDescriptorSetsInit() {

	}

	void pipelinesAndDescriptorSetsCleanup() {

	}

	void localCleanup() {

	}

	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {

	}

	void updateUniformBuffer(uint32_t currentImage) {

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
