#include "model.h"

Model::Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    // Configurar VBO, VAO y EBO para las caras
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // Configurar VBO, VAO y EBO para las aristas
    glGenVertexArrays(1, &edgeVAO);
    glGenBuffers(1, &edgeVBO);
    glGenBuffers(1, &edgeEBO);

    // Definir los índices de las aristas (líneas)
    edgeIndices = {
        0, 1, 1, 2, 2, 3, 3, 0,  // Cara frontal
        4, 5, 5, 6, 6, 7, 7, 4,  // Cara trasera
        0, 4, 1, 5, 2, 6, 3, 7   // Aristas laterales
    };

    glBindVertexArray(edgeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, edgeVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, edgeIndices.size() * sizeof(unsigned int), edgeIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Model::drawFaces() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  // Dibujar caras
    glBindVertexArray(0);
}

void Model::drawEdges() {
    glBindVertexArray(edgeVAO);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);  // Dibujar aristas
    glBindVertexArray(0);
}

void Model::setTransform(glm::mat4 transform) {
    this->transform = transform;
}