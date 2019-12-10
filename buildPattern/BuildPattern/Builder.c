#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Builder.h"
#include "ConcreateBuild.h"
#include "AmdCpu.h"

typedef struct BuildPrivateData {
    struct ConcrateBuild *obj;
} BuildPrivateData_t;


static void buildHWCompute(struct Builder *obj)
{
    struct AmdProduct *amdProduct = NULL;
    struct BuildPrivateData *buildPrivateData;

    assert(obj);

    buildPrivateData = (struct BuildPrivateData *)obj->privateData;
    assert(buildPrivateData->obj);

    constructAmdCpu(&amdProduct, "amd cpu 1", "amd cpu");
    buildPrivateData->obj->setProduct(buildPrivateData->obj, amdProduct->getProduct(amdProduct));
    buildPrivateData->obj->buildCompute(buildPrivateData->obj);


    free(amdProduct);
}

static int initePrivateData(struct BuildPrivateData *buildPrivateData)
{
    assert(buildPrivateData);

    return constructConcrateBuild(&buildPrivateData->obj);
}

static void initOperators(struct Builder *obj)
{
    assert(obj);
    obj->buildHWCompute = buildHWCompute;
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

int constructBuild(struct Builder **obj)
{
    struct BuildPrivateData *buildPrivateData = NULL;

    if (obj == NULL) {
        return -1;
    }

    *obj = (struct Builder *)mallocZeroObj(sizeof(struct Builder));
    if (*obj == NULL) {
        return -1;
    }

    buildPrivateData = (struct BuildPrivateData *)mallocZeroObj(sizeof(struct BuildPrivateData));
    if (buildPrivateData == NULL) {
        return -1;
    }

    initePrivateData(buildPrivateData);

    (*obj)->privateData = buildPrivateData;
    initOperators(*obj);

    return 0;
}

void freeBuild(struct Builder *obj)
{
    if (obj == NULL) {
        return;
    }

    if (obj->privateData == NULL) {
       free(obj);
       return;
    }

    freeConcrateBuild(((struct BuildPrivateData *)(obj->privateData))->obj);

    free(obj->privateData);
    free(obj);
}
