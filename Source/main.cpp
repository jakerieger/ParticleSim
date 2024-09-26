// Author: Jake Rieger
// Created: 9/4/2024.
//

#include "Types.h"
#include "OpenGLTK.h"
#include "Glfw/GlfwApp.h"

class ParticleSim final : public GLTK::IGlfwApp {
public:
    ParticleSim(const str& title, int width, int height) : IGlfwApp(title, width, height) {}
    void Update(f32 dT) override {}
    void Render() override {}
};

int main() {
    ParticleSim app("ParticleSim", 800, 600);
    app.Run();
    return 0;
}