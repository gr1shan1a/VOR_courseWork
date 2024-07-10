



#include <iostream>

#include <vector>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


using namespace std;


vector<glm::vec3> vertices;
vector<glm::vec2> texCoords;
vector<glm::vec3> normals;
vector<GLuint> indices;

void loadModel(const char* path) {
    ifstream file(path);

    if (!file.is_open()) {
        cerr << "Error opening file: " << path << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string token;

        iss >> token;

        if (token == "v") {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (token == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            texCoords.push_back(texCoord);
        } else if (token == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (token == "f") {
            GLuint vertexIndices[3];

            for (int i = 0; i < 3; i++) {
                iss >> token;
                istringstream indexStream(token);

                indexStream >> vertexIndices[i];

                vertexIndices[i]--;
            }

            for (int i = 0; i < 3; i++) {
                indices.push_back(vertexIndices[i]);
            }
        }
    }

    file.close();
}





float a = 1;
float scale = 1.0f;
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;
float posX = 0.0f;
float posY = 0.0f;
float posZ = 0.0f;

struct Vector {
    float x;
    float y;
    float z;
};

//Vector vector(float x, float y, float z) {
//    Vector result;
//    result.x = x;
//    result.y = y;
//    result.z = z;
//    return result;
//}
//
//void scaleVertex(Vector* vertex, float scale) {
//    vertex->x *= scale;
//    vertex->y *= scale;
//    vertex->z *= scale;
//}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    float delta = 0.05f;
    float scaleDelta = 0.015f;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                posY += delta;
                break;
            case GLFW_KEY_S:
                posY -= delta;
                break;
            case GLFW_KEY_A:
                posX -= delta;
                break;
            case GLFW_KEY_D:
                posX += delta;
                break;
            case GLFW_KEY_Q:
                angleZ += 3.0f;
                break;
            case GLFW_KEY_E:
                angleZ -= 3.0f;
                break;
            case GLFW_KEY_R:
                angleX += 3.0f;
                break;
            case GLFW_KEY_F:
                angleX -= 3.0f;
                break;
            case GLFW_KEY_T:
                angleY += 3.0f;
                break;
            case GLFW_KEY_G:
                angleY -= 3.0f;
                break;
            case GLFW_KEY_UP:
                scale += scaleDelta;
                break;
            case GLFW_KEY_DOWN:
                scale -= scaleDelta;
                break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "CUBE_GK", NULL, NULL);
    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    // загрузка obj - файла
    loadModel("/Users/macbook/CLionProjects/VOR_courseWork/tie_fighter.obj");

//    cout << indices.data() << endl;

    glfwMakeContextCurrent(window);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }


    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }


    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (vertices.size() * 3 + texCoords.size() * 2 + normals.size() * 3), nullptr, GL_STATIC_DRAW);

    GLfloat* buffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (int i = 0; i < vertices.size(); i++) {
        buffer[i * 3] = vertices[i].x;
        buffer[i * 3 + 1] = vertices[i].y;
        buffer[i * 3 + 2] = vertices[i].z;
    }

    for (int i = 0; i < texCoords.size(); i++) {
        buffer[vertices.size() * 3 + i * 2] = texCoords[i].x;
        buffer[vertices.size() * 3 + i * 2 + 1] = texCoords[i].y;
    }

    for (int i = 0; i < normals.size(); i++) {
        buffer[vertices.size() * 3 + texCoords.size() * 2 + i * 3] = normals[i].x;
        buffer[vertices.size() * 3 + texCoords.size() * 2 + i * 3 + 1] = normals[i].y;
        buffer[vertices.size() * 3 + texCoords.size() * 2 + i * 3 + 2] = normals[i].z;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * vertices.size() * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * (vertices.size() * 3 + texCoords.size() * 2)));
    glEnableVertexAttribArray(2);



    // установка проекционной матрицы
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // установка матрицы моделирования
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        glTranslatef(posX, posY, posZ);
        glRotatef(angleX, 1.0f, 0.0f, 0.0f);
        glRotatef(angleY, 0.0f, 1.0f, 0.0f);
        glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

        glScalef(scale, scale, scale);


        glColor3f(1.0f, 0.0f, 0.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // отрисовка модели
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}