#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {
} EMPTY_ARG;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590();
extern void func_80065820(void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_80174808(void) __attribute__((noreturn));
extern u8 D_80083160[];

void func_80174618(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    register u8 *packet ASM_REG("$20");
    register u8 *scratch ASM_REG("$19") = (u8 *)0x1F800000;
    u8 *packet2;
    u8 *context;
    register u8 *global_page ASM_REG("$18");
    u8 *packet8;
    u8 *packetC;
    register u8 *call_arg0 ASM_REG("$4");
    register u8 *arg9 ASM_REG("$10");
    register u8 *arg10 ASM_REG("$9");
    u16 flags;
    u16 value;
    register s32 packet_payload ASM_REG("$3");
    register u16 final_value ASM_REG("$8");
    s32 index;
    MATRIX matrix;
    EMPTY_ARG no_arg;

    FIELD(scratch, u8 *, 0x24) = *(u8 **)D_80083160 + 0xB0;
    FIELD(scratch, s32, 0x88) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0x8C) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0x90) = FIELD(arg1, s16, 0xA);
    FIELD(arg2, u16, 0x14) |= 0x8000;

    func_800649A0();

    FIELD(scratch, s32, 0x3C) = 0x2000;
    FIELD(scratch, s32, 0x38) = 0x2000;
    FIELD(scratch, s32, 0x34) = 0x2000;
    FIELD(scratch, u16, 0xA4) = FIELD(arg2, u16, 0x16);
    FIELD(scratch, u16, 0xA8) = FIELD(arg2, u16, 0x1A);
    FIELD(scratch, u16, 0xA6) = FIELD(arg2, u16, 0x18);
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    arg9 = scratch + 0xD0;
    arg10 = scratch + 0xD4;
    call_arg0 = scratch + 0xB0;
    ASM_KEEP(call_arg0);

    value = FIELD(arg2, u16, 0x14);
    context = *(u8 **)D_80083160;
    FIELD(scratch, u16, 0x28) = value;
    packet = FIELD(context, u8 *, 0x8D0);
    FIELD(context, u8 *, 0x8D0) = packet + 0x10;

    value = FIELD(arg0, u16, 0x64);
    FIELD(scratch, u16, 0xC0) = value;
    FIELD(scratch, u16, 0xB0) = value;
    value = FIELD(arg0, u16, 0x6A);
    FIELD(scratch, u16, 0xC8) = value;
    FIELD(scratch, u16, 0xB8) = value;
    value = FIELD(arg0, u16, 0x66);
    FIELD(scratch, u16, 0xC2) = value;
    FIELD(scratch, u16, 0xB2) = value;
    value = FIELD(arg0, u16, 0x6C);
    FIELD(scratch, u16, 0xCA) = value;
    FIELD(scratch, u16, 0xBA) = value;
    value = FIELD(arg0, u16, 0x68);
    FIELD(scratch, u16, 0xC4) = value;
    FIELD(scratch, u16, 0xB4) = value;
    final_value = FIELD(arg0, u16, 0x6E);
    packet8 = packet + 8;
    packetC = packet + 0xC;
    index = func_80065590(call_arg0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet8, packetC,
                          packet8, packetC,
                          arg9, arg10,
                          (FIELD(scratch, u16, 0xCC) = final_value,
                           FIELD(scratch, u16, 0xBC) = final_value,
                           no_arg));
    index = index - arg3 - 6;
    ASM_SCHED_BARRIER();
    FIELD(scratch, s32, 0x100) = index;
    flags = FIELD(scratch, u16, 0x28);
    global_page = D_80083160 - 0x3160;
    ASM_SET(global_page);
    packet2 = global_page + 0x3160;

    if (flags & 8) {
        if (flags & 4) {
            u8 tail_value;
            tail_value = *(volatile u8 *)((u8 *)arg2 + 0xF) | 2;
            ASM_TAILSLOT_PIN_TIED(tail_value);
            func_80174808();
            return;
        }
        FIELD(arg2, u8, 0xF) &= 0xFD;
    }

    packet_payload = FIELD(arg2, s32, 0xC);
    FIELD(packet, s8, 3) = 3;
    FIELD(packet, s32, 4) = packet_payload;
    FIELD(packet, s8, 7) = 0x40;
    flags = FIELD(scratch, u16, 0x28);
    if (flags & 8) {
        s32 packet_type = flags & 4;
        if (packet_type) {
            packet_type = 0x42;
        } else {
            packet_type = 0x40;
        }
        FIELD(packet, s8, 7) = packet_type;
    }

    {
    register u32 low_mask ASM_REG("$17");
    register s32 zero ASM_REG("$4");
    register u32 high_mask ASM_REG("$18");
    low_mask = 0x00FFFFFF;
    zero = 0;
    ASM_KEEP(zero);
    high_mask = 0xFF000000;
    FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & high_mask) |
                            (FIELD(scratch, u32 *, 0x24)[FIELD(scratch, s32, 0x100)] & low_mask);
    FIELD(scratch, u32 *, 0x24)[FIELD(scratch, s32, 0x100)] =
        (FIELD(scratch, u32 *, 0x24)[FIELD(scratch, s32, 0x100)] & high_mask) |
        ((u32)packet & low_mask);

    context = *(u8 **)packet2;
    packet2 = FIELD(context, u8 *, 0x8D0);
    FIELD(context, u8 *, 0x8D0) = packet2 + 0xC;
    func_80067F20(packet2, 0, 0, (u16)func_80066460(zero, 1, zero, zero), 0);

    FIELD(packet2, u32, 0) = (FIELD(packet2, u32, 0) & high_mask) |
                             (FIELD(scratch, u32 *, 0x24)[FIELD(scratch, s32, 0x100)] & low_mask);
    packet2 = (u8 *)((u32)packet2 & low_mask);
    FIELD(scratch, u32 *, 0x24)[FIELD(scratch, s32, 0x100)] =
        (FIELD(scratch, u32 *, 0x24)[FIELD(scratch, s32, 0x100)] & high_mask) |
        (u32)packet2;

    func_80064A40();
    ASM_KEEP(packet);
    ASM_KEEP(scratch);
    }
}
