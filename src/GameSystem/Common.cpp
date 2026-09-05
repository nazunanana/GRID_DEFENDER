#include "Common.h"
#include "DxLib.h"

unsigned int BlockColor(ColorId id)
{
    switch (id)
    {
    case ColorId::Magenta:
        return GetColor(255, 50, 150);
    case ColorId::Cyan:
        return GetColor(100, 255, 255);
    case ColorId::Purple:
        return GetColor(160, 80, 255);
    default:
        return GetColor(5, 0, 40);
    }
}

unsigned int RippleColor(ColorId id)
{
    switch (id)
    {
    case ColorId::Magenta:
        return GetColor(230, 0, 126);
    case ColorId::Cyan:
        return GetColor(0, 237, 250);
    case ColorId::Purple:
        return GetColor(134, 36, 255);
    default:
        return GetColor(255, 255, 255);
    }
}