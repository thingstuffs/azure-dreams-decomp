#include "common.h"
#include "records/Rec_D_80083160.h"

typedef struct S_8009E798_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8009E798_0;   /* state in func_8009E798 */

typedef struct S_8009E798_1 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x8];
    u8 * unk_20;
    u16 unk_24;
    u8 pad_26[0x2];
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x2];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0xC];
    s32 unk_48;
    u8 pad_4C[0x24];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0xA];
    u16 unk_98;
    u16 unk_9A;
    u16 unk_9C;
    u8 pad_9E[0x46];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
} S_8009E798_1;   /* scratch in func_8009E798 */

typedef struct S_8009E798_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009E798_2;   /* arg1 in func_8009E798 */

typedef struct S_8009E798_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_14;   /* overlapping accesses */
    u16 unk_16;
    u8 pad_18[0x4];
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_1C;   /* overlapping accesses */
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    u8 pad_24[0x1];
    u8 unk_25;
} S_8009E798_3;   /* var_s2 in func_8009E798 */


typedef struct S_8009E798_5_pre {
    u32 unk_00;
    u8 pad_04[0x4];
    u32 unk_08;
    u8 pad_0C[0x4];
    u32 unk_10;
    u8 pad_14[0x4];
    u32 unk_18;
    u8 pad_1C[0x4];
} S_8009E798_5_pre;   /* the 0x20 bytes before var_s1 in func_8009E798, addressed as var_s1[-1] */

typedef struct S_8009E798_5 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    union { struct { s16 v; } at00; struct { u32 v; } at00u; struct { u8 v; } at00p; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; u8 v; } at02u; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { struct { u8 v; } at00; struct { u32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_08;   /* overlapping accesses */
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
} S_8009E798_5;   /* var_s1 in func_8009E798 */

typedef struct S_8009E798_6 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x12];
    u16 unk_22;
    u16 unk_24;
} S_8009E798_6;   /* packet in func_8009E798 */

typedef struct S_8009E798_7 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_8009E798_7;   /* var_s4 in func_8009E798 */

typedef struct S_8009E798_8 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8009E798_8;   /* ret_state in func_8009E798 */


#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))

extern void func_8003DB6C(void *, void *, s32);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065320(void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_800666E0(void *);
extern void func_800666F4(void *);
extern void func_80067E2C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, s32);

extern u8 D_80083160[];
extern u8 D_801C9E40[16];

