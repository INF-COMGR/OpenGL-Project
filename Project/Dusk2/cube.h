#ifndef CUBE_H
#define CUBE_H
class Texture;
class HitBox;

class Cube
{
public:
    Cube(double x1, double y1, double z1, double x2, double y2, double z2);
    void draw(bool isWireframe);
    HitBox *getHitbox() const;
    void setHitbox(HitBox *value);

private:
    double x1, y1, z1;
    double x2, y2, z2;
    Texture* texture;
    HitBox* hitbox;
};

#endif // CUBE_H
