#include "ocean.hpp"
#include <iostream>

Ocean::Ocean(size_t width, size_t height)
    : grid_(width, height) {}

Ocean::~Ocean() = default;

std::mt19937& Ocean::getRandomEngine() {
    return rng_;
}

void Ocean::tick() {
    std::vector<std::pair<size_t, size_t>> positions;

    for (size_t y = 0; y < grid_.getHeight(); ++y) {
        for (size_t x = 0; x < grid_.getWidth(); ++x) {
            if (grid_.at(x, y)) {
                positions.emplace_back(x, y);
            }
        }
    }

    for (auto [x, y] : positions) {
        auto& cell = grid_.at(x, y);
        if (cell && cell->isAlive()) {
            cell->update(*this); // Обновляем только живых
        }
    }

    // После всех update(), можно явно очистить мертвых
    for (size_t y = 0; y < grid_.getHeight(); ++y) {
        for (size_t x = 0; x < grid_.getWidth(); ++x) {
            auto& cell = grid_.at(x, y);
            if (cell && !cell->isAlive()) {
                cell.reset(); // Удаляем мертвую сущность
            }
        }
    }
}

void Ocean::display() const {
    for (size_t y = 0; y < grid_.getHeight(); ++y) {
        for (size_t x = 0; x < grid_.getWidth(); ++x) {
            auto& cell = grid_.at(x, y);
            if (cell && cell->isAlive()) {
                std::cout << cell->getSymbol() << ' ';
            } else {
                std::cout << "  "; // или ' ', чтобы не было символа
            }
        }
        std::cout << '\n';
    }
    std::cout << "\n-------------------------\n\n";
}

std::optional<std::pair<int, int>> Ocean::findPosition(const Entity& entity) const {
    for (size_t y = 0; y < grid_.getHeight(); ++y) {
        for (size_t x = 0; x < grid_.getWidth(); ++x) {
            auto& cell = grid_.at(x, y);
            if (cell.get() == &entity) {
                return std::make_pair(static_cast<int>(x), static_cast<int>(y));
            }
        }
    }
    return std::nullopt;
}


int Ocean::countLivingEntities() const {
    int count = 0;

    for (size_t y = 0; y < grid_.getHeight(); ++y) {
        for (size_t x = 0; x < grid_.getWidth(); ++x) {
            auto& cell = grid_.at(x, y);
            if (cell && cell->isAlive()) {
                ++count;
            }
        }
    }

    return count;
}
