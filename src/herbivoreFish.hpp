#pragma once
#include "entity.hpp"

class Ocean;


class HerbivoreFish : public Entity {
public:
    explicit HerbivoreFish(int maxAge = 20, int maxFullness = 10);

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
    void eatAlgae(Ocean& ocean);
    void reproduce(Ocean& ocean);
};