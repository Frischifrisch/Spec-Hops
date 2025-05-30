#include "Background.h"

#include "../Application.h"
#include "../Input.h"

Background::Background(const std::string& name)
   : GameObject(name, DrawPriority::Background, {0, 0})
   , pointBuffer(Buffer<glm::vec2>(
        {
           glm::vec2(-1, -1),
           glm::vec2(+1, -1),
           glm::vec2(+1, +1),
           glm::vec2(-1, +1),
        },
        wgpu::bothBufferUsages(wgpu::BufferUsage::CopyDst, wgpu::BufferUsage::Vertex)))
   , indexBuffer(IndexBuffer(
        {
           0, 1, 2, // Triangle #0 connects points #0, #1 and #2
           0, 2, 3  // Triangle #1 connects points #0, #2 and #3
        },
        wgpu::bothBufferUsages(wgpu::BufferUsage::CopyDst, wgpu::BufferUsage::Index)))
   , uniformBuffer(
        UniformBuffer<StarUniforms>({StarUniforms(0.0f, Application::get().windowSize())},
                                    wgpu::bothBufferUsages(wgpu::BufferUsage::CopyDst, wgpu::BufferUsage::Uniform))) {}

void Background::render(Renderer& renderer, RenderPass& renderPass) {
   StarUniforms uniform(Input::currentTime, Application::get().windowSize());
   uniformBuffer.upload({uniform});
   BindGroup bindGroup =
      renderer.stars.BindGroups(std::forward_as_tuple(std::forward_as_tuple(uniformBuffer, 0))).front();

   renderPass.Draw(renderer.stars, pointBuffer, indexBuffer, bindGroup, {});
}

void Background::update() {
   // Update logic for Background
}
