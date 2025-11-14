#pragma once
#include <array>
#include <cassert>

#include "geom.h"

class Tile {
public:
    // Размер тайла 8*8 пикселей.
    constexpr static int SIZE = 8;

    // Конструктор по умолчанию. Заполняет тайл указанным цветом.
    Tile(char color = ' ') noexcept {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                pixels_[i][j] = color;
            }
        }

        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    Tile(const Tile& other) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                pixels_[i][j] = other.pixels_[i][j];
            }
        }

        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    ~Tile() {
        // -------------- Не удалять ------------
        --instance_count_;  // Уменьшаем счётчик тайлов.
        assert(instance_count_ >= 0);
        // -------------- не удалять ------------
    }

    /**
     * Изменяет цвет пикселя тайла.
     * Если координаты выходят за пределы тайла, метод ничего не делает.
     */
    void SetPixel(Point p, char color) noexcept {
        if (IsPointInSize(p, size_)) {
            pixels_[p.y][p.x] = color;
        }
    }

    /**
     * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
     */
    char GetPixel(Point p) const noexcept {
        if (IsPointInSize(p, size_)) {
            return pixels_[p.y][p.x];
        }
        else {
            return ' ';
        }
    }

    // Возвращает количество экземпляра класса Tile в программе.
    static int GetInstanceCount() noexcept {
        // -------------- не удалять ------------
        return instance_count_;
        // -------------- не удалять ------------
    }

private:
    // -------------- не удалять ------------
    inline static int instance_count_ = 0;
    // -------------- не удалять ------------

    std::array<std::array<char, SIZE>, SIZE> pixels_;
    Size size_{ SIZE, SIZE };

};