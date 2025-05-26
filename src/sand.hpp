#pragma once
#include "entity.hpp"


class Sand : public Entity {
public:
    void update(class Ocean& ocean) override;
    char getSymbol() const override;
    bool isAlive() const override;
    std::unique_ptr<Entity> clone() const override;
};
