#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "mesh.h"
#include "model.h"
#include "framebuffer.h"
#include "shadow_map.h"
#include "matrix_stack.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <vector>

CLASS_PTR(Context)
class Context{
public:
    static ContextUPtr Create();
    void Render();
    void ProcessInput(GLFWwindow* window);
    void Reshape(int width, int height);
    void MouseMove(double x, double y);
    void MouseButton(int button, int action, double x, double y);

    void DrawScene(const glm::mat4& projection, const glm::mat4& view, const Program* program);
    void DrawTree(const glm::mat4& projection, const glm::mat4& view, const Program* treeProgram, const Program* leafProgram);
    // void DrawLeaves(const glm::mat4& projection, const glm::mat4& view,
    //     const glm::mat4 modelTransform, const Program* program, char direction);
    void DrawCylinder(const glm::mat4& projection, const glm::mat4 view,
        const glm::mat4 modelTransform, const Program* program);
    
    std::string MakeCodes();
    void MakeMatrices();

private:
    Context(){}
    bool Init();
    ProgramUPtr m_program;
    ProgramUPtr m_simpleProgram;
    ProgramUPtr m_textureProgram;
    ProgramUPtr m_postProgram;
    float m_gamma { 0.85f };

    MeshUPtr m_box;
    MeshUPtr m_plane;
    MeshUPtr m_cylinder;
    MeshUPtr m_leaf;

    // clear color
    glm::vec4 m_clearColor { glm::vec4(0.1f, 0.2f, 0.3f, 0.0f) };

    // light parameter
    struct Light {
        bool directional { true };
        glm::vec3 position { glm::vec3(0.0f, 15.0f, 1.0f) };
        glm::vec3 direction { glm::vec3(2.0f, -7.0f, -1.0f) };
        glm::vec2 cutoff { glm::vec2(50.0f, 5.0f) };
        float distance { 150.0f };
        glm::vec3 ambient { glm::vec3(0.3f, 0.3f, 0.3f) };
        glm::vec3 diffuse { glm::vec3(0.5f, 0.5f, 0.5f) };
        glm::vec3 specular { glm::vec3(1.0f, 1.0f, 1.0f) };
    };
    Light m_light;
    bool m_blinn { false };

    // material parameter
    MaterialPtr m_planeMaterial;
    MaterialPtr m_box1Material;
    MaterialPtr m_branchMaterial;
    MaterialPtr m_leafMaterial;
    TexturePtr m_windowTexture;

    // camera parameter
    bool m_cameraControl { false };
    glm::vec2 m_prevMousePos { glm::vec2(0.0f) };
    float m_cameraPitch { -14.0f };
    float m_cameraYaw { 0.0f };
    glm::vec3 m_cameraPos { glm::vec3(0.0f, 4.0f, 12.0f) };
    glm::vec3 m_cameraFront { glm::vec3(0.0f, 0.0f, -1.0f) };
    glm::vec3 m_cameraUp { glm::vec3(0.0f, 1.0f, 0.0f) };

    // framebuffer
    FramebufferUPtr m_framebuffer;

    // cubemap
    CubeTextureUPtr m_cubeTexture;
    ProgramUPtr m_skyboxProgram;
    ProgramUPtr m_envMapProgram;

    // shadow map
    ShadowMapUPtr m_shadowMap;
    ProgramUPtr m_lightingShadowProgram;

    // cylinder length;
    float m_cylinderRadius { 0.1f };
    float m_cylinderHeight { 1.0f };
    float m_leafRadius { 0.03f };
    float m_leafHeight { 0.1f };
    float m_radiusScaling { 0.75f };
    float m_heightScaling { 0.75f };

    ProgramUPtr m_cylinderProgram;
    BufferUPtr m_cylinderPosBuffer;
    VertexLayoutUPtr m_cylinderInstance;
    TexturePtr m_cylinderTexture;
    
    ProgramUPtr m_leafProgram;
    BufferUPtr m_leafPosBuffer;
    VertexLayoutUPtr m_leafInstance;
    TexturePtr m_leafTexture;

    // tree
    float m_angle { 30.0f };
    bool m_newCodes { false };
    bool m_stochastic { false };
    std::vector<std::string> m_codesVector;
    std::vector<glm::mat4> m_modelMatrices;
    std::vector<glm::mat4> m_leafMatrices;
    std::string m_codes { NULL };
    int m_iteration { 3 };

    // tree gui
    float gui_angle { m_angle };
    float gui_radius = { m_cylinderRadius };
    float gui_length = { m_cylinderHeight };
    char gui_axiom[1024] = { "FFA" }; 
    char gui_rules[1024 * 4] = {
        "A=F[--&&&FC][++&&&FC][--^FC][++^FC]\n"
        "C=F[--<&&FC]||[++>&&FC]||[+<^^FC]||[->^^FC]" };

    std::string m_axiom { gui_axiom };
    std::string m_rules { gui_rules };

    int m_width { WINDOW_WIDTH };
    int m_height { WINDOW_HEIGHT };
};

#endif // __CONTEXT_H__