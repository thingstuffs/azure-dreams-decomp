#include "common.h"

typedef struct S_800C4030_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800C4030_0;   /* arg0 in func_800C4030 */

typedef struct S_800C4030_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C4030_1;   /* state in func_800C4030 */



extern s32 func_8004A658(s32, s32);
extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099368(s32, s32);
extern s32 func_80099734(void *, s32);
extern s32 func_800999B0(s32);
extern void func_8009BF7C(s32, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern s8 func_800A6DA4(s32, s32);
extern s32 func_800AD6FC(void *, s32, s32);

extern s32 D_80082E80;
extern s32 D_80083460;
extern s32 D_80083780;
extern u8 D_800893DC[];
extern u16 D_800DDE84[];
extern u8 D_800E187C[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];
extern void *D_800E3D7C;

/* Handles a target or active-slot update and decrements the shared count on completion. */
s32 func_800C4030(S_800C4030_0 *target, s32 action, s16 action_type, s32 action_param)
{
    s32 result;
    s32 slot_index;
    u8 *slot_data;
    u8 *slot_state;
    u8 *table_base;
    s32 first_arg;
    register s32 second_arg ASM_REG("$5");   /* MATCH pin: retail callee-saved_context set / frame layout depends on it */
    register s32 scratch_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 saved_context;

    if (action_type == 0xD) {
        return func_80098864(action, action_param);
    }

    if (target == D_800E3D7C) {
        target->unk_110 = action;
        func_8008D344(target, &D_80083780, &D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        result = func_800990FC();
        first_arg = action;
        second_arg = result;
        ASM_KEEP(second_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
        saved_context = second_arg;
        result = func_80099368(first_arg, second_arg);
        result = func_80099194(D_800E187C, result);
        result = func_80099734(target, result);
        result = func_80099194(D_800893DC, result);
        result = func_800999B0(result);
        func_80099290(result);
        func_800A5720(saved_context);

        first_arg = (s32)target;
        ASM_KEEP(first_arg);   /* MATCH pin: retail callee-saved_context set / frame layout depends on it */
        table_base = (u8 *)0x800E0000;
        ASM_KEEP(table_base);   /* MATCH pin: retail callee-saved_context set / frame layout depends on it */
        scratch_value = target->unk_13;
        table_base -= 0x217C;
        second_arg = ((u16 *)table_base)[scratch_value];
        ASM_KEEP(table_base);   /* MATCH pin: retail callee-saved_context set / frame layout depends on it */
        if (func_800AD6FC((void *)first_arg, second_arg & 3, action) == 0) {
            func_800A5F38(target, action);
            return 1;
        }
    } else {
        func_8009BF7C(1, 8);
        func_800A56E0(0x80F);
        slot_index = 0;
        scratch_value = 0x800E0000;
        ASM_KEEP(scratch_value);   /* MATCH pin: load-bearing for the whole function shape */
        slot_data = (u8 *)(scratch_value + 0x36C8);
        scratch_value = 0x800E0000;
        ASM_KEEP(scratch_value);   /* MATCH pin: load-bearing for the whole function shape */
        slot_state = (u8 *)(scratch_value + 0x3548);
        do {
            if (slot_state[1] != 0) {
                first_arg = 0xE;
                second_arg = 3;
                ASM_KEEP(first_arg);   /* MATCH pin: retail callee-saved_context set / frame layout depends on it */
                ASM_KEEP(second_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
                scratch_value = first_arg;
                slot_state[1] = scratch_value;
                scratch_value = second_arg;
                slot_state[0] = scratch_value;
                *(s32 *)(slot_data + 8) = func_8004A658(first_arg, second_arg);
                slot_state[2] = func_800A6DA4(0x10, 0x18);
                scratch_value = 1;
                slot_state[3] = scratch_value;
            }
            slot_data += 0xC;
            slot_index++;
            slot_state += 4;
        } while (slot_index < 0x40);
    }

    table_base = (u8 *)0x80080000;
    ASM_KEEP(table_base);   /* MATCH pin: retail callee-saved_context set / frame layout depends on it */
    table_base += 0x3460;
    result = ((S_800C4030_1 *)table_base)->unk_0A;
    first_arg = action;
    result--;
    ((S_800C4030_1 *)table_base)->unk_0A = result;
    func_80098B38(first_arg);
    return 1;
}

/* MECHANISM: Exact callee arities plus guarded short-lived a0/a1, v0, and saved-s0 roles
   recover the retail frame and call triangles without false long-lived constants.
   A pinned v1 D_80083460 base splits the shared tail halfword RMW across both CFG paths. */
