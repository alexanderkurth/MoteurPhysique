#ifndef GLSTUFF_H
#define GLSTUFF_H

// #include <ft2build.h>
// #include FT_FREETYPE_H

#include "../../include/glm/gtc/type_ptr.hpp"
#include "../../include/GL/glew.h"
#include "../physics/rigidbody.h"
#include "shader.h"
#include "mesh.h"
#include <map>

// FT_Library ft;
// FT_Face face;

// int Init()
// {
//     if (FT_Init_FreeType(&ft))
//     {
//         return -1;
//     }

//     if (FT_New_Face(ft, "../../arial.ttf", 0, &face))
//     {
//         return -1;
//     }

//     FT_Set_Pixel_Sizes(face, 0, 48);

//     if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
//     {
//         return -1;
//     }
// }

// struct Character
// {
//     unsigned int TextureID; // ID handle of the glyph texture
//     glm::ivec2 Size;        // Size of glyph
//     glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
//     unsigned int Advance;   // Offset to advance to next glyph
// };

// std::map<char, Character> Characters;



Shader *shader = nullptr;


// Compile and enable the shader.
void useShader(const char *vs, const char *fs)
{
    shader = new Shader(vs, fs);
    shader->use();
}

// Create the required buffer for openGL.
unsigned VBO, VAO, VAOCube, VBOCube, VAOPlane, VBOPlane, VAOText, VBOText;
void setupRendering()
{
    // Vertex array.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Fill vertex buffer with cube points.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(meshSmallCubeDataArray), meshSmallCubeDataArray, GL_STATIC_DRAW);

    glBindVertexArray(VAO); //Binds the Vertices Buffer Object to the Vertex Array Object

    // Specify that vertex position start at index 0.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Speficy that vertex normal start at index 3
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /**/
    // Vertex array.
    glGenVertexArrays(1, &VAOCube);
    glGenBuffers(1, &VBOCube);

    // Fill vertex buffer with cube points.
    glBindBuffer(GL_ARRAY_BUFFER, VBOCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(meshDataArray), meshDataArray, GL_STATIC_DRAW);

    glBindVertexArray(VAOCube); //Binds the Vertices Buffer Object to the Vertex Array Object

    // Specify that vertex position start at index 0.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Speficy that vertex normal start at index 3
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /**/
    // Vertex array.
    glGenVertexArrays(1, &VAOPlane);
    glGenBuffers(1, &VBOPlane);

    // Fill vertex buffer with cube points.
    glBindBuffer(GL_ARRAY_BUFFER, VBOPlane);
    glBufferData(GL_ARRAY_BUFFER, sizeof(meshBigCubeDataArray), meshBigCubeDataArray, GL_STATIC_DRAW);

    glBindVertexArray(VAOPlane); //Binds the Vertices Buffer Object to the Vertex Array Object

    // Specify that vertex position start at index 0.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /**/
    glGenVertexArrays(1, &VAOText);
    glGenBuffers(1, &VBOText);
    glBindVertexArray(VAOText);
    glBindBuffer(GL_ARRAY_BUFFER, VBOText);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  
}

// Free up the allocated buffers.
void cleanRendering()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAOCube);
    glDeleteBuffers(1, &VBOCube);
    glDeleteVertexArrays(1, &VAOPlane);
    glDeleteBuffers(1, &VBOPlane);
    glDeleteVertexArrays(1, &VAOText);
    glDeleteBuffers(1, &VBOText);
}

// Send projection matrix and other info to shader.
void setupCamera(float screenWidth, float screenHeight)
{
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
    shader->setMat4("projection", projection);

    // pass transformation matrices to the shader
    shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", glm::vec3(3.0f, 0.0f, -3.0f));
}

// Change the view matrix of the camera.
void changeViewPoint(const glm::vec3 &pos)
{
    glm::mat4 view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader->setMat4("view", view);
}

// Display the rigid body on the screen.
void renderBody(const RigidBody &body)
{
    glm::mat4 model = glm::transpose(glm::make_mat4(body.transform.matrix.data));
    shader->setMat4("model", model);
    shader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

    glBindVertexArray(VAOCube);
    glDrawArrays(GL_LINE_STRIP, 0, 24);
}

void renderPlane(Vector3 v)
{
    Matrix4 pos{1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1};

    pos = pos * make_translate(v);

    glm::mat4 model = glm::transpose(glm::make_mat4(pos.data));
    shader->setMat4("model", model);
    shader->setVec3("objectColor", glm::vec3(0.35f, 0.35f, 0.0f));

    glBindVertexArray(VAOPlane);
    glDrawArrays(GL_LINE_STRIP, 0, 24);
}

// Display the rigid body on the screen.
void renderPoint(Vector3 v)
{
    Matrix4 pos{1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1};

    Vector3 v1{0.1f, 0.1f, 0.1f};

    pos = pos * make_translate(v);

    glm::mat4 model = glm::transpose(glm::make_mat4(pos.data));
    shader->setMat4("model", model);

    shader->setVec3("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

// void RenderText (std::string text, float x, float y, float scale, glm::vec3 color)
// {
//     // activate corresponding render state	
//     Shader *s = new Shader("..\\..\\shaders\\glyph.vs","..\\..\\shaders\\glyph.fs");

//     glUniform3f(glGetUniformLocation(s->ID, "textColor"), color.x, color.y, color.z);
//     glActiveTexture(GL_TEXTURE0);
//     glBindVertexArray(VAOText);

//     // iterate through all characters
//     std::string::const_iterator c;
//     for (c = text.begin(); c != text.end(); c++)
//     {
//         Character ch = Characters[*c];

//         float xpos = x + ch.Bearing.x * scale;
//         float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

//         float w = ch.Size.x * scale;
//         float h = ch.Size.y * scale;
//         // update VBO for each character
//         float vertices[6][4] = {
//             { xpos,     ypos + h,   0.0f, 0.0f },            
//             { xpos,     ypos,       0.0f, 1.0f },
//             { xpos + w, ypos,       1.0f, 1.0f },

//             { xpos,     ypos + h,   0.0f, 0.0f },
//             { xpos + w, ypos,       1.0f, 1.0f },
//             { xpos + w, ypos + h,   1.0f, 0.0f }           
//         };
//         // render glyph texture over quad
//         glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//         // update content of VBO memory
//         glBindBuffer(GL_ARRAY_BUFFER, VBOText);
//         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         // render quad
//         glDrawArrays(GL_TRIANGLES, 0, 6);
//         // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//         x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
//     }
//     glBindVertexArray(0);
//     glBindTexture(GL_TEXTURE_2D, 0);
// }

#endif // !GLSTUFF_H