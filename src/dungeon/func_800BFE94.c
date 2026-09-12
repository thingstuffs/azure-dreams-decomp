#include "common.h"

typedef struct S_800C55F4_0 {
    u8 ** unk_00;
    u8 pad_04[0x4];
    u8 ** unk_08;
} S_800C55F4_0;   /* descriptor in func_800C55F4 */

typedef struct S_800C55F4_1 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x2];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x28];
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    u32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    u32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u32 unk_80;
    u16 unk_84;
    u8 pad_86[0x3A];
    union { s32 s; volatile s32 u; } unk_C0;   /* accessed as both */
    s32 unk_C4;
    union { s32 s; volatile s32 u; } unk_C8;   /* accessed as both */
    s32 unk_CC;
    u8 pad_D0[0x44];
    s32 unk_114;
} S_800C55F4_1;   /* scratch in func_800C55F4 */

typedef struct S_800C55F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C55F4_2;   /* arg2_alias in func_800C55F4 */

typedef struct S_800C55F4_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C55F4_3;   /* arg1_record in func_800C55F4 */

typedef struct S_800C55F4_4 {
    u8 unk_00;
    u8 pad_01[0x315F];
    u8 * unk_3160;
} S_800C55F4_4;   /* page_record7 in func_800C55F4 */

typedef struct S_800C55F4_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C55F4_5;   /* root in func_800C55F4 */

typedef struct S_800C55F4_6 {
    u32 unk_00;
    u16 unk_04;
} S_800C55F4_6;   /* (x << 3) + (u32)table in func_800C55F4 */

typedef struct S_800C55F4_7_pre {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x8];
} S_800C55F4_7_pre;   /* the 0xA bytes before entry in func_800C55F4, addressed as entry[-1] */

typedef struct S_800C55F4_7 {
    s8 unk_00;
} S_800C55F4_7;   /* entry in func_800C55F4 */

typedef struct S_800C55F4_8 {
    u8 pad_00[0x30];
    s16 unk_30;
    s16 unk_32;
} S_800C55F4_8;   /* arg0_pin in func_800C55F4 */

typedef struct S_800C55F4_9 {
    u8 * unk_00;
} S_800C55F4_9;   /* global_base in func_800C55F4 */

typedef struct S_800C55F4_10 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C55F4_10;   /* ((S_800C55F4_9 *)global_base)->unk_00 in func_800C55F4 */



extern s32 func_8004CECC();
extern s32 func_80064840();
extern s32 func_800649A0();
extern s32 func_80064A40();
extern s32 func_80064AE0();
extern s32 func_80064BC0();
extern s32 func_80064CF0();
extern s32 func_80064D80();
extern s32 func_80065420();
extern s32 func_80065480();
extern s32 func_80065820();
extern s32 func_8006658C();
extern s32 func_800666B8();
extern s32 func_80067F20();

extern u8 D_80083160[];

