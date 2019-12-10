#include "product.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

typedef struct ProductPrivata {
       struct VirtualOpt virtualOpt;
}ProductPrivata_t;

static char *getName(struct product *obj)
{
    struct ProductPrivata *privateData = NULL;

    if (obj == NULL || obj->privateDate == NULL) {
        return "";
    }
    privateData = ((ProductPrivata_t *)(obj->privateDate));

    if (privateData->virtualOpt.getName != NULL && privateData->virtualOpt.thisObj != NULL) {
        return privateData->virtualOpt.getName(privateData->virtualOpt.thisObj);
    }

    return "";
}

static char *getType(struct product *obj)
{
    struct ProductPrivata *privateData = NULL;

    if (obj == NULL || obj->privateDate == NULL) {
        return "";
    }
    privateData = ((ProductPrivata_t *)(obj->privateDate));

    if (privateData->virtualOpt.getType != NULL && privateData->virtualOpt.thisObj != NULL) {
        return privateData->virtualOpt.getType(privateData->virtualOpt.thisObj);
    }

    return "";
}

void *virtualbuild(struct product *obj)
{
    if (obj == NULL) {
        printf("product object is null\n");
        return NULL;
    }
    struct ProductPrivata *privateData = NULL;

      privateData = ((ProductPrivata_t *)(obj->privateDate));

    if (privateData->virtualOpt.getType != NULL && privateData->virtualOpt.thisObj != NULL) {
        privateData->virtualOpt.build(privateData->virtualOpt.thisObj);
    }

    return obj;
}

static void setVirtualOpt(struct product *obj, struct VirtualOpt *virtualOpt)
{
    struct ProductPrivata *privateData = NULL;
    if (virtualOpt == NULL || obj == NULL) {
        return;
    }

    privateData = ((ProductPrivata_t *)(obj->privateDate));

    privateData->virtualOpt.build = virtualOpt->build;
    privateData->virtualOpt.getName = virtualOpt->getName;
    privateData->virtualOpt.getType = virtualOpt->getType;
    privateData->virtualOpt.thisObj = virtualOpt->thisObj;
}

static int getVirtualOpt(struct product *obj, struct VirtualOpt *virtualOpt)
{
    struct ProductPrivata *privateData = NULL;

    if (virtualOpt == NULL || obj == NULL) {
        return -1;
    }

    privateData = ((ProductPrivata_t *)(obj->privateDate));

    virtualOpt->build = privateData->virtualOpt.build;
    virtualOpt->getName = privateData->virtualOpt.getName;
    virtualOpt->getType = privateData->virtualOpt.getType;
    virtualOpt->thisObj = privateData->virtualOpt.thisObj;

    return 0;
}

static int initPrivateData(ProductPrivata_t *data)
{
    void *ret;
    if (data == NULL) {
        return -1;
    }

    ret = memset(&data->virtualOpt, 0, sizeof(struct VirtualOpt));

    if (ret == NULL) {
        return -1;
    }

    return 0;
}


static int initOperators(struct product *obj)
{
    obj->getName = getName;
    obj->getType = getType;

    obj->build = virtualbuild;
    obj->setVirtualOpt = setVirtualOpt;
    obj->getVirtualOpt = getVirtualOpt;
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

int constructProduct(struct product **obj)
{
    struct ProductPrivata *data = NULL;

    if (obj == NULL) {
        return -1;
    }

    *obj = (struct product *)mallocZeroObj(sizeof(struct product));
    if (obj == NULL) {
        return -1;
    }

    data = (struct ProductPrivata*)mallocZeroObj(sizeof(struct ProductPrivata));
    if(data == NULL) {
        free(*obj);
        return -1;
    }

    initPrivateData((ProductPrivata_t *)((*obj)->privateDate));
    initOperators(*obj);

    (*obj)->privateDate = data;

    return 0;
}

void freeProduct(struct product *obj)
{
    if (obj == NULL) {
        return;
    }

    if (obj->privateDate != NULL) {
        free(obj->privateDate);
    }

    free(obj);
}


