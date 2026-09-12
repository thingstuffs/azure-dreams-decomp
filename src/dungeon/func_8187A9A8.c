#include "common.h"

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {} EmptyArg;

typedef struct S_func_8187A9A8_1 {
    u8 pad_00[0xC];
    union {
        s32 as_s32_0C;
        u16 as_u16_0C;
    } unk_0C;
    union {
        s32 as_s32_10;
        u16 as_u16_10;
    } unk_10;
    union {
        s32 as_s32_14;
        u16 as_u16_14;
    } unk_14;
    union {
        s32 as_s32_18;
        u16 as_u16_18;
    } unk_18;
    u8 pad_1C[0x8];
    void * unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    union {
        s16 as_s16_B0;
        u16 as_u16_B0;
    } unk_B0;
    union {
        s16 as_s16_B2;
        u16 as_u16_B2;
    } unk_B2;
    union {
        s16 as_s16_B4;
        u16 as_u16_B4;
    } unk_B4;
    u8 pad_B6[0x2];
    union {
        s16 as_s16_B8;
        u16 as_u16_B8;
    } unk_B8;
    union {
        s16 as_s16_BA;
        u16 as_u16_BA;
    } unk_BA;
    union {
        s16 as_s16_BC;
        u16 as_u16_BC;
    } unk_BC;
    u8 pad_BE[0x2];
    union {
        s16 as_s16_C0;
        u16 as_u16_C0;
    } unk_C0;
    union {
        s16 as_s16_C2;
        u16 as_u16_C2;
    } unk_C2;
    union {
        s16 as_s16_C4;
        u16 as_u16_C4;
    } unk_C4;
    u8 pad_C6[0x2];
    union {
        s16 as_s16_C8;
        u16 as_u16_C8;
    } unk_C8;
    union {
        s16 as_s16_CA;
        u16 as_u16_CA;
    } unk_CA;
    union {
        s16 as_s16_CC;
        u16 as_u16_CC;
    } unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_func_8187A9A8_1;

typedef struct S_func_8187A9A8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_8187A9A8_2;

typedef struct S_func_8187A9A8_3 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        u32 as_u32_0C;
        struct {
            u8 pad_0C[0x3];
            u8 unk_0F;
        } as_u8_0F;
    } unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_func_8187A9A8_3;

typedef struct S_func_8187A9A8_4 {
    u8 pad_00[0x4E];
    u8 unk_4E;
    u8 pad_4F[0x9];
    union {
        s16 as_s16_58;
        u16 as_u16_58;
    } unk_58;
    union {
        s16 as_s16_5A;
        u16 as_u16_5A;
    } unk_5A;
    union {
        s16 as_s16_5C;
        u16 as_u16_5C;
    } unk_5C;
    union {
        s16 as_s16_5E;
        u16 as_u16_5E;
    } unk_5E;
    union {
        s16 as_s16_60;
        u16 as_u16_60;
    } unk_60;
    union {
        s16 as_s16_62;
        u16 as_u16_62;
    } unk_62;
    union {
        s16 as_s16_64;
        u16 as_u16_64;
    } unk_64;
    union {
        s16 as_s16_66;
        u16 as_u16_66;
    } unk_66;
    union {
        s16 as_s16_68;
        u16 as_u16_68;
    } unk_68;
    union {
        s16 as_s16_6A;
        u16 as_u16_6A;
    } unk_6A;
    union {
        s16 as_s16_6C;
        u16 as_u16_6C;
    } unk_6C;
    union {
        s16 as_s16_6E;
        u16 as_u16_6E;
    } unk_6E;
} S_func_8187A9A8_4;

typedef struct S_func_8187A9A8_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_func_8187A9A8_5;

