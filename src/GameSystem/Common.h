#pragma once

struct Vec2{
  float x;
  float y;
};

enum class ColorId {
    None = -1,
    Magenta = 0,
    Cyan = 1,
    Purple = 2,

    COUNT
};

enum class Difficulty {
    Normal,
    Hard
};

unsigned int BlockColor(ColorId id);
unsigned int RippleColor(ColorId id);