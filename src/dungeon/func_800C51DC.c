#include "common.h"

typedef struct S_800CA93C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
} S_800CA93C_0;   /* obj in func_800CA93C */

typedef struct S_800CA93C_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CA93C_1_pre;   /* the 0x14 bytes before entry in func_800CA93C, addressed as entry[-1] */

typedef struct S_800CA93C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CA93C_2;   /* arg2_hold in func_800CA93C */

typedef struct S_800CA93C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CA93C_3;   /* other in func_800CA93C */



extern s32 func_8009B4B0(void *, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, void *);
extern void *func_800A3D18();
extern void func_800CA444(void *, s32, void *, void *);
extern void func_800CA788(void *, s32, void *, void *);

s32 func_800CA93C(void *arg0, s32 arg1, void *arg2) {
    register void *obj0 = arg0;
    s32 arg1_hold = arg1;
    S_800CA93C_2 *arg2_hold = arg2;
    void *obj;
    s32 mask;
    S_800CA93C_3 *other;
    register void *call_arg0 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 found;
    void *entry;

    call_arg0 = arg2_hold;
    obj = obj0;
    ((S_800CA93C_0 *)obj)->unk_14 |= 0x2000;
    ((S_800CA93C_0 *)obj)->unk_1C |= 0x2000;
    ((S_800CA93C_0 *)obj)->unk_60 = func_800A3D18(call_arg0, obj, 4);
    ASM_KEEP(obj);   /* MATCH pin: keeps a statement from moving across a call/branch */

    mask = -0x2001;
    ((S_800CA93C_0 *)obj)->unk_14 &= mask;
    entry = ((S_800CA93C_0 *)obj)->unk_60;
    ((S_800CA93C_0 *)obj)->unk_1C &= mask;
    if (entry != 0) {
        other = ((S_800CA93C_1_pre *)entry)[-1].unk_00;
        ((S_800CA93C_0 *)obj)->unk_14 |= 0x2000;
        ((S_800CA93C_0 *)obj)->unk_1C |= 0x2000;
        found = func_8009B4B0(
            obj,
            arg2_hold->unk_24,
            arg2_hold->unk_25);
        ((S_800CA93C_0 *)obj)->unk_14 &= mask;
        ((S_800CA93C_0 *)obj)->unk_1C &= mask;
        if (found == (s32)((S_800CA93C_0 *)obj)->unk_60) {
            ASM_KEEP(other);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            ASM_KEEP(mask);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            func_800CA788(obj, arg1_hold, arg2_hold, obj);
            return 0;
        }
        ((S_800CA93C_0 *)obj)->unk_2A = func_800A0818(
            arg2_hold->unk_24,
            arg2_hold->unk_25,
            other->unk_24,
            other->unk_25,
            (u8 *)obj + 0x98);
        ((S_800CA93C_0 *)obj)->unk_46 |= 0x8000;
    }

    ASM_KEEP(obj0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(arg1_hold);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg2_hold);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    func_800CA444(obj0, arg1_hold, arg2_hold, obj);
    return 0;
}

/* MECHANISM: the 0x38 frame holds natural s4 plus pinned s5/s2/s0/s1/s3 roles.
   Selective DEPIN of obj0 preserves natural s4 but makes the first call source s0;
   the post-call s0 keep splits later live ranges without disturbing call setup. */
