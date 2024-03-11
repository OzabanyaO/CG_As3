#undef GLFW_DLL
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <cmath>

#include "Libs/Shader.h"
#include "Libs/Window.h"
#include "Libs/Mesh.h"
#include "Libs/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint WIDTH = 800, HEIGHT = 600;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

float yaw = -90.0f, pitch = 0.0f;

glm::vec3 lightColour = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec3 lightPos = glm::vec3(5.0f, 5.0f, 0.0f);

//Vertex Shader
static const char* vShader = "Shaders/shader.vert";
static const char* lightVShader = "Shaders/lightShader.vert";

//Fragment Shader
static const char* fShader = "Shaders/shader.frag";
static const char* lightFShader = "Shaders/lightShader.frag";

void CreateOBJ()
{   
    Mesh *obj1 = new Mesh();
    bool loaded1 = obj1->CreateMeshFromOBJ("Models/chairComponent.obj");
    if (loaded1)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj1);
        }
    }
    else
    {
        std::cout<<"Failed to load model1"<<std::endl;
    }

    Mesh *obj2 = new Mesh();
    bool loaded2 = obj2->CreateMeshFromOBJ("Models/chairPad.obj");
    if (loaded2)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj2);
        }
    }
    else
    {
        std::cout<<"Failed to load model2"<<std::endl;
    }

    Mesh *obj3 = new Mesh();
    bool loaded3 = obj3->CreateMeshFromOBJ("Models/tableLeg.obj");
    if (loaded3)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj3);
        }
    }
    else
    {
        std::cout<<"Failed to load model3"<<std::endl;
    }

    Mesh *obj4 = new Mesh();
    bool loaded4 = obj4->CreateMeshFromOBJ("Models/tablePad.obj");
    if (loaded4)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj4);
        }
    }
    else
    {
        std::cout<<"Failed to load model4"<<std::endl;
    }

    Mesh *obj5 = new Mesh();
    bool loaded5 = obj5->CreateMeshFromOBJ("Models/cutAndPlate.obj");
    if (loaded5)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj5);
        }
    }
    else
    {
        std::cout<<"Failed to load model5"<<std::endl;
    }

    Mesh *obj6 = new Mesh();
    bool loaded6 = obj6->CreateMeshFromOBJ("Models/floor.obj");
    if (loaded6)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj6);
        }
    }
    else
    {
        std::cout<<"Failed to load model6"<<std::endl;
    }

    Mesh *obj7 = new Mesh();
    bool loaded7 = obj7->CreateMeshFromOBJ("Models/wall.obj");
    if (loaded7)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj7);
        }
    }
    else
    {
        std::cout<<"Failed to load model7"<<std::endl;
    }

    Mesh *obj8 = new Mesh();
    bool loaded8 = obj8->CreateMeshFromOBJ("Models/glass.obj");
    if (loaded8)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj8);
        }
    }
    else
    {
        std::cout<<"Failed to load model8"<<std::endl;
    }

    Mesh *obj13 = new Mesh();
    bool loaded13 = obj13->CreateMeshFromOBJ("Models/cube.obj");
    if (loaded13)
    {
        for (int i = 0; i < 1; i++)
        {
            meshList.push_back(obj13);
        }
    }
    else
    {
        std::cout<<"Failed to load model13"<<std::endl;
    }
}

void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(shader1);

    Shader* shader5 = new Shader();
    shader5->CreateFromFiles(lightVShader, lightFShader);
    shaderList.push_back(shader5);
}

void checkMouse() 
{
    double xpos, ypos;

    glfwGetCursorPos(mainWindow.getWindow(), &xpos, &ypos);

    static bool firstMouse = true;
    static float lastX = 0.0f;
    static float lastY = 0.0f;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
    }
    
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);
}

unsigned int LoadTextureJPG(const std::string& filename)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }

    stbi_image_free(data);
    return textureID;
}

unsigned int LoadTexturePNG(const std::string& filename)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }

    stbi_image_free(data);
    return textureID;
}

