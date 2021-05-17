#include "texture.h"
#include "stb_image.h"
#include "util.h"

Texture::Texture()
{

}

void Texture::initTexture(QString path) {
    //QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg"};
    //std::cout << " " << path.toStdString() << " ";
    image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (image != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else {
        perror( stbi_failure_reason() );
    }
    //stbi_image_free(image);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // use our previously defined texture
}

void Texture::addTexture() {
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D , texture );

}
void Texture::stopTexture() {
    glBindTexture( GL_TEXTURE_2D , 0 );

}

unsigned int Texture::getTexture() const
{
    return texture;
}

void Texture::setTexture(unsigned int value)
{
    texture = value;
}
