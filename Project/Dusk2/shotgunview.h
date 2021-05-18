#ifndef SHOTGUNVIEW_H
#define SHOTGUNVIEW_H
class Shotgun;
class Texture;

class ShotgunView
{
private:
    Shotgun* shotgun;
    Texture* texture;

public:
    ShotgunView();
    void draw(bool isWireframe = false);
};

#endif // SHOTGUNVIEW_H
