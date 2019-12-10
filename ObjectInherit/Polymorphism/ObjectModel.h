#ifndef OBJECTMODEL_H_INCLUDED
#define OBJECTMODEL_H_INCLUDED

typedef struct ObjectModel {
    int  (*publicOperator)(struct ObjectModel *obj, int p);
} ObjectModel_t;


#endif // OBJECTMODEL_H_INCLUDED
