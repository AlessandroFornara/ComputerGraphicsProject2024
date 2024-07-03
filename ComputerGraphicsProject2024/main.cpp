// This has been adapted from the Vulkan tutorial
// test 2 donato repo clone
#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"

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
