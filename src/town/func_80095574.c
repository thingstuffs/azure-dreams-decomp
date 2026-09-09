#include "common.h"

typedef struct {
    s8 pad0[0x10];
    u32 pressed;
} SharedInput;

typedef struct {
    u8 pad0[0x14];
    s32 field14;
} TownObject;

extern SharedInput D_80083160;
extern u8 D_800CFCEE[];

extern void func_80095C80(TownObject *);
extern void func_80094C1C(void *);
extern void func_80094C74(TownObject *);
extern void func_800954F4(TownObject *);
extern void func_80095388(TownObject *);
extern void func_80094714(void *, TownObject *, void *);
extern void func_80094620(void *, TownObject *, void *);

void func_80092CD4(void *arg0, TownObject *arg1, void *arg2)
{
    SharedInput *input = &D_80083160;

    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80094C74(arg1);

    if (D_800CFCEE[0] != 0) {
        arg1->field14 = 0;
        func_800954F4(arg1);
    } else {
        func_80095388(arg1);
    }

    if (input->pressed & 0x40) {
        func_80094714(arg0, arg1, arg2);
        return;
    }

    if (arg1->field14 >= 0) {
        func_80094620(arg0, arg1, arg2);
    }
}
