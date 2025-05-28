#pragma once
#include "entity.hpp"

class Ocean;


class Algae : public Entity {
public:
    explicit Algae(int maxAge = 20);

    void update(Ocean& ocean) override;
    char getSymbol() const override;
    bool isAlive() const override;
    std::unique_ptr<Entity> clone() const override;

private:
    int age_;
    const int maxAge_;
};
