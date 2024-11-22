#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
    private: GLFWwindow* window;
    private: VkInstance instance;

public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow() {
        glfwInit();
        // init glfw window without opengl context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // disable resizable window 
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // assign window with constant dimensions, nullptr for monitor and share params
        window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanTriangle", nullptr, nullptr);

    }

private:
    void initVulkan() {
        createInstance();
    }

    /* Application main loop executes until window is desrtoyed*/
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    /* Cleanup the application on close, destroy unused objects.*/
    void cleanup() {
        // destroy vulkan isntance before widow exits
        
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);

        glfwTerminate();
    }

    /* Create the vulkan instance and pass a struct of aplication data */
    void createInstance(){
        VkApplicationInfo appInfo{};

        // specify the struct type
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        // assign struct values
        appInfo.pApplicationName = "VulkanTriangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        // check the supported extensions by the users gpu driver
        // first get number of extensions to allocate memory to an array
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        // create vector/array extensions
        std::vector<VkExtensionProperties> extensions(extensionCount);

        //querey for available extensions
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:\n";

        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }


        // create instance. Vk functions almost always return success or failure status code
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }
};

int main() {
    // create app
    HelloTriangleApplication app;

    try {
        // run app
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}