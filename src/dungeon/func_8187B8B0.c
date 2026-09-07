#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_80024DA0;
extern s32 D_80024FF0;

void func_8187B8B0(
    void *arg0,
    s16 arg1,
    s32 arg2,
    s16 arg3,
    s32 arg4,
    s32 arg5,
    s32 arg6)
{
    register s32 held_arg4 ASM_REG("$18") = arg4;   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *held_arg0 = arg0;
    register s16 held_arg1 ASM_REG("$22") = arg1;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 held_arg2 ASM_REG("$23") = arg2;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s16 held_arg3 ASM_REG("$20") = arg3;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 held_arg5 = arg5;
    s32 held_arg6 = arg6;
    void *temp_s0;
    void *actor;
    s32 random1;
    s32 random2;
    s32 random3;
    s32 offset1;
    s32 offset2;
    s32 offset3;
    s32 value1;
    s32 value2;
    s32 value3;
    register void *call_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_data;
    void *dest1;
    void *dest2;
    void *dest3;

    temp_s0 = func_8003FD64(0x211, held_arg0);
    if (temp_s0 != NULL) {
        FIELD(temp_s0, s32 *, 0x10) = (s32)&D_80024FF0;
        random1 = rand() & 0x1F;
        value1 = FIELD(FIELD(held_arg0, void **, 8), u16 *, 2);
        dest1 = FIELD(temp_s0, void **, 8);
        value1 += random1;
        offset1 = held_arg4 - 0x10;
        value1 += offset1;
        FIELD(dest1, s16 *, 2) = (s16)value1;

        random2 = rand() & 0x1F;
        value2 = FIELD(FIELD(held_arg0, void **, 8), u16 *, 6);
        dest2 = FIELD(temp_s0, void **, 8);
        value2 += random2;
        offset2 = held_arg5 - 0x10;
        value2 += offset2;
        FIELD(dest2, s16 *, 6) = (s16)value2;

        random3 = rand();
        call_obj = temp_s0;
        call_data = &D_80024DA0;
        ASM_USE2(call_obj, call_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        random3 &= 0x1F;
        value3 = FIELD(FIELD(held_arg0, void **, 8), u16 *, 0xA);
        actor = (u8 *)temp_s0 + 0x20;
        dest3 = FIELD(temp_s0, void **, 8);
        value3 += random3;
        offset3 = held_arg6 - 0x10;
        value3 += offset3;
        FIELD(dest3, s16 *, 0xA) = (s16)value3;
        ASM_KEEP(held_arg4);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(held_arg5);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(held_arg6);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        FIELD(actor, s16 *, 0x4) = held_arg1;
        ASM_KEEP(held_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        FIELD(actor, s16 *, 0x10) = held_arg3;
        FIELD(actor, s16 *, 0x12) = held_arg3;
        func_8004491C(call_obj, call_data, dest3);
        ASM_KEEP(held_arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
        FIELD(actor, s32 *, 0xB4) = rand() + 0x10000;
        FIELD(temp_s0, s32 *, 0x20) = held_arg2;
        ASM_KEEP(held_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
}

/* MECHANISM: The 0x38 frame and s2/s3/s5 stack-argument roles come from guarded held locals.
   Separate random/value/destination/offset names reproduce each v0/v1/a0 coordinate live range.
   Anchoring a0/a1 before splitting the third random mask fixes the final word-47 schedule seam. */
