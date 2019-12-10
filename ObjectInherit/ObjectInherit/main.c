#include "Object.h"

int mian()
{
    Object_t object = {0};
    register(&object);

    object.constructObject(&object);

    object.publicOperator(&object, 1);
    object.publicOperator(&object, 1);
    object.publicOperator(&object, 1);

    object.freeObject(&object);

    return 0;
}
