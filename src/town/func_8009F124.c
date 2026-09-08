#include "common.h"

extern void func_8008F01C(void *, s32, void *);
extern void func_8009B218(void *, s32, void *, void *);

extern s32 D_800CFD00[];
extern s32 D_800D06AC[];
extern s32 D_800D0704[];
extern s32 D_800F8C44[];

/* Sets up an object's resource tables and associated state. */
void func_8009C884(void *object, s32 init_arg, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8C44;
    *(void **)((u8 *)object + 0x80) = D_800D0704;
    func_8008F01C(object, init_arg, D_800CFD00);
    func_8009B218(object, init_arg, state, D_800D06AC);
}
