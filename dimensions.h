#ifndef DIMENSIONS_H
#define DIMENSIONS_H


class Dimensions
{
public:
    Dimensions(int, int ,int, int, int);
    int getPosY(int num);

    int posX_;
    int initialPosY_;
    int width_;
    int height_;
    int vertSpace_;
};

#endif // DIMENSIONS_H