typedef struct S_func_8187A9A8_6 {
    union {
        u32 as_u32_00;
        struct {
            u8 pad_00[0x3];
            u8 unk_03;
        } as_u8_03;
    } unk_00;
    union {
        u32 as_u32_04;
        struct {
            u8 pad_04[0x3];
            u8 unk_07;
        } as_u8_07;
    } unk_04;
    union {
        s16 as_s16_08;
        u16 as_u16_08;
    } unk_08;
    union {
        s16 as_s16_0A;
        u16 as_u16_0A;
    } unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union {
        u16 as_u16_14;
        u8 as_u8_14;
    } unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    union {
        u16 as_u16_1C;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } as_u8_1D;
    } unk_1C;
    u8 pad_1E[0x2];
    union {
        s16 as_s16_20;
        u16 as_u16_20;
    } unk_20;
    union {
        s16 as_s16_22;
        u16 as_u16_22;
    } unk_22;
    union {
        u16 as_u16_24;
        u8 as_u8_24;
        struct {
            u8 pad_24[0x1];
            u8 unk_25;
        } as_u8_25;
    } unk_24;
} S_func_8187A9A8_6;

typedef struct S_func_8187A9A8_7 {
    u8 unk_00;
    u8 pad_01[0x6];
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
} S_func_8187A9A8_7;