/* Build and enqueue transformed sprite quads and restore the drawing area. */
s32 func_8009E798(void *draw_area, void *placement, void *sprite)
{
    register u8 *area_source ASM_REG("$20") = draw_area;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *sprite_or_copy ASM_REG("$18") = sprite;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 **state_ptr = (u8 **)D_80083160;
    u8 *state = *state_ptr;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet = ((S_8009E798_0 *)state)->unk_8D0;
    register u8 *frame_or_packet ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    register u8 *queued_packet ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 *active_state ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 lower_buffer = state != D_801C9E40;
    s16 vertex_y;
    s16 vertex_x;
    u16 rect[4];

    ((S_8009E798_1 *)scratch)->unk_20 = state + 0xB0;
    ((S_8009E798_1 *)scratch)->unk_38 = 0x1000;
    ((S_8009E798_1 *)scratch)->unk_48 = 0;

    func_80067E2C(packet, state);
    func_8006658C(((S_8009E798_1 *)scratch)->unk_20 + ((S_8009E798_2 *)placement)->unk_0A * 4,
                  packet);

    ((S_8009E798_1 *)scratch)->unk_30 = ((S_8009E798_3 *)sprite_or_copy)->unk_1C.at00.v;
    ((S_8009E798_1 *)scratch)->unk_34 = ((S_8009E798_3 *)sprite_or_copy)->unk_1E;
    ((S_8009E798_1 *)scratch)->unk_00.u = ((S_8009E798_2 *)placement)->unk_02;
    ((S_8009E798_1 *)scratch)->unk_02 = ((S_8009E798_2 *)placement)->unk_06;
    frame_or_packet = ((S_8009E798_3 *)sprite_or_copy)->unk_08;
    ((S_8009E798_1 *)scratch)->unk_24 = ((S_8009E798_3 *)sprite_or_copy)->unk_14.at00.v;
    func_800649A0();

    ((S_8009E798_1 *)scratch)->unk_98 = 0;
    ((S_8009E798_1 *)scratch)->unk_9A = 0;
    ((S_8009E798_1 *)scratch)->unk_9C = ((Rec_D_80083160 *)D_80083160)->unk_C8.as_u16;
    func_80065820(scratch + 0x98, scratch + 0xD0);
    func_80064BC0(scratch + 0xD0, scratch + 0x30);

    ((S_8009E798_1 *)scratch)->unk_EC = 0;
    ((S_8009E798_1 *)scratch)->unk_E4 = ((S_8009E798_1 *)scratch)->unk_00.s;
    ((S_8009E798_1 *)scratch)->unk_E8 = (s16)((S_8009E798_1 *)scratch)->unk_02;
    func_80064CF0(scratch + 0xD0);
    func_80064D80(scratch + 0xD0);

    ((S_8009E798_1 *)scratch)->unk_28 = 0x20 - ((S_8009E798_3 *)sprite_or_copy)->unk_20;
    ((S_8009E798_1 *)scratch)->unk_2A = 0x20 - ((S_8009E798_3 *)sprite_or_copy)->unk_22;
    ((S_8009E798_1 *)scratch)->unk_2C = 0;
    func_80065320(scratch + 0x28, scratch + 0x100, scratch + 0x94);

    packet += 0xC;
    ((S_8009E798_1 *)scratch)->unk_100 -= ((S_8009E798_1 *)scratch)->unk_00.u;
    ((S_8009E798_1 *)scratch)->unk_102 -= ((S_8009E798_1 *)scratch)->unk_02;

    ((S_8009E798_1 *)scratch)->unk_08 = ((S_8009E798_5 *)frame_or_packet)->unk_08.at00.v;
    ((S_8009E798_1 *)scratch)->unk_0C = ((S_8009E798_5 *)frame_or_packet)->unk_08.at01.v;
    ((S_8009E798_1 *)scratch)->unk_10 = ((S_8009E798_5 *)frame_or_packet)->unk_08.at02.v;
    ((S_8009E798_1 *)scratch)->unk_14 = ((S_8009E798_5 *)frame_or_packet)->unk_08.at03.v;

    vertex_x = (s8)((S_8009E798_5 *)frame_or_packet)->unk_02;
    ((S_8009E798_1 *)scratch)->unk_80 = vertex_x;
    ((S_8009E798_1 *)scratch)->unk_70 = vertex_x;
    vertex_x += VFIELD(scratch, u16, 0x10);
    ((S_8009E798_1 *)scratch)->unk_88 = vertex_x;
    ((S_8009E798_1 *)scratch)->unk_78 = vertex_x;

    vertex_y = (s8)((S_8009E798_5 *)frame_or_packet)->unk_03;
    ((S_8009E798_1 *)scratch)->unk_8C = 0;
    ((S_8009E798_1 *)scratch)->unk_84 = 0;
    ((S_8009E798_1 *)scratch)->unk_7C = 0;
    ((S_8009E798_1 *)scratch)->unk_74 = 0;
    ((S_8009E798_1 *)scratch)->unk_7A = vertex_y;
    ((S_8009E798_1 *)scratch)->unk_72 = vertex_y;
    vertex_y += VFIELD(scratch, u16, 0x14);
    ((S_8009E798_1 *)scratch)->unk_8A = vertex_y;
    ((S_8009E798_1 *)scratch)->unk_82 = vertex_y;

    func_80065320(scratch + 0x70, packet + 8, scratch + 0x94);
    func_80065320(scratch + 0x78, packet + 0x10, scratch + 0x94);
    func_80065320(scratch + 0x80, packet + 0x18, scratch + 0x94);
    func_80065320(scratch + 0x88, packet + 0x20, scratch + 0x94);

    (*(u16 *)((u8 *)packet + 8)) += VFIELD(scratch, u16, 0x100);
    (*(u16 *)((u8 *)packet + 0x10)) += VFIELD(scratch, u16, 0x100);
    (*(u16 *)((u8 *)packet + 0x18)) += VFIELD(scratch, u16, 0x100);
    (*(u16 *)((u8 *)packet + 0x20)) += VFIELD(scratch, u16, 0x100);
    (*(u16 *)((u8 *)packet + 0xA)) += VFIELD(scratch, u16, 0x102);
    (*(u16 *)((u8 *)packet + 0x12)) += VFIELD(scratch, u16, 0x102);
    (*(u16 *)((u8 *)packet + 0x1A)) += VFIELD(scratch, u16, 0x102);
    ((S_8009E798_6 *)packet)->unk_22 += VFIELD(scratch, u16, 0x102);

    ((S_8009E798_1 *)scratch)->unk_10 += ((S_8009E798_1 *)scratch)->unk_08;
    ((S_8009E798_1 *)scratch)->unk_14 =
        (((S_8009E798_1 *)scratch)->unk_14 + ((S_8009E798_1 *)scratch)->unk_0C) << 8;
    ((S_8009E798_1 *)scratch)->unk_0C <<= 8;

    ((S_8009E798_6 *)packet)->unk_0E = ((S_8009E798_3 *)sprite_or_copy)->unk_12 + ((S_8009E798_5 *)frame_or_packet)->unk_04.at02.v;
    ((S_8009E798_6 *)packet)->unk_0C = VFIELD(scratch, u16, 0xC) + VFIELD(scratch, u16, 8);
    (*(s32 *)((u8 *)packet + 0x14)) = VFIELD(scratch, s32, 0xC) +
        VFIELD(scratch, s32, 0x10) +
        ((((S_8009E798_3 *)sprite_or_copy)->unk_10 | ((S_8009E798_5 *)frame_or_packet)->unk_04.at00.v) << 16);
    (*(u16 *)((u8 *)packet + 0x1C)) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 8);
    ((S_8009E798_6 *)packet)->unk_24 = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 0x10);
    ((S_8009E798_6 *)packet)->unk_04.at00.v = ((S_8009E798_3 *)sprite_or_copy)->unk_0C.at00.v;
    func_800666F4(packet);

    sprite_or_copy = packet;
    sprite_or_copy += 0x28;
    func_8003DB6C(sprite_or_copy, packet, 0xA);
    frame_or_packet = sprite_or_copy + 0x28;
    ((S_8009E798_6 *)packet)->unk_04.at03.v |= 2;
    ((S_8009E798_3 *)sprite_or_copy)->unk_0C.at01.v = (((S_8009E798_3 *)sprite_or_copy)->unk_14.at01.v += 0x40);
    ((S_8009E798_3 *)sprite_or_copy)->unk_1C.at01.v = (((S_8009E798_3 *)sprite_or_copy)->unk_25 += 0x40);
    ((S_8009E798_3 *)sprite_or_copy)->unk_16 |= 0x100;

    func_8006658C(((S_8009E798_1 *)scratch)->unk_20 + ((S_8009E798_2 *)placement)->unk_0A * 4,
                  sprite_or_copy);
    func_8006658C(((S_8009E798_1 *)scratch)->unk_20 + ((S_8009E798_2 *)placement)->unk_0A * 4,
                  sprite_or_copy - 0x28);

    ((S_8009E798_5 *)frame_or_packet)->unk_04.at00u.v = 0x00606060;
    ((S_8009E798_5 *)frame_or_packet)->unk_08.at00u.v = ((S_8009E798_5_pre *)frame_or_packet)[-1].unk_00;
    ((S_8009E798_5 *)frame_or_packet)->unk_0C = ((S_8009E798_5_pre *)frame_or_packet)[-1].unk_08;
    ((S_8009E798_5 *)frame_or_packet)->unk_10 = ((S_8009E798_5_pre *)frame_or_packet)[-1].unk_10;
    ((S_8009E798_5 *)frame_or_packet)->unk_14 = ((S_8009E798_5_pre *)frame_or_packet)[-1].unk_18;
    ((S_8009E798_5 *)frame_or_packet)->unk_04.at00p.v >>= 1;
    ((S_8009E798_5 *)frame_or_packet)->unk_04.at01.v >>= 1;
    ((S_8009E798_5 *)frame_or_packet)->unk_04.at02u.v >>= 1;
    func_800666E0(frame_or_packet);
    ((S_8009E798_5 *)frame_or_packet)->unk_04.at03.v |= 2;

    queued_packet = frame_or_packet;
    frame_or_packet = sprite_or_copy + 0x40;
    func_8006658C(((S_8009E798_1 *)scratch)->unk_20 + ((S_8009E798_2 *)placement)->unk_0A * 4,
                  queued_packet);
    func_80067F20(frame_or_packet, 0, 0, 0x40, 0);
    func_8006658C(((S_8009E798_1 *)scratch)->unk_20 + ((S_8009E798_2 *)placement)->unk_0A * 4,
                  frame_or_packet);

    rect[0] = ((S_8009E798_7 *)area_source)->unk_04;
    rect[1] = ((S_8009E798_7 *)area_source)->unk_06;
    rect[2] = ((S_8009E798_7 *)area_source)->unk_08;
    rect[3] = ((S_8009E798_7 *)area_source)->unk_0A;
    frame_or_packet = sprite_or_copy + 0x4C;
    if (lower_buffer) {
        rect[1] += 0xE0;
    }

    func_80067E2C(frame_or_packet, rect);
    queued_packet = frame_or_packet;
    frame_or_packet = sprite_or_copy + 0x58;
    func_8006658C(((S_8009E798_1 *)scratch)->unk_20 + ((S_8009E798_2 *)placement)->unk_0A * 4,
                  queued_packet);
    ASM_KEEP(area_source);   /* MATCH pin: retail schedule: same instructions, different order without it */
    func_80064A40();
    active_state = *state_ptr;
    ((S_8009E798_8 *)active_state)->unk_8D0 = frame_or_packet;
    return 0;
}
