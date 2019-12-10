#ifndef BUILD_H_INCLUDED
#define BUILD_H_INCLUDED

typedef struct Builder {
    void *privateData;

    void (*buildHWCompute)(struct Builder *obj);
} Builder_t;

int constructBuild(struct Builder **obj);
void freeBuild(struct Builder *obj);

#endif // BUILD_H_INCLUDED
