#include "Object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ObjectData {
    int invokerCount;
} ObjectData_t;

int publicOperator(Object_t *obj, int p)
{
    if (obj == NULL) {
        return -1;
    }

    ObjectData_t *objData = (ObjectData_t *)obj->privateData;

    printf("arg paramer : %d\n", p);
    printf("invoker time : %d\n", objData->invokerCount);
    objData->invokerCount++;

    return 0;
}

int constructObject(Object_t *obj)
{
    ObjectData_t *objData = NULL;

    if (obj == NULL) {
        return -1;
    }

    objData = (ObjectData_t *)malloc(sizeof(ObjectData_t));
    if (objData == NULL) {
        return -1;
    }

    objData = memset(objData, 0, sizeof(ObjectData_t));
    if (objData == NULL) {
        free(objData);
        return -1;
    }

    objData->invokerCount = 0;
    obj->privateData = (void *)objData;

    return 0;
}

void freeObject(Object_t *obj)
{
    if (obj != NULL && obj->privateData != NULL) {
        free(obj->privateData);
    }
}

int objRegister(Object_t *obj)
{
    obj->publicOperator = publicOperator;
    obj->constructObject = constructObject;
    obj->freeObject = freeObject;

    return 0;
}
