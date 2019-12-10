#include "CpuProduct.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct CpuProductPrivateData {
    struct product *product;
    struct VirtualOpt virtualOpt;
} CpuProductPrivateData_t;

static void* build(void *obj)
{
    struct CpuProduct *ptr = (struct CpuProduct*)obj;
    struct CpuProductPrivateData *privateData = NULL;
    if (obj == NULL) {
        return NULL;
    }

    privateData = (CpuProductPrivateData_t *)ptr->privateData;
    privateData->virtualOpt.build(privateData->virtualOpt.thisObj);

    return obj;
}

static char* getName(void *obj)
{
    struct CpuProduct *ptr = (struct CpuProduct*)obj;
    struct CpuProductPrivateData *privateData = NULL;

    if (obj == NULL) {
        return "";
    }

    privateData = ((CpuProductPrivateData_t *)(ptr->privateData));

    return privateData->virtualOpt.getName(privateData->virtualOpt.thisObj);
}

static char* getType(void *obj)
{
    struct CpuProduct *ptr = (struct CpuProduct*)obj;
    struct CpuProductPrivateData *privateData = NULL;
    if (obj == NULL) {
        return "";
    }

    privateData = (struct CpuProductPrivateData *)(ptr->privateData);

    return privateData->virtualOpt.getType(privateData->virtualOpt.thisObj);
}

static struct product *getProduct(struct CpuProduct *cpuProduct)
{
    CpuProductPrivateData_t *cpuProductPrivateData = NULL;
    if (cpuProduct == NULL) {
        return NULL;
    }

    cpuProductPrivateData = (CpuProductPrivateData_t *)(cpuProduct->privateData);

    return cpuProductPrivateData->product;
}

static void setVirtualOpt(struct CpuProduct *obj, const struct VirtualOpt *virtualOpt)
{
    struct CpuProductPrivateData *privateData = NULL;
    struct VirtualOpt virtualOptTmp;
    if (virtualOpt == NULL || obj == NULL) {
        return;
    }

    privateData = ((CpuProductPrivateData_t *)obj->privateData);

    privateData->virtualOpt.build = virtualOpt->build;
    privateData->virtualOpt.getName = virtualOpt->getName;
    privateData->virtualOpt.getType = virtualOpt->getType;
    privateData->virtualOpt.thisObj = virtualOpt->thisObj;

    virtualOptTmp.build = build;
    virtualOptTmp.getName = getName;
    virtualOptTmp.getType = getType;
    virtualOptTmp.thisObj = obj;

    privateData->product->setVirtualOpt(privateData->product, &virtualOptTmp);
}

static int getVirtualOpt(struct CpuProduct *obj, struct VirtualOpt *virtualOpt)
{
    CpuProductPrivateData_t *privateData = NULL;

    if (virtualOpt == NULL || obj == NULL) {
        return -1;
    }

    privateData = ((CpuProductPrivateData_t *)(obj->privateData));
    privateData->product->getVirtualOpt(privateData->product, virtualOpt);

    return 0;
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

static void initOperators(struct CpuProduct *obj)
{
    if (obj != NULL) {
        obj->setVirtualOpt = setVirtualOpt;
        obj->getVirtualOpt = getVirtualOpt;
        obj->getProduct = getProduct;
    }
}

static int initPrivateData(struct CpuProduct *obj)
{
    int result;
    struct CpuProductPrivateData *cpuPrivData = NULL;

    assert(obj);

    cpuPrivData = mallocZeroObj(sizeof(struct CpuProductPrivateData));
    if (cpuPrivData == NULL) {
        return -1;
    }

    result = constructProduct(&cpuPrivData->product);
    if (result != 0) {
        free(cpuPrivData);
        return -1;
    }

    obj->privateData = cpuPrivData;

    return 0;
}

int constructCPUProduct(struct CpuProduct **obj)
{
    int ret;

    if (obj == NULL) {
        return -1;
    }

    *obj = (struct CpuProduct *)mallocZeroObj(sizeof(struct CpuProduct));
    if (*obj  == NULL) {
        return -1;
    }

    ret = initPrivateData(*obj);
    if (ret != 0) {
        free(*obj);
        return -1;
    }

    initOperators(*obj);

    return 0;
}

void freeCpuProduct(struct CpuProduct *obj)
{
    CpuProductPrivateData_t *productPrivata = NULL;

    if (obj == NULL) {
        return;
    }

    if (obj->privateData != NULL) {
        productPrivata = (CpuProductPrivateData_t *)obj->privateData;
        freeProduct(productPrivata->product);
        free(obj->privateData);
    }

    free(obj);
}
