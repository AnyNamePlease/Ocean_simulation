#pragma once

#include <memory>
#include <string>

class Ocean;


class Entity {
public:

    virtual ~Entity();


    virtual void update(Ocean& ocean) = 0;


    virtual char getSymbol() const = 0;


    virtual bool isAlive() const { return true; }


    virtual std::unique_ptr<Entity> clone() const = 0;

    
    //virtual std::string getType() const = 0;

};
