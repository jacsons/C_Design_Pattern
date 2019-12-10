#ifndef AMDCPU_H_INCLUDED
#define AMDCPU_H_INCLUDED
#include "CpuProduct.h"

typedef struct AmdProduct {
    void *privateData;

    struct product *(*getProduct)(struct AmdProduct *obj);
} AmdProduct_t;

int constructAmdCpu(struct AmdProduct **obj, char *name, char *type);
void freeAmdCpu(struct AmdProduct *obj);

#endif // AMDCPU_H_INCLUDED
