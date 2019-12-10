#include <stdio.h>
#include <stdlib.h>
#include "Builder.h"

int main()
{
    int ret;
    struct Builder *build = NULL;
    ret = constructBuild(&build);
    if (ret != 0) {
        printf("constructBuild failed, ret = %d\n", ret);
        return -1;
    }

    build->buildHWCompute(build);

    freeBuild(build);

    return 0;
}
