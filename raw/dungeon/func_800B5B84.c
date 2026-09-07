#include "common.h"

typedef struct {
    s16 x;
    s16 y;
} CoordPair;

extern s32 func_8006658C();
extern s32 func_80067E2C();
extern s32 func_80067EF4();
extern s32 func_800B8FC8();

extern u8 D_80083160[];
extern u8 D_801C9E40[16];

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

void func_800BB2E4(s32 *arg0, s32 *arg1, u8 *arg2, s32 arg3, s32 arg4)
{
    CoordPair point;
    register u8 *arg2_r ASM_REG("$18") = arg2;
    register s32 arg3_r ASM_REG("$22") = arg3;
    register s32 arg4_r ASM_REG("$19") = arg4;
    register u8 **state_addr ASM_REG("$21");
    u8 *state;
    register u8 *base ASM_REG("$17");
    u8 *packet;
    register u8 *primitive ASM_REG("$16");
    u16 height;
    s32 shifted_height;
    register s32 y ASM_REG("$3");
    register s32 comparison ASM_REG("$2");
    register s32 shifted_arg ASM_REG("$6");
    register s32 shifted ASM_REG("$23");
    register s32 shift_test ASM_REG("$2");
    register s32 shift_test2 ASM_REG("$2");
    register u8 *call_base ASM_REG("$4");
    s32 primitive_flag;

    state_addr = (u8 **)D_80083160;
    state = *(u8 **)D_80083160;
    base = state + 0x8B0;
    comparison = (s32)state ^ (s32)D_801C9E40;
    shifted_arg = comparison != 0;
    shifted = shifted_arg;
    ASM_KEEP_NV(arg2_r);
    ASM_KEEP_NV(arg3_r);
    ASM_KEEP_DEP_NV(arg4_r, base);
    ASM_KEEP_NV(state_addr);
    ASM_KEEP_NV(base);

    if (arg4_r != 0) {
        primitive = FIELD(state, u8 *, 0x8D0);
        FIELD(state, u8 *, 0x8D0) = primitive + 0xC;
        func_80067EF4(primitive, 0, 0);
        func_8006658C(base, primitive);

        height = FIELD(arg2_r, u16, 4);
        shifted_height = height << 16;
        point.x = FIELD(arg2_r, u16, 0) +
            ((s32)((shifted_height >> 16) +
                ((u32)shifted_height >> 31)) >> 1);
        point.y = FIELD(arg2_r, u16, 2) + FIELD(arg2_r, u16, 6);
        func_800B8FC8(arg4_r, arg2_r, &point, 0, 0);
        state = *(u8 **)D_80083160;
        ASM_USE(state);
        primitive_flag = 1;
        goto allocate_primitive;
    }

    if ((arg3 << 16) == 0) {
        packet = FIELD(state, u8 *, 0x8D0);
        FIELD(state, u8 *, 0x8D0) = packet + 0x10;
        FIELD(packet, s32, 8) = *arg0;
        FIELD(packet, s32, 0xC) = *arg1;
        ASM_SCHED_BARRIER();
        shift_test = shifted_arg;
        ASM_KEEP_NV(shift_test);
        call_base = base;
        if (shift_test != 0) {
            FIELD(packet, u16, 0xA) -= 0xE0;
            FIELD(packet, u16, 0xE) -= 0xE0;
        }
        FIELD(packet, s8, 3) = 3;
        ASM_UNDEF(arg4_r);
        FIELD(packet, s32, 4) = 0;
        FIELD(packet, s8, 7) = 0x40;
        func_8006658C(call_base, packet, shifted_arg);

        state = *(u8 **)D_80083160;
        ASM_USE(state);
        primitive_flag = 0;
allocate_primitive:
        primitive = FIELD(state, u8 *, 0x8D0);
        FIELD(state, u8 *, 0x8D0) = primitive + 0xC;
        func_80067EF4(primitive, primitive_flag, 0);
        func_8006658C(base, primitive);
    } else {
        goto draw_packet;
    }

    ASM_SCHED_BARRIER();
    if ((arg3_r << 16) != 0) {
draw_packet:
        state = *state_addr;
        packet = FIELD(state, u8 *, 0x8D0);
        FIELD(state, u8 *, 0x8D0) = packet + 0x10;
        FIELD(packet, s32, 4) = 0x60000000;
        FIELD(packet, s8, 3) = 3;
        FIELD(packet, u16, 8) = FIELD(arg2_r, u16, 0);
        ASM_SCHED_BARRIER();
        shift_test2 = shifted;
        y = FIELD(arg2_r, s16, 2);
        ASM_USE2(shift_test2, y);
        if (shift_test2 != 0) {
            y -= 0xE0;
        }
        FIELD(packet, s16, 0xA) = y;
        FIELD(packet, u16, 0xC) = FIELD(arg2_r, u16, 4);
        FIELD(packet, u16, 0xE) = FIELD(arg2_r, u16, 6);
        func_8006658C(base, packet);

        state = *state_addr;
        primitive = FIELD(state, u8 *, 0x8D0);
        FIELD(state, u8 *, 0x8D0) = primitive + 0xC;
        func_80067EF4(primitive, 0, 1);
        func_8006658C(base, primitive);

        state = *state_addr;
        primitive = FIELD(state, u8 *, 0x8D0);
        FIELD(state, u8 *, 0x8D0) = primitive + 0xC;
        func_80067E2C(primitive, arg2_r);
        func_8006658C(base, primitive);
    }

    ASM_USE(arg3_r);
}
