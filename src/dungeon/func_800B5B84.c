#include "common.h"

typedef struct S_800BB2E4_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BB2E4_0;   /* state in func_800BB2E4 */

typedef struct S_800BB2E4_1 {
    u16 unk_00;
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u16 unk_04;
    u16 unk_06;
} S_800BB2E4_1;   /* arg2_r in func_800BB2E4 */

typedef struct S_800BB2E4_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_0C;   /* overlapping accesses */
} S_800BB2E4_2;   /* packet in func_800BB2E4 */


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


void func_800BB2E4(s32 *arg0, s32 *arg1, u8 *arg2, s32 arg3, s32 arg4)
{
    CoordPair point;
    u8 *arg2_r = arg2;
    register s32 arg3_r ASM_REG("$22") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 arg4_r ASM_REG("$19") = arg4;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 **state_addr ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *state;
    register u8 *base ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *packet;
    u8 *primitive;
    u16 height;
    s32 shifted_height;
    s32 y;
    register s32 comparison ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 shifted_arg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 shifted;
    register s32 shift_test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 shift_test2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *call_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 primitive_flag;

    state_addr = (u8 **)D_80083160;
    state = *(u8 **)D_80083160;
    base = state + 0x8B0;
    comparison = (s32)state ^ (s32)D_801C9E40;
    shifted_arg = comparison != 0;
    shifted = shifted_arg;
    ASM_KEEP_NV(arg2_r);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg3_r);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(state_addr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    if (arg4_r != 0) {
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 0, 0);
        func_8006658C(base, primitive);

        height = ((S_800BB2E4_1 *)arg2_r)->unk_04;
        shifted_height = height << 16;
        point.x = ((S_800BB2E4_1 *)arg2_r)->unk_00 +
            ((s32)((shifted_height >> 16) +
                ((u32)shifted_height >> 31)) >> 1);
        point.y = ((S_800BB2E4_1 *)arg2_r)->unk_02.u + ((S_800BB2E4_1 *)arg2_r)->unk_06;
        func_800B8FC8(arg4_r, arg2_r, &point, 0, 0);
        state = *(u8 **)D_80083160;
        primitive_flag = 1;
        goto allocate_primitive;
    }

    if ((arg3 << 16) == 0) {
        packet = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_08.at00.v = *arg0;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00.v = *arg1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        shift_test = shifted_arg;
        ASM_KEEP_NV(shift_test);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        call_base = base;
        if (shift_test != 0) {
            ((S_800BB2E4_2 *)packet)->unk_08.at02.v -= 0xE0;
            ((S_800BB2E4_2 *)packet)->unk_0C.at02.v -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ASM_UNDEF(arg4_r);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0;
        ((S_800BB2E4_2 *)packet)->unk_04.at03.v = 0x40;
        func_8006658C(call_base, packet, shifted_arg);

        state = *(u8 **)D_80083160;
        ASM_USE(state);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        primitive_flag = 0;
allocate_primitive:
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, primitive_flag, 0);
        func_8006658C(base, primitive);
    } else {
        goto draw_packet;
    }

    if ((arg3_r << 16) != 0) {
draw_packet:
        state = *state_addr;
        packet = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0x60000000;
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ((S_800BB2E4_2 *)packet)->unk_08.at00u.v = ((S_800BB2E4_1 *)arg2_r)->unk_00;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        shift_test2 = shifted;
        y = ((S_800BB2E4_1 *)arg2_r)->unk_02.s;
        ASM_USE2(shift_test2, y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (shift_test2 != 0) {
            y -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_08.at02u.v = y;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00u.v = ((S_800BB2E4_1 *)arg2_r)->unk_04;
        ((S_800BB2E4_2 *)packet)->unk_0C.at02.v = ((S_800BB2E4_1 *)arg2_r)->unk_06;
        func_8006658C(base, packet);

        state = *state_addr;
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 0, 1);
        func_8006658C(base, primitive);

        state = *state_addr;
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067E2C(primitive, arg2_r);
        func_8006658C(base, primitive);
    }

    ASM_USE(arg3_r);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
