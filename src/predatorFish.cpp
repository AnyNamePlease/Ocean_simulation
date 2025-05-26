#include "predatorFish.hpp"
#include "herbivoreFish.hpp"
#include "ocean.hpp"
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>

PredatorFish::PredatorFish(int maxAge, int maxFullness)
    : age_(0), fullness_(maxFullness), maxAge_(maxAge), maxFullness_(maxFullness) {}

char PredatorFish::getSymbol() const {
    return 'P';
}

bool PredatorFish::isAlive() const {
    return age_ < maxAge_ && fullness_ > 0;
}

std::unique_ptr<Entity> PredatorFish::clone() const {
    return std::make_unique<PredatorFish>(*this);
}

void PredatorFish::update(Ocean& ocean) {
    if (!isAlive()) {
        return;
    }

    ++age_;
    --fullness_;

    hunt(ocean);
    move(ocean);
    reproduce(ocean);
}


void PredatorFish::hunt(Ocean& ocean) {
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
                if (cell && dynamic_cast<HerbivoreFish*>(cell.get())) {
                    fullness_ = maxFullness_; // насытились
                    cell.reset(); // съели жертву
                    return;
                }
            }
        }
    }
}


void PredatorFish::move(Ocean& ocean) {
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

            if (!cell || dynamic_cast<HerbivoreFish*>(cell.get())) {
                auto newPredator = this->clone(); // Сначала клонируем
                ocean.getGrid().at(x, y).reset();  // Удаляем старого
                ocean.getGrid().at(nx, ny) = std::move(newPredator); // Перемещаем
                return;
            }
        }
    }
}


void PredatorFish::reproduce(Ocean& ocean) {
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
                    cell = this->clone(); // рождается новая хищная рыба
                    fullness_ -= 3; // затраты на размножение
                    return;
                }
            }
        }
    }
}
