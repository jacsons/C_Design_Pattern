#include "Object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int publicOperator(ObjectModel_t *obj, int p)
{
    if (obj == NULL) {
        return -1;
    }

    printf("type 1 arg paramer : %d\n", p);
    printf("type 1 invoker\n");

    return 0;
}

int objRegister1(ObjectModel_t *obj)
{
    obj->publicOperator = publicOperator;

    return 0;
}
