#pragma once
#include "common.h"

class Texture {
public:
    explicit Texture(Image image)
        : image_(std::move(image)) {
    }

    // ¬озвращает размер изображени€
    Size GetSize() const {
        return GetImageSize(image_);
    }

    // ¬озвращает цвет пиксел€.
    // ≈сли координаты выход€т за границы изображени€, возвращаетс€ пробел
    char GetPixelColor(Point p) const {
        if (GetSize().height == 0 || GetSize().width == 0) {
            return '.';  // или любое другое значение по умолчанию
        }
        if (IsPointInSize(p, GetSize())) {
            return image_[p.y][p.x];
        } else {
            return '.';
        }
    }

private:
    Image image_;
};