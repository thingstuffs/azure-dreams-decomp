#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 field_A;
    u8 padC[8];
    s32 field_14;
} TownObject;

extern u8 D_800CFCEF;
extern u8 D_800FE488[9];

extern void func_80093D48(void *, TownObject *, void *);
extern void func_80094C1C(void *);
extern void func_80094C74(TownObject *);
extern void func_80095388(TownObject *);
extern void func_800954F4(TownObject *);
extern s16 func_80095978(TownObject *, void *);
extern void func_80095A94(TownObject *, s16, void *);
extern void func_80095C80(TownObject *);

/* Updates a town object based on its computed threshold and the global flag. */
void func_80093250(void *context, TownObject *object, void *update_data)
{
    s16 threshold;
    u8 *threshold_data;

    func_80095C80(object);
    func_80094C1C(context);
    func_80094C74(object);
    threshold_data = D_800FE488;
    threshold = func_80095978(object, threshold_data);

    if (object->field_A >= threshold) {
        func_80095A94(object, threshold, threshold_data);
        func_80093D48(context, object, update_data);
        return;
    }

    if (D_800CFCEF != 0) {
        object->field_14 = 0;
        func_800954F4(object);
        func_80093D48(context, object, update_data);
    } else {
        func_80095388(object);
    }
}
