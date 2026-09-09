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

/* Updates the town object and dispatches its action based on input and state. */
void func_80092CD4(void *context, TownObject *object, void *action_data)
{
    SharedInput *input = &D_80083160;

    func_80095C80(object);
    func_80094C1C(context);
    func_80094C74(object);

    if (D_800CFCEE[0] != 0) {
        object->field14 = 0;
        func_800954F4(object);
    } else {
        func_80095388(object);
    }

    if (input->pressed & 0x40) {
        func_80094714(context, object, action_data);
        return;
    }

    if (object->field14 >= 0) {
        func_80094620(context, object, action_data);
    }
}
