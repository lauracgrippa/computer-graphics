////////////////////////////////////////////////
//                                            //
// Universidade Federal do Rio Grande do Sul  //
// Instituto de Informática                   //
// Departamento de Informática Aplicada       //
//                                            //
// INF01047 Fundamentos de Computação Gráfica //
// Prof. Eduardo Gastal                       //
//                                            //
////////////////////////////////////////////////
//                                            //
// LABORATÓRIO 1                              //
// Tarefa 2: Terceira Parte                   //
//                                            //
// Aluna Laura Cárdenas Grippa                //
//                                            //
////////////////////////////////////////////////

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils.h"

GLuint BuildZeroCharacter(float pos); // Constrói triângulos para renderizar 0
GLuint BuildOneCharacter(float pos); // Constrói triângulos para renderizar 1
GLuint LoadShader_Vertex(const char* filename);
GLuint LoadShader_Fragment(const char* filename);
void LoadShader(const char* filename, GLuint shader_id);
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    int success = glfwInit();
    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(500, 500, "INF01047 - 00219351 - Laura Cardenas Grippa", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, KeyCallback);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    GLuint vertex_shader_id = LoadShader_Vertex("../../src/shader_vertex.glsl");
    GLuint fragment_shader_id = LoadShader_Fragment("../../src/shader_fragment.glsl");
    GLuint program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);

    // Variáveis para a lógica do contador
    long long previous = -1;
    long long number = -1;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program_id);

        // A partir daqui, lida-se com a lógica do contador
        // Utiliza-se glfwGetTime() como recomendado
        long long time = (long long)(1.0 * glfwGetTime());

        if (time != previous) {
            number += 1;
            if (number > 15) {
                number = 0;
            }
        }

        if (number == 0)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 1)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 2)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 3)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 4)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 5)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 6)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 7)
        {
            glBindVertexArray(BuildZeroCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 8)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 9)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 10)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 11)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 12)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 13)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 14)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildZeroCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_STRIP, 96, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }
        else if (number == 15)
        {
            glBindVertexArray(BuildOneCharacter(-0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(-0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.25));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            glBindVertexArray(BuildOneCharacter(+0.7));
            glDrawElements(GL_TRIANGLE_FAN, 48, GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);
        }

        previous = time;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

// Construção do caracter "0"
GLuint BuildZeroCharacter(float pos) {
    GLfloat NDC_coefficients[] = {
        0.7f, 0.0f,   0.0f, 1.0f,
        0.646716f,    0.2678781,   0.0f, 1.0f,
        0.4949749f,   0.4949749f,  0.0f, 1.0f,
        0.2678781f,   0.646716f,   0.0f, 1.0f,
        0.0f,         0.7f,        0.0f, 1.0f,
        -0.2678781f,  0.646716f,   0.0f, 1.0f,
        -0.4949749f,  0.4949749f,  0.0f, 1.0f,
        -0.646716f,   0.2678781f,  0.0f, 1.0f,
        -0.7f,        0.0f,        0.0f, 1.0f,
        -0.646716f,   -0.2678781f, 0.0f, 1.0f,
        -0.4949749f,  -0.4949749f, 0.0f, 1.0f,
        -0.2678781f,  -0.646716f,  0.0f, 1.0f,
        0.0f,         -0.7f,       0.0f, 1.0f,
        0.2678781f,   -0.646716f,  0.0f, 1.0f,
        0.4949749f,   -0.4949749f, 0.0f, 1.0f,
        0.646716f,    -0.2678781f, 0.0f, 1.0f,

        0.5f,         0.0f,        0.0f, 1.0f,
        0.46194f,     0.1913415,   0.0f, 1.0f,
        0.3535535f,   0.3535535f,  0.0f, 1.0f,
        0.1913415f,   0.46194f,    0.0f, 1.0f,
        0.0f,         0.5f,        0.0f, 1.0f,
        -0.1913415f,  0.46194f,    0.0f, 1.0f,
        -0.3535535f,  0.3535535f,  0.0f, 1.0f,
        -0.46194f,    0.1913415f,  0.0f, 1.0f,
        -0.5f,        0.0f, 0.0f,  1.0f,
        -0.46194f,    -0.1913415,  0.0f, 1.0f,
        -0.3535535f,  -0.3535535f, 0.0f, 1.0f,
        -0.1913415f,  -0.46194f,   0.0f, 1.0f,
        0.0f,         -0.5f,       0.0f, 1.0f,
        0.1913415f,  -0.46194f,    0.0f, 1.0f,
        0.3535535f,  -0.3535535f,  0.0f, 1.0f,
        0.46194f,    -0.1913415f,  0.0f, 1.0f
    };

    for (int i = 0; i < 32; i++) {
        NDC_coefficients[i * 4] = NDC_coefficients[i * 4] * 0.2 + pos;
    }


    GLuint VBO_NDC_coefficients_id;
    glGenBuffers(1, &VBO_NDC_coefficients_id);

    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);


    glBindVertexArray(vertex_array_object_id);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NDC_coefficients_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(NDC_coefficients), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(NDC_coefficients), NDC_coefficients);

    GLuint location = 0;            // "(location = 0)" em "shader_vertex.glsl"

    GLint number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"

    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(location);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLfloat color_coefficients[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1;             // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLubyte indices[] = {
        0, 1, 16,
        16, 17, 1,
        1, 2, 17,
        17, 18, 2,
        2, 3, 18,
        18, 19, 3,
        3, 4, 19,
        19, 20, 4,
        4, 5, 20,
        20, 21, 5,
        5, 6, 21,
        21, 22, 6,
        6, 7, 22,
        22, 23, 7,
        7, 8, 23,
        23, 24, 8,
        8, 9, 24,
        24, 25, 9,
        9, 10, 25,
        25, 26, 10,
        10, 11, 26,
        26, 27, 11,
        11, 12, 27,
        27, 28, 12,
        12, 13, 28,
        28, 29, 13,
        13, 14, 29,
        29, 30, 14,
        14, 15, 30,
        30, 31, 15,
        15, 0, 31,
        31, 16, 0
    };

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glBindVertexArray(0);

    return vertex_array_object_id;
}

