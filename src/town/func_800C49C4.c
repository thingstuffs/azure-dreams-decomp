#include "common.h"

typedef struct {
    void *callback;
    s16 x;
    s16 z;
    s16 range_x;
    s16 range_z;
    u8 pad_C[4];
    s16 effect_a;
    s16 effect_b;
    s16 check_id;
} TownObject;

typedef struct {
    s16 pad_0;
    s16 x;
    s16 pad_4;
    s16 z;
    s16 pad_8;
    s16 pad_A;
} TownPosition;

extern s32 func_80033B2C(s32, s32);
extern void func_800C15C0(s32, s32);
extern u8 D_80083780[8];
extern u8 D_800C21F8[];

s32 func_800C2124(TownObject *arg0) {
    TownPosition *position;
    register s32 scratch ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 dx ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 check_id;
    register void *callback ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s16 abs_x;
    register s16 abs_z ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */

    position = (TownPosition *)D_80083780;
    ASM_KEEP(position);   /* MATCH pin: retail immediate-load split depends on it */
    dx = arg0->x;
    scratch = position->x;
    check_id = arg0->check_id;
    position = (TownPosition *)(s32)position->z;
    dx -= scratch;
    scratch = arg0->z;
    abs_x = dx;
    if (dx < 0) {
        abs_x = -abs_x;
    }
    scratch -= (s32)position;
    abs_z = scratch;
    if (scratch < 0) {
        abs_z = -abs_z;
    }
    ASM_KEEP(check_id);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (func_80033B2C(check_id, dx) != 0) {
        if (arg0->range_x >= abs_x) {
            scratch = abs_z;
            if (arg0->range_z >= scratch) {
                func_800C15C0(arg0->effect_a, arg0->effect_b);
                scratch = 1;
                ASM_KEEP(scratch);   /* MATCH pin: retail basic-block layout depends on it */
                callback = D_800C21F8;
                arg0->callback = callback;
                return;
            }
        }
        return 0;
    }
    return 0;
}

/* MECHANISM: A pinned $v1 position base plus explicit $a1/$v0/$a0 load roles reproduces
   retail's interleaved five-load prologue body without load-delay nops.  Keeping the
   narrow $s1/$s2 distances live makes $v0 perform both sign extensions; the named
   second widening places its sll before the range load, and a short $v1 callback holds la. */
