#include "common.h"


typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[6];
    s16 fieldA;
} D_80083460_t;

extern void func_8008FD34();
extern void func_8008FD1C(void *, u8, s32);
#ifndef NON_MATCHING
extern void func_8008FD1C_state0(void *, u8, s32) __asm__("func_8008FD1C");
#endif
extern void func_8008FCE8(void) __attribute__((noreturn));
extern void func_80099F70(s32);
extern void func_80099F04(s32);
extern void func_80048A44(void *, u8, s16, s32);
extern s16 func_8009AF18(s16, void *, void *, s32);

extern s32 D_80081484[3];
extern s16 D_80083228[];
extern D_80083460_t D_80083460;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];
extern u8 D_800DCFB0[8];
extern u8 D_800DCFD0[8];
extern u8 D_800DD060[8];
extern u8 D_800DD0B8[8];
extern volatile u8 D_800DD0C8[8];
extern s32 D_800E3540[];


typedef struct S_8008FA7C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8008FA7C_0;   /* arg1 in func_8008FA7C */

typedef struct S_8008FA7C_1 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008FA7C_1;   /* state0_call_arg in func_8008FA7C */

typedef struct S_8008FA7C_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_8008FA7C_2;   /* arg3 in func_8008FA7C */

typedef struct S_8008FA7C_3 {
    u8 pad_00[0x8C];
    union { u8 * p; s32 * p2; } unk_8C;   /* accessed as both */
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0xA];
    u16 unk_A2;
    u8 pad_A4[0x80];
    union { u8 * p; u32 i; } unk_124;   /* accessed as both */
} S_8008FA7C_3;   /* arg0 in func_8008FA7C */

typedef struct S_8008FA7C_4 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8008FA7C_4;   /* object in func_8008FA7C */

typedef struct S_8008FA7C_5 {
    u8 pad_00[0x8A];
    s16 unk_8A;
} S_8008FA7C_5;   /* object2 in func_8008FA7C */

typedef struct S_8008FA7C_6 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x78];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x34BA];
    s32 unk_3540;
} S_8008FA7C_6;   /* (u8 *)state1_v1 in func_8008FA7C */

typedef struct S_8008FA7C_7 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008FA7C_7;   /* (u8 *)state1_a1 in func_8008FA7C */

typedef struct S_8008FA7C_8 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008FA7C_8;   /* call_arg in func_8008FA7C */

typedef struct S_8008FA7C_9 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008FA7C_9;   /* state2_call_arg in func_8008FA7C */

typedef struct S_8008FA7C_10 {
    u8 pad_00[0x84];
    u8 unk_84;
    u8 unk_85;
} S_8008FA7C_10;   /* ((S_8008FA7C_3 *)arg0)->unk_124.p in func_8008FA7C */

