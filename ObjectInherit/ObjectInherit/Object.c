#include "Object.h"
#include <stdio.h>
#include <stdlib.h>


typdef struct ObjectData {
    int invokerCount;
} ObjectData_t;

int publicOperator(Object_t *obj, int p)
{
    if (obj == NULL) {
        return -1;
    }
    ObjectData_t *objData = (ObjectData_t *)obj->privateData;

    printf("arg paramer : %d", p);
    printf("arg paramer : %d", objData->invokerCount);
    objData->invokerCount++;

    return 0;
}

int constructObject(Object_t*)
{
    int ret;
    ObjectData_t *objData = NULL;

    if (obj == NULL) {
        return -1;
    }

    objData = (ObjectData_t *)malloc(sizeof(ObjectData_t));
    if (objData == NULL) {
        return -1;
    }

    ret = memset(objData, 0, sizeof(ObjectData_t));
    if (ret != EOK) {
        free(objData);
        return -1;
    }

    obj->privateData = (void *)objData;
}

void freeObject(Object_t *obj)
{
    if (obj != NULL && obj->privateData != NULL) {
        free(obj->privateData);
    }
}

int register(Object_t *obj)
{
    obj->publicOperator = publicOperator;
    obj->constructObject = constructObject;
    obj->freeObject = freeObject;

    return 0;
}
