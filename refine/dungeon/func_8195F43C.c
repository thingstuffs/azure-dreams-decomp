#include "common.h"

typedef struct S_8195F43C_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x10];
    u32 unk_34;
    u8 pad_38[0x18];
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
    u8 pad_5A[0x16];
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
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
} S_8195F43C_0;   /* scratch in func_8195F43C */

typedef struct S_8195F43C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195F43C_1;   /* arg1 in func_8195F43C */

typedef struct S_8195F43C_2 {
    u16 unk_00;
    u16 unk_02;
} S_8195F43C_2;   /* table in func_8195F43C */

typedef struct S_8195F43C_3 {
    u16 unk_00;
    u16 unk_02;
} S_8195F43C_3;   /* table2 in func_8195F43C */

typedef struct S_8195F43C_4 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8195F43C_4;   /* base in func_8195F43C */

typedef struct S_8195F43C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8195F43C_5;   /* object in func_8195F43C */

typedef struct S_8195F43C_6 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u8 pad_06[0x2];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8195F43C_6;   /* texture in func_8195F43C */

typedef struct S_8195F43C_7 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 pad_15[0x3];
    u16 unk_18;
    u16 unk_1A;
    u8 pad_1C[0x1];
    u8 unk_1D;
    u8 pad_1E[0x2];
    union { u16 u; s16 s; } unk_20;   /* accessed as both */
    union { u16 u; s16 s; } unk_22;   /* accessed as both */
    u8 unk_24;
    u8 unk_25;
} S_8195F43C_7;   /* packet in func_8195F43C */

typedef struct S_8195F43C_8 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8195F43C_8;   /* *global in func_8195F43C */


#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))

extern void func_80024FEC(void) __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u8 D_8002745C[];
extern u8 D_80083160[];

