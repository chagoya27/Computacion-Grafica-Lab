/*	Practica 4
*	Chagoya Gonzalez Leonardo
*	4 de septiembre de 2024
*	318218814
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 800, HEIGHT = 600;
//manipulacion de la vista sin tener que estan compilando
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;



//Colores
using Color = std::array<float, 3>;

Color colorPiel = { 0.6078f,0.8745f,0.2667f };
Color sombraPiel = { 0.4863f,0.7059f,0.2235f };
Color ojosBase = { 0.7451f,0.8667f,0.9686f };
Color ojosSombra = { 0.6157f,0.7098f,0.7882f };
Color pupilas = { 0.0f,0.0f,0.0f };
Color trajeBase = { 0.2627f, 0.5412f, 0.8667 };
Color trajeSombra = { 0.2039f,0.4392f, 0.6980f };
Color colorCuello = { 0.5137f, 0.2824f, 0.7843f };
Color insignia = { 0.9882f, 0.5961f, 0.2196f };
Color cinturon = { 0.2078f, 0.3098f, 0.5373f };

struct Buffers {
	GLuint VAO;
	GLuint VBO;
};

Buffers generar_cubo(Color enfrente, Color detras, Color arriba, Color abajo, 
	Color izq, Color der);

std::vector<float> generar_vertices(Color enfrente, Color detras, Color arriba, Color abajo
	, Color izq, Color der);

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4.Leonardo Chagoya", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

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
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	//generar los buffers de los cubos
	Buffers buffCabeza = generar_cubo(colorPiel,colorPiel,colorPiel,colorPiel,colorPiel,sombraPiel);
	Buffers buffOjos = generar_cubo(ojosBase, ojosBase, ojosBase, ojosBase, ojosBase, ojosSombra);
	Buffers buffPupilas = generar_cubo(pupilas, pupilas, pupilas, pupilas, pupilas, pupilas);
	Buffers buffCuello = generar_cubo(colorCuello, colorCuello, colorCuello, colorCuello, colorCuello, colorCuello);
	Buffers buffTraje = generar_cubo(trajeBase, trajeBase, trajeBase, trajeBase, trajeBase, trajeSombra);
	Buffers buffCinturon = generar_cubo(cinturon, cinturon, cinturon, cinturon, cinturon, cinturon);
	Buffers buffInsignia = generar_cubo(insignia, insignia, insignia, insignia, insignia, insignia);

	

	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		//Camaras se le envia el valor de mov a la vista
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));


		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		//cabeza
		//principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.6f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCabeza.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//oreja izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.1f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 1.6f, 0.4f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCabeza.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//oreja derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.1f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 1.6f, 0.4f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCabeza.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);



		//antena
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 3.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCabeza.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//ojos
		//1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 2.4f, 1.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffOjos.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.4f, 1.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffOjos.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 2.4f, 1.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffOjos.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//pupilas
		//1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 2.4f, 1.15f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffPupilas.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.4f, 1.15f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffPupilas.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 2.4f, 1.15f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffPupilas.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//cuerpo

		//cuello
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 0.2f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCuello.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//torso
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.6f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffTraje.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//cinturon
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 0.2f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCinturon.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//cadera
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 0.4f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffTraje.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//piernas
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.8f, 0.0f));
		model = glm::scale(model, glm::vec3(2.8f, 0.8f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffTraje.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//pies
		//1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.9f, -2.3f, 0.1f));
		model = glm::scale(model, glm::vec3(1.4f, 0.2f, 2.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCinturon.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.9f, -2.3f, 0.1f));
		model = glm::scale(model, glm::vec3(1.4f, 0.2f, 2.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCinturon.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//brazo 1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.7f, -0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 1.4f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffTraje.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		
		//mano 1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.7f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCabeza.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		
		//brazo 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.7f, -0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 1.4f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffTraje.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//mano 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.7f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffCabeza.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		
		//insignia
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 0.4f, 1.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.4f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(buffInsignia.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		


		// Swap the screen buffers
		glfwSwapBuffers(window);

	}

	glDeleteVertexArrays(1, &buffCabeza.VAO);
	glDeleteBuffers(1, &buffCabeza.VBO);
	glDeleteVertexArrays(1, &buffTraje.VAO);
	glDeleteBuffers(1, &buffTraje.VBO);

	glDeleteVertexArrays(1, &buffCuello.VAO);
	glDeleteBuffers(1, &buffCuello.VBO);
	glDeleteVertexArrays(1, &buffPupilas.VAO);
	glDeleteBuffers(1, &buffPupilas.VBO);

	glDeleteVertexArrays(1, &buffOjos.VAO);
	glDeleteBuffers(1, &buffOjos.VBO);
	glDeleteVertexArrays(1, &buffCinturon.VAO);
	glDeleteBuffers(1, &buffCinturon.VBO);

	glDeleteVertexArrays(1, &buffInsignia.VAO);
	glDeleteBuffers(1, &buffInsignia.VBO);




	glfwTerminate();
	return EXIT_SUCCESS;
}

//funcion para mover la camara con las teclas
void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.4f;
}







std::vector<float> generar_vertices(Color enfrente, Color detras, Color arriba, Color abajo, Color izq, Color der) {
	std::vector<float> vertices = {
		//cara frontal
		-0.5f, -0.5f, 0.5f, enfrente[0], enfrente[1], enfrente[2],
		0.5f, -0.5f, 0.5f,  enfrente[0], enfrente[1], enfrente[2],
		0.5f,  0.5f, 0.5f,  enfrente[0], enfrente[1], enfrente[2],
		0.5f,  0.5f, 0.5f,  enfrente[0], enfrente[1], enfrente[2],
		-0.5f,  0.5f, 0.5f, enfrente[0], enfrente[1], enfrente[2],
		-0.5f, -0.5f, 0.5f, enfrente[0], enfrente[1], enfrente[2],

		//cara trasera
		-0.5f, -0.5f,-0.5f, detras[0], detras[1], detras[2],
		 0.5f, -0.5f,-0.5f, detras[0], detras[1], detras[2],
		 0.5f,  0.5f,-0.5f, detras[0], detras[1], detras[2],
		 0.5f,  0.5f,-0.5f, detras[0], detras[1], detras[2],
		-0.5f,  0.5f,-0.5f, detras[0], detras[1], detras[2],
		-0.5f, -0.5f,-0.5f, detras[0], detras[1], detras[2],

		//cara de arriba
		-0.5f,  0.5f, -0.5f, arriba[0], arriba[1], arriba[2],
		0.5f,  0.5f, -0.5f,  arriba[0], arriba[1], arriba[2],
		0.5f,  0.5f,  0.5f,  arriba[0], arriba[1], arriba[2],
		0.5f,  0.5f,  0.5f,  arriba[0], arriba[1], arriba[2],
		-0.5f,  0.5f,  0.5f, arriba[0], arriba[1], arriba[2],
		-0.5f,  0.5f, -0.5f, arriba[0], arriba[1], arriba[2],

		//cara de abajo
		-0.5f, -0.5f, -0.5f, abajo[0], abajo[1], abajo[2],
		0.5f, -0.5f, -0.5f,  abajo[0], abajo[1], abajo[2],
		0.5f, -0.5f,  0.5f,  abajo[0], abajo[1], abajo[2],
		0.5f, -0.5f,  0.5f,  abajo[0], abajo[1], abajo[2],
		-0.5f, -0.5f,  0.5f, abajo[0], abajo[1], abajo[2],
		-0.5f, -0.5f, -0.5f, abajo[0], abajo[1], abajo[2],

		//cara derecha
		0.5f, -0.5f,  0.5f,  der[0], der[1], der[2],
		 0.5f, -0.5f, -0.5f,  der[0], der[1], der[2],
		 0.5f,  0.5f, -0.5f,  der[0], der[1], der[2],
		 0.5f,  0.5f, -0.5f,  der[0], der[1], der[2],
		 0.5f,  0.5f,  0.5f,  der[0], der[1], der[2],
		 0.5f,  -0.5f, 0.5f, der[0], der[1], der[2],

		 //cara izquierda
		 -0.5f,  0.5f,  0.5f,  izq[0], izq[1], izq[2],
		 -0.5f,  0.5f, -0.5f,  izq[0], izq[1], izq[2],
		 -0.5f, -0.5f, -0.5f,  izq[0], izq[1], izq[2],
		 -0.5f, -0.5f, -0.5f,  izq[0], izq[1], izq[2],
		 -0.5f, -0.5f,  0.5f,  izq[0], izq[1], izq[2],
		 -0.5f,  0.5f,  0.5f,  izq[0], izq[1], izq[2],


		
	};

	return vertices;
}



Buffers generar_cubo(Color enfrente, Color detras, Color arriba, Color abajo, Color izq, Color der) {

	std::vector<float> vertices = generar_vertices(enfrente,detras,arriba,abajo,izq,der);

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	
	return { VAO,VBO };
}