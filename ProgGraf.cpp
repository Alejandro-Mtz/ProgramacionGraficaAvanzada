// ProgGraf.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Medidas de la pantalla

const unsigned int largo = 800;
const unsigned int ancho = 800;

const char *vertexShaderSource = "#version 330 core \n"
"layout (location - 0) in vec3 aPos; \n"
"void main() \n"
"{ \n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
"} \n\0";

const char *fragmentshaderSource = "#version 330 core \n"
"out vec4 FragColor; \n"
"void main() \n"
"{ \n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f); \n"
"} \n\0";

using namespace std;

int main()
{
    //Inicializar glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Contexto version mayor
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Contexto version menor
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creacion de la ventana
	GLFWwindow* window = glfwCreateWindow(largo, ancho, "screen", NULL, NULL);
	if (window == NULL)
	{
		cout << "Fallo" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "glad no se esta ejecutando" << endl;
		return -1;
	}

	//Inicializaciones
	//Inicializacion del vertex
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Comprobacion del vertex
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "Error \n" << infoLog << endl;
	}

	//Inicializacion del fragment
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &vertexShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Comprobacion del fragment
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "Error \n" << infoLog << endl;
	}

	//Inicializar programa
	//Linkear todo
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Comprobar linkeos
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "Error" << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Configurar el objeto
	float vertices[]
	{
		-0.5f, -0.5f, 0.0f, //izquierda
		0.5f, -0.5f, 0.0f, //derecha
		0.0f, 0.5f, 0.0f //arriba
	};

	float hexagono[]
	{
		//X     Y     Z
		-0.1f, 0.1f, 0.0f,
		0.0f, 0.2f, 0.0f,
		0.1f, 0.1f, 0.0f,
		0.1f, -0.1f, 0.0f,
		0.0f, -0.2f, 0.0f,
		-0.1f, -0.1f, 0.0f
	};

	float triangulos[]
	{
		//X     Y     Z
		0.0f, 0.2f, 0.0f,
		0.2f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//X     Y     Z
		0.1f, 0.1f, 0.0f,
		0.1f, 0.25f, 0.0f,
		0.25f, 0.1f, 0.0f,

		//X     Y     Z
		0.0f, 0.3f, 0.0f,
		0.125f, 0.4f, 0.0f,
		0.25f, 0.3f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Unificar
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//Habilitar atributos de coordenadas
	glEnableVertexAttribArray(0);
	//Unificacion de los buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Generacion del ciclo de dibujado
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//Color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Dibujado
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

