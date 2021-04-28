#ifndef GLOBE_H
#define GLOBE_H

class Globe
{
public:
    Globe(float radius,  float red, float yellow, float blue);
    float getRadius();
    float getRed();
    float getYellow();
    float getBlue();

private:
    float radius;
    float red;
    float yellow;
    float blue;


};

#endif // GLOBE_H
