#include "Object.h"

int main()
{
    Object_t object;
    objRegister(&object);

    object.constructObject(&object);

    object.publicOperator(&object, 1);
    object.publicOperator(&object, 1);
    object.publicOperator(&object, 1);

    object.freeObject(&object);

    return 0;
}
