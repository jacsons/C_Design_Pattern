#include "InterCpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *build(struct product *obj)
{
    if (obj == NULL) {
        return NULL;
    }

    printf("build Inter cpu product\n");

    return obj;
}

static void initOperators(struct InterProduct *obj)
{

}

static void* mallocZeroObj(unsigned int objSize)
{
    void *obj = NULL;

    obj = malloc(objSize);
    if (obj == NULL) {
        return NULL;
    }

    obj = memset(obj, 0, objSize);
    if (obj == NULL) {
        free(obj);
        return NULL;
    }

    return obj;
}

int constructInterCpu(struct InterProduct **obj, char *name, char *type)
{
    int result;

    if (obj == NULL) {
        return -1;
    }

    *obj = (struct InterProduct *)mallocZeroObj(sizeof(struct InterProduct));
    if (*obj  == NULL) {
        return -1;
    }

    result = constructCPUProduct(&((*obj)->product));
    if (result != 0) {
        return -1;
    }

    initOperators(*obj);

    return 0;
}

void freeInterCpu(struct InterProduct *obj)
{
     if (obj == NULL) {
        return;
    }

    freeCpuProduct(obj->product);
    free(obj);
}
