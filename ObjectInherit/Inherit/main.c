#include "ChildObject.h"

int main()
{
    ChildObject_t object;

    childRegister(&object);

    object.constructObject(&object);

    object.publicOperator(&object, 1);
    object.publicOperator(&object, 1);
    object.publicOperator(&object, 1);

    object.freeObject(&object);

    return 0;
}
