#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 field_A;
    u8 padC[8];
    s32 field_14;
} TownObject;

extern u8 D_800CFCEF;
extern u8 D_800FE488[9];

extern void func_800932EC(void *);
extern void func_80093308(void);
extern void func_80093D48(void *, TownObject *, void *);
extern void func_80094C1C(void *);
extern void func_80094C74(TownObject *);
extern void func_80095388(TownObject *);
extern void func_800954F4(TownObject *);
extern s16 func_80095978(TownObject *, void *);
extern void func_80095A94(TownObject *, s16, void *);
extern void func_80095C80(TownObject *);

void func_80093250(void *arg0, TownObject *arg1, void *arg2)
{
    s16 value;
    u8 *data;

    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80094C74(arg1);
    data = D_800FE488;
    value = func_80095978(arg1, data);

    if (arg1->field_A >= value) {
        func_80095A94(arg1, value, data);
        func_800932EC(arg0);
        return;
    }

    if (D_800CFCEF != 0) {
        arg1->field_14 = 0;
        func_800954F4(arg1);
        func_80093D48(arg0, arg1, arg2);
        func_80093308();
        return;
    }

    func_80095388(arg1);
}
