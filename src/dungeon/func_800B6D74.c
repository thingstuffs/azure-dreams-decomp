#include "common.h"

typedef struct S_800BC4D4_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BC4D4_0;   /* root in func_800BC4D4 */

typedef struct S_800BC4D4_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    union { u32 u32; s32 s32; u16 u16; } unk_08;   /* accessed as both */
    union { u32 u; s32 s; } unk_0C;   /* accessed as both */
    union { u32 u32; u16 u16; s32 s32; } unk_10;   /* accessed as both */
    union { u32 u32; u16 u16; s32 s32; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    u8 * unk_20;
    u16 unk_24;
    u8 pad_26[0xA];
    union { s32 s; u32 u; } unk_30;   /* accessed as both */
    union { s32 s; u32 u; } unk_34;   /* accessed as both */
    s32 unk_38;
    u8 pad_3C[0x34];
    union { s16 s; u16 u; } unk_70;   /* accessed as both */
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    union { s16 s; u16 u; } unk_78;   /* accessed as both */
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
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
} S_800BC4D4_1;   /* scratch in func_800BC4D4 */

typedef struct S_800BC4D4_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800BC4D4_2;   /* arg1 in func_800BC4D4 */

typedef struct S_800BC4D4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC4D4_3;   /* arg0 in func_800BC4D4 */

typedef struct S_800BC4D4_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800BC4D4_4;   /* matrix in func_800BC4D4 */

typedef struct S_800BC4D4_5_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800BC4D4_5_pre;   /* the 0x4 bytes before packet_field in func_800BC4D4, addressed as packet_field[-1] */

typedef struct S_800BC4D4_5 {
    u8 unk_00;
    u8 pad_01[0xC];
    u8 unk_0D;
    u8 pad_0E[0x8];
    u8 unk_16;
    u8 pad_17[0x6];
    u8 unk_1D;
    u8 unk_1E;
} S_800BC4D4_5;   /* packet_field in func_800BC4D4 */

typedef struct S_800BC4D4_6 {
    u16 unk_00;
} S_800BC4D4_6;   /* texture_data in func_800BC4D4 */

typedef struct S_800BC4D4_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BC4D4_7;   /* *global in func_800BC4D4 */

#define KEEP_NV_EXPR(v) ({ ASM_KEEP_NV(v); 0; })
#define KEEP_DEP_NV_EXPR(v, d) ({ ASM_KEEP_DEP_NV(v, d); 0; })

typedef struct ScratchGeom {
    u8 pad70[0x70];
    s16 p70;
    u8 pad72[6];
    s16 p78;
    u8 pad7a[6];
    s16 p80;
    u8 pad82[6];
    s16 p88;
    u8 pad8a[6];
    s16 p90;
    u8 pad92[2];
    s16 p94;
    u8 pad96[0x5a];
    s16 pF0;
    u8 padF2[2];
    s16 pF4;
    u8 padF6[2];
    s16 pF8;
    u8 padFA[2];
    s16 pFC;
    u8 padFE[2];
} ScratchGeom;

typedef struct GeomTailArgs {
    s16 *arg9;
    s16 *arg10;
} GeomTailArgs;

typedef struct GeomSideEffects {
} GeomSideEffects;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0(s16 *, s16 *, s16 *, s16 *, s16 *, s16 *, s16 *, s16 *,
                          GeomTailArgs, GeomSideEffects);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern u8 D_8006CD30[];
extern u8 D_80083160[];

#ifdef NON_MATCHING
#define GLOBAL_PAGE_8008 (D_80083160 - 0x3160)
#else
#define GLOBAL_PAGE_8008 ((u8 *)0x80080000)
#endif

