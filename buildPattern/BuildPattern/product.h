#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

struct VirtualOpt;

typedef struct product
{
    void *privateDate;

    void (*setVirtualOpt)(struct product *obj, struct VirtualOpt *virtualOpt);
    int (*getVirtualOpt)(struct product *obj, struct VirtualOpt *virtualOpt);

    char *(*getName)(struct product *obj);
    char *(*getType)(struct product *obj);
    void *(*build)(struct product *obj); //virtual build function
} product_t;

// virtual function group
typedef struct VirtualOpt {
    void *thisObj;

    char *(*getName)(void *parm);
    char *(*getType)(void *parm);
    void *(*build)(void *parm); //virtual build function
} virtualOpt_t;

// construct funtion and deconstruct function
int constructProduct(struct product **obj);
void freeProduct(struct product *obj);

#endif // PRODUCT_H_INCLUDED
