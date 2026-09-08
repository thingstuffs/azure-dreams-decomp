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

/* Selects a target and updates the object's state before dispatching its action. */
s32 func_800CA93C(void *actor_arg, s32 action_arg, void *origin_arg) {
    register void *saved_actor = actor_arg;
    s32 action = action_arg;
    S_800CA93C_2 *origin = origin_arg;
    void *actor;
    s32 clear_flag_mask;
    S_800CA93C_3 *target;
    register void *lookup_origin ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 found_entry;
    void *target_entry;

    lookup_origin = origin;
    actor = saved_actor;
    ((S_800CA93C_0 *)actor)->unk_14 |= 0x2000;
    ((S_800CA93C_0 *)actor)->unk_1C |= 0x2000;
    ((S_800CA93C_0 *)actor)->unk_60 = func_800A3D18(lookup_origin, actor, 4);
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    clear_flag_mask = -0x2001;
    ((S_800CA93C_0 *)actor)->unk_14 &= clear_flag_mask;
    target_entry = ((S_800CA93C_0 *)actor)->unk_60;
    ((S_800CA93C_0 *)actor)->unk_1C &= clear_flag_mask;
    if (target_entry != 0) {
        target = ((S_800CA93C_1_pre *)target_entry)[-1].unk_00;
        ((S_800CA93C_0 *)actor)->unk_14 |= 0x2000;
        ((S_800CA93C_0 *)actor)->unk_1C |= 0x2000;
        found_entry = func_8009B4B0(
            actor,
            origin->unk_24,
            origin->unk_25);
        ((S_800CA93C_0 *)actor)->unk_14 &= clear_flag_mask;
        ((S_800CA93C_0 *)actor)->unk_1C &= clear_flag_mask;
        if (found_entry == (s32)((S_800CA93C_0 *)actor)->unk_60) {
            ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(clear_flag_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            func_800CA788(actor, action, origin, actor);
            return 0;
        }
        ((S_800CA93C_0 *)actor)->unk_2A = func_800A0818(
            origin->unk_24,
            origin->unk_25,
            target->unk_24,
            target->unk_25,
            (u8 *)actor + 0x98);
        ((S_800CA93C_0 *)actor)->unk_46 |= 0x8000;
    }

    ASM_KEEP(saved_actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(action);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(origin);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_800CA444(saved_actor, action, origin, actor);
    return 0;
}

/* MECHANISM: the 0x38 frame holds natural s4 plus pinned s5/s2/s0/s1/s3 roles.
   Selective DEPIN of saved_actor preserves natural s4 but makes the first call source s0;
   the post-call s0 keep splits later live ranges without disturbing call setup. */
