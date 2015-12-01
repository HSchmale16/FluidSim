#ifndef EMITTER_H
#define EMITTER_H

#include <cstdint>

class Emitter {
public:
    Emitter();
    virtual ~Emitter();

protected:

private:
    uint64_t _x;
    uint64_t _y;
    uint64_t _amount; //!< Amount fluid produced per tick
};

#endif // EMITTER_H
