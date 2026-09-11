#include "common.h"


typedef void (*Callback)(s32, void *, void *, void *);

typedef struct {
    u8 pad[0x3160];
    u8 *table[3];
} GlobalPage;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);

extern u8 *D_80083160[3];
extern GlobalPage D_80080000;
__asm__(".set D_80080000, 0x80080000");


typedef struct S_800D07C8_0 {
    u8 pad_00[0x8];
    union { s32 s32; u16 u16; } unk_08;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_0C;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_10;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    union { void * p; u8 * p2; } unk_20;   /* accessed as both */
    u16 unk_24;
    u8 pad_26[0xA];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x34];
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
    u8 pad_8E[0x32];
    s32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
    u8 pad_106[0x2];
    u16 unk_108;
    u16 unk_10A;
} S_800D07C8_0;   /* scratch in func_800D07C8 */

typedef struct S_800D07C8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D07C8_1;   /* arg1 in func_800D07C8 */

typedef struct S_800D07C8_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D07C8_2;   /* global_page->table[0] in func_800D07C8 */

typedef struct S_800D07C8_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_800D07C8_3;   /* arg2 in func_800D07C8 */

typedef struct S_800D07C8_4 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_800D07C8_4;   /* temp_s3 in func_800D07C8 */

typedef struct S_800D07C8_5_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800D07C8_5_pre;   /* the 0x4 bytes before temp_s0 in func_800D07C8, addressed as temp_s0[-1] */

typedef struct S_800D07C8_5 {
    u8 unk_00;
    u8 pad_01[0x10];
    u8 unk_11;
    u8 pad_12[0xC];
    u8 unk_1E;
    u8 pad_1F[0xA];
    u8 unk_29;
    u8 unk_2A;
} S_800D07C8_5;   /* temp_s0 in func_800D07C8 */

typedef struct S_800D07C8_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D07C8_6;   /* table[0] in func_800D07C8 */