// Construção do caracter "1"
GLuint BuildOneCharacter(float pos) {
    GLfloat NDC_coefficients[] = {
        0.0f,         0.0f,        0.0f, 1.0f,
        0.7f,         0.0f,        0.0f, 1.0f,
        0.646716f,    0.2678781,   0.0f, 1.0f,
        0.4949749f,   0.4949749f,  0.0f, 1.0f,
        0.2678781f,   0.646716f,   0.0f, 1.0f,
        0.0f,         0.7f,        0.0f, 1.0f,
        -0.2678781f,  0.646716f,   0.0f, 1.0f,
        -0.4949749f,  0.4949749f,  0.0f, 1.0f,
        -0.646716f,   0.2678781f,  0.0f, 1.0f,
        -0.7f,        0.0f,        0.0f, 1.0f,
        -0.646716f,   -0.2678781f, 0.0f, 1.0f,
        -0.4949749f,  -0.4949749f, 0.0f, 1.0f,
        -0.2678781f,  -0.646716f,  0.0f, 1.0f,
        0.0f,         -0.7f,       0.0f, 1.0f,
        0.2678781f,   -0.646716f,  0.0f, 1.0f,
        0.4949749f,   -0.4949749f, 0.0f, 1.0f,
        0.646716f,    -0.2678781f, 0.0f, 1.0f
    };

    for (int i = 0; i < 17; i++) {
        NDC_coefficients[i * 4] = NDC_coefficients[i * 4] * 0.04 + pos;
    }

    GLuint VBO_NDC_coefficients_id;
    glGenBuffers(1, &VBO_NDC_coefficients_id);

    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);

    glBindVertexArray(vertex_array_object_id);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NDC_coefficients_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(NDC_coefficients), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(NDC_coefficients), NDC_coefficients);

    GLuint location = 0;            // "(location = 0)" em "shader_vertex.glsl"

    GLint number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"

    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(location);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat color_coefficients[] = {
        //  R     G     B     A
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };

    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1;             // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLubyte indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 9,
        0, 9, 10,
        0, 10, 11,
        0, 11, 12,
        0, 12, 13,
        0, 13, 14,
        0, 14, 15,
        0, 15, 16,
        0, 16, 1
    };

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glBindVertexArray(0);

    return vertex_array_object_id;
}