/* Project sprite tiles and append textured quads to the ordering table. */
void func_800BC4D4(void *position, void *sprite, u16 world_z, s32 depth_bias)
{
    register u8 *scratch_base ASM_REG("$4") = (u8 *)0x1F800000;
    register u8 *screen_pos ASM_REG("$5") = scratch_base;
    u8 *perspective;
    u8 *clip_flags;
    register u8 *scratch ASM_REG("$17");
    u8 *global_page;
    register u8 **root_ptr ASM_REG("$23");
    register u8 *page_reg ASM_REG("$2");
    u8 *matrix;
    u8 *packet;
    u8 *packet_next;
    u8 *texture;
    u8 *texture_data;
    u8 *packet_field;
    u8 *root;
    u32 projected_depth;
    u32 biased_depth;
    u32 ot_index;
    s32 scale;
    s32 clamped_scale;
    register s32 tex_u ASM_REG("$4");
    register s32 quad_height ASM_REG("$5");
    s32 uv_word;
    s32 uv_sum;
    s32 uv_v_end;
    register s32 coord_x;
    register s32 coord_y;
    u16 screen_x;
    u16 sprite_z;
    u16 sprite_flags;
    u16 world_x;
    u16 world_y;

    screen_pos = (u8 *)((u32)screen_pos | 0xB8);
    ASM_KEEP_MEMDEP_NV(scratch_base, page_reg, *(u8 **)D_80083160);
    perspective = scratch_base;
    ASM_KEEP_NV(perspective);
    scratch = scratch_base;
    perspective = (u8 *)((u32)perspective | 0x90);
    root = *(u8 **)D_80083160;
    packet = ((S_800BC4D4_0 *)root)->unk_8D0;
    ((S_800BC4D4_1 *)scratch)->unk_20 = root + 0xB0;
#ifdef NON_MATCHING
    global_page = D_80083160 - 0x3160;
#else
    ASM_SET(global_page);
#endif
    ((S_800BC4D4_1 *)scratch)->unk_EC = 0;
    ((S_800BC4D4_1 *)scratch)->unk_E8 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_E4 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_8C = 0;
    ((S_800BC4D4_1 *)scratch)->unk_84 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_7C = 0;
    ((S_800BC4D4_1 *)scratch)->unk_74 = 0;

    texture = ((S_800BC4D4_2 *)sprite)->unk_08;
    sprite_flags = ((S_800BC4D4_2 *)sprite)->unk_14;
    ASM_CLOBBER("$7");
    clip_flags = scratch_base;
    ASM_KEEP_NV(clip_flags);
    ((S_800BC4D4_1 *)scratch)->unk_24 = sprite_flags;
    world_x = ((S_800BC4D4_3 *)position)->unk_02;
    clip_flags = (u8 *)((u32)clip_flags | 0x94);
    ((S_800BC4D4_1 *)scratch)->unk_00 = world_x;
    world_y = ((S_800BC4D4_3 *)position)->unk_06;
    ASM_CLOBBER("$23");
    root_ptr = (u8 **)(global_page + 0x3160);
    ((S_800BC4D4_1 *)scratch)->unk_02 = world_y;
    ((S_800BC4D4_1 *)scratch)->unk_04 = world_z;

    projected_depth = func_80065420(scratch_base, screen_pos,
                              perspective, clip_flags);
    matrix = D_8006CD30;
    ((S_800BC4D4_1 *)scratch)->unk_C0 = projected_depth;
    ((S_800BC4D4_4 *)matrix)->unk_1C = projected_depth * 4;
    biased_depth = projected_depth - 7;
    ot_index = biased_depth - depth_bias;
    ((S_800BC4D4_1 *)scratch)->unk_C0 = ot_index;

    if (ot_index < 0x1E0U) {
        func_800649A0();

        screen_x = ((S_800BC4D4_1 *)scratch)->unk_B8;
        sprite_z = ((S_800BC4D4_1 *)scratch)->unk_04;
        ((S_800BC4D4_1 *)scratch)->unk_B8 = screen_x - 0xA0;
        ((S_800BC4D4_1 *)scratch)->unk_BA -= 0x78;
        scale = ((((S_800BC4D4_3 *)position)->unk_0A - (s16)sprite_z) << 5) + 0x1000;
        ((S_800BC4D4_1 *)scratch)->unk_38 = scale;
        if (scale < 0) {
            ((S_800BC4D4_1 *)scratch)->unk_38 = 0;
        }

        clamped_scale = ((S_800BC4D4_1 *)scratch)->unk_38;
        ((S_800BC4D4_1 *)scratch)->unk_30.s = clamped_scale;
        ((S_800BC4D4_1 *)scratch)->unk_34.s = (s32)(clamped_scale + ((u32)clamped_scale >> 31)) >> 1;
        func_80065820((void *)0x1F800100, (void *)0x1F8000D0);
        texture_data = texture + 4;

        packet_field = packet + 7;
        func_80064840(matrix, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);

        ((S_800BC4D4_1 *)scratch)->unk_30.u = ((S_800BC4D4_2 *)sprite)->unk_1C;
        ((S_800BC4D4_1 *)scratch)->unk_34.u = ((S_800BC4D4_2 *)sprite)->unk_1E;
        ((S_800BC4D4_1 *)scratch)->unk_38 = 0x1000;
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);

        for (;;) {
            if (!(texture[0] & 0x20)) {
                register s32 mode_flag ASM_REG("$5");
                register s32 mode_flag_copy ASM_REG("$6");
                register u8 *packet_arg ASM_REG("$4");
                u32 tile_u;
                u32 tile_width;
                u32 tile_height;

                mode_flag = 0;
                ASM_KEEP_NV(mode_flag);
                tile_u = texture_data[4];
                packet_arg = packet;
                ASM_KEEP_NV(packet_arg);
                ((S_800BC4D4_1 *)scratch)->unk_08.u32 = tile_u;
                ((S_800BC4D4_1 *)scratch)->unk_0C.u = texture_data[5];
                tile_width = texture_data[6];
                mode_flag_copy = mode_flag;
                ((S_800BC4D4_1 *)scratch)->unk_10.u32 = tile_width;
                tile_height = texture_data[7];
                packet_field += 0xC;
                ((S_800BC4D4_1 *)scratch)->unk_14.u32 = tile_height;

                func_80067EF4(packet_arg, mode_flag, mode_flag_copy);
                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                                  ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet_next = packet + 0xC;
                packet = packet_next;

                if ((texture[0] ^ ((S_800BC4D4_1 *)scratch)->unk_24) & 1) {
                    u32 quad_width;

                    coord_x = texture_data[-2];
                    quad_width = ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                    ASM_KEEP_DEP_NV(coord_x, quad_width);
                    coord_x = (s8)coord_x;
                    coord_x = -coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_80 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_70.s = coord_x;
                    coord_x -= quad_width;
                } else {
                    u32 quad_width;

                    coord_x = texture_data[-2];
                    quad_width = ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                    ASM_KEEP_DEP_NV(coord_x, quad_width);
                    coord_x = (s8)coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_80 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_70.s = coord_x;
                    coord_x += quad_width;
                }
                ((S_800BC4D4_1 *)scratch)->unk_88 = coord_x;
                ((S_800BC4D4_1 *)scratch)->unk_78.s = coord_x;

                if ((texture[0] ^ ((S_800BC4D4_1 *)scratch)->unk_24) & 2) {
                    u32 quad_height;

                    coord_y = texture_data[-1];
                    quad_height = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    ASM_KEEP_DEP_NV(coord_y, quad_height);
                    coord_y = (s8)coord_y;
                    coord_y = -coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_7A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_72 = coord_y;
                    coord_y -= quad_height;
                } else {
                    u32 quad_height;

                    coord_y = texture_data[-1];
                    quad_height = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    ASM_KEEP_DEP_NV(coord_y, quad_height);
                    coord_y = (s8)coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_7A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_72 = coord_y;
                    coord_y += quad_height;
                }
                ((S_800BC4D4_1 *)scratch)->unk_8A = coord_y;
                ((S_800BC4D4_1 *)scratch)->unk_82 = coord_y;

                ASM_KEEP_NV(scratch);
                {
                    s16 *top_left = (s16 *)(scratch + 0x70);
                    s16 *top_right = (s16 *)(scratch + 0x78);
                    register s16 *bottom_left ASM_REG("$6") = (s16 *)(scratch + 0x80);
                    register s16 *bottom_right ASM_REG("$7") = (s16 *)(scratch + 0x88);
                    u16 left_vertex_x;
                    u16 right_vertex_x;

                    ASM_KEEP4_NV(top_left, top_right, bottom_left, bottom_right);
                    func_800654B0(top_left, top_right, bottom_left, bottom_right,
                                  (s16 *)(scratch + 0xF0), (s16 *)(scratch + 0xF4),
                                  (s16 *)(scratch + 0xF8), (s16 *)(scratch + 0xFC),
                                  (GeomTailArgs){(s16 *)(scratch + 0x90),
                                                 (s16 *)(scratch + 0x94)},
                                  (left_vertex_x = ((S_800BC4D4_1 *)scratch)->unk_70.u,
                                   KEEP_NV_EXPR(left_vertex_x),
                                   right_vertex_x = ((S_800BC4D4_1 *)scratch)->unk_78.u,
                                   left_vertex_x += 6,
                                   right_vertex_x += 6,
                                   KEEP_DEP_NV_EXPR(left_vertex_x, right_vertex_x),
                                   ((S_800BC4D4_1 *)scratch)->unk_70.u = left_vertex_x,
                                   ((S_800BC4D4_1 *)scratch)->unk_78.u = right_vertex_x,
                                   (GeomSideEffects){}));
                }

                (*(s16 *)((u8 *)packet_field + 1)) = ((S_800BC4D4_1 *)scratch)->unk_F0 + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)((u8 *)packet_field + 3)) = ((S_800BC4D4_1 *)scratch)->unk_F2 + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)((u8 *)packet_field + 9)) = ((S_800BC4D4_1 *)scratch)->unk_F4 + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)((u8 *)packet_field + 0xB)) = ((S_800BC4D4_1 *)scratch)->unk_F6 + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)((u8 *)packet_field + 0x11)) = ((S_800BC4D4_1 *)scratch)->unk_F8 + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)((u8 *)packet_field + 0x13)) = ((S_800BC4D4_1 *)scratch)->unk_FA + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)((u8 *)packet_field + 0x19)) = ((S_800BC4D4_1 *)scratch)->unk_FC + ((S_800BC4D4_1 *)scratch)->unk_B8;
                {
                    u16 bottom_y = ((S_800BC4D4_1 *)scratch)->unk_FE;
                    u16 screen_y = ((S_800BC4D4_1 *)scratch)->unk_BA;

                    ((S_800BC4D4_5_pre *)packet_field)[-1].unk_00 = 9;
                    (*(s16 *)((u8 *)packet_field + 0x1B)) = bottom_y + screen_y;
                }

                uv_sum = ((S_800BC4D4_1 *)scratch)->unk_10.s32;
                tex_u = ((S_800BC4D4_1 *)scratch)->unk_08.s32;

                uv_v_end = ((S_800BC4D4_1 *)scratch)->unk_0C.s;
                quad_height = ((S_800BC4D4_1 *)scratch)->unk_14.s32;
                uv_sum += tex_u;
                uv_v_end += quad_height;
                ((S_800BC4D4_1 *)scratch)->unk_10.s32 = uv_sum;
                uv_sum = ((S_800BC4D4_1 *)scratch)->unk_0C.s;
                uv_v_end <<= 8;
                ((S_800BC4D4_1 *)scratch)->unk_14.s32 = uv_v_end;
                uv_sum <<= 8;
                ((S_800BC4D4_1 *)scratch)->unk_0C.s = uv_sum;
                uv_word = uv_sum;
                uv_word += tex_u;

                {
                    register u32 texture_page;

                    if (((S_800BC4D4_6 *)texture_data)->unk_00 & 0x80) {

                        texture_page = 0x7F800000;
                    } else {
                        ASM_SCHED_BARRIER();
                        texture_page = 0x7FC00000;
                    }

                    uv_word += texture_page;
                }
                (*(s32 *)((u8 *)packet_field + 5)) = uv_word;
                (*(s32 *)((u8 *)packet_field + 0xD)) = ((S_800BC4D4_1 *)scratch)->unk_0C.s +
                                                      ((S_800BC4D4_1 *)scratch)->unk_10.s32 +
                                                      ((s16)((S_800BC4D4_6 *)texture_data)->unk_00 << 16);
                {
                    s32 uv_left;
                    s32 u_left;
                    s32 left_x;

                    uv_left = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    u_left = ((S_800BC4D4_1 *)scratch)->unk_08.u16;
                    left_x = (*(s16 *)((u8 *)packet_field + 1));
                    uv_left += u_left;
                    (*(s16 *)((u8 *)packet_field + 0x15)) = uv_left;
                    ASM_SCHED_BARRIER();
                    {
                        s32 uv_right;
                        s32 u_right;
                        register s32 right_x ASM_REG("$2");

                        uv_right = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                        u_right = ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                        right_x = (*(s16 *)((u8 *)packet_field + 0x19));
                        uv_right += u_right;
                        (*(s16 *)((u8 *)packet_field + 0x1D)) = uv_right;

                        if (right_x < left_x) {
                            ((S_800BC4D4_5 *)packet_field)->unk_0D--;
                            ((S_800BC4D4_5 *)packet_field)->unk_1D--;
                        }
                    }
                }
                if ((*(s16 *)((u8 *)packet_field + 3)) > (*(s16 *)((u8 *)packet_field + 0x1B))) {
                    ((S_800BC4D4_5 *)packet_field)->unk_16--;
                    ((S_800BC4D4_5 *)packet_field)->unk_1E--;
                }

                (*(s32 *)((u8 *)packet_field + -3)) = ((S_800BC4D4_2 *)sprite)->unk_0C;
                ((S_800BC4D4_5 *)packet_field)->unk_00 = 0x2E;
                packet_field += 0x28;
                ASM_KEEP_NV(packet_field);
                packet_field += 0xC;
                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                                  ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet += 0x28;
                func_80067EF4(packet, 1, 0);
                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                                  ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet += 0xC;
            }

            texture_data += 0xC;
            if ((s8)texture[0] >= 0) {

                ASM_KEEP(texture_data);
                texture += 0xC;
                continue;
            }
            break;
        }
        func_80064A40();
    }

    ((S_800BC4D4_7 *)(*root_ptr))->unk_8D0 = packet;
}