typedef struct S_func_8187A9A8_8 {
    u8 unk_00;
    u8 pad_01[0x3];
    u16 unk_04;
    u16 unk_06;
} S_func_8187A9A8_8;


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
void func_8187A9A8(void *mesh_data, S_func_8187A9A8_2 *transform, void *object_data, s32 depth_bias)
{
    register u8 *ot_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *barrier_scratch;
    S_func_8187A9A8_4 *mesh = mesh_data;
    S_func_8187A9A8_3 *object = object_data;
    S_func_8187A9A8_1 *scratch = (S_func_8187A9A8_1 *)0x1F800000;
    register s32 raw_depth_bias ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    S_func_8187A9A8_8 *texture;
    register S_func_8187A9A8_7 *texture_data ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 addr_mask ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u32 tag_mask;
    s32 depth_offset;
    u16 object_flags;
    MATRIX matrix;
    u16 render_flags;

    ot_base = *(u8 **)(D_80083150 + 0x10);
    ASM_KEEP_MEMDEP(ot_base, barrier_scratch, *(u8 **)(D_80083150 + 0x10));   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(mesh);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch->unk_24 = ot_base + 0xB0;
    scratch->unk_88 = transform->unk_02;
    scratch->unk_8C = transform->unk_06;
    raw_depth_bias = depth_bias;
    scratch->unk_90 = transform->unk_0A;
    addr_mask = 0x00FFFFFF;
    object_flags = object->unk_14;
    object_flags |= 0x8000;
    tag_mask = 0xFF000000;
    ASM_USE_NV(tag_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    object->unk_14 = object_flags;

    func_800649A0();

    scratch->unk_3C = 0x2000;
    scratch->unk_38 = 0x2000;
    scratch->unk_34 = 0x2000;
    scratch->unk_A4 = object->unk_16;
    scratch->unk_A8 = object->unk_1A;
    scratch->unk_A6 = object->unk_18;
    func_80065820((u8 *)0x1F8000A4, (u8 *)0x1F800074);
    func_80064AE0(&matrix);
    func_80064840(&matrix, (u8 *)0x1F800074, (u8 *)0x1F800054);
    func_80064BC0((u8 *)0x1F800054, (u8 *)0x1F800034);
    func_80064D80((u8 *)0x1F800054);
    func_80064CF0((u8 *)0x1F800054);
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    depth_offset = (s16)raw_depth_bias;
    texture = object->unk_08;
    texture_data = (S_func_8187A9A8_7 *)((u8 *)texture + 1);
    scratch->unk_28 = object->unk_14;
    ASM_KEEP(texture);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    if (mesh->unk_4E != 0) {
        S_func_8187A9A8_6 *packet;
        s32 ot_index;
        u8 texture_flags;
        s32 texture_adjust;
        S_func_8187A9A8_5 *render_state;
        register S_func_8187A9A8_5 **render_state_ref ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        render_state_ref = (S_func_8187A9A8_5 **)D_80083160_quad;
        ASM_KEEP(render_state_ref);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        render_state = *render_state_ref;
        packet = render_state->unk_8D0;
        render_state->unk_8D0 = (u8 *)packet + 0x28;

        scratch->unk_0C.as_s32_0C = texture_data->unk_07;
        scratch->unk_10.as_s32_10 = texture_data->unk_08;
        scratch->unk_14.as_s32_14 = texture_data->unk_09;
        scratch->unk_18.as_s32_18 = texture_data->unk_0A;

        scratch->unk_B0.as_u16_B0 = mesh->unk_58.as_u16_58;
        scratch->unk_B8.as_u16_B8 = mesh->unk_5A.as_u16_5A;
        scratch->unk_C0.as_u16_C0 = mesh->unk_5C.as_u16_5C;
        scratch->unk_C8.as_u16_C8 = mesh->unk_5E.as_u16_5E;
        scratch->unk_B2.as_u16_B2 = mesh->unk_60.as_u16_60;
        scratch->unk_BA.as_u16_BA = mesh->unk_62.as_u16_62;
        scratch->unk_C2.as_u16_C2 = mesh->unk_64.as_u16_64;
        scratch->unk_CA.as_u16_CA = mesh->unk_66.as_u16_66;
        scratch->unk_B4.as_u16_B4 = mesh->unk_68.as_u16_68;
        scratch->unk_BC.as_u16_BC = mesh->unk_6A.as_u16_6A;
        scratch->unk_C4.as_u16_C4 = mesh->unk_6C.as_u16_6C;
        scratch->unk_CC.as_u16_CC = mesh->unk_6E.as_u16_6E;

        ot_index = func_80065590((u8 *)scratch + 0xB0, (u8 *)scratch + 0xB8,
                              (u8 *)scratch + 0xC0, (u8 *)scratch + 0xC8,
                              (u8 *)packet + 8, (u8 *)packet + 0x10,
                              (u8 *)packet + 0x18, (u8 *)packet + 0x20,
                              (u8 *)scratch + 0xD0, (u8 *)scratch + 0xD4,
                              ({ EmptyArg empty; empty; })) - depth_offset - 6;
        scratch->unk_100 = ot_index;

        if ((u32)ot_index < 0x1E0 &&
            ((((u16)(packet->unk_08.as_u16_08 + 0x20) < 0x181) &&
              ((u16)(packet->unk_0A.as_u16_0A + 0x20) < 0x121)) |
             (((u16)(packet->unk_10 + 0x20) < 0x181) &&
              ((u16)(packet->unk_12 + 0x20) < 0x121)) |
             (((u16)(packet->unk_18 + 0x20) < 0x181) &&
              ((u16)(packet->unk_1A + 0x20) < 0x121)) |
             (((u16)(packet->unk_20.as_u16_20 + 0x20) < 0x181) &&
              ((u16)(packet->unk_22.as_u16_22 + 0x20) < 0x121)))) {
            packet->unk_00.as_u8_03.unk_03 = 9;
            packet->unk_04.as_u8_07.unk_07 = 0x2C;
            object->unk_14 &= 0x7FFF;

            scratch->unk_14.as_s32_14 += scratch->unk_0C.as_s32_0C;
            if (scratch->unk_14.as_s32_14 & 0x100) {
                scratch->unk_14.as_s32_14--;
            }
            scratch->unk_18.as_s32_18 += scratch->unk_10.as_s32_10;
            if (scratch->unk_18.as_s32_18 & 0x100) {
                scratch->unk_18.as_s32_18--;
            }
            scratch->unk_10.as_s32_10 <<= 8;
            scratch->unk_18.as_s32_18 <<= 8;

            texture_adjust = object->unk_12;
            if (texture_adjust != 0) {
                if (scratch->unk_28 & 0x100) {
                    packet->unk_0E = texture_adjust;
                    func_80024594();
                }
                {
                    u32 palette_id;
                    palette_id = texture_adjust + ((S_func_8187A9A8_8 *)((u8 *)texture_data - 1))->unk_06;
                    ASM_TAILSLOT_PIN(palette_id);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_8002458C();
                }
            }
            packet->unk_0E = ((S_func_8187A9A8_8 *)((u8 *)texture_data - 1))->unk_06;

            packet->unk_0C = scratch->unk_10.as_u16_10 +
                                       scratch->unk_0C.as_u16_0C;
            packet->unk_14.as_u16_14 = scratch->unk_10.as_u16_10 +
                                       scratch->unk_14.as_u16_14;

            texture_adjust = object->unk_10;
            if (texture_adjust != 0) {
                u32 texture_page;
                texture_page = texture_adjust +
                    (((S_func_8187A9A8_8 *)((u8 *)texture_data - 1))->unk_04 & 0xFF9F);
                ASM_TAILSLOT_PIN(texture_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_800245E4();
            }
            packet->unk_16 = ((S_func_8187A9A8_8 *)((u8 *)texture_data - 1))->unk_04;

            packet->unk_1C.as_u16_1C = scratch->unk_18.as_u16_18 +
                                       scratch->unk_0C.as_u16_0C;
            packet->unk_24.as_u16_24 = scratch->unk_18.as_u16_18 +
                                       scratch->unk_14.as_u16_14;

            if (packet->unk_08.as_s16_08 > packet->unk_20.as_s16_20) {
                packet->unk_14.as_u8_14--;
                packet->unk_24.as_u8_24--;
            }
            if (packet->unk_0A.as_s16_0A > packet->unk_22.as_s16_22) {
                packet->unk_1C.as_u8_1D.unk_1D--;
                packet->unk_24.as_u8_25.unk_25--;
            }

            texture_flags = texture_data->unk_00;
            object->unk_0C.as_u8_0F.unk_0F = texture_flags;
            render_flags = scratch->unk_28;
            if (render_flags & 8) {
                object->unk_0C.as_u8_0F.unk_0F = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            packet->unk_04.as_u32_04 = object->unk_0C.as_u32_0C;
            packet->unk_00.as_u32_00 = (packet->unk_00.as_u32_00 & tag_mask) |
                (((u32 *)scratch->unk_24)[scratch->unk_100] & addr_mask);
            ((u32 *)scratch->unk_24)[scratch->unk_100] =
                (((u32 *)scratch->unk_24)[scratch->unk_100] & tag_mask) |
                ((u32)packet & addr_mask);
        }
    }

    if (mesh->unk_4E == 0) {
        register S_func_8187A9A8_6 *packet ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 ot_index;
        s32 midpoint;
        s32 midpoint_z;
        s32 coord_a;
        s32 coord_b;
        s32 end_z_a;
        s32 end_z_b;
        u8 *vertex_a;
        u8 *vertex_b;
        u8 *vertex_c;
        u8 *vertex_d;
        u8 *screen_a;
        u8 *screen_b;
        u8 *fog_out;
        u8 *flags_out;
        register s32 tpage_zero ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register s32 blend_mode ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        u32 *ot_entry;
        u32 color_code;
        s32 packet_code;
        register S_func_8187A9A8_5 *render_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register S_func_8187A9A8_5 **render_state_ref ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        render_state_ref = (S_func_8187A9A8_5 **)D_80083160_line;
        ASM_KEEP(render_state_ref);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        render_state = *render_state_ref;
        packet = render_state->unk_8D0;
        render_state->unk_8D0 = (u8 *)packet + 0x10;

        coord_a = mesh->unk_58.as_s16_58;
        coord_b = mesh->unk_5C.as_s16_5C;
        vertex_a = (u8 *)scratch + 0xB0;
        midpoint = (coord_a + coord_b) / 2;
        scratch->unk_C0.as_s16_C0 = midpoint;
        scratch->unk_B0.as_s16_B0 = midpoint;
        coord_a = mesh->unk_5A.as_s16_5A;
        coord_b = mesh->unk_5E.as_s16_5E;
        vertex_b = (u8 *)scratch + 0xB8;
        midpoint = (coord_a + coord_b) / 2;
        scratch->unk_C8.as_s16_C8 = midpoint;
        scratch->unk_B8.as_s16_B8 = midpoint;
        coord_a = mesh->unk_60.as_s16_60;
        coord_b = mesh->unk_64.as_s16_64;
        vertex_c = (u8 *)scratch + 0xC0;
        midpoint = (coord_a + coord_b) / 2;
        scratch->unk_C2.as_s16_C2 = midpoint;
        scratch->unk_B2.as_s16_B2 = midpoint;
        coord_a = mesh->unk_62.as_s16_62;
        coord_b = mesh->unk_66.as_s16_66;
        vertex_d = (u8 *)scratch + 0xC8;
        midpoint = (coord_a + coord_b) / 2;
        scratch->unk_CA.as_s16_CA = midpoint;
        scratch->unk_BA.as_s16_BA = midpoint;
        coord_a = mesh->unk_68.as_s16_68;
        coord_b = mesh->unk_6C.as_s16_6C;
        screen_a = (u8 *)packet + 8;
        midpoint = (coord_a + coord_b) / 2;
        scratch->unk_C4.as_s16_C4 = midpoint;
        scratch->unk_B4.as_s16_B4 = midpoint;
        end_z_a = mesh->unk_6A.as_s16_6A;
        end_z_b = mesh->unk_6E.as_s16_6E;
        screen_b = (u8 *)packet + 0x0C;
        fog_out = (u8 *)scratch + 0xD0;
        flags_out = (u8 *)scratch + 0xD4;

        ot_index = func_80065590(vertex_a, vertex_b,
                              vertex_c, vertex_d,
                              screen_a, screen_b,
                              screen_a, screen_b,
                              fog_out, flags_out,
                              ({
                                  EmptyArg empty;
                                  midpoint_z = (end_z_a + end_z_b) / 2;
                                  scratch->unk_CC.as_s16_CC = midpoint_z;
                                  scratch->unk_BC.as_s16_BC = midpoint_z;
                                  empty;
                              })) - depth_offset - 6;
        scratch->unk_100 = ot_index;

        render_flags = scratch->unk_28;
        if (render_flags & 8) {
            if (render_flags & 4) {
                u32 draw_flags;
                draw_flags = object->unk_0C.as_u8_0F.unk_0F | 2;
                ASM_TAILSLOT_PIN(draw_flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80024854();
            }
            object->unk_0C.as_u8_0F.unk_0F &= 0xFD;
        }

        tpage_zero = 0;
        color_code = object->unk_0C.as_u32_0C;
        packet->unk_00.as_u8_03.unk_03 = 3;
        ASM_SET(packet_code);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        packet_code = 0x42;
        blend_mode = 1;
        render_state_ref = (S_func_8187A9A8_5 **)D_80083160_tpage;
        ASM_KEEP(render_state_ref);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        packet->unk_04.as_u32_04 = color_code;
        packet->unk_04.as_u8_07.unk_07 = packet_code;

        packet->unk_00.as_u32_00 = (packet->unk_00.as_u32_00 & tag_mask) |
            (((u32 *)scratch->unk_24)[scratch->unk_100] & addr_mask);
        ot_entry = (u32 *)
            (((u32)scratch->unk_100 << 2) +
             (u32)scratch->unk_24);
        ASM_KEEP(ot_entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        {
            u32 ot_tag;
            register u32 packet_addr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            ot_tag = *ot_entry;
            packet_addr = (u32)packet & addr_mask;
            ot_tag &= tag_mask;
            ot_tag |= packet_addr;
            *ot_entry = ot_tag;
        }

        render_state = *render_state_ref;
        packet = render_state->unk_8D0;
        render_state->unk_8D0 = (u8 *)packet + 0x0C;
        func_80067F20(packet, 0, 0,
                     func_80066460(tpage_zero, blend_mode,
                                   tpage_zero, tpage_zero) & 0xFFFF, 0);

        packet->unk_00.as_u32_00 = (packet->unk_00.as_u32_00 & tag_mask) |
            (((u32 *)scratch->unk_24)[scratch->unk_100] & addr_mask);
        ((u32 *)scratch->unk_24)[scratch->unk_100] =
            (((u32 *)scratch->unk_24)[scratch->unk_100] & tag_mask) |
            ((u32)packet & addr_mask);
    }

    if ((s8)texture->unk_00 >= 0) {
        texture_data = (S_func_8187A9A8_7 *)((u8 *)texture_data + 0x0C);
        ASM_KEEP(texture_data);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        texture = (S_func_8187A9A8_8 *)((u8 *)texture + 0x0C);
        ASM_TAILSLOT_PIN(texture);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_800242C8();
    }
    func_80064A40();
}
