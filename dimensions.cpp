#include "dimensions.h"

Dimensions::Dimensions(int x, int y, int w, int h, int vs)
{
    posX_ = x;
    initialPosY_ = y;
    width_ = w;
    height_ = h;
    vertSpace_ = vs;
}

int Dimensions::getPosY(int num) {
    return initialPosY_ + (height_ + vertSpace_) * num;
}
