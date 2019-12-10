#ifndef CPUPRODUCT_H_INCLUDED
#define CPUPRODUCT_H_INCLUDED
#include "product.h"

typedef struct CpuProduct {
    void *privateData;

    void (*setVirtualOpt)(struct CpuProduct *obj, struct VirtualOpt *virtualOpt);
    int (*getVirtualOpt)(struct CpuProduct *obj, struct VirtualOpt *virtualOpt);

    struct product *(*getProduct)(struct CpuProduct *cpuProduct);
} CpuProduct_t;

int constructCPUProduct(struct CpuProduct **obj);
void freeCpuProduct(struct CpuProduct *obj);

#endif // CPUPRODUCT_H_INCLUDED
