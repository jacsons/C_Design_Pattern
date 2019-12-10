#include "ChildObject.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int publicOperator(ObjectModel_t *obj, int p)
{
    printf("type 2 arg paramer : %d\n", p);
    printf("type 2 invoker\n");

    return 0;
}

int objRegister2(ObjectModel_t *obj)
{
    obj->publicOperator = publicOperator;
    return 0;
}
