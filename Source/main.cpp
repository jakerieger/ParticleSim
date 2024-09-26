// Author: Jake Rieger
// Created: 9/4/2024.
//

#include "Types.h"

#define GLTK_INCLUDE_GLFW
#include "OpenGLTK.h"
#include "Primitives.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace GLTK;

class ParticleSim final : public IGlfwApp {
public:
    ParticleSim(const str& title, int width, int height) : IGlfwApp(title, width, height) {
        mCamera = std::make_shared<OrthoCamera>(width, height);
    }

    void CreateGLResources() override {
        mParticleShader = std::make_shared<Shader>(Path("Data/shaders/particle.vert"),
                                                   Path("Data/shaders/particle.frag"));

        mParticleTexture = Texture::Load("Data/sprites/particle.png");

        mParticleVAO                 = std::make_unique<VertexArray>();
        Vector<VertexAttrib> attribs = {
          VertexAttrib("aVertex", 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)0),
        };
        mParticleVAO->Bind();
        mParticleVAO->CreateVertexBuffer<f32>(Primitives::QuadVertTex, attribs);
        VertexArray::Unbind();
    }

    void DestroyGLResources() override {
        mParticleShader.reset();
        mParticleVAO.reset();
        Texture::Delete(mParticleTexture);
    }

    void Update() override {
        // `mClock` is a member of IGlfwApp and can be used to get various time metrics.
        const auto dT = mClock->GetDeltaTime();

        mCamera->Update();
    }

    void Render() override {
        mParticleShader->Bind();
        mParticleShader->SetInt("uSprite", 0);
        auto model     = glm::mat4(1.0f);
        model          = glm::scale(model, glm::vec3(10.f, 10.f, 10.f));
        const auto mvp = mCamera->GetViewProjection() * model;
        mParticleShader->SetMat4("uMVP", mvp);

        Texture::Bind(mParticleTexture, 0);

        mParticleVAO->Bind();
        mParticleVAO->Draw(GL_TRIANGLE_STRIP);

        VertexArray::Unbind();
        Texture::Unbind();
        Shader::Unbind();
    }

private:
    Shared<OrthoCamera> mCamera;
    Shared<Shader> mParticleShader;
    Unique<VertexArray> mParticleVAO;
    u32 mParticleTexture = 0;
};

int main() {
    ParticleSim app("ParticleSim", 800, 600);
    app.Run();
    return 0;
}