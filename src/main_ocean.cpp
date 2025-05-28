#include "ocean.hpp"
#include "algae.hpp"
#include "herbivoreFish.hpp"
#include "predatorFish.hpp"
#include "sand.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

constexpr size_t WIDTH = 20;
constexpr size_t HEIGHT = 10;
constexpr int MAX_TICKS = 100;
constexpr float INITIAL_ALGAE_DENSITY = 0.2f;
constexpr float INITIAL_HERBIVORE_DENSITY = 0.08f;
constexpr float INITIAL_PREDATOR_DENSITY = 0.02f;

void initializeOceanRandomly(Ocean& ocean) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    size_t totalCells = ocean.getGrid().getWidth() * ocean.getGrid().getHeight();

    // Расставляем водоросли
    for (size_t i = 0; i < totalCells * INITIAL_ALGAE_DENSITY; ++i) {
        int x = rand() % ocean.getGrid().getWidth();
        int y = rand() % ocean.getGrid().getHeight();
        if (!ocean.getGrid().at(x, y)) {
            ocean.getGrid().at(x, y) = std::make_unique<Algae>();
        }
    }

    // Расставляем травоядных рыб
    for (size_t i = 0; i < totalCells * INITIAL_HERBIVORE_DENSITY; ++i) {
        int x = rand() % ocean.getGrid().getWidth();
        int y = rand() % ocean.getGrid().getHeight();
        if (!ocean.getGrid().at(x, y)) {
            ocean.getGrid().at(x, y) = std::make_unique<HerbivoreFish>();
        }
    }

    // Расставляем хищных рыб
    for (size_t i = 0; i < totalCells * INITIAL_PREDATOR_DENSITY; ++i) {
        int x = rand() % ocean.getGrid().getWidth();
        int y = rand() % ocean.getGrid().getHeight();
        if (!ocean.getGrid().at(x, y)) {
            ocean.getGrid().at(x, y) = std::make_unique<PredatorFish>();
        }
    }

    // Остальные ячейки остаются пустыми (Sand будет по умолчанию)
}

int main() {
    Ocean ocean(WIDTH, HEIGHT);
    initializeOceanRandomly(ocean);

    for (int tick = 0; tick < MAX_TICKS; ++tick) {
        std::cout << "Tick " << tick << "\n";
        ocean.display();
        ocean.tick();
        
        if (ocean.countLivingEntities() == 0) {
            break;
        }

        // Задержка для удобства наблюдения (UNIX/Linux)
        usleep(300000);
    }

    return 0;
}
