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
void func_800BB2E4(s32 *line_start, s32 *line_end, u8 *rect, s16 fill, s32 content_id)
{
    CoordPair bottom_center;
    u8 **state_addr;
    u8 *state;
    u8 *buf;
    u8 *ordering_table;
    u8 *packet;
    u8 *primitive;
    s32 y;
    s16 odd;

    state_addr = (u8 **)D_80083160;
    state = *(u8 **)D_80083160;
    ordering_table = state + 0x8B0;
    odd = state != D_801C9E40;

    if (content_id != 0) {
        primitive = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 0, 0);
        func_8006658C(ordering_table, primitive);

        bottom_center.x = ((S_800BB2E4_1 *)rect)->unk_00 + (s16)((S_800BB2E4_1 *)rect)->unk_04 / 2;
        bottom_center.y = ((S_800BB2E4_1 *)rect)->unk_02.u + ((S_800BB2E4_1 *)rect)->unk_06;
        func_800B8FC8(content_id, rect, &bottom_center, 0, 0);
        buf = *(u8 **)D_80083160;
        primitive = ((S_800BB2E4_0 *)buf)->unk_8D0;
        ((S_800BB2E4_0 *)buf)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 1, 0);
        func_8006658C(ordering_table, primitive);
    } else if (fill == 0) {
        packet = ((S_800BB2E4_0 *)state)->unk_8D0;
        ((S_800BB2E4_0 *)state)->unk_8D0 = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_08.at00.v = *line_start;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00.v = *line_end;
        if (odd) {
            ((S_800BB2E4_2 *)packet)->unk_08.at02.v -= 0xE0;
            ((S_800BB2E4_2 *)packet)->unk_0C.at02.v -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0;
        ((S_800BB2E4_2 *)packet)->unk_04.at03.v = 0x40;
        func_8006658C(ordering_table, packet);

        buf = *(u8 **)D_80083160;
        primitive = ((S_800BB2E4_0 *)buf)->unk_8D0;
        ((S_800BB2E4_0 *)buf)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 0, 0);
        func_8006658C(ordering_table, primitive);
    }

    if (fill != 0) {
        buf = *state_addr;
        packet = ((S_800BB2E4_0 *)buf)->unk_8D0;
        ((S_800BB2E4_0 *)buf)->unk_8D0 = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0x60000000;
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ((S_800BB2E4_2 *)packet)->unk_08.at00u.v = ((S_800BB2E4_1 *)rect)->unk_00;
        y = ((S_800BB2E4_1 *)rect)->unk_02.s;
        if (odd) {
            y -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_08.at02u.v = y;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00u.v = ((S_800BB2E4_1 *)rect)->unk_04;
        ((S_800BB2E4_2 *)packet)->unk_0C.at02.v = ((S_800BB2E4_1 *)rect)->unk_06;
        func_8006658C(ordering_table, packet);

        buf = *state_addr;
        primitive = ((S_800BB2E4_0 *)buf)->unk_8D0;
        ((S_800BB2E4_0 *)buf)->unk_8D0 = primitive + 0xC;
        func_80067EF4(primitive, 0, 1);
        func_8006658C(ordering_table, primitive);

        buf = *state_addr;
        primitive = ((S_800BB2E4_0 *)buf)->unk_8D0;
        ((S_800BB2E4_0 *)buf)->unk_8D0 = primitive + 0xC;
        func_80067E2C(primitive, rect);
        func_8006658C(ordering_table, primitive);
    }
}
