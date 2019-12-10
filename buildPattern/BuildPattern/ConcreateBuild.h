#ifndef CONCRATEBUILD_H_INCLUDED
#define CONCRATEBUILD_H_INCLUDED
#include "product.h"

typedef struct ConcrateBuild {
    struct product *product;

    void (*setProduct)(struct ConcrateBuild *obj, struct product *product);
    void (*buildCompute)(struct ConcrateBuild *obj);
} ConcrateBuild_t;

int constructConcrateBuild(struct ConcrateBuild **obj);
void freeConcrateBuild(struct ConcrateBuild *obj);

#endif // CONCRATEBUILD_H_INCLUDED
