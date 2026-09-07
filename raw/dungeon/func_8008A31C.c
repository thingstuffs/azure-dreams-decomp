#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

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

void func_8008FA7C(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    s16 countdown;
    s32 index;
    s16 state;
#ifndef NON_MATCHING
    register s32 saved ASM_REG("$8");
    register s16 result ASM_REG("$6");
    register u8 *dead_v0 ASM_REG("$2");
    register u8 *state3_arg2 ASM_REG("$18");
    register u32 state1_a1 ASM_REG("$5");
    register u32 state1_v1 ASM_REG("$3");
    register u8 *state0_call_arg ASM_REG("$4");
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
        ASM_KEEP_NV(state0_call_arg);
#endif
        func_8008FD34(state0_call_arg);
        return;
    }
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_8008FD34();
    return;

state_0:
        FIELD(arg1, s32, 0x14) = 0xFFEA0000;
        ASM_KEEP(state0_call_arg);
        FIELD(state0_call_arg, u8 *, 0x2C) = D_800DD0C8;
        {
#ifndef NON_MATCHING
            s32 state0_index;
            u8 state0_byte;

            state0_index = ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            state0_index += (u32)D_800DD0C8;
            state0_byte = *(volatile u8 *)state0_index;
            ASM_USE_NV(state0_byte);
            func_8008FD1C_state0(state0_call_arg, state0_byte, 0);
#else
            u8 *lookup_v0;
            u8 lookup_byte;
            index = ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            lookup_v0 = &D_800DD0C8[index];
            lookup_byte = *lookup_v0;
            func_8008FD1C(state0_call_arg, lookup_byte, 0);
#endif
        }
        return;

state_1:
        countdown = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = countdown;
        if (countdown > 0) {
            return;
        }

        result = func_8009AF18(FIELD(arg3, s16, 0x2A), arg1, arg2, 8);
#ifndef NON_MATCHING
        ASM_KEEP(result);
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
            register s32 state1_angle ASM_REG("$7");
#else
            s32 state1_angle;
#endif
            s32 state1_index;
            s32 state1_byte;
            u32 masked_flags;

#ifndef NON_MATCHING
            state1_a1 = 0xFFEF0000;
            ASM_KEEP(state1_a1);
#else
            clear_mask = 0xFFEF0000;
#endif
            object = FIELD(arg0, u8 *, 0x124);
#ifndef NON_MATCHING
            ASM_KEEP(object);
#endif
            set_mask = 0x200000;
#ifndef NON_MATCHING
            ASM_KEEP(set_mask);
#endif
            object_flags = FIELD(object, u32, 0x1C);
#ifndef NON_MATCHING
            ASM_KEEP(object_flags);
#endif
#ifndef NON_MATCHING
            state1_a1 |= 0xFFFF;
            ASM_KEEP(state1_a1);
#else
            clear_mask |= 0xFFFF;
#endif
            object_flags |= set_mask;
            FIELD(object, u32, 0x1C) = object_flags;
            object2 = FIELD(arg0, u8 *, 0x124);
#ifndef NON_MATCHING
            ASM_KEEP(object2);
#endif
            call_arg = arg2;
#ifndef NON_MATCHING
            ASM_KEEP(call_arg);
#endif
            FIELD(object2, s16, 0x8A) = result;
#ifndef NON_MATCHING
            state1_byte = 0x78;
            state1_v1 = FIELD(arg0, u32, 0x124);
            ASM_KEEP(state1_v1);
            FIELD((u8 *)state1_v1, u8, 0x84) = state1_byte;
            state1_v1 = FIELD(arg0, u32, 0x124);
            ASM_KEEP(state1_v1);
            FIELD((u8 *)state1_v1, u8, 0x85) = 2;
#else
            FIELD(FIELD(arg0, u8 *, 0x124), u8, 0x84) = 0x78;
            FIELD(FIELD(arg0, u8 *, 0x124), u8, 0x85) = 2;
