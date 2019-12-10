#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "AmdCpu.h"

typedef struct AmdProductData {
   char *name;
   char *type;

   struct CpuProduct *product;
} AmdProductData_t;

static char *getName(void *obj)
{
    struct AmdProduct *amdProduct = NULL;
    AmdProductData_t *amdProductData = NULL;
    if (obj == NULL) {
        return "";
    }
    amdProduct = (struct AmdProduct*)obj;
    amdProductData = (AmdProductData_t *)amdProduct->privateData;

    return amdProductData->name;
}

static char *getType(void *obj)
{
    struct AmdProduct *amdProduct = NULL;
    AmdProductData_t *amdProductData = NULL;
    if (obj == NULL) {
        return "";
    }
    amdProduct = (struct AmdProduct*)obj;
    amdProductData = (AmdProductData_t *)amdProduct->privateData;

    return amdProductData->type;
}

static struct product *getProduct(struct AmdProduct *obj)
{
    struct AmdProduct *amdProduct = NULL;
    AmdProductData_t *amdProductData = NULL;
    if (obj == NULL) {
        return NULL;
    }
    amdProduct = (struct AmdProduct*)obj;
    amdProductData = (AmdProductData_t *)amdProduct->privateData;

    return amdProductData->product->getProduct(amdProductData->product);
}

static void* build(void *obj)
{
    struct AmdProduct *amdProduct = NULL;
    if (obj == NULL) {
        return NULL;
    }

    amdProduct = (struct AmdProduct*)obj;

    printf("build amd product\n");
    return amdProduct;
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

static int initPrivateData(struct AmdProduct *obj, char *name, char *type)
{
    int ret;
    AmdProductData_t *amdProductData = NULL;

    amdProductData = (AmdProductData_t *)mallocZeroObj(sizeof(AmdProductData_t));
    if (amdProductData == NULL) {
        return -1;
    }

    ret = constructCPUProduct(&amdProductData->product);
    if (ret != 0) {
        return -1;
    }

    amdProductData->name = name;
    amdProductData->type = type;

    obj->privateData = amdProductData;

    return 0;
}

static int initOperators(struct AmdProduct *amdProduct)
{
    AmdProductData_t *amdProductData = NULL;
    struct VirtualOpt virtualOptTemp;

    if (amdProduct == NULL) {
        return -1;
    }

    amdProductData = (struct AmdProductData*)mallocZeroObj(sizeof(struct AmdProductData));
    constructCPUProduct(&amdProductData->product);

    virtualOptTemp.build = build;
    virtualOptTemp.getName = getName;
    virtualOptTemp.getType = getType;
    virtualOptTemp.thisObj = amdProduct;
    amdProductData->product->setVirtualOpt(amdProductData->product, &virtualOptTemp);

    amdProduct->getProduct = getProduct;
    amdProduct->privateData = amdProductData;

    return 0;
}

int constructAmdCpu(struct AmdProduct **obj, char *name, char *type)
{
    int ret;

    if (obj == NULL) {
        return -1;
    }

    *obj = (struct AmdProduct *)mallocZeroObj(sizeof(struct AmdProduct));
    if (*obj  == NULL) {
        return -1;
    }

    ret = initOperators(*obj);
    if (ret < 0) {
        return -1;
    }

    ret = initPrivateData(*obj, name, type);
    if (ret < 0) {
        return -1;
    }

    return 0;
}

void freeAmdCpu(struct AmdProduct *obj)
{
    AmdProductData_t *amdProductData = NULL;
     if (obj == NULL) {
        return;
    }

    if (obj->privateData != NULL) {
        amdProductData = (AmdProductData_t *)obj->privateData;
        freeCpuProduct(amdProductData->product);
        free(obj->privateData);
    }

    free(obj);
}
