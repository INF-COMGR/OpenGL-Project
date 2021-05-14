#ifndef SHOTGUNVIEW_H
#define SHOTGUNVIEW_H
class Shotgun;

class ShotgunView
{
private:
    Shotgun* shotgun;
    void getTexture();
public:
    ShotgunView();
    void draw(bool isWireframe = false);
};

#endif // SHOTGUNVIEW_H
