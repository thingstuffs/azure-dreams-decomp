#include "common.h"

typedef struct S_81988C1C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
    u8 pad_28[0x18];
    u8 unk_40;
    u8 pad_41[0x1];
    u8 unk_42;
    u8 pad_43[0x1];
    u8 unk_44;
    u8 pad_45[0x1];
    u8 unk_46;
    u8 pad_47[0x7];
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
} S_81988C1C_0;   /* item in func_81988C1C */

typedef struct S_81988C1C_1 {
    u16 unk_00;
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_81988C1C_1;   /* output in func_81988C1C */

typedef struct S_81988C1C_2 {
    union { void * s; u32 u; } unk_00;   /* accessed as both */
} S_81988C1C_2;   /* base in func_81988C1C */

typedef struct S_81988C1C_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_81988C1C_3;   /* pool in func_81988C1C */

typedef struct S_81988C1C_4 {
    u32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[0x4];
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x2];
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[0x4];
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
} S_81988C1C_4;   /* packet in func_81988C1C */

typedef struct S_81988C1C_5 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_81988C1C_5;   /* (u8 *)index in func_81988C1C */

typedef struct S_81988C1C_6_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_81988C1C_6_pre;   /* the 0x8 bytes before node in func_81988C1C, addressed as node[-1] */

typedef struct S_81988C1C_7 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_81988C1C_7;   /* (u8 *)(index + ((S_81988C1C_2 *)base)->unk_00.u) in func_81988C1C */


typedef struct {
    u8 pad[0x1FC];
    s32 unk1FC;
} S_800A1600_D80083160;

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) ASM_UNDEF(var)
#endif

extern S_800A1600_D80083160 D_80083160;
extern s32 func_80065420();
extern void func_80066640();
extern void func_800666F4();

/* Projects linked items into textured quads and adds them to the ordering table. */
s32 func_81988C1C(void *first_item) {
    u16 world_pos[4];
    u8 screen_points[8];
    s32 projection_scratch;
    void *node = first_item;
    S_800A1600_D80083160 *render_state = &D_80083160;
    void *screen_base = screen_points;
    register void *next_node ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    do {
        void *item = node;
        void *screen_point;
        s32 point_index;
        u32 depth_index;
        s32 half_width;
        u16 center_z;

        world_pos[0] = ((S_81988C1C_0 *)item)->unk_1E;
        world_pos[1] = ((S_81988C1C_0 *)item)->unk_22;
        center_z = ((S_81988C1C_0 *)item)->unk_26;
        world_pos[2] = center_z;
        world_pos[2] = center_z - ((s32)(((S_81988C1C_0 *)item)->unk_4E << 16) >> 17);

        point_index = 0;
        screen_point = screen_base;
        do {
            depth_index = func_80065420(world_pos, screen_point, &projection_scratch, &projection_scratch) - 8;
            screen_point = (u8 *)screen_point + 4;
            point_index++;
            world_pos[2] += ((S_81988C1C_0 *)item)->unk_4E;
        } while (point_index < 2);

        half_width = (((S_81988C1C_1 *)screen_points)->unk_02.s - ((S_81988C1C_1 *)screen_points)->unk_06.s) >> 1;
        if (depth_index < 0x1E0U) {
            void *packet_pool;
            void *packet;
            register u8 tex_v;
            u8 tex_u;
            register u8 tex_width ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u16 screen_coord;
            u32 ot_slot;
            u32 addr_mask;
            register u32 color_or_tag_mask ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            color_or_tag_mask = 0xA00000;
            packet_pool = ((S_81988C1C_2 *)render_state)->unk_00.s;
            packet = ((S_81988C1C_3 *)packet_pool)->unk_8D0;
            color_or_tag_mask |= 0xA0A0;
            ((S_81988C1C_3 *)packet_pool)->unk_8D0 = (u8 *)packet + 0x34;
            ((S_81988C1C_4 *)packet)->unk_04 = color_or_tag_mask;
            func_800666F4(packet, color_or_tag_mask);
            func_80066640(packet, 1);

            ((S_81988C1C_4 *)packet)->unk_16 = ((S_81988C1C_0 *)item)->unk_50;
            (*(u16 *)((u8 *)packet + 0x0E)) = ((S_81988C1C_0 *)item)->unk_52;
            screen_coord = ((S_81988C1C_1 *)screen_points)->unk_00 + half_width;
            (*(u16 *)((u8 *)packet + 0x10)) = screen_coord;
            (*(u16 *)((u8 *)packet + 0x08)) = screen_coord;
            screen_coord = *(volatile u16 *)&screen_points[0] - half_width;
            (*(u16 *)((u8 *)packet + 0x20)) = screen_coord;
            (*(u16 *)((u8 *)packet + 0x18)) = screen_coord;
            screen_coord = ((S_81988C1C_1 *)screen_points)->unk_02.u;
            ((S_81988C1C_4 *)packet)->unk_1A = screen_coord;
            ((S_81988C1C_4 *)packet)->unk_0A = screen_coord;
            screen_coord = ((S_81988C1C_1 *)screen_points)->unk_06.u;
            ((S_81988C1C_4 *)packet)->unk_22 = screen_coord;
            ((S_81988C1C_4 *)packet)->unk_12 = screen_coord;

            tex_u = ((S_81988C1C_0 *)item)->unk_40;
            addr_mask = 0xFFFFFF;
            ((S_81988C1C_4 *)packet)->unk_14 = tex_u;
            ((S_81988C1C_4 *)packet)->unk_0C = tex_u;
            tex_width = ((S_81988C1C_0 *)item)->unk_44;
            tex_u += tex_width;
            ((S_81988C1C_4 *)packet)->unk_24 = tex_u;
            ((S_81988C1C_4 *)packet)->unk_1C = tex_u;
            tex_v = ((S_81988C1C_0 *)item)->unk_42;
            ot_slot = depth_index << 2;
            ((S_81988C1C_4 *)packet)->unk_1D = tex_v;
            ((S_81988C1C_4 *)packet)->unk_0D = tex_v;
            tex_v += ((S_81988C1C_0 *)item)->unk_46;
            color_or_tag_mask = 0xFF000000;
            ((S_81988C1C_4 *)packet)->unk_25 = tex_v;
            ((S_81988C1C_4 *)packet)->unk_15 = tex_v;

            ((S_81988C1C_4 *)packet)->unk_00 =
                (((S_81988C1C_4 *)packet)->unk_00 & color_or_tag_mask) |
                (((S_81988C1C_7 *)((u8 *)(ot_slot + ((S_81988C1C_2 *)render_state)->unk_00.u)))->unk_B0 & addr_mask);
            ot_slot += (u32)((S_81988C1C_2 *)render_state)->unk_00.s;
            ((S_81988C1C_5 *)((u8 *)ot_slot))->unk_B0 =
                (((S_81988C1C_5 *)((u8 *)ot_slot))->unk_B0 & color_or_tag_mask) |
                ((u32)packet & addr_mask);
            ASM_KEEP(addr_mask);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        }

        next_node = ((S_81988C1C_6_pre *)node)[-1].unk_00;
        node = (u8 *)next_node + 0x20;
    } while (next_node != 0);

    {
        register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        register s32 return_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        READ_ZERO(zero);
        return_value = zero;
        return return_value;
    }
}
