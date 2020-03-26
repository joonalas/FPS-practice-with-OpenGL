#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include "Vector4.h"
#include "Util.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum ACTION
{
    FORWARD = 0x1,
    BACKWARD = 0x2,
    TURN_LEFT = 0x4,
    TURN_RIGHT = 0x8,
    STRAFE_LEFT = 0x10,
    STRAFE_RIGHT = 0x20
};

int width, height;
Point wall1, wall2;
//Field of Vision
Point fov1(-1.0f, 0.0f, 0.0f, 0.0f);
Point fov2(1.0f, 0.0f, 0.0f, 0.0f);
float angle;
float points[12];
unsigned short p_action = 0;
GLFWwindow *window;

void error_callback(int error, const char *description)
{
    std::cerr << "Error: " << description << std::endl;
}

void closeWindow_callback(GLFWwindow *window)
{
    glfwDestroyWindow(window);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
        {
            p_action |= FORWARD;
        }
        else if (action == GLFW_RELEASE)
        {
            p_action ^= FORWARD;
        }
    }
    if (key == GLFW_KEY_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            p_action |= TURN_LEFT;
        }
        else if (action == GLFW_RELEASE)
        {
            p_action ^= TURN_LEFT;
        }
    }
    if (key == GLFW_KEY_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            p_action |= TURN_RIGHT;
        }
        else if (action == GLFW_RELEASE)
        {
            p_action ^= TURN_RIGHT;
        }
    }
    if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS)
        {
            p_action |= BACKWARD;
        }
        else if (action == GLFW_RELEASE)
        {
            p_action ^= BACKWARD;
        }
    }
    if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS)
        {
            p_action |= STRAFE_LEFT;
        }
        else if (action == GLFW_RELEASE)
        {
            p_action ^= STRAFE_LEFT;
        }
    }
    if (key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS)
        {
            p_action |= STRAFE_RIGHT;
        }
        else if (action == GLFW_RELEASE)
        {
            p_action ^= STRAFE_RIGHT;
        }
    }
}

void update()
{
    if ((p_action & FORWARD) && !(p_action & BACKWARD))
    {
        wall1 -= Point(sin(angle) * 0.01f, cos(angle) * 0.01f, 0.0f, 0.0f);
        wall2 -= Point(sin(angle) * 0.01f, cos(angle) * 0.01f, 0.0f, 0.0f);
    }
    if ((p_action & TURN_LEFT) && !(p_action & TURN_RIGHT))
    {
        angle -= 0.04f;
    }
    if ((p_action & TURN_RIGHT) && !(p_action & TURN_LEFT))
    {
        angle += 0.04f;
    }
    if ((p_action & STRAFE_LEFT) && !(p_action & STRAFE_RIGHT))
    {
        wall1 += Point(sin(angle + 3.14f/2) * 0.01f, cos(angle + 3.14f/2) * 0.01f, 0.0f, 0.0f);
        wall2 += Point(sin(angle + 3.14f/2) * 0.01f, cos(angle + 3.14f/2) * 0.01f, 0.0f, 0.0f);
    }
    if ((p_action & STRAFE_RIGHT) && !(p_action & STRAFE_LEFT))
    {
        wall1 -= Point(sin(angle + 3.14f/2) * 0.01f, cos(angle + 3.14f/2) * 0.01f, 0.0f, 0.0f);
        wall2 -= Point(sin(angle + 3.14f/2) * 0.01f, cos(angle + 3.14f/2) * 0.01f, 0.0f, 0.0f);
    }
    if ((p_action & BACKWARD) && !(p_action & FORWARD))
    {
        wall1 += Point(sin(angle) * 0.01f, cos(angle) * 0.01f, 0.0f, 0.0f);
        wall2 += Point(sin(angle) * 0.01f, cos(angle) * 0.01f, 0.0f, 0.0f);
    }

    Point t1(
        wall1.getX() * cos(angle) - wall1.getY() * sin(angle),
        wall1.getX() * sin(angle) + wall1.getY() * cos(angle),
        wall1.getZ(),
        wall1.getW());
    Point t2(
        wall2.getX() * cos(angle) - wall2.getY() * sin(angle),
        wall2.getX() * sin(angle) + wall2.getY() * cos(angle),
        wall2.getZ(),
        wall2.getW());

    // Cross product
    float cross1 = (t1 ^ fov1).getZ();
    float cross2 = (t2 ^ fov1).getZ();

    if ((cross1 <= 0 || cross2 <= 0) && !(cross1 < 0 && cross2 < 0))
    {
        Point intersect = intersection2D(t1, t2, fov1, fov2);

        if (cross1 <= 0)
        {
            t1.setY(0.000001f);
            t1.setX(intersect.getX());
        }
        if (cross2 <= 0)
        {
            t2.setY(0.000001f);
            t2.setX(intersect.getX());
        }
    }
    if (!(cross1 < 0 && cross2 < 0))
    {

        points[0] = t1.getX() / t1.getY();
        points[1] = 0.2f / t1.getY();
        points[2] = 0.2f;
        points[3] = t1.getX() / t1.getY();
        points[4] = -0.2f / t1.getY();
        points[5] = 0.2f;
        points[6] = t2.getX() / t2.getY();
        points[7] = 0.2f / t2.getY();
        points[8] = 0.2f;
        points[9] = t2.getX() / t2.getY();
        points[10] = -0.2f / t2.getY();
        points[11] = 0.2f;
        
    }
}

void setFrameBufferSize_callback(GLFWwindow *window, int w, int h)
{
    //cout << __func__ << ": Framebuffer size changed" << endl;
    width = w;
    height = h;
}

bool readExtFile(const char *f, string &out)
{
    string line;
    fstream file;
    file.open(f, fstream::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            out.append(line);
            out.append("\n");
        }

        file.close();
        return true;
    }

    cerr << "Unable to open file" << endl;
    return false;
}

bool glInit()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowCloseCallback(window, closeWindow_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window, setFrameBufferSize_callback);

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "Renderer version: " << renderer << std::endl;
    std::cout << "OpenGL version: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

int main(int argc, const char *argv[])
{
    if (!glInit())
    {
        cerr << "Failed to initialize OpenGL" << endl;
        return -1;
    }

    //World angle
    angle = 0.0f;

    wall1.setX(-0.8f);
    wall2.setX(0.8f);
    wall1.setY(0.7f);
    wall2.setY(0.7f);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    string vertex_shader;
    readExtFile("vertex_shader.vert", vertex_shader);
    GLchar const *v_files[] = {vertex_shader.c_str()};

    string fragment_shader;
    readExtFile("fragment_shader_player.frag", fragment_shader);
    GLchar const *f_files[] = {fragment_shader.c_str()};

    string fragment_shader_wall;
    readExtFile("fragment_shader_wall.frag", fragment_shader_wall);
    GLchar const *fw_files[] = {fragment_shader_wall.c_str()};

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, v_files, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, f_files, NULL);
    glCompileShader(fs);
    GLuint fs_w = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs_w, 1, fw_files, NULL);
    glCompileShader(fs_w);

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, vs);
    glAttachShader(shader_programme, fs);
    glLinkProgram(shader_programme);

    GLuint shader_programme_wall = glCreateProgram();
    glAttachShader(shader_programme_wall, vs);
    glAttachShader(shader_programme_wall, fs_w);
    glLinkProgram(shader_programme_wall);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        update();
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}