// Carrega um Vertex Shader de um arquivo
GLuint LoadShader_Vertex(const char* filename)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

    LoadShader(filename, vertex_shader_id);

    // Retorna o ID gerado acima
    return vertex_shader_id;
}

// Carrega um Fragment Shader de um arquivo
GLuint LoadShader_Fragment(const char* filename)
{
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    LoadShader(filename, fragment_shader_id);

    // Retorna o ID gerado acima
    return fragment_shader_id;
}

// Função auxilar, utilizada pelas duas funções acima. Carrega código de GPU de
// um arquivo GLSL e faz sua compilação.
void LoadShader(const char* filename, GLuint shader_id)
{
    // Lemos o arquivo de texto indicado pela variável "filename"
    // e colocamos seu conteúdo em memória, apontado pela variável
    // "shader_string".
    std::ifstream file;
    try {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    } catch ( std::exception& e ) {
        fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    // Define o código do shader GLSL, contido na string "shader_string"
    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

    // Compila o código do shader GLSL (em tempo de execução)
    glCompileShader(shader_id);

    // Verificamos se ocorreu algum erro ou "warning" durante a compilação
    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    // Alocamos memória para guardar o log de compilação.
    // A chamada "new" em C++ é equivalente ao "malloc()" do C.
    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

    // Imprime no terminal qualquer erro ou "warning" de compilação
    if ( log_length != 0 )
    {
        std::string  output;

        if ( !compiled_ok )
        {
            output += "ERROR: OpenGL compilation of \"";
            output += filename;
            output += "\" failed.\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        else
        {
            output += "WARNING: OpenGL compilation of \"";
            output += filename;
            output += "\".\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }

        fprintf(stderr, "%s", output.c_str());
    }

    delete [] log;
}

// Esta função cria um programa de GPU, o qual contém obrigatoriamente um
// Vertex Shader e um Fragment Shader.
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    // Criamos um identificador (ID) para este programa de GPU
    GLuint program_id = glCreateProgram();

    // Definição dos dois shaders GLSL que devem ser executados pelo programa
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    // Linkagem dos shaders acima ao programa
    glLinkProgram(program_id);

    // Verificamos se ocorreu algum erro durante a linkagem
    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

    // Imprime no terminal qualquer erro de linkagem
    if ( linked_ok == GL_FALSE )
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

        // Alocamos memória para guardar o log de compilação.
        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(program_id, log_length, &log_length, log);

        std::string output;

        output += "ERROR: OpenGL linking of program failed.\n";
        output += "== Start of link log\n";
        output += log;
        output += "== End of link log\n";

        delete [] log;

        fprintf(stderr, "%s", output.c_str());
    }

    // Retorna o ID gerado acima
    return program_id;
}

// Função que será chamada sempre que a janela do sistema for redimensionada
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Indicamos que queremos renderizar em toda região do framebuffer. A
    // função "glViewport" define o mapeamento das "normalized device
    // coordinates" (NDC) para "pixel coordinates".  Essa é a operação de
    // "Screen Mapping" ou "Viewport Mapping" vista em aula (slides 138-145 do documento Aula_03_Rendering_Pipeline_Grafico.pdf).
    glViewport(0, 0, width, height);
}

// Função que será chamada sempre que o usuário pressionar alguma tecla
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // ===============
    // Não modifique este loop! Ele é utilizando para correção automatizada dos
    // laboratórios. Deve ser sempre o primeiro comando desta função KeyCallback().
    for (int i = 0; i < 10; ++i)
        if (key == GLFW_KEY_0 + i && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
            std::exit(100 + i);
    // ===============

    // Se o usuário pressionar a tecla ESC, fechamos a janela.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// Definimos o callback para impressão de erros da GLFW no terminal
void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
