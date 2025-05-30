#pragma once
#include <vector>
#include <memory>
#include <random>
#include "entity.hpp"
#include "utils/grid.hpp"

class Ocean {
public:
    using Grid = utils::Grid<std::unique_ptr<Entity>>;

    Ocean(size_t width, size_t height);
    ~Ocean();

    // Удаление копирования
    Ocean(const Ocean&) = delete;
    Ocean& operator=(const Ocean&) = delete;

    // Поддержка перемещения
    Ocean(Ocean&&) noexcept = default;
    Ocean& operator=(Ocean&&) noexcept = default;
    
    std::mt19937& getRandomEngine();
    
    int countLivingEntities() const;

    void tick();
    void display() const;

    const Grid& getGrid() const { return grid_; }
    Grid& getGrid() { return grid_; }

    // Находит координаты указанной сущности в сетке
    std::optional<std::pair<int, int>> findPosition(const Entity& entity) const;

private:
    Grid grid_;
    std::mt19937 rng_;
};
