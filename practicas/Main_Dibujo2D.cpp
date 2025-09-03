// Practica 2
// Leonardo Chagoya Gonzalez
// 23 de agosto de 2025
// 318218814


#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"
#include <vector>

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600, pixelSize = 20;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2. Leonardo Chagoya", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	//se carga la informacion de los shaders por separado
	//los parametrisos son las rutas de los archivos de los shaders
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	float vertices[] = {
		//Cuerpo del Boo
		// Rectángulo 1
		-0.8f, -0.4f, 0.0f,  1.0f, 1.0f, 1.0f,  // Abajo izquierda
		-0.8f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  // Arriba izquierda
		-0.7f, -0.4f, 0.0f,  1.0f, 1.0f, 1.0f,  // Abajo derecha
		-0.7f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  // Arriba derecha

		// Rectángulo 2
		-0.7f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,
		-0.7f,  0.2f, 0.0f,  1.0f, 1.0f, 1.0f,  
		-0.2f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 
		-0.2f,  0.2f, 0.0f,  1.0f, 1.0f, 1.0f,  

		// Rectangulo 3
		-0.6f, 0.2f, 0.0f,	1.0f,1.0f,1.0f,
		-0.6f, 0.4f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, 0.2f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, 0.4f, 0.0f,	1.0f,1.0f,1.0f,

		// Rectangulo 4
		-0.5f, 0.4f, 0.0f,	1.0f,1.0f,1.0f,
		-0.5f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, 0.4f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 5
		-0.3f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,
		-0.3f, 0.6f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, 0.6f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 6
		-0.4f, -0.6f, 0.0f,	1.0f,1.0f,1.0f,
		-0.4f, -0.5f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, -0.6f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, -0.5f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 7
		-0.2f, -0.7f, 0.0f,	1.0f,1.0f,1.0f,
		-0.2f, 0.6f, 0.0f,	1.0f,1.0f,1.0f,
		0.2f, -0.7f, 0.0f,	1.0f,1.0f,1.0f,
		0.2f, 0.6f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 8
		0.2f, -0.6f, 0.0f,	1.0f,1.0f,1.0f,
		0.2f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,
		0.5f, -0.6f, 0.0f,	1.0f,1.0f,1.0f,
		0.5f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 9
		0.2f, -0.6f, 0.0f,	1.0f,1.0f,1.0f,
		0.2f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,
		0.5f, -0.6f, 0.0f,	1.0f,1.0f,1.0f,
		0.5f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,

		
		// Rectangulo 10
		0.2f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,
		0.2f, 0.6f, 0.0f,	1.0f,1.0f,1.0f,
		0.3f, 0.5f, 0.0f,	1.0f,1.0f,1.0f,
		0.3f, 0.6f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 10
		0.5f, -0.5f, 0.0f,	1.0f,1.0f,1.0f,
		0.5f, -0.3f, 0.0f,	1.0f,1.0f,1.0f,
		0.6f, -0.5f, 0.0f,	1.0f,1.0f,1.0f,
		0.6f, -0.3f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 11
		0.5f, -0.3f, 0.0f,	1.0f,1.0f,1.0f,
		0.5f, 0.2f, 0.0f,	1.0f,1.0f,1.0f,
		0.7f, -0.3f, 0.0f,	1.0f,1.0f,1.0f,
		0.7f, 0.2f, 0.0f,	1.0f,1.0f,1.0f,


		// Rectangulo 12
		0.5f, 0.2f, 0.0f,	1.0f,1.0f,1.0f,
		0.5f, 0.4f, 0.0f,	1.0f,1.0f,1.0f,
		0.6f, 0.2f, 0.0f,	1.0f,1.0f,1.0f,
		0.6f, 0.4f, 0.0f,	1.0f,1.0f,1.0f,


		//sombras

		//rectangulo 13
		-0.2f, -0.7f, 0.0f,	0.5f,0.5f,0.5f,
		-0.2f, -0.6f, 0.0f,	0.5f,0.5f,0.5f,
		0.2f, -0.7f, 0.0f,	0.5f,0.5f,0.5f,
		0.2f, -0.6f, 0.0f,	0.5f,0.5f,0.5f,


		//rectangulo 14
		-0.4f, -0.6f, 0.0f,	0.5f,0.5,0.5f,
		-0.4f, -0.5f, 0.0f,	0.5f,0.5f,0.5f,
		-0.1f, -0.6f, 0.0f,	0.5f,0.5f,0.5f,
		-0.1f, -0.5f, 0.0f,	0.5f,0.5f,0.5f,


		//rectangulo 15
		-0.7f, -0.5f, 0.0f, 0.5f, 0.5, 0.5f,
		-0.7f, -0.4f, 0.0f, 0.5f, 0.5, 0.5f,
		-0.3f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.3f, -0.4f, 0.0f, 0.5f, 0.5f, 0.5f,

		//rectangulo 16
		-0.8f, -0.4f, 0.0f, 0.5f, 0.5, 0.5f,
		-0.8f, -0.3f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.6f, -0.4f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.6f, -0.3f, 0.0f, 0.5f, 0.5f, 0.5f,


		//rectangulo 17
		-0.8f, -0.3f, 0.0f, 0.5f, 0.5, 0.5f,
		-0.8f, -0.1f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.7f, -0.3f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.7f, -0.1f, 0.0f, 0.5f, 0.5f, 0.5f,

		//rectangulo 18
		-0.7f, -0.1f, 0.0f, 0.5f, 0.5, 0.5f,
		-0.7f, 0.2f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.6f, -0.1f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.6f, 0.2f, 0.0f, 0.5f, 0.5f, 0.5f,

		//rectangulo 19
		-0.6f, 0.2f, 0.0f, 0.5f, 0.5, 0.5f,
		-0.6f, 0.4f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.5f, 0.2f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.5f, 0.4f, 0.0f, 0.5f, 0.5f, 0.5f,

		//rectangulo 20
		-0.5f, 0.4f, 0.0f, 0.5f, 0.5, 0.5f,
		-0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.3f, 0.4f, 0.0f, 0.5f, 0.5f, 0.5f,
		-0.3f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f,


		// <<<<<<OJOS>>>>>>>
		//rectangulo 21
		0.2f, 0.1f, 0.0f, 0.0f, 0.0F, 0.0f,
		0.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.3f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.3f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,

		//rectangulo 22
		0.4f, 0.1f, 0.0f, 0.0f, 0.0F, 0.0f,
		0.4f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,


		// <<<<<<<BOCA>>>>>>>
		0.0f, -0.5f, 0.0f, 1.0f, 0.0F, 0.0f,
		0.0f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.1f, -0.4f, 0.0f, 1.0f, 0.0F, 0.0f,
		0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.2f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.2f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,


		0.2f, -0.5f, 0.0f, 1.0f, 0.0F, 0.0f,
		0.2f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.3f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.3f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.3f, -0.4f, 0.0f, 1.0f, 0.0F, 0.0f,
		0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.4f, -0.5f, 0.0f, 1.0f, 0.0F, 0.0f,
		0.4f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,


		0.5f, -0.3f, 0.0f, 1.0f, 0.0F, 0.0f,
		0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.6f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.6f, -0.0f, 0.0f, 1.0f, 0.0f, 0.0f,


		// <<<<<<<<DETALLE>>>>>>>>>>

		-0.5f, -0.2f, 0.0f,	0.0f, 0.0F, 0.0f,
		-0.5f, -0.1f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.4f, -0.2f, 0.0f,	0.0f, 0.0f, 0.0f,
		-0.4f, -0.1f, 0.0f,	0.0f, 0.0f, 0.0f,

		-0.6f, -0.1f, 0.0f, 0.0f, 0.0F, 0.0f,
		-0.6f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,


		-0.5f, 0.1f, 0.0f, 0.0f, 0.0F, 0.0f,
		-0.5f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.3f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.3f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.3f, 0.0f, 0.0f, 0.0f, 0.0F, 0.0f,
		-0.3f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.2f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,



	};


	//indices de los vertices
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};







	// Generamos los buffers y los enlazamos
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	/*glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);*/
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)





	// Se dibuja en frames por segundo
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);


		//dibujo de puntos/vertices
		glPointSize(pixelSize);

		//glDrawArrays(GL_TRIANGLES, 0, 12); // 12 vértices (2 rectángulos × 6 vértices)



		//dibujar todos los rectangulos
		float i = 0;
		for (i = 0; i < sizeof(vertices); i = i + 4)
		{
			glDrawArrays(GL_TRIANGLE_STRIP, i, 4);
		}

		//dibujo de lineas
		//glLineWidth(10.0f);
		//glDrawArrays(GL_LINES,0,2); //apartir del 0 hasta el vertice 2, las dos primeras lineas
        //glDrawArrays(GL_LINE_LOOP,0,4); //ciera todos los vertices
        
		//dibujo de triangulos
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}