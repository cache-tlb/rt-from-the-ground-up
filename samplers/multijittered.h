#ifndef MULTIJITTERED_H
#define MULTIJITTERED_H

#include "sampler.h"

class MultiJittered: public Sampler {
public:
    MultiJittered(void);
    MultiJittered(const int num_samples);
    MultiJittered(const int num_samples, const int m);
    MultiJittered(const MultiJittered& mjs);

    MultiJittered&
    operator= (const MultiJittered& rhs);

    virtual MultiJittered*
    clone(void) const;

    virtual
    ~MultiJittered(void);

private:
    virtual void
    generate_samples(void);
};

#endif // MULTIJITTERED_H
