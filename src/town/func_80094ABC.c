#include "common.h"

typedef struct TownObject {
    u8 pad0[0xA];
    s16 limit;
    u8 padC[8];
    s32 state;
} TownObject;

extern void func_80095C80(TownObject *arg);
extern void func_80094C1C(void *arg);
extern void func_80094C74(TownObject *arg);
extern void func_80094910(void);
extern s16 func_80095978(TownObject *arg, s32 *table);
extern void func_80095A94(TownObject *arg, s16 value, s32 *table);
extern void func_800ABD74(TownObject *arg);
extern void func_800954F4(TownObject *arg);
extern void func_80093D48(void *arg0, TownObject *arg1, s32 arg2);
extern void func_80095388(TownObject *arg);

extern u8 D_800CFCEF;
extern s32 D_800FE488[];

void func_8009221C(void *arg0, TownObject *arg1, s32 arg2)
{
    s16 value;

    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80094C74(arg1);
    value = func_80095978(arg1, D_800FE488);

    if (arg1->limit >= value) {
        func_80094910();
        func_80095A94(arg1, value, D_800FE488);
        func_800ABD74(arg1);
        func_80093D48(arg0, arg1, arg2);
    } else if (D_800CFCEF != 0) {
        func_80094910();
        arg1->state = 0;
        func_800954F4(arg1);
        func_80093D48(arg0, arg1, arg2);
    } else {
        func_80095388(arg1);
    }
}
