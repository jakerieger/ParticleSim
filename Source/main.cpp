// Author: Jake Rieger
// Created: 9/4/2024.
//

#include "Types.h"
#include "OpenGLTK.h"
#include "Glfw/GlfwApp.h"

class ParticleSim final : public GLTK::IGlfwApp {
public:
    ParticleSim(const str& title, int width, int height) : IGlfwApp(title, width, height) {
        mCamera = GLTK::CreateCamera<GLTK::OrthoCamera>(width, height);
    }

    void CreateGLResources() override {
        mParticleShader = std::make_shared<GLTK::Shader>(Path("Data/shaders/particle.vert"),
                                                         Path("Data/shaders/particle.frag"));
    }

    void DestroyGLResources() override {}

    void Update(f32 dT) override {
        mCamera->Update();
    }

    void Render() override {}

private:
    Shared<GLTK::OrthoCamera> mCamera;
    Shared<GLTK::Shader> mParticleShader;
};

int main() {
    ParticleSim app("ParticleSim", 800, 600);
    app.Run();
    return 0;
}