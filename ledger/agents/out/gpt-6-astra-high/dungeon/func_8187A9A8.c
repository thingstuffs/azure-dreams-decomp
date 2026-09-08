#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {} EmptyArg;

extern void func_800242C8(void) __attribute__((noreturn));
extern void func_8002458C(void) __attribute__((noreturn));
extern void func_80024594(void) __attribute__((noreturn));
extern void func_800245E4(void) __attribute__((noreturn));
extern void func_80024854(void) __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, EmptyArg);
extern void func_80065820(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern u8 D_80083150[];
extern u8 D_80083160_quad[] __asm__("D_80083160");
extern u8 D_80083160_line[] __asm__("D_80083160");
extern u8 D_80083160_tpage[] __asm__("D_80083160");

/* Transform the mesh and enqueue textured quads or lines in the ordering table. */
void func_8187A9A8(void *mesh_data, void *transform, void *object_data, s32 depth_bias)
{
    register u8 *ot_base ASM_REG("$2");
    u8 *barrier_scratch;
    u8 *mesh = mesh_data;
    u8 *object = object_data;
    u8 *scratch = (u8 *)0x1F800000;
    register s32 raw_depth_bias ASM_REG("$16");
    u8 *texture;
    register u8 *texture_data ASM_REG("$19");
    register u32 addr_mask ASM_REG("$21");
    u32 tag_mask;
    s32 depth_offset;
    u16 object_flags;
    MATRIX matrix;

    ot_base = *(u8 **)(D_80083150 + 0x10);
    ASM_KEEP_MEMDEP(ot_base, barrier_scratch, *(u8 **)(D_80083150 + 0x10));
    ASM_KEEP(mesh);
    ASM_KEEP(object);
    FIELD(scratch, u8 *, 0x24) = ot_base + 0xB0;
    FIELD(scratch, s32, 0x88) = FIELD(transform, s16, 2);
    FIELD(scratch, s32, 0x8C) = FIELD(transform, s16, 6);
    raw_depth_bias = depth_bias;
    FIELD(scratch, s32, 0x90) = FIELD(transform, s16, 0xA);
    addr_mask = 0x00FFFFFF;
    object_flags = FIELD(object, u16, 0x14);
    object_flags |= 0x8000;
    tag_mask = 0xFF000000;
    ASM_USE_NV(tag_mask);
    FIELD(object, u16, 0x14) = object_flags;

    func_800649A0();

    FIELD(scratch, s32, 0x3C) = 0x2000;
    FIELD(scratch, s32, 0x38) = 0x2000;
    FIELD(scratch, s32, 0x34) = 0x2000;
    FIELD(scratch, u16, 0xA4) = FIELD(object, u16, 0x16);
    FIELD(scratch, u16, 0xA8) = FIELD(object, u16, 0x1A);
    FIELD(scratch, u16, 0xA6) = FIELD(object, u16, 0x18);
    func_80065820((u8 *)0x1F8000A4, (u8 *)0x1F800074);
    func_80064AE0(&matrix);
    func_80064840(&matrix, (u8 *)0x1F800074, (u8 *)0x1F800054);
    func_80064BC0((u8 *)0x1F800054, (u8 *)0x1F800034);
    func_80064D80((u8 *)0x1F800054);
    func_80064CF0((u8 *)0x1F800054);
    ASM_KEEP(scratch);

    depth_offset = (s16)raw_depth_bias;
    texture = FIELD(object, u8 *, 8);
    texture_data = texture + 1;
    FIELD(scratch, u16, 0x28) = FIELD(object, u16, 0x14);
    ASM_KEEP(texture);

    if (FIELD(mesh, u8, 0x4E) != 0) {
        u8 *packet;
        s32 ot_index;
        u16 render_flags;
        u8 texture_flags;
        s32 texture_adjust;
        u8 *render_state;
        register u8 **render_state_ref ASM_REG("$10");

        render_state_ref = (u8 **)D_80083160_quad;
        ASM_KEEP(render_state_ref);
        render_state = *render_state_ref;
        packet = FIELD(render_state, u8 *, 0x8D0);
        FIELD(render_state, u8 *, 0x8D0) = packet + 0x28;

        FIELD(scratch, s32, 0x0C) = texture_data[7];
        FIELD(scratch, s32, 0x10) = texture_data[8];
        FIELD(scratch, s32, 0x14) = texture_data[9];
        FIELD(scratch, s32, 0x18) = texture_data[0xA];

        FIELD(scratch, u16, 0xB0) = FIELD(mesh, u16, 0x58);
        FIELD(scratch, u16, 0xB8) = FIELD(mesh, u16, 0x5A);
        FIELD(scratch, u16, 0xC0) = FIELD(mesh, u16, 0x5C);
        FIELD(scratch, u16, 0xC8) = FIELD(mesh, u16, 0x5E);
        FIELD(scratch, u16, 0xB2) = FIELD(mesh, u16, 0x60);
        FIELD(scratch, u16, 0xBA) = FIELD(mesh, u16, 0x62);
        FIELD(scratch, u16, 0xC2) = FIELD(mesh, u16, 0x64);
        FIELD(scratch, u16, 0xCA) = FIELD(mesh, u16, 0x66);
        FIELD(scratch, u16, 0xB4) = FIELD(mesh, u16, 0x68);
        FIELD(scratch, u16, 0xBC) = FIELD(mesh, u16, 0x6A);
        FIELD(scratch, u16, 0xC4) = FIELD(mesh, u16, 0x6C);
        FIELD(scratch, u16, 0xCC) = FIELD(mesh, u16, 0x6E);

        ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                              scratch + 0xC0, scratch + 0xC8,
                              packet + 8, packet + 0x10,
                              packet + 0x18, packet + 0x20,
                              scratch + 0xD0, scratch + 0xD4,
                              ({ EmptyArg empty; empty; })) - depth_offset - 6;
        FIELD(scratch, s32, 0x100) = ot_index;

        if ((u32)ot_index < 0x1E0 &&
            ((((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121)) |
             (((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121)) |
             (((u16)(FIELD(packet, u16, 0x18) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0x1A) + 0x20) < 0x121)) |
             (((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121)))) {
            FIELD(packet, u8, 3) = 9;
            FIELD(packet, u8, 7) = 0x2C;
            FIELD(object, u16, 0x14) &= 0x7FFF;

            FIELD(scratch, s32, 0x14) += FIELD(scratch, s32, 0x0C);
            if (FIELD(scratch, s32, 0x14) & 0x100) {
                FIELD(scratch, s32, 0x14)--;
            }
            FIELD(scratch, s32, 0x18) += FIELD(scratch, s32, 0x10);
            if (FIELD(scratch, s32, 0x18) & 0x100) {
                FIELD(scratch, s32, 0x18)--;
            }
            FIELD(scratch, s32, 0x10) <<= 8;
            FIELD(scratch, s32, 0x18) <<= 8;

            texture_adjust = FIELD(object, u16, 0x12);
            if (texture_adjust != 0) {
                if (FIELD(scratch, u16, 0x28) & 0x100) {
                    FIELD(packet, u16, 0x0E) = texture_adjust;
                    func_80024594();
                }
                {
                    u32 palette_id;
                    palette_id = texture_adjust + FIELD(texture_data, u16, 5);
                    ASM_TAILSLOT_PIN(palette_id);
                    func_8002458C();
                }
            }
            FIELD(packet, u16, 0x0E) = FIELD(texture_data, u16, 5);

            FIELD(packet, u16, 0x0C) = FIELD(scratch, u16, 0x10) +
                                       FIELD(scratch, u16, 0x0C);
            FIELD(packet, u16, 0x14) = FIELD(scratch, u16, 0x10) +
                                       FIELD(scratch, u16, 0x14);

            texture_adjust = FIELD(object, u16, 0x10);
            if (texture_adjust != 0) {
                u32 texture_page;
                texture_page = texture_adjust +
                    (FIELD(texture_data, u16, 3) & 0xFF9F);
                ASM_TAILSLOT_PIN(texture_page);
                func_800245E4();
            }
            FIELD(packet, u16, 0x16) = FIELD(texture_data, u16, 3);

            FIELD(packet, u16, 0x1C) = FIELD(scratch, u16, 0x18) +
                                       FIELD(scratch, u16, 0x0C);
            FIELD(packet, u16, 0x24) = FIELD(scratch, u16, 0x18) +
                                       FIELD(scratch, u16, 0x14);

            if (FIELD(packet, s16, 8) > FIELD(packet, s16, 0x20)) {
                FIELD(packet, u8, 0x14)--;
                FIELD(packet, u8, 0x24)--;
            }
            if (FIELD(packet, s16, 0x0A) > FIELD(packet, s16, 0x22)) {
                FIELD(packet, u8, 0x1D)--;
                FIELD(packet, u8, 0x25)--;
            }

            texture_flags = texture_data[0];
            FIELD(object, u8, 0x0F) = texture_flags;
            render_flags = FIELD(scratch, u16, 0x28);
            if (render_flags & 8) {
                FIELD(object, u8, 0x0F) = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }
            ASM_KEEP(render_flags);

            FIELD(packet, u32, 4) = FIELD(object, u32, 0x0C);
            FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & tag_mask) |
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & addr_mask);
            FIELD(FIELD(scratch, u32 *, 0x24), u32,
                  FIELD(scratch, s32, 0x100) * 4) =
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & tag_mask) |
                ((u32)packet & addr_mask);
        }
    }

    if (FIELD(mesh, u8, 0x4E) == 0) {
        register u8 *packet ASM_REG("$16");
        s32 ot_index;
        s32 midpoint;
        s32 midpoint_z;
        s32 coord_a;
        s32 coord_b;
        s32 end_z_a;
        s32 end_z_b;
        u16 render_flags;
        u8 *vertex_a;
        u8 *vertex_b;
        u8 *vertex_c;
        u8 *vertex_d;
        u8 *screen_a;
        u8 *screen_b;
        u8 *fog_out;
        u8 *flags_out;
        register s32 tpage_zero ASM_REG("$4");
        register s32 blend_mode ASM_REG("$5");
        u32 *ot_entry;
        u32 color_code;
        s32 packet_code;
        register u8 *render_state ASM_REG("$3");
        register u8 **render_state_ref ASM_REG("$10");

        render_state_ref = (u8 **)D_80083160_line;
        ASM_KEEP(render_state_ref);
        render_state = *render_state_ref;
        packet = FIELD(render_state, u8 *, 0x8D0);
        FIELD(render_state, u8 *, 0x8D0) = packet + 0x10;

        coord_a = FIELD(mesh, s16, 0x58);
        coord_b = FIELD(mesh, s16, 0x5C);
        vertex_a = scratch + 0xB0;
        midpoint = (coord_a + coord_b) / 2;
        FIELD(scratch, s16, 0xC0) = midpoint;
        FIELD(scratch, s16, 0xB0) = midpoint;
        coord_a = FIELD(mesh, s16, 0x5A);
        coord_b = FIELD(mesh, s16, 0x5E);
        vertex_b = scratch + 0xB8;
        midpoint = (coord_a + coord_b) / 2;
        FIELD(scratch, s16, 0xC8) = midpoint;
        FIELD(scratch, s16, 0xB8) = midpoint;
        coord_a = FIELD(mesh, s16, 0x60);
        coord_b = FIELD(mesh, s16, 0x64);
        vertex_c = scratch + 0xC0;
        midpoint = (coord_a + coord_b) / 2;
        FIELD(scratch, s16, 0xC2) = midpoint;
        FIELD(scratch, s16, 0xB2) = midpoint;
        coord_a = FIELD(mesh, s16, 0x62);
        coord_b = FIELD(mesh, s16, 0x66);
        vertex_d = scratch + 0xC8;
        midpoint = (coord_a + coord_b) / 2;
        FIELD(scratch, s16, 0xCA) = midpoint;
        FIELD(scratch, s16, 0xBA) = midpoint;
        coord_a = FIELD(mesh, s16, 0x68);
        coord_b = FIELD(mesh, s16, 0x6C);
        screen_a = packet + 8;
        midpoint = (coord_a + coord_b) / 2;
        FIELD(scratch, s16, 0xC4) = midpoint;
        FIELD(scratch, s16, 0xB4) = midpoint;
        end_z_a = FIELD(mesh, s16, 0x6A);
        end_z_b = FIELD(mesh, s16, 0x6E);
        screen_b = packet + 0x0C;
        fog_out = scratch + 0xD0;
        flags_out = scratch + 0xD4;

        ot_index = func_80065590(vertex_a, vertex_b,
                              vertex_c, vertex_d,
                              screen_a, screen_b,
                              screen_a, screen_b,
                              fog_out, flags_out,
                              ({
                                  EmptyArg empty;
                                  midpoint_z = (end_z_a + end_z_b) / 2;
                                  FIELD(scratch, s16, 0xCC) = midpoint_z;
                                  FIELD(scratch, s16, 0xBC) = midpoint_z;
                                  empty;
                              })) - depth_offset - 6;
        FIELD(scratch, s32, 0x100) = ot_index;

        render_flags = FIELD(scratch, u16, 0x28);
        if (render_flags & 8) {
            if (render_flags & 4) {
                u32 draw_flags;
                draw_flags = FIELD(object, u8, 0x0F) | 2;
                ASM_TAILSLOT_PIN(draw_flags);
                func_80024854();
            }
            FIELD(object, u8, 0x0F) &= 0xFD;
        }

        tpage_zero = 0;
        color_code = FIELD(object, u32, 0x0C);
        FIELD(packet, u8, 3) = 3;
        ASM_SET(packet_code);
        packet_code = 0x42;
        blend_mode = 1;
        render_state_ref = (u8 **)D_80083160_tpage;
        ASM_KEEP(render_state_ref);
        FIELD(packet, u32, 4) = color_code;
        FIELD(packet, u8, 7) = packet_code;

        FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & tag_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & addr_mask);
        ot_entry = (u32 *)
            (((u32)FIELD(scratch, s32, 0x100) << 2) +
             (u32)FIELD(scratch, u32 *, 0x24));
        ASM_KEEP(ot_entry);
        {
            u32 ot_tag;
            register u32 packet_addr ASM_REG("$2");

            ot_tag = *ot_entry;
            packet_addr = (u32)packet & addr_mask;
            ot_tag &= tag_mask;
            ot_tag |= packet_addr;
            *ot_entry = ot_tag;
        }

        render_state = *render_state_ref;
        packet = FIELD(render_state, u8 *, 0x8D0);
        FIELD(render_state, u8 *, 0x8D0) = packet + 0x0C;
        func_80067F20(packet, 0, 0,
                     func_80066460(tpage_zero, blend_mode,
                                   tpage_zero, tpage_zero) & 0xFFFF, 0);

        FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & tag_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & addr_mask);
        FIELD(FIELD(scratch, u32 *, 0x24), u32,
              FIELD(scratch, s32, 0x100) * 4) =
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & tag_mask) |
            ((u32)packet & addr_mask);
    }

    if ((s8)*texture >= 0) {
        texture_data += 0x0C;
        ASM_KEEP(texture_data);
        texture += 0x0C;
        ASM_TAILSLOT_PIN(texture);
        func_800242C8();
    }
    func_80064A40();
}