/* Transform sprite parts into textured quads, queue visible quads, and invoke part callbacks. */
void func_800D07C8(s32 context, u8 *position, u8 *sprite, s16 depth_bias) {
    u8 matrix[32];
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet_code;
    u8 *part_uv;
    u8 *part;
    u8 *packet;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 vertex_x;
    s32 vertex_y;
    s32 first_three_visible;
    s32 first_pair_visible;
    s32 color;
    s32 u_end;
    s32 v_end;
    s32 vertex_2_visible;
    s32 vertex_0_visible;
    s32 vertex_1_visible;
    s32 vertex_3_visible;
    u32 depth;
    u16 sprite_flags;
    u8 part_command;
    u8 draw_command;
    register GlobalPage *global_page ASM_REG("$4") = &D_80080000;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Callback callback;

    ((S_800D07C8_0 *)scratch)->unk_20.p = global_page->table[0] + 0xB0;
    ((S_800D07C8_0 *)scratch)->unk_E4 = ((S_800D07C8_1 *)position)->unk_02;
    ((S_800D07C8_0 *)scratch)->unk_E8 = ((S_800D07C8_1 *)position)->unk_06;
    ((S_800D07C8_0 *)scratch)->unk_EC = ((S_800D07C8_1 *)position)->unk_0A;
    ((S_800D07C8_0 *)scratch)->unk_8C = 0;
    ((S_800D07C8_0 *)scratch)->unk_84 = 0;
    ((S_800D07C8_0 *)scratch)->unk_7C = 0;
    ((S_800D07C8_0 *)scratch)->unk_74 = 0;
    packet = ((S_800D07C8_2 *)(global_page->table[0]))->unk_8D0;
    ((S_800D07C8_3 *)sprite)->unk_14 |= 0x8000;
    func_800649A0();
    ((S_800D07C8_0 *)scratch)->unk_108 = ((S_800D07C8_3 *)sprite)->unk_20;
    ((S_800D07C8_0 *)scratch)->unk_10A = ((S_800D07C8_3 *)sprite)->unk_22;
    ((S_800D07C8_0 *)scratch)->unk_30 = ((S_800D07C8_3 *)sprite)->unk_1C * 2;
    ((S_800D07C8_0 *)scratch)->unk_34 = ((S_800D07C8_3 *)sprite)->unk_1E * 2;
    ((S_800D07C8_0 *)scratch)->unk_38 = 0;
    ((S_800D07C8_0 *)scratch)->unk_100 = ((S_800D07C8_3 *)sprite)->unk_16;
    ((S_800D07C8_0 *)scratch)->unk_104 = ((S_800D07C8_3 *)sprite)->unk_1A;
    ((S_800D07C8_0 *)scratch)->unk_102 = ((S_800D07C8_3 *)sprite)->unk_18;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    packet_code = packet + 7;
    func_80064AE0(matrix);
    func_80064840(matrix, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    part = ((S_800D07C8_3 *)sprite)->unk_08;
    part_uv = part + 8;
    ((S_800D07C8_0 *)scratch)->unk_24 = ((S_800D07C8_3 *)sprite)->unk_14;
    for (;;) {
        ASM_KEEP_NV(part_uv);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        if (!(((S_800D07C8_4 *)part)->unk_00.u & 0x20)) {
            ((S_800D07C8_0 *)scratch)->unk_08.s32 = (*(u8 *)((u8 *)part_uv + 0));
            ((S_800D07C8_0 *)scratch)->unk_0C.s32 = (*(u8 *)((u8 *)part_uv + 1));
            ((S_800D07C8_0 *)scratch)->unk_10.s32 = (*(u8 *)((u8 *)part_uv + 2));
            ((S_800D07C8_0 *)scratch)->unk_14.s32 = (*(u8 *)((u8 *)part_uv + 3));
            if ((((S_800D07C8_4 *)part)->unk_00.u ^ ((S_800D07C8_0 *)scratch)->unk_24) & 1) {
                vertex_x = (0 - (s8)(*(volatile u8 *)((u8 *)part_uv + -6))) - ((S_800D07C8_0 *)scratch)->unk_108;
                ((S_800D07C8_0 *)scratch)->unk_80 = vertex_x;
                ((S_800D07C8_0 *)scratch)->unk_70 = vertex_x;
                vertex_x -= ((S_800D07C8_0 *)scratch)->unk_10.u16;
            } else {
                vertex_x = (s8)(*(volatile u8 *)((u8 *)part_uv + -6)) - ((S_800D07C8_0 *)scratch)->unk_108;
                ((S_800D07C8_0 *)scratch)->unk_80 = vertex_x;
                ((S_800D07C8_0 *)scratch)->unk_70 = vertex_x;
                vertex_x = vertex_x + ((S_800D07C8_0 *)scratch)->unk_10.u16;
            }
            ((S_800D07C8_0 *)scratch)->unk_88 = vertex_x;
            ((S_800D07C8_0 *)scratch)->unk_78 = vertex_x;
            if ((((S_800D07C8_4 *)part)->unk_00.u ^ ((S_800D07C8_0 *)scratch)->unk_24) & 2) {
                vertex_y = (0 - (s8)(*(volatile u8 *)((u8 *)part_uv + -5))) - ((S_800D07C8_0 *)scratch)->unk_10A;
                ((S_800D07C8_0 *)scratch)->unk_7A = vertex_y;
                ((S_800D07C8_0 *)scratch)->unk_72 = vertex_y;
                vertex_y -= ((S_800D07C8_0 *)scratch)->unk_14.u16;
            } else {
                vertex_y = (s8)(*(volatile u8 *)((u8 *)part_uv + -5)) - ((S_800D07C8_0 *)scratch)->unk_10A;
                ((S_800D07C8_0 *)scratch)->unk_7A = vertex_y;
                ((S_800D07C8_0 *)scratch)->unk_72 = vertex_y;
                vertex_y = vertex_y + ((S_800D07C8_0 *)scratch)->unk_14.u16;
            }
            do {
                ((S_800D07C8_0 *)scratch)->unk_8A = vertex_y;
            } while (0);
            ((S_800D07C8_0 *)scratch)->unk_82 = vertex_y;

            depth = (func_80065590(scratch + 0x70, scratch + 0x78,
                                       scratch + 0x80, scratch + 0x88,
                                       packet + 8, packet + 0x14,
                                       packet + 0x20, packet + 0x2C,
                                       scratch + 0x90, scratch + 0x94) - depth_bias) - 6;
            ((S_800D07C8_0 *)scratch)->unk_C0 = depth;
            if (depth < 0x1E0U) {
                vertex_0_visible = 0;
                if ((u32)(((*(u16 *)((u8 *)packet_code + 1)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)((u8 *)packet_code + 3)) + 0x20) & 0xFFFF);
                    vertex_0_visible = screen_y < 0x121U;
                }
                vertex_1_visible = 0;
                if ((u32)(((*(u16 *)((u8 *)packet_code + 0xD)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)((u8 *)packet_code + 0xF)) + 0x20) & 0xFFFF);
                    vertex_1_visible = screen_y < 0x121U;
                }
                vertex_2_visible = 0;
                first_pair_visible = vertex_0_visible | vertex_1_visible;
                if ((u32)(((*(u16 *)((u8 *)packet_code + 0x19)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)((u8 *)packet_code + 0x1B)) + 0x20) & 0xFFFF);
                    vertex_2_visible = screen_y < 0x121U;
                }
                vertex_3_visible = 0;
                first_three_visible = first_pair_visible | vertex_2_visible;
                if ((u32)(((*(u16 *)((u8 *)packet_code + 0x25)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)((u8 *)packet_code + 0x27)) + 0x20) & 0xFFFF);
                    vertex_3_visible = screen_y < 0x121U;
                }
                if ((first_three_visible | vertex_3_visible) != 0) {
                    ((S_800D07C8_3 *)sprite)->unk_14 &= 0x7FFF;
                    u_end = ((S_800D07C8_0 *)scratch)->unk_10.s32 + ((S_800D07C8_0 *)scratch)->unk_08.s32;
                    ((S_800D07C8_0 *)scratch)->unk_10.s32 = u_end;
                    if (u_end & 0x100) {
                        ((S_800D07C8_0 *)scratch)->unk_10.s32 = u_end - 1;
                    }
                    v_end = ((S_800D07C8_0 *)scratch)->unk_14.s32 + ((S_800D07C8_0 *)scratch)->unk_0C.s32;
                    ((S_800D07C8_0 *)scratch)->unk_14.s32 = v_end;
                    if (v_end & 0x100) {
                        ((S_800D07C8_0 *)scratch)->unk_14.s32 = v_end - 1;
                    }
                    ((S_800D07C8_0 *)scratch)->unk_0C.s32 <<= 8;
                    ((S_800D07C8_0 *)scratch)->unk_14.s32 <<= 8;
                    if (((S_800D07C8_0 *)scratch)->unk_24 & 0x100) {
                        (*(s16 *)((u8 *)packet_code + 7)) = ((S_800D07C8_3 *)sprite)->unk_12;
                    } else {
                        (*(s16 *)((u8 *)packet_code + 7)) = ((S_800D07C8_3 *)sprite)->unk_12 + (*(u16 *)((u8 *)part_uv + -2));
                    }
                    (*(s16 *)((u8 *)packet_code + 5)) = ((S_800D07C8_0 *)scratch)->unk_0C.u16 + ((S_800D07C8_0 *)scratch)->unk_08.u16;
                    (*(s16 *)((u8 *)packet_code + 0x11)) = ((S_800D07C8_0 *)scratch)->unk_0C.u16 + ((S_800D07C8_0 *)scratch)->unk_10.u16;
                    {
                        s32 tpage_base = ((S_800D07C8_3 *)sprite)->unk_10;
                        s32 tpage;
                        if (tpage_base != 0) {
                            tpage = tpage_base + ((*(u16 *)((u8 *)part_uv + -4)) & 0xFF9F);
                        } else {
                            tpage = (*(u16 *)((u8 *)part_uv + -4));
                        }
                        (*(u16 *)((u8 *)packet_code + 0x13)) = tpage;
                    }
                    (*(s16 *)((u8 *)packet_code + 0x1D)) = ((S_800D07C8_0 *)scratch)->unk_14.u16 + ((S_800D07C8_0 *)scratch)->unk_08.u16;
                    (*(s16 *)((u8 *)packet_code + 0x29)) = ((S_800D07C8_0 *)scratch)->unk_14.u16 + ((S_800D07C8_0 *)scratch)->unk_10.u16;
                    if ((*(s16 *)((u8 *)packet_code + 1)) > (*(s16 *)((u8 *)packet_code + 0x25))) {
                        ((S_800D07C8_5 *)packet_code)->unk_11--;
                        ((S_800D07C8_5 *)packet_code)->unk_29--;
                    }
                    if ((*(s16 *)((u8 *)packet_code + 3)) > (*(s16 *)((u8 *)packet_code + 0x27))) {
                        ((S_800D07C8_5 *)packet_code)->unk_1E--;
                        ((S_800D07C8_5 *)packet_code)->unk_2A--;
                    }
                    color = ((S_800D07C8_3 *)sprite)->unk_0C;
                    (*(s32 *)((u8 *)packet_code + 0x21)) = 0;
                    (*(s32 *)((u8 *)packet_code + 0x15)) = 0;
                    ((S_800D07C8_5_pre *)packet_code)[-1].unk_00 = 0xC;
                    (*(s32 *)((u8 *)packet_code + 9)) = color;
                    (*(s32 *)((u8 *)packet_code + -3)) = color;
                    part_command = (*(u8 *)((u8 *)part_uv + -7));
                    ((S_800D07C8_5 *)packet_code)->unk_00 = part_command;
                    sprite_flags = ((S_800D07C8_0 *)scratch)->unk_24;
                    if (sprite_flags & 8) {
                        draw_command = sprite_flags & 4;
                        if (draw_command == 0) {
                            draw_command = part_command & 0xFD;
                        } else {
                            draw_command = part_command | 2;
                        }
                        ((S_800D07C8_5 *)packet_code)->unk_00 = draw_command;
                    }
                    {
                        u8 *draw_packet = packet;
                        do {
                            packet_code += 0x34;
                        } while (0);
                        packet += 0x34;
                        func_8006658C(((S_800D07C8_0 *)scratch)->unk_20.p2 + (((S_800D07C8_0 *)scratch)->unk_C0 * 4), draw_packet);
                    }
                    ASM_KEEP(packet_code);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                }
            }
        } else {
            callback = (*(Callback *)((u8 *)part_uv + 0));
            if (callback != 0) {
                callback(context, position, sprite, part);
            }
        }

        part_uv += 0xC;
        if (((S_800D07C8_4 *)part)->unk_00.s >= 0) {
            part += 0xC;
        } else {
            break;
        }
    }
    func_80064A40();
    {
        register u8 **table ASM_REG("$8") = D_80083160;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_800D07C8_6 *)(table[0]))->unk_8D0 = packet;
    }
}
