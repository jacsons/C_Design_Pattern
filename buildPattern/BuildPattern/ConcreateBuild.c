#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "ConcreateBuild.h"

static void setProduct(struct ConcrateBuild *obj, struct product *product)
{
    assert(obj);
    obj->product = product;
}

static void buildCompute(struct ConcrateBuild *obj)
{
    printf("start build product!!!\n");

    if (obj != NULL && obj->product != NULL) {
        obj->product->build(obj->product);
    }

    printf("end build product!!!\n");
}

static void initOperators(struct ConcrateBuild *obj)
{
    assert(obj);

    obj->setProduct = setProduct;
    obj->buildCompute = buildCompute;
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

int constructConcrateBuild(struct ConcrateBuild **obj)
{
    if (obj == NULL) {
        return -1;
    }

    *obj = (struct ConcrateBuild *)mallocZeroObj(sizeof(struct ConcrateBuild));
    if (*obj == NULL) {
        return -1;
    }

    initOperators(*obj);

    return 0;
}

void freeConcrateBuild(struct ConcrateBuild *obj)
{
    if (obj != NULL) {
        free(obj);
    }
}