int main()
{
    mainWindow = Window(WIDTH, HEIGHT, 3, 3);
    mainWindow.initialise();

    CreateOBJ();
    CreateShaders();

    GLuint uniformModel = 0;
    GLuint uniformProjection = 0;
    GLuint uniformView = 0;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPos);
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDirection, up));
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat) mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    //texture
    unsigned int texture1 = LoadTextureJPG("Textures/brownwood.jpg");
    unsigned int texture2 = LoadTextureJPG("Textures/chairPadTextures.jpg");
    unsigned int texture3 = LoadTextureJPG("Textures/brownwood.jpg");
    unsigned int texture4 = LoadTextureJPG("Textures/tablePadTextures.jpg");
    unsigned int texture5 = LoadTextureJPG("Textures/steelTextures.jpg");
    unsigned int texture6 = LoadTextureJPG("Textures/floorTextures.jpg");
    unsigned int texture7 = LoadTextureJPG("Textures/blackwood.jpg");
    unsigned int texture8 = LoadTextureJPG("Textures/glassTextures.jpg");

    unsigned int textures[] = { texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8 };

    float deltaTime, lastFrame;

    //Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        float currenFrame = static_cast<float>(glfwGetTime());
        deltaTime = currenFrame - lastFrame;
        lastFrame = currenFrame;

        //Get + Handle user input events
        glfwPollEvents();

        checkMouse();

        glm::vec3 direction;

        direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        direction.y = sin(glm::radians(pitch));

        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            cameraPos += cameraDirection * deltaTime * 5.0f;
        }
        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            cameraPos -= cameraDirection * deltaTime * 5.0f;
        }
        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            cameraPos -= cameraRight * deltaTime * 5.0f;
        }
        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            cameraPos += cameraRight * deltaTime * 5.0f;
        }

        cameraDirection = glm::normalize(direction);
        cameraRight = glm::normalize(glm::cross(cameraDirection, up));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));

        //Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw here 1
        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->GetUniformLocation("model");
        uniformProjection = shaderList[0]->GetUniformLocation("projection");
        uniformView = shaderList[0]->GetUniformLocation("view");

        glm::mat4 view (1.0f);
        glm::mat4 cameraPosMat (1.0f);
        cameraPosMat[3][0] = -cameraPos.x;
        cameraPosMat[3][1] = -cameraPos.y;
        cameraPosMat[3][2] = -cameraPos.z;

        glm::mat4 cameraRotateMat(1.0f);
        cameraRotateMat[0] = glm::vec4(cameraRight.x, cameraUp.x, -cameraDirection.x, 0.0f);
        cameraRotateMat[1] = glm::vec4(cameraRight.y, cameraUp.y, -cameraDirection.y, 0.0f);
        cameraRotateMat[2] = glm::vec4(cameraRight.z, cameraUp.z, -cameraDirection.z, 0.0f);

        view = cameraRotateMat * cameraPosMat;

        //light
        glUniform3fv(shaderList[0]->GetUniformLocation("lightColour"), 1, (GLfloat *)&lightColour);
        glUniform3fv(shaderList[0]->GetUniformLocation("lightPos"), 1, (GLfloat *)&lightPos);
        glUniform3fv(shaderList[0]->GetUniformLocation("viewPos"), 1, (GLfloat *)&cameraPos);

        //Object
        for (int i = 0; i < 8;i++)
        {
            glm::mat4 model (1.0f);
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[i]); 
            
            meshList[i]->RenderMesh();
        }

        shaderList[1]->UseShader();
        uniformModel = shaderList[1]->GetUniformLocation("model");
        uniformProjection = shaderList[1]->GetUniformLocation("projection");
        uniformView = shaderList[1]->GetUniformLocation("view");

        glm::mat4 model (1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

        glUniform3fv(shaderList[1]->GetUniformLocation("lightColour"), 1, (GLfloat *)&lightColour);

        meshList[8]->RenderMesh();
        //end draw

        glUseProgram(0);

        //magic word - SAKURA

        mainWindow.swapBuffers();
    }

    return 0;
}
