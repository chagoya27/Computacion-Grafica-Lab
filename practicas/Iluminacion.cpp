/*	Práctica 8
*	Chagoya Gonzalez Leonardo
*	12  de octubre de 2025
*	318218814
*/


// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(-4.0f, 0.0f, 0.0f); //para modificar la posición inicial de la luz 1
glm::vec3 lightPos2(0.0f, 0.0f, -10.0f); //para modificar la posición inicial de la luz 2
float movelightPos = 0.0f; //movimiento de la luz
float movelightPos2 = 0.0f; //movimiento de la luz 2
float theta1 = 0.0f; //angulo de la luz
float theta2 = 0.0f; //angulo de la luz 2

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

// variables para generar las trayectorias de las luces (elipse)
float a1 = 16.0f, b1 = 10.0f, c1 = 0.0f;
float a2 = 20.0f, b2 = 10.0f, c2 = 0.0f;

// Variables para el modo dia y noche
bool light1On = true;
bool light2On = false;


float PI_LIMIT = 3.1415926535f;

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 8. Leonardo Chagoya", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }


    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



    // Load models
    Model red_dog((char*)"Models/escenarioP6.obj");
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

	//posiciones y normales del cubo
    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    image = stbi_load("Models/Texture_albedo.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Movimiento de elipses de las luces

        float x1 = a1 * cos(theta1);
        float y1 = b1 * sin(theta1);
        float z1 = c1 * sin(theta1 * 2.0f);

		float x2 = a2 * cos(theta2);
		float y2 = b2 * sin(theta2);
		float z2 = c2 * sin(theta2 * 2.0f);

        glm::vec3 currentLightPos1 = lightPos + glm::vec3(x1, y1, z1);
        glm::vec3 currentLightPos2 = lightPos2 + glm::vec3(0,y2 ,x2);
        
        lightingShader.Use();
        
        //posicion de la camara
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


        //luz1
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position"); //shader de iluminacion
        glUniform3f(lightPosLoc, currentLightPos1.x, currentLightPos1.y, currentLightPos1.z);
		
        //luz 2
        GLint lightPosLoc2 = glGetUniformLocation(lightingShader.Program, "light2.position");
        glUniform3f(lightPosLoc2, 0, currentLightPos2.y, currentLightPos2.x);

		//colores de las luces
		glm::vec3 lightColor1 = glm::vec3(1.00f, 1.00f, 0.98f); //blanco para el dia
        glm::vec3 lightColor2 = glm::vec3(0.00f, 0.00f, 1.00f); // azul intenso para la noche



		//luz 1 
        if (light1On) //encendida
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"),
                lightColor1.r * 0.25f, lightColor1.g * 0.25f, lightColor1.b * 0.25f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"),
                lightColor1.r * 1.0f, lightColor1.g * 1.0f, lightColor1.b * 1.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"),
                lightColor1.r * 0.2f, lightColor1.g * 0.2f, lightColor1.b * 0.2f);
        }
		else //apagada
        {
            
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.0f, 0.0f, 0.0f);
        }

        // Luz 2
		if (light2On) //encendida
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"),
                lightColor2.r * 0.5f, lightColor2.g * 0.5f, lightColor2.b * 0.2f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"),
                lightColor2.r * 0.2f, lightColor2.g * 0.2f, lightColor2.b * 1.5f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"),
                lightColor2.r * 0.5f, lightColor2.g * 0.5f, lightColor2.b * 0.2f);
        }
		else //apagada
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"), 0.0f, 0.0f, 0.0f);
        }



        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Set material properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.9f, 0.9f, 0.9f); 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.3f, 0.3f, 0.3f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);



        // Draw the loaded model
        glm::mat4 model(1);
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        red_dog.Draw(lightingShader);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        

        glBindVertexArray(0);




        //dibujar las lamparas
        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// cubo blanco (luz 1)
        model = glm::mat4(1.0f);
        model = glm::translate(model, currentLightPos1);
        model = glm::scale(model, glm::vec3(0.5f));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(lampshader.Program, "lampColor"), lightColor1.r, lightColor1.g, lightColor1.b);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

		// cubo azul (luz 2)
        model = glm::mat4(1.0f);
        model = glm::translate(model, currentLightPos2);
        model = glm::scale(model, glm::vec3(0.5f));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(lampshader.Program, "lampColor"), lightColor2.r, lightColor2.g, lightColor2.b);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
    if (keys[GLFW_KEY_O])
    {
        if (theta1 < PI_LIMIT)
        {
            theta1 += 0.05f;
        }
    }

    if (keys[GLFW_KEY_L])
    {
        if (theta1 > 0.0f)
        {
            theta1 -= 0.05f;
        }
    }
    if (keys[GLFW_KEY_I])
    {
        if (theta2 < PI_LIMIT)
        {
            theta2 += 0.05f;
        }
    }

    if (keys[GLFW_KEY_K])
    {

        if (theta2 > 0.0f)
        {
            theta2 -= 0.05f;
        }
    }

    if (keys[GLFW_KEY_1])
    {
        light1On = true;
        light2On = false;
    }

    if (keys[GLFW_KEY_2])
    {
        light1On = false;
        light2On = true;
    }


}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


