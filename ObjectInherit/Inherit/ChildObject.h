#ifndef CHILDOBJECT_H_INCLUDED
#define CHILDOBJECT_H_INCLUDED
#include "Object.h"

typedef struct ChildObject {
    Object_t parentObj;

    int  (*publicOperator)(struct ChildObject *obj, int p);
    int (*constructObject)(struct ChildObject *obj);
    void (*freeObject)(struct ChildObject *obj);
    void *privateData;
} ChildObject_t;

int childRegister(ChildObject_t *obj);


#endif // CHILDOBJECT_H_INCLUDED
