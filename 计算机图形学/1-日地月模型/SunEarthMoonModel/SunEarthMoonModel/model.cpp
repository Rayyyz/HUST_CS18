//////////////////////////////////////////////////////////////////////////////
//
//  model.cpp
//  1. ����Ļ��ƣ�������������еĵ㣩
//  2. ������Ƭ�Ĺ���
//  3. ����ͳһ�����������ݴ���
//////////////////////////////////////////////////////////////////////////////

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vmath.h>
#include <vector>

//���ڴ�С����
const unsigned int SCR_WIDTH = 2000;
const unsigned int SCR_HEIGHT = 1500;
float aspact = (float)4.0 / (float)3.0;

//��ת����-�յع�ת
static GLfloat xRot1 = 20.0f;
static GLfloat yRot1 = 20.0f;

//��ת����-���¹�ת
static GLfloat xRot2 = 20.0f;
static GLfloat yRot2 = 20.0f;

static GLfloat xRot = 20.0f;

//�������
GLuint vertex_array_object; // == VAO���
GLuint vertex_buffer_object; // == VBO���
GLuint element_buffer_object;//==EBO���
int shader_program;//��ɫ��������

//������ݲ���
std::vector<float> sphereVertices;
std::vector<int> sphereIndices;
const int Y_SEGMENTS = 30;
const int X_SEGMENTS = 30;
const float Radio = 3.0;
const GLfloat  PI = 3.14159265358979323846f;


void initial(void)
{
	//�������嶥���������Ƭ�ļ���
	// ������Ķ���
	for (int y = 0; y <= Y_SEGMENTS; y++)
	{
		for (int x = 0; x <= X_SEGMENTS; x++)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * Radio * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * Radio * PI) * std::sin(ySegment * PI);

			sphereVertices.push_back(xPos);
			sphereVertices.push_back(yPos);
			sphereVertices.push_back(zPos);
		}
	}

	// ������Ķ���
	for (int i = 0; i < Y_SEGMENTS; i++)
	{
		for (int j = 0; j < X_SEGMENTS; j++)
		{

			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);

			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
		}
	}

	// ��
	glGenVertexArrays(1, &vertex_array_object);
	glGenBuffers(1, &vertex_buffer_object);
	//���ɲ��������VAO��VBO
	glBindVertexArray(vertex_array_object);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	// ���������ݰ�����ǰĬ�ϵĻ�����
	glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &element_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ���VAO��VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ������ɫ����Ƭ����ɫ��Դ��
	const char *vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 vPos;\n"           // λ�ñ���������λ��ֵΪ0
		"out vec4 vColor;\n"           // λ�ñ���������λ��ֵΪ0
		"uniform mat4 transform;\n"
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = transform*vec4(vPos, 1.0);\n"
		"    vColor = color;\n"
		"}\n\0";
	const char *fragment_shader_source =
		"#version 330 core\n"
		"in vec4 vColor;\n"                   // �������ɫ����
		"out vec4 FragColor;\n"                   // �������ɫ����
		"void main()\n"
		"{\n"
		"    FragColor = vColor;\n"
		"}\n\0";

	// ���ɲ�������ɫ��
	// ������ɫ��
	int success;
	char info_log[512];
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	// �����ɫ���Ƿ�ɹ����룬�������ʧ�ܣ���ӡ������Ϣ
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	// Ƭ����ɫ��
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	// �����ɫ���Ƿ�ɹ����룬�������ʧ�ܣ���ӡ������Ϣ
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	// ���Ӷ����Ƭ����ɫ����һ����ɫ������
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	// �����ɫ���Ƿ�ɹ����ӣ��������ʧ�ܣ���ӡ������Ϣ
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	// ɾ����ɫ��
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glUseProgram(shader_program);

	//�趨�����������
	glPointSize(15);//���õ�Ĵ�С
	glLineWidth(5);//�����߿�

	//�����޳�����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);	//�޳�����α���

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_UP:
		xRot1 -= 3.0f;
		xRot2 -= 3.0f;
		break;
	case GLFW_KEY_DOWN:
		xRot1 += 3.0f;
		xRot2 += 3.0f;
		break;
	case GLFW_KEY_LEFT:
		yRot1 -= 3.0f;
		yRot2 -= 3.0f;
		break;
	case GLFW_KEY_RIGHT:
		yRot1 += 3.0f;
		yRot2 += 3.0f;
		break;
	case GLFW_KEY_1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case GLFW_KEY_2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case GLFW_KEY_3:
		glEnable(GL_CULL_FACE);    //�򿪱����޳�
		glCullFace(GL_BACK);          //�޳�����εı���
		break;
	case GLFW_KEY_4:
		glDisable(GL_CULL_FACE);     //�رձ����޳�
		break;
	default:
		break;
	}
}

void Draw(void)
{
	// �����ɫ�������Ȼ�����
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//����ͼ�ε���ת
	unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
	glBindVertexArray(vertex_array_object);       // ��VAO

	// ���ƺ�ɫ��̫��
	vmath::mat4 trans1 = vmath::perspective(60, aspact, 1.0f, 500.0f) *vmath::translate(0.0f, 0.0f, -6.0f);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans1);
	GLfloat vColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	unsigned int colorLoc = glGetUniformLocation(shader_program, "color");
	glUniform4fv(colorLoc, 1, vColor);
	glDrawElements(GL_TRIANGLES, X_SEGMENTS*Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);

	//������ɫ�ĵ���
	xRot1 += (float)0.10f;
	xRot += (float)1.0f;
	vmath::mat4 trans2 = trans1* vmath::rotate(xRot1, vmath::vec3(0.0, 0.0, 1.0))*vmath::translate(3.0f, 0.0f, 0.0f)*vmath::scale(0.3f);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans2);
	GLfloat vColor2[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glUniform4fv(colorLoc, 1, vColor2);
	glDrawElements(GL_TRIANGLES, X_SEGMENTS*Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);

	//���ƻ�ɫ������
	xRot2 += (float)0.80f;
	vmath::mat4 trans3 = trans2 * vmath::rotate(xRot2, vmath::vec3(0.0, 0.6, 0.8))*vmath::translate(1.5f, 0.0f, 0.0f)*vmath::scale(0.3f);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans3);
	GLfloat vColor3[4] = { 0.8f, 0.8f, 0.0f, 1.0f };
	glUniform4fv(colorLoc, 1, vColor3);
	glDrawElements(GL_TRIANGLES, X_SEGMENTS*Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);

	// �����
	glBindVertexArray(0); 

}

void reshaper(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	if (height == 0)
	{
		aspact = (float)width;
	}
	else
	{
		aspact = (float)width / (float)height;
	}

}

int main()
{
	glfwInit(); // ��ʼ��GLFW

	// OpenGL�汾Ϊ3.3�����ΰ汾�ž���Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	// ʹ�ú���ģʽ(������������)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������(���ߡ���������)
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sun-Earth-Moon", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to Create OpenGL Context" << std::endl;
		glfwTerminate();
		return -1;
	}

	// �����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);

	// ��ʼ��GLAD������OpenGL����ָ���ַ�ĺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	initial();//��ʼ��

	//���ڴ�С�ı�ʱ����reshaper����
	glfwSetFramebufferSizeCallback(window, reshaper);

	//�������м��̲���ʱ����key_callback����
	glfwSetKeyCallback(window, key_callback);


	while (!glfwWindowShouldClose(window))
	{
		Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ����ɾ��VAO��VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteBuffers(1, &vertex_buffer_object);

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
