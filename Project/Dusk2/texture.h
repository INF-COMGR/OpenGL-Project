#ifndef TEXTURE_H
#define TEXTURE_H
#include <QString>

class Texture
{
public:
    Texture();
    void initTexture(QString path);
    void addTexture();
    void stopTexture();
    unsigned int getTexture() const;
    void setTexture(unsigned int value);

private:
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char* image;
};

#endif // TEXTURE_H
