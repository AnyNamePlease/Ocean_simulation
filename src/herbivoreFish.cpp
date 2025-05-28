#include "herbivoreFish.hpp"
#include "ocean.hpp"
#include "algae.hpp"
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>

HerbivoreFish::HerbivoreFish(int maxAge, int maxFullness)
    : age_(0), fullness_(maxFullness), maxAge_(maxAge), maxFullness_(maxFullness) {}

char HerbivoreFish::getSymbol() const {
    return 'H';
}

bool HerbivoreFish::isAlive() const {
    return age_ < maxAge_ && fullness_ > 0;
}

std::unique_ptr<Entity> HerbivoreFish::clone() const {
    return std::make_unique<HerbivoreFish>(*this);
}

void HerbivoreFish::update(Ocean& ocean) {
    if (!isAlive()) {
        return; // если рыба мертва — выходим
    }

    ++age_;
    --fullness_;

    eatAlgae(ocean);
    move(ocean);
    reproduce(ocean);
}


void HerbivoreFish::move(Ocean& ocean) {
    // Получаем текущие координаты (предположим, что они известны через Ocean)
    auto pos = ocean.findPosition(*this);
    if (!pos) return;

    int x = pos->first;
    int y = pos->second;

    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };

    std::shuffle(directions.begin(), directions.end(), ocean.getRandomEngine());

    for (auto [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;

        size_t width = ocean.getGrid().getWidth();
        size_t height = ocean.getGrid().getHeight();

        if (nx >= 0 && nx < static_cast<int>(width) &&
            ny >= 0 && ny < static_cast<int>(height)) {

            auto& cell = ocean.getGrid().at(nx, ny);

            if (!cell || dynamic_cast<Algae*>(cell.get())) {
                // перемещаем рыбу на новое место
                auto newFish = this->clone(); // Сначала клонируем
                ocean.getGrid().at(x, y).reset(); // Теперь можно безопасно удалить
                ocean.getGrid().at(nx, ny) = std::move(newFish); // Перемещаем
                return;
            }
        }
    }
}


void HerbivoreFish::eatAlgae(Ocean& ocean) {
    auto pos = ocean.findPosition(*this);
    if (!pos) return;

    int x = pos->first;
    int y = pos->second;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            size_t width = ocean.getGrid().getWidth();
            size_t height = ocean.getGrid().getHeight();

            if (nx >= 0 && nx < static_cast<int>(width) &&
                ny >= 0 && ny < static_cast<int>(height)) {

                auto& cell = ocean.getGrid().at(nx, ny);
                if (cell && dynamic_cast<Algae*>(cell.get())) {
                    fullness_ = maxFullness_; // насытились
                    cell.reset(); // съели водоросль
                    return;
                }
            }
        }
    }
}


void HerbivoreFish::reproduce(Ocean& ocean) {
    if (fullness_ < maxFullness_) return; // недостаточно энергии

    auto pos = ocean.findPosition(*this);
    if (!pos) return;

    int x = pos->first;
    int y = pos->second;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            size_t width = ocean.getGrid().getWidth();
            size_t height = ocean.getGrid().getHeight();

            if (nx >= 0 && nx < static_cast<int>(width) &&
                ny >= 0 && ny < static_cast<int>(height)) {

                auto& cell = ocean.getGrid().at(nx, ny);
                if (!cell) {
                    cell = this->clone(); // рождается новая рыба
                    fullness_ -= 2; // затраты на размножение
                    return;
                }
            }
        }
    }
}
