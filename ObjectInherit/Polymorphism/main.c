#include "ObjectModel.h"

#include "Object.h"
#include "Object2.h"
int main()
{
    ObjectModel_t object;

    objRegister1(&object);

    object.publicOperator(&object, 1);

    objRegister2(&object);
    object.publicOperator(&object, 1);

    return 0;
}
