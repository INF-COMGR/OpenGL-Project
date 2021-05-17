#ifndef SHOTGUNVIEW_H
#define SHOTGUNVIEW_H
class Shotgun;

class ShotgunView
{
private:
    Shotgun* shotgun;
    void getTexture();

    unsigned int texture;
    int width, height, nrChannels;
    unsigned char* image;
    void initTextures();
    void addTexture();
public:
    ShotgunView();
    void draw(bool isWireframe = false);
};

#endif // SHOTGUNVIEW_H
