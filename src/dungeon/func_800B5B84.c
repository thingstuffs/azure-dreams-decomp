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


/* Queues a line or filled rectangle with optional content and drawing state commands. */
void func_800BB2E4(s32 *line_start, s32 *line_end, u8 *rect, s32 fill, s32 content_id)
{
    CoordPair bottom_center;
    register s32 fill_rect ASM_REG("$22") = fill;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 draw_id = content_id;
    register u8 **state_addr ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *state;
    u8 *ordering_table;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *packet;
    u8 *primitive;
    u16 width;
    s32 width_hi;
    s32 y;
    register s32 offset_y ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 rect_offset_y;
    register s32 line_offset_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 apply_offset_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *line_table;
    s32 primitive_flag;

    state_addr = (u8 **)D_80083160;
    state = *(u8 **)D_80083160;
    ordering_table = state + 0x8B0;
    width_hi = (s32)state ^ (s32)D_801C9E40;
    offset_y = width_hi != 0;
    rect_offset_y = offset_y;
    ASM_KEEP_NV(fill_rect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(state_addr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(ordering_table);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    if (draw_id != 0) {
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 0, 0);
        func_8006658C(ordering_table, primitive);

        width = ((S_800BB2E4_1 *)rect)->unk_04;
        width_hi = width << 16;
        bottom_center.x = ((S_800BB2E4_1 *)rect)->unk_00 +
            ((s32)((width_hi >> 16) +
                ((u32)width_hi >> 31)) >> 1);
        bottom_center.y = ((S_800BB2E4_1 *)rect)->unk_02.u + ((S_800BB2E4_1 *)rect)->unk_06;
        func_800B8FC8(draw_id, rect, &bottom_center, 0, 0);
        state = *(u8 **)D_80083160;
        primitive_flag = 1;
        goto allocate_primitive;
    }

    if ((fill << 16) == 0) {
        packet = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_08.at00.v = *line_start;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00.v = *line_end;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        line_offset_y = offset_y;
        ASM_KEEP_NV(line_offset_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        line_table = ordering_table;
        if (line_offset_y != 0) {
            ((S_800BB2E4_2 *)packet)->unk_08.at02.v -= 0xE0;
            ((S_800BB2E4_2 *)packet)->unk_0C.at02.v -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0;
        ((S_800BB2E4_2 *)packet)->unk_04.at03.v = 0x40;
        func_8006658C(line_table, packet, offset_y);

        state = *(u8 **)D_80083160;
        ASM_USE(state);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        primitive_flag = 0;
allocate_primitive:
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, primitive_flag, 0);
        func_8006658C(ordering_table, primitive);
    } else {
        goto draw_packet;
    }

    if ((fill_rect << 16) != 0) {
draw_packet:
        state = *state_addr;
        packet = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0x60000000;
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ((S_800BB2E4_2 *)packet)->unk_08.at00u.v = ((S_800BB2E4_1 *)rect)->unk_00;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        apply_offset_y = rect_offset_y;
        y = ((S_800BB2E4_1 *)rect)->unk_02.s;
        ASM_USE2(apply_offset_y, y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (apply_offset_y != 0) {
            y -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_08.at02u.v = y;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00u.v = ((S_800BB2E4_1 *)rect)->unk_04;
        ((S_800BB2E4_2 *)packet)->unk_0C.at02.v = ((S_800BB2E4_1 *)rect)->unk_06;
        func_8006658C(ordering_table, packet);

        state = *state_addr;
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 0, 1);
        func_8006658C(ordering_table, primitive);

        state = *state_addr;
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067E2C(primitive, rect);
        func_8006658C(ordering_table, primitive);
    }

    ASM_USE(fill_rect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
