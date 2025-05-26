#include "sand.hpp"

void Sand::update(Ocean& ocean) {
    // Ничего не делает — статическая ячейка
}

char Sand::getSymbol() const {
    return ' ';
}

bool Sand::isAlive() const {
    return false; // Считаем, что песок не является "живой" сущностью
}

std::unique_ptr<Entity> Sand::clone() const {
    return std::make_unique<Sand>(*this);
}
