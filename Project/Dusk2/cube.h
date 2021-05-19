#ifndef CUBE_H
#define CUBE_H
class Texture;

class Cube
{
public:
    Cube(double x1, double y1, double z1, double x2, double y2, double z2);
    void draw(bool isWireframe);
private:
    double x1, y1, z1;
    double x2, y2, z2;
    Texture* texture;
};

#endif // CUBE_H
