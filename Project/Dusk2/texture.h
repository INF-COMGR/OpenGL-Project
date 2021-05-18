#ifndef TEXTURE_H
#define TEXTURE_H
#include <QString>

class Texture
{
public:
    Texture(QString imageName);
    void bindTexture();
    void unBindTexture();

private:
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char* image;
};

#endif // TEXTURE_H