/* Project a textured object quad onto the height grid and add it to the ordering table. */
void func_8195F43C(void *unused, void *origin, u8 *object, s16 tile_x, s16 tile_y)
{
    u8 **render_state = (u8 **)D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *height_grid = D_8002745C;
    u8 *render_ctx;
    u8 *packet;
    u8 *texture;
    u8 *height_row;
    u8 *next_height_row;
    u32 depth;
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    s32 visible_0;
    s32 visible_1;
    s32 visible_2;
    s32 visible_3;
    s32 visible_01;
    s32 visible_012;
    s32 edge_uv;
    u32 address_mask;
    u32 tag_mask;
    u16 page_offset;
    s32 scale_y;

    (void)unused;
    render_ctx = *render_state;
    ((S_8195F43C_0 *)scratch)->unk_20 = render_ctx + 0xB0;
    ((S_8195F43C_0 *)scratch)->unk_E4 = ((S_8195F43C_1 *)origin)->unk_02 + ((tile_x - 3) << 6);
    ((S_8195F43C_0 *)scratch)->unk_E8 = ((S_8195F43C_1 *)origin)->unk_06 + ((tile_y - 3) << 6);
    ((S_8195F43C_0 *)scratch)->unk_EC = ((S_8195F43C_1 *)origin)->unk_0A;

    height_row = (u8 *)((u32)(tile_y * 2) +
        (u32)(height_grid + tile_x * 0x10));
    height_grid += 0x10;
    next_height_row = (u8 *)((u32)(tile_y * 2) +
        (u32)(height_grid + tile_x * 0x10));
    {
        register u32 height ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

        height = ((S_8195F43C_2 *)height_row)->unk_00;
        ((S_8195F43C_0 *)scratch)->unk_74 = (s16)height / 2;
    }
    ((S_8195F43C_0 *)scratch)->unk_7C = (s16)((S_8195F43C_3 *)next_height_row)->unk_00 / 2;
    ((S_8195F43C_0 *)scratch)->unk_84 = (s16)((S_8195F43C_2 *)height_row)->unk_02 / 2;
    ((S_8195F43C_0 *)scratch)->unk_8C = (s16)((S_8195F43C_3 *)next_height_row)->unk_02 / 2;

    packet = ((S_8195F43C_4 *)render_ctx)->unk_8D0;
    func_800649A0();

    VFIELD(scratch, u32, 0x30) = ((S_8195F43C_5 *)object)->unk_1C * 2;
    scale_y = ((S_8195F43C_5 *)object)->unk_1E;
    VFIELD(scratch, u32, 0x38) = 0x2000;
    VFIELD(scratch, u16, 0x102) = 0;
    VFIELD(scratch, u16, 0x104) = 0;
    VFIELD(scratch, u16, 0x100) = 0;
    ((S_8195F43C_0 *)scratch)->unk_34 = scale_y * 2;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(scratch + 0x11C);
    func_80064840(scratch + 0x11C, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    texture = ((S_8195F43C_5 *)object)->unk_08;
    left = (s8)((S_8195F43C_6 *)texture)->unk_02;
    ((S_8195F43C_0 *)scratch)->unk_80 = left;
    ((S_8195F43C_0 *)scratch)->unk_70 = left;
    right = left + ((S_8195F43C_6 *)texture)->unk_0A;
    ((S_8195F43C_0 *)scratch)->unk_88 = right;
    ((S_8195F43C_0 *)scratch)->unk_78 = right;
    top = (s8)((S_8195F43C_6 *)texture)->unk_03;
    ((S_8195F43C_0 *)scratch)->unk_7A = top;
    ((S_8195F43C_0 *)scratch)->unk_72 = top;
    bottom = top + ((S_8195F43C_6 *)texture)->unk_0B;
    ((S_8195F43C_0 *)scratch)->unk_8A = bottom;
    ((S_8195F43C_0 *)scratch)->unk_82 = bottom;

    depth = func_80065590(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0x90, scratch + 0x94);
    ((S_8195F43C_0 *)scratch)->unk_C0 = depth;

    if (depth < 0x1E0U) {
        visible_0 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_08.u + 0x20) < 0x181U) {
            visible_0 = (u16)(((S_8195F43C_7 *)packet)->unk_0A.u + 0x20) < 0x121U;
        }
        visible_1 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_10 + 0x20) < 0x181U) {
            visible_1 = (u16)(((S_8195F43C_7 *)packet)->unk_12 + 0x20) < 0x121U;
        }
        visible_01 = visible_0 | visible_1;
        visible_2 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_18 + 0x20) < 0x181U) {
            visible_2 = (u16)(((S_8195F43C_7 *)packet)->unk_1A + 0x20) < 0x121U;
        }
        visible_012 = visible_01 | visible_2;
        visible_3 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_20.u + 0x20) < 0x181U) {
            visible_3 = (u16)(((S_8195F43C_7 *)packet)->unk_22.u + 0x20) < 0x121U;
        }

        if ((visible_012 | visible_3) != 0) {
            VFIELD(scratch, s32, 8) = ((S_8195F43C_6 *)texture)->unk_08;
            VFIELD(scratch, s32, 0x10) = ((S_8195F43C_6 *)texture)->unk_0A;
            VFIELD(scratch, s32, 0xC) = ((S_8195F43C_6 *)texture)->unk_09;
            VFIELD(scratch, s32, 0x14) = ((S_8195F43C_6 *)texture)->unk_0B;

            ((S_8195F43C_7 *)packet)->unk_0E = ((S_8195F43C_5 *)object)->unk_12 + (*(u16 *)((u8 *)texture + 6));
            page_offset = ((S_8195F43C_5 *)object)->unk_10;
            if (page_offset != 0) {
                u32 texture_page;
                texture_page = page_offset + (((S_8195F43C_6 *)texture)->unk_04 & 0xFF9F);
                ASM_TAILSLOT_PIN(texture_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_80024FEC();
                return;
            }
            (*(u16 *)((u8 *)packet + 0x16)) = ((S_8195F43C_6 *)texture)->unk_04;

            {
                s32 u;
                s32 width;

                u = VFIELD(scratch, s32, 8);
                width = VFIELD(scratch, s32, 0x10);
                if (u + width >= 0x100) {
                    VFIELD(scratch, s32, 0x10) = width - 1;
                }
            }
            {
                s32 v;
                s32 height;

                v = VFIELD(scratch, s32, 0xC);
                height = VFIELD(scratch, s32, 0x14);
                if (v + height >= 0x100) {
                    VFIELD(scratch, s32, 0x14) = height - 1;
                }
            }

            {
                s32 v_end;
                u16 uv_row;
                register u16 packed_u ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

                {
                    register s32 v ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

                    {
                        s32 width;
                        register s32 u ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                        width = VFIELD(scratch, s32, 0x10);
                        u = VFIELD(scratch, s32, 8);
                        v = VFIELD(scratch, s32, 0xC);
                        VFIELD(scratch, s32, 0x10) = width + u;
                    }
                    {
                        register s32 packed_v ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                        packed_v = v;
                        ASM_USE(packed_v);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        v_end = VFIELD(scratch, s32, 0x14);
                        packed_v <<= 8;
                        VFIELD(scratch, s32, 0xC) = packed_v;
                        uv_row = VFIELD(scratch, u16, 0xC);
                        v_end += v;
                    }
                }
                packed_u = VFIELD(scratch, u16, 8);
                VFIELD(scratch, s32, 0x14) = v_end;
                VFIELD(scratch, s32, 0x14) = v_end << 8;
                (*(u16 *)((u8 *)packet + 0xC)) = uv_row + packed_u;
            }
            (*(u16 *)((u8 *)packet + 0x14)) = VFIELD(scratch, u16, 0xC) + VFIELD(scratch, u16, 0x10);
            (*(u16 *)((u8 *)packet + 0x1C)) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 8);
            (*(u16 *)((u8 *)packet + 0x24)) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 0x10);

            if (((S_8195F43C_0 *)scratch)->unk_50 >= 0x1800) {
                edge_uv = ((S_8195F43C_7 *)packet)->unk_24;
                {
                    s32 edge_uv_prev;

                    edge_uv_prev = edge_uv + 0xFF;
                    ((S_8195F43C_7 *)packet)->unk_24 = edge_uv_prev;
                }
                ((S_8195F43C_7 *)packet)->unk_14 = edge_uv;
            }
            if (((S_8195F43C_0 *)scratch)->unk_58 >= 0x1800) {
                edge_uv = ((S_8195F43C_7 *)packet)->unk_25;
                {
                    s32 edge_uv_prev;

                    edge_uv_prev = edge_uv + 0xFF;
                    ((S_8195F43C_7 *)packet)->unk_25 = edge_uv_prev;
                }
                ((S_8195F43C_7 *)packet)->unk_1D = edge_uv;
            }
            if (((S_8195F43C_7 *)packet)->unk_08.s > ((S_8195F43C_7 *)packet)->unk_20.s) {
                ((S_8195F43C_7 *)packet)->unk_14--;
                ((S_8195F43C_7 *)packet)->unk_24--;
            }
            if (((S_8195F43C_7 *)packet)->unk_0A.s > ((S_8195F43C_7 *)packet)->unk_22.s) {
                ((S_8195F43C_7 *)packet)->unk_1D--;
                ((S_8195F43C_7 *)packet)->unk_25--;
            }

            ((S_8195F43C_7 *)packet)->unk_04.at00.v = ((S_8195F43C_5 *)object)->unk_0C;
            ((S_8195F43C_7 *)packet)->unk_00.at03.v = 9;
            ((S_8195F43C_7 *)packet)->unk_04.at03.v = 0x2C;
            if (((S_8195F43C_5 *)object)->unk_14 & 4) {
                ((S_8195F43C_7 *)packet)->unk_04.at03.v = 0x2E;
            }

            address_mask = 0x00FFFFFF;
            tag_mask = 0xFF000000;
            ((S_8195F43C_7 *)packet)->unk_00.at00.v = (((S_8195F43C_7 *)packet)->unk_00.at00.v & tag_mask) |
                ((*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20) + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) & address_mask);
            (*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20) + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) =
                ((*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20) + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) & tag_mask) |
                ((u32)packet & address_mask);
            packet += 0x28;
        }
    }

    func_80064A40();
    ((S_8195F43C_8 *)(*render_state))->unk_8D0 = packet;
}
