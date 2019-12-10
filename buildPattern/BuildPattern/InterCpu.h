#ifndef INTERCPU_H_INCLUDED
#define INTERCPU_H_INCLUDED
#include "CpuProduct.h"

typedef struct InterProduct {
    struct CpuProduct *product;
} AmdProduct_t;

int constructInterCpu(struct InterProduct **obj, char *name, char *type);
void freeInterCpu(struct InterProduct *obj);

#endif // INTERCPU_H_INCLUDED
