/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void func_8008F01C(void *, s32, void *);
extern void func_8009B218(void *, s32, void *, void *);

extern s32 D_800CFD00[];
extern s32 D_800D0690[];
extern s32 D_800D0710[];
extern s32 D_800F8C80[];

void func_8009C8FC(void *object, s32 init_arg, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8C80;
    *(void **)((u8 *)object + 0x7C) = D_800D0710;
    func_8008F01C(object, init_arg, D_800CFD00);
    func_8009B218(object, init_arg, state, D_800D0690);
}