#endif
#ifndef NON_MATCHING
            masked_flags = FIELD(arg3, u32, 0x1C);
            ASM_SCHED_BARRIER();
            state1_v1 = 0x80080000;
            ASM_KEEP(state1_v1);
            masked_flags &= state1_a1;
            state1_a1 = 0x80080000;
            ASM_KEEP(state1_a1);
            saved = FIELD((u8 *)state1_a1, s32, 0x1484);
            state1_v1 += 0x3460;
            FIELD((u8 *)state1_a1, s32, 0x1484) = 0;
            state1_a1 = 0x800E0000;
            ASM_KEEP(state1_a1);
            FIELD(arg3, u32, 0x1C) = masked_flags;
            countdown = FIELD((u8 *)state1_v1, s16, 0xA);
            state1_a1 -= 0x3030;
            countdown++;
            FIELD((u8 *)state1_v1, s16, 0xA) = countdown;
            FIELD(call_arg, u8 *, 0x2C) = (u8 *)state1_a1;
            state1_index = D_80083228[0];
            state1_angle = FIELD(arg3, s16, 0x2A);
            ASM_KEEP(state1_angle);
            ASM_SCHED_BARRIER();
            state1_v1 = 0x800E0000;
            ASM_KEEP(state1_v1);
            FIELD((u8 *)state1_v1, s32, 0x3540) = saved;
            state1_index += state1_angle;
            state1_index += 0x100;
            state1_index >>= 9;
            state1_index &= 7;
            state1_index += state1_a1;
            func_8008FD1C(call_arg, *(u8 *)state1_index, 5);
#else
            FIELD(arg3, u32, 0x1C) &= clear_mask;
            saved = D_80081484[0];
            D_80081484[0] = 0;
            D_80083460.fieldA++;
            table_a1 = D_800DCFD0;
            FIELD(call_arg, u8 *, 0x2C) = table_a1;
            D_800E3540[0] = saved;
            index = ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            lookup_v0 = &table_a1[index];
#ifndef NON_MATCHING
            ASM_KEEP(table_a1);
#endif
            func_8008FD1C(call_arg, *lookup_v0, 5);
#endif
        }
        return;

state_2:
    {
        register u8 *state2_call_arg ASM_REG("$4");

        if (!(FIELD(arg0, u16, 0xA2) & 0x10)) {
            return;
        }
        FIELD(arg1, s32, 0x14) = 0;
        state2_call_arg = arg2;
        if (FIELD(arg3, u32, 0x1C) & 0x100000) {
            goto increment_state;
        }
        ASM_KEEP(state2_call_arg);
        FIELD(state2_call_arg, u8 *, 0x2C) = D_800DD060;
        {
#ifndef NON_MATCHING
            s32 state2_index;

            state2_index = ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            state2_index += (u32)D_800DD060;
            func_8008FD1C(state2_call_arg, *(u8 *)state2_index, 0);
#else
            u8 *lookup_v0;
            index = ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
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
        func_80099F70(FIELD(arg3, s32, 0x5C));
        func_80099F04(FIELD(arg3, s32, 0x5C));
        if (FIELD(arg3, u32, 0x1C) & 0x100000) {
#ifndef NON_MATCHING
            dead_v0 = (u8 *)0x80090000;
            ASM_KEEP(dead_v0);
            FIELD(arg0, u8 *, 0x8C) = dead_v0 - 0x1538;
            dead_v0 = (u8 *)0x800E0000;
            ASM_KEEP(dead_v0);
            dead_v0 -= 0x2F48;
            ASM_TAILSLOT_PIN(dead_v0);
#else
            FIELD(arg0, u8 *, 0x8C) = D_8008EAC8;
#endif
            func_8008FCE8();
            return;
        }
#ifndef NON_MATCHING
        dead_v0 = (u8 *)0x80090000;
        ASM_KEEP(dead_v0);
#endif
        FIELD(arg0, s32 *, 0x8C) = &D_8008ACDC;
        FIELD(state3_arg2, u8 *, 0x2C) = D_800DCFB0;
#ifndef NON_MATCHING
        ASM_KEEP(state3_arg2);
#endif
        index = ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80048A44(state3_arg2, FIELD(state3_arg2, u8 * volatile, 0x2C)[index], 0, 1);
        goto increment_state;

increment_state:
    arg0[0x9B]++;
}
