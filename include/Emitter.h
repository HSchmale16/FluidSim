#ifndef EMITTER_H
#define EMITTER_H

#include <cstdint>

class Emitter {
public:
    Emitter();
    virtual ~Emitter();

    int _x;
    int _y;
    int _amount; //!< Amount fluid produced per tick
protected:

private:
};

#endif // EMITTER_H
