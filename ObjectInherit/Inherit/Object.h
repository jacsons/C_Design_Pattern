#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

typedef struct Object {
    int  (*publicOperator)(struct Object *obj, int p);
    int (*constructObject)(struct Object *obj);
    void (*freeObject)(struct Object *obj);
    void *privateData;
} Object_t;

int objRegister(struct Object *obj);

#endif // OBJECT_H_INCLUDED