/* Transform mesh triangles, shade visible vertices, and append draw packets to the ordering table. */
void func_800C55F4(void *render_params, void *translation, void *mesh, s32 depth_offset)
{
    u8 saved_matrix[0x20];
    register u8 *params = render_params;
    u8 *record = translation;
    void *mesh_data = mesh;
    register s32 depth_bias ASM_REG("$17") = depth_offset;
    register u8 *scratch ASM_REG("$19");
    register u32 output_addr ASM_REG("$8");
    register u8 *vector_arg ASM_REG("$4");
    u8 *screen_arg;
    void *volatile perspective_out;
    void *volatile flags_out;
    u8 *descriptor;
    register u8 *vertices ASM_REG("$21");
    register u8 *face_end ASM_REG("$20");
    register u8 *face ASM_REG("$22");
    u8 *packet_code;
    u8 *render_state;
    u8 *packet;
    register u8 *state_ptr ASM_REG("$8");
    u8 packet_flags;
    s32 result;
    s32 face_flags;
    u32 vertex_index;
    u32 vertex_depth;
    void *vertex_arg;
    void *perspective_arg;
    void *flags_arg;

    ASM_KEEP4_NV(params, record, mesh_data, packet_code);
    output_addr = 0x1F800000;
    output_addr |= 0x90;
    perspective_out = (void *)output_addr;
    output_addr = 0x1F800000;

    descriptor = (*(u8 ** *)((u8 *)mesh_data + 8));
    output_addr |= 0x94;
    flags_out = (void *)output_addr;
    ASM_CLOBBER("$18");
    vertices = ((S_800C55F4_0 *)descriptor)->unk_00;
    face = ((S_800C55F4_0 *)descriptor)->unk_08;

    func_800649A0();

    packet_code = (u8 *)0x80080000;
    vector_arg = (u8 *)0x1F800028;
    screen_arg = (u8 *)0x1F800000;
    ASM_KEEP_NV(screen_arg);
    scratch = (u8 *)0x1F800000;

    ((S_800C55F4_1 *)scratch)->unk_30 = ((S_800C55F4_2 *)mesh_data)->unk_1C;
    {
        u32 translation_y;

        translation_y = ((S_800C55F4_2 *)mesh_data)->unk_1E;
        screen_arg = (u8 *)((u32)screen_arg | 0xF0);
        ((S_800C55F4_1 *)scratch)->unk_34 = translation_y;
    }
    ((S_800C55F4_1 *)scratch)->unk_38 = ((S_800C55F4_2 *)mesh_data)->unk_20;

    {
        s32 translation_coord;

        translation_coord = ((S_800C55F4_3 *)record)->unk_02;
        ((S_800C55F4_1 *)scratch)->unk_64 = translation_coord;
        ((S_800C55F4_1 *)scratch)->unk_28 = translation_coord;
        translation_coord = ((S_800C55F4_3 *)record)->unk_06;
        ((S_800C55F4_1 *)scratch)->unk_68 = translation_coord;
        ((S_800C55F4_1 *)scratch)->unk_2A = translation_coord;
        translation_coord = ((S_800C55F4_3 *)record)->unk_0A;
        ((S_800C55F4_1 *)scratch)->unk_6C = translation_coord;
        ((S_800C55F4_1 *)scratch)->unk_2C = translation_coord;
    }

    result = func_80065420(vector_arg, screen_arg,
                          (void *)0x1F800090, (void *)0x1F800094);
    vector_arg = saved_matrix;
    ASM_USE_NV(vector_arg);
    depth_bias = (s16)depth_bias;
    ((S_800C55F4_1 *)scratch)->unk_CC = result - depth_bias;
    func_80064AE0(vector_arg);
    func_80065820((u8 *)mesh_data + 0x16, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064840(saved_matrix, scratch + 0x50, scratch + 0xD0);
    func_80064D80(scratch + 0xD0);
    func_80064CF0(scratch + 0xD0);
    ASM_KEEP(scratch);

    render_state = ((S_800C55F4_4 *)packet_code)->unk_3160;
    face_end = face + 0xB;
    ((S_800C55F4_1 *)scratch)->unk_20 = render_state + 0xB0;
    record = ((S_800C55F4_5 *)render_state)->unk_8D0;
    packet_code = record + 7;
    ((S_800C55F4_2 *)mesh_data)->unk_14 |= 0x8000;

    for (;;) {
        vertex_index = *face;
        ((S_800C55F4_1 *)scratch)->unk_70 = ((S_800C55F4_6 *)((vertex_index << 3) + (u32)vertices))->unk_00;
        vertex_index = ((S_800C55F4_7_pre *)face_end)[-1].unk_00;
        ((S_800C55F4_1 *)scratch)->unk_78 = ((S_800C55F4_6 *)((vertex_index << 3) + (u32)vertices))->unk_00;
        vertex_index = ((S_800C55F4_7_pre *)face_end)[-1].unk_01;
        ((S_800C55F4_1 *)scratch)->unk_80 = ((S_800C55F4_6 *)((vertex_index << 3) + (u32)vertices))->unk_00;
        vertex_index = *face;
        ((S_800C55F4_1 *)scratch)->unk_74 = ((S_800C55F4_6 *)((vertex_index << 3) + (u32)vertices))->unk_04;
        vertex_index = ((S_800C55F4_7_pre *)face_end)[-1].unk_00;
        vertex_arg = scratch + 0x70;
        ((S_800C55F4_1 *)scratch)->unk_7C = ((S_800C55F4_6 *)((vertex_index << 3) + (u32)vertices))->unk_04;
        vertex_index = *(volatile u8 *)(face_end - 9);
        perspective_arg = perspective_out;
        flags_arg = flags_out;
        ((S_800C55F4_1 *)scratch)->unk_84 = ((S_800C55F4_6 *)((vertex_index << 3) + (u32)vertices))->unk_04;

        {
            s32 depth;

            depth = func_80065420(vertex_arg, record + 8,
                                        perspective_arg, flags_arg);
            vertex_arg = scratch + 0x78;
            perspective_arg = perspective_out;
            flags_arg = flags_out;
            ((S_800C55F4_1 *)scratch)->unk_C0.s = depth;
            depth = func_80065420(vertex_arg, record + 0x10,
                                        perspective_arg, flags_arg);
            vertex_arg = scratch + 0x80;
            perspective_arg = perspective_out;
            flags_arg = flags_out;
            ((S_800C55F4_1 *)scratch)->unk_C4 = depth;
            depth = func_80065420(vertex_arg, record + 0x18,
                                        perspective_arg, flags_arg);
            ((S_800C55F4_1 *)scratch)->unk_C8.s = depth;
        }

        result = func_80065480((*(s32 *)((u8 *)packet_code + 1)),
                               (*(s32 *)((u8 *)packet_code + 9)),
                               (*(s32 *)((u8 *)packet_code + 0x11)));
        ((S_800C55F4_1 *)scratch)->unk_114 = result;

        if (result > 0) {
            s32 third_depth;

            ((S_800C55F4_1 *)scratch)->unk_C0.u -= depth_bias;
            third_depth = ((S_800C55F4_1 *)scratch)->unk_C8.u;
            ((S_800C55F4_1 *)scratch)->unk_C4 -= depth_bias;
            vertex_depth = *(volatile u32 *)(scratch + 0xC0);
            ((S_800C55F4_1 *)scratch)->unk_C8.s = third_depth - depth_bias;
            if (vertex_depth < 0x1E0) {
                {
                    s32 first_shade;
                    register s32 first_height ASM_REG("$4");

                    first_shade = 0x100;
                    first_height = ((S_800C55F4_8 *)params)->unk_32;
                    first_shade -= first_height;
                    first_shade -=
                        (((S_800C55F4_1 *)scratch)->unk_CC - vertex_depth) << 5;
                    if (first_shade < 0x20) {
                        first_shade = 0x20;
                    } else if (first_shade >= 0x100) {
                        first_shade = 0xFF;
                    }
                    {
                        s32 shade_arg;

                        shade_arg = (s32)(s16)first_shade;
                        ASM_KEEP_DEP_NV(shade_arg, first_shade);
                        func_8004CECC(((S_800C55F4_8 *)params)->unk_30,
                                      shade_arg, 0xFF, record + 4);
                    }
                }

                {
                    s32 second_base_shade;
                    register s32 second_shade ASM_REG("$3");
                    s32 second_delta;
                    s32 second_height;

                    second_base_shade = 0x100;
                    do {
                        second_height = ((S_800C55F4_8 *)params)->unk_32;
                    } while (0);
                    second_delta = ((S_800C55F4_1 *)scratch)->unk_CC;
                    second_shade = ((S_800C55F4_1 *)scratch)->unk_C4;
                    second_base_shade -= second_height;
                    second_delta -= second_shade;
                    second_delta <<= 5;
                    second_shade = second_base_shade - second_delta;
                    if (second_shade < 0x20) {
                        second_shade = 0x20;
                    } else if (second_shade >= 0x100) {
                        second_shade = 0xFF;
                    }
                    {
                        s32 shade_arg;

                        shade_arg = (s32)(s16)second_shade;
                        ASM_KEEP_DEP_NV(shade_arg, second_shade);
                        func_8004CECC(((S_800C55F4_8 *)params)->unk_30,
                                      shade_arg, 0xFF,
                                      record + 0xC);
                    }
                }

                {
                    s32 third_base_shade;
                    register s32 third_shade ASM_REG("$3");
                    s32 third_delta;
                    s32 third_height;

                    third_base_shade = 0x100;
                    do {
                        third_height = ((S_800C55F4_8 *)params)->unk_32;
                    } while (0);
                    third_delta = ((S_800C55F4_1 *)scratch)->unk_CC;
                    third_shade = ((S_800C55F4_1 *)scratch)->unk_C8.s;
                    third_base_shade -= third_height;
                    third_delta -= third_shade;
                    third_delta <<= 5;
                    third_shade = third_base_shade - third_delta;
                    if (third_shade < 0x20) {
                        third_shade = 0x20;
                    } else if (third_shade >= 0x100) {
                        third_shade = 0xFF;
                    }
                    {
                        s32 shade_arg;

                        shade_arg = (s32)(s16)third_shade;
                        ASM_KEEP_DEP_NV(shade_arg, third_shade);
                        func_8004CECC(((S_800C55F4_8 *)params)->unk_30,
                                      shade_arg, 0xFF,
                                      record + 0x14);
                    }
                }

                func_800666B8(record);
                packet = record;
                packet_flags = ((S_800C55F4_4 *)packet_code)->unk_00;
                record += 0x1C;
                ((S_800C55F4_4 *)packet_code)->unk_00 = packet_flags | 2;
                packet_code += 0x1C;
                ASM_KEEP(packet_code);
                packet_code += 0xC;
                func_8006658C(((S_800C55F4_1 *)scratch)->unk_20 +
                              (((S_800C55F4_1 *)scratch)->unk_C0.s << 2), packet);

                ((S_800C55F4_2 *)mesh_data)->unk_14 &= 0x7FFF;
                func_80067F20(record, 0, 0, 0, 0);
                packet = record;
                record += 0xC;
                func_8006658C(((S_800C55F4_1 *)scratch)->unk_20 +
                              (((S_800C55F4_1 *)scratch)->unk_C0.s << 2), packet);
            }
        }

        face_flags = ((S_800C55F4_7 *)face_end)->unk_00;
        if (face_flags >= 0) {
            face_end += 0xC;
            face += 0xC;
            continue;
        }
        break;
    }
    func_80064A40();
    state_ptr = D_80083160;
    ASM_KEEP(state_ptr);
    ((S_800C55F4_10 *)(((S_800C55F4_9 *)state_ptr)->unk_00))->unk_8D0 = record;
}
