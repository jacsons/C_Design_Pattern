#include "ChildObject.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ChildObjectData {
    int invokerCount;
} ChildObjectData_t;

static int publicOperator(ChildObject_t *obj, int p)
{
    if (obj == NULL) {
        return -1;
    }

    ChildObjectData_t *objData = (ChildObjectData_t *)obj->privateData;

    printf("child arg paramer : %d\n", p);
    printf("child invoker time : %d\n", objData->invokerCount);
    objData->invokerCount++;

    obj->parentObj.publicOperator(&obj->parentObj, 1);

    return 0;
}

static int constructObject(ChildObject_t *obj)
{
    int ret;
    ChildObjectData_t *objData = NULL;

    if (obj == NULL) {
        return -1;
    }

    ret = obj->parentObj.constructObject(&obj->parentObj);
    if (ret != 0) {
        return -1;
    }

    objData = (ChildObjectData_t *)malloc(sizeof(ChildObjectData_t));
    if (objData == NULL) {
        return -1;
    }

    objData = memset(objData, 0, sizeof(ChildObjectData_t));
    if (objData == NULL) {
        free(objData);
        return -1;
    }

    objData->invokerCount = 0;
    obj->privateData = (void *)objData;

    return 0;
}

static void freeObject(ChildObject_t *obj)
{
    if (obj != NULL && obj->privateData != NULL) {
        free(obj->privateData);
    }


    obj->parentObj.freeObject(&obj->parentObj);

}

int childRegister(ChildObject_t *obj)
{
    objRegister(&obj->parentObj);

    obj->publicOperator = publicOperator;
    obj->constructObject = constructObject;
    obj->freeObject = freeObject;

    return 0;
}
