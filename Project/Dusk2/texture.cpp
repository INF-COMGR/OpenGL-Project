#include "texture.h"
#include "util.h"
#include "stb_image.h"

#include <QCoreApplication>

Texture::Texture(QString imageName)
{
    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/" + imageName};
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

void Texture::bindTexture() {
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D , texture );
}

void Texture::unBindTexture() {
     glBindTexture( GL_TEXTURE_2D , 0 );
}
