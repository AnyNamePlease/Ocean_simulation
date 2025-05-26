#pragma once
#include "entity.hpp"

class Ocean;


class PredatorFish : public Entity {
public:
    explicit PredatorFish(int maxAge = 30, int maxFullness = 15);

    void update(Ocean& ocean) override;
    char getSymbol() const override;
    bool isAlive() const override;
    std::unique_ptr<Entity> clone() const override;

private:
    int age_;
    int fullness_;
    const int maxAge_;
    const int maxFullness_;

    void move(Ocean& ocean);
    void hunt(Ocean& ocean);
    void reproduce(Ocean& ocean);
};