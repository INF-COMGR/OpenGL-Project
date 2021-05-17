#include "renderer.h"
#include <QtMath>

Renderer::Renderer()
{

}
/*// This will identify our vertex buffer
        GLuint vertexbuffer;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);*/
void Renderer::renderEntity(Entity entity, ShaderStatic shader) {
    //TexturedModel model = entity.getModel();
    RawModel rawModel = entity.getModel();
    glBindVertexArrayAPPLE(rawModel.getVaoID());
    glEnableVertexAttribArray(0);

    QMatrix4x4 transformationMatrix = createTransformationMatrix(
            entity.getPosition(),
            entity.getRotX(), entity.getRotY(), entity.getRotZ(),
            entity.getScale());

    //shader.loadTransformationMatrix(transformationMatrix);

    glDrawElements(rawModel.getMode(),  rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
    //GL11.glDrawArrays(rawModel.getMode(), 0, rawModel.getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArrayAPPLE(0);
}

QMatrix4x4 Renderer::createTransformationMatrix(QVector3D translation, float rx, float ry, float rz, float scale) {
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(translation);


    matrix.rotate(qDegreesToRadians(rx), QVector3D(1,0,0));
    matrix.rotate(qDegreesToRadians(ry), QVector3D(0,1,0));
    matrix.rotate(qDegreesToRadians(rz), QVector3D(0,0,1));
    matrix.scale(scale);
    //matrix.scale(new QVector3D(scale, scale, scale));
    return matrix;
    /* Matrix4f. */
}

void Renderer::render( QVector<float> vertices) {
    float g_vertex_buffer_data[vertices.length()];
    for (int i = 0 ; i < vertices.length(); ++ i) {
        g_vertex_buffer_data[i] = vertices[i];
    }

    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}