void func_8008FA7C(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    s16 countdown;
    s32 index;
    s16 state;
#ifndef NON_MATCHING
    register s32 saved ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
    s16 result;
    u8 *dead_v0;
    register u8 *state3_arg2 ASM_REG("$18");   /* MATCH pin: retail basic-block layout depends on it */
    u32 state1_a1;
    u32 state1_v1;
    register u8 *state0_call_arg ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
#else
    s32 saved;
    s16 result;
    u8 *state3_arg2;
    u8 *state0_call_arg;
#endif

    state = arg0[0x9B];
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        state0_call_arg = arg2;
        if (state == 0) {
            goto state_0;
        }
#ifndef NON_MATCHING
#endif
        func_8008FD34(state0_call_arg);
        return;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_8008FD34();
    return;

state_0:
        ((S_8008FA7C_0 *)arg1)->unk_14 = 0xFFEA0000;
        ((S_8008FA7C_1 *)state0_call_arg)->unk_2C = D_800DD0C8;
        {
#ifndef NON_MATCHING
            s32 state0_index;
            u8 state0_byte;

            state0_index = ((D_80083228[0] + ((S_8008FA7C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7;
            state0_index += (u32)D_800DD0C8;
            state0_byte = *(volatile u8 *)state0_index;
            func_8008FD1C_state0(state0_call_arg, state0_byte, 0);
#else
            u8 *lookup_v0;
            u8 lookup_byte;
            index = ((D_80083228[0] + ((S_8008FA7C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7;
            lookup_v0 = &D_800DD0C8[index];
            lookup_byte = *lookup_v0;
            func_8008FD1C(state0_call_arg, lookup_byte, 0);
#endif
        }
        return;

state_1:
        countdown = ((S_8008FA7C_3 *)arg0)->unk_96 - 1;
        ((S_8008FA7C_3 *)arg0)->unk_96 = countdown;
        if (countdown > 0) {
            return;
        }

        result = func_8009AF18(((S_8008FA7C_2 *)arg3)->unk_2A, arg1, arg2, 8);
#ifndef NON_MATCHING
#endif
        if (result == 0) {
            goto increment_state;
        }
        {
            u32 clear_mask;
            u32 set_mask;
            u32 object_flags;
            u8 *object;
            u8 *object2;
            u8 *call_arg;
            u8 *table_a1;
            u8 *lookup_v0;
#ifndef NON_MATCHING
            register s32 state1_angle ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
#else
            s32 state1_angle;
#endif
            s32 state1_index;
            s32 state1_byte;
            u32 masked_flags;

#ifndef NON_MATCHING
            state1_a1 = 0xFFEF0000;
            ASM_KEEP(state1_a1);   /* MATCH pin: retail delay-slot fill depends on it */
#else
            clear_mask = 0xFFEF0000;
#endif
            object = ((S_8008FA7C_3 *)arg0)->unk_124.p;
#ifndef NON_MATCHING
            ASM_KEEP(object);   /* MATCH pin: retail basic-block layout depends on it */
#endif
            set_mask = 0x200000;
#ifndef NON_MATCHING
            ASM_KEEP(set_mask);   /* MATCH pin: retail register colouring depends on it */
#endif
            object_flags = ((S_8008FA7C_4 *)object)->unk_1C;
#ifndef NON_MATCHING
            ASM_KEEP(object_flags);   /* MATCH pin: retail basic-block layout depends on it */
#endif
#ifndef NON_MATCHING
            state1_a1 |= 0xFFFF;
#else
            clear_mask |= 0xFFFF;
#endif
            object_flags |= set_mask;
            ((S_8008FA7C_4 *)object)->unk_1C = object_flags;
            object2 = ((S_8008FA7C_3 *)arg0)->unk_124.p;
#ifndef NON_MATCHING
            ASM_KEEP(object2);   /* MATCH pin: retail basic-block layout depends on it */
#endif
            call_arg = arg2;
#ifndef NON_MATCHING
            ASM_KEEP(call_arg);   /* MATCH pin: retail delay-slot fill depends on it */
#endif
            ((S_8008FA7C_5 *)object2)->unk_8A = result;
#ifndef NON_MATCHING
            state1_byte = 0x78;
            state1_v1 = ((S_8008FA7C_3 *)arg0)->unk_124.i;
            ASM_KEEP(state1_v1);   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_8008FA7C_6 *)((u8 *)state1_v1))->unk_84 = state1_byte;
            state1_v1 = ((S_8008FA7C_3 *)arg0)->unk_124.i;
            ((S_8008FA7C_6 *)((u8 *)state1_v1))->unk_85 = 2;
#else
            ((S_8008FA7C_10 *)(((S_8008FA7C_3 *)arg0)->unk_124.p))->unk_84 = 0x78;
            ((S_8008FA7C_10 *)(((S_8008FA7C_3 *)arg0)->unk_124.p))->unk_85 = 2;
#endif
#ifndef NON_MATCHING
            masked_flags = ((S_8008FA7C_2 *)arg3)->unk_1C;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            state1_v1 = 0x80080000;
            ASM_KEEP(state1_v1);   /* MATCH pin: retail delay-slot fill depends on it */
            masked_flags &= state1_a1;
            state1_a1 = 0x80080000;
            saved = ((S_8008FA7C_7 *)((u8 *)state1_a1))->unk_1484;
            state1_v1 += 0x3460;
            ((S_8008FA7C_7 *)((u8 *)state1_a1))->unk_1484 = 0;
            state1_a1 = 0x800E0000;
            ASM_KEEP(state1_a1);   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_8008FA7C_2 *)arg3)->unk_1C = masked_flags;
            countdown = ((S_8008FA7C_6 *)((u8 *)state1_v1))->unk_0A;
            state1_a1 -= 0x3030;
            countdown++;
            ((S_8008FA7C_6 *)((u8 *)state1_v1))->unk_0A = countdown;
            ((S_8008FA7C_8 *)call_arg)->unk_2C = (u8 *)state1_a1;
            state1_index = D_80083228[0];
            state1_angle = ((S_8008FA7C_2 *)arg3)->unk_2A;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            state1_v1 = 0x800E0000;
            ASM_KEEP(state1_v1);   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_8008FA7C_6 *)((u8 *)state1_v1))->unk_3540 = saved;
            state1_index += state1_angle;
            state1_index += 0x100;
            state1_index >>= 9;
            state1_index &= 7;
            state1_index += state1_a1;
            func_8008FD1C(call_arg, *(u8 *)state1_index, 5);
#else
            ((S_8008FA7C_2 *)arg3)->unk_1C &= clear_mask;
            saved = D_80081484[0];
            D_80081484[0] = 0;
            D_80083460.fieldA++;
            table_a1 = D_800DCFD0;
            ((S_8008FA7C_8 *)call_arg)->unk_2C = table_a1;
            D_800E3540[0] = saved;
            index = ((D_80083228[0] + ((S_8008FA7C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7;
            lookup_v0 = &table_a1[index];
#ifndef NON_MATCHING
#endif
            func_8008FD1C(call_arg, *lookup_v0, 5);
#endif
        }
        return;

state_2:
    {
        u8 *state2_call_arg;

        if (!(((S_8008FA7C_3 *)arg0)->unk_A2 & 0x10)) {
            return;
        }
        ((S_8008FA7C_0 *)arg1)->unk_14 = 0;
        state2_call_arg = arg2;
        if (((S_8008FA7C_2 *)arg3)->unk_1C & 0x100000) {
            goto increment_state;
        }
        ASM_KEEP(state2_call_arg);   /* MATCH pin: retail delay-slot fill depends on it */
        ((S_8008FA7C_9 *)state2_call_arg)->unk_2C = D_800DD060;
        {
#ifndef NON_MATCHING
            s32 state2_index;

            state2_index = ((D_80083228[0] + ((S_8008FA7C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7;
            state2_index += (u32)D_800DD060;
            func_8008FD1C(state2_call_arg, *(u8 *)state2_index, 0);
#else
            u8 *lookup_v0;
            index = ((D_80083228[0] + ((S_8008FA7C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7;
            lookup_v0 = &D_800DD060[index];
            func_8008FD1C(state2_call_arg, *lookup_v0, 0);
#endif
        }
        return;
    }

state_3:
        state3_arg2 = arg2;
        if (D_80083460.fieldA != 0) {
            return;
        }
        D_80083460.field2 |= 0x412;
        func_80099F70(((S_8008FA7C_2 *)arg3)->unk_5C);
        func_80099F04(((S_8008FA7C_2 *)arg3)->unk_5C);
        if (((S_8008FA7C_2 *)arg3)->unk_1C & 0x100000) {
#ifndef NON_MATCHING
            dead_v0 = (u8 *)0x80090000;
            ASM_KEEP(dead_v0);   /* MATCH pin: keeps a constant in a register as retail does */
            ((S_8008FA7C_3 *)arg0)->unk_8C.p = dead_v0 - 0x1538;
            dead_v0 = (u8 *)0x800E0000;
            ASM_KEEP(dead_v0);   /* MATCH pin: keeps a constant in a register as retail does */
            dead_v0 -= 0x2F48;
            ASM_TAILSLOT_PIN(dead_v0);   /* MATCH pin: retail delay-slot contents depend on it */
#else
            ((S_8008FA7C_3 *)arg0)->unk_8C.p = D_8008EAC8;
#endif
            func_8008FCE8();
            return;
        }
#ifndef NON_MATCHING
        dead_v0 = (u8 *)0x80090000;
#endif
        ((S_8008FA7C_3 *)arg0)->unk_8C.p2 = &D_8008ACDC;
        (*(u8 * *)((u8 *)state3_arg2 + (0x2C))) = D_800DCFB0;
#ifndef NON_MATCHING
        ASM_KEEP(state3_arg2);   /* MATCH pin: keeps a statement from moving across a call/branch */
#endif
        index = ((D_80083228[0] + ((S_8008FA7C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7;
        func_80048A44(state3_arg2, (*(u8 * volatile *)((u8 *)state3_arg2 + (0x2C)))[index], 0, 1);
        goto increment_state;

increment_state:
    arg0[0x9B]++;
}
