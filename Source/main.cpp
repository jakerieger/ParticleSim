
#include "Types.h"
#include "OpenGLTK.h"

#include <Panic/Panic.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace GLTK;

static constexpr i32 kWindowWidth = 800;
static constexpr i32 kWindowHeight = 600;

GLFWwindow* gWindow = None;
Unique<Clock> gClock;

void Update(f32 dT);
void Render();

int main() {
    if (!glfwInit())
        Panic("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gWindow = glfwCreateWindow(kWindowWidth, kWindowHeight, "ParticleSim (x64)", None, None);
    if (!gWindow) {
        glfwTerminate();
        Panic("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(gWindow);

    if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        Panic("Failed to initialize OpenGL context");
    }

    glViewport(0, 0, kWindowWidth, kWindowHeight);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    gClock = std::make_unique<Clock>();
    gClock->Start();
    while (!glfwWindowShouldClose(gWindow)) {
        gClock->Tick();
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Update(gClock->GetDeltaTime());
        Render();

        glfwSwapBuffers(gWindow);
        gClock->Update();
    }
    gClock->Stop();

    gClock.reset();
    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}

void Update(f32 dT) {
}

void Render() {}