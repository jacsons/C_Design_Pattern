#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

typedef struct Object {
    int ги*publicOperator)(Object_t *obj, int p);
    int (*constructObject)(Object_t *obj);
    void (*freeObject)(Object_t *obj);
    void *privateData;
} Object_t;

int register(Object_t *obj);

#endif // OBJECT_H_INCLUDED
