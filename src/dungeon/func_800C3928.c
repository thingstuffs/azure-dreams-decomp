#include "common.h"

typedef struct S_800C9088_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x4];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C9088_0;   /* object in func_800C9088 */

typedef struct S_800C9088_1 {
    u8 pad_00[0x20];
    union { u8 * s; void * u; } unk_20;   /* accessed as both */
    u8 pad_24[0xC];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0xE];
    s32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    s32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s32 unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    s32 unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    s32 unk_C0;
    u8 pad_C4[0x50];
    volatile s32 unk_114;
} S_800C9088_1;   /* scratch in func_800C9088 */

typedef struct S_800C9088_2 {
    u8 unk_00;
    u8 pad_01[0x1];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x3154];
    u8 * unk_3160;
} S_800C9088_2;   /* ptr_s0 in func_800C9088 */

typedef struct S_800C9088_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C9088_3;   /* state in func_800C9088 */

typedef struct S_800C9088_4 {
    u8 * unk_00;
    u8 * unk_04;
    u8 * unk_08;
} S_800C9088_4;   /* descriptor in func_800C9088 */

typedef struct S_800C9088_5 {
    u16 unk_00;
} S_800C9088_5;   /* indices in func_800C9088 */

typedef struct S_800C9088_6 {
    s32 unk_00;
} S_800C9088_6;   /* table + next_index * 8 in func_800C9088 */

typedef struct S_800C9088_7 {
    s32 unk_00;
} S_800C9088_7;   /* word2_ptr in func_800C9088 */

typedef struct S_800C9088_8 {
    s32 unk_00;
} S_800C9088_8;   /* word3_ptr in func_800C9088 */

typedef struct S_800C9088_9 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800C9088_9;   /* table + half_index * 8 in func_800C9088 */

typedef struct S_800C9088_10_pre {
    u8 unk_00;
} S_800C9088_10_pre;   /* the 0x1 bytes before ptr_s1 in func_800C9088, addressed as ptr_s1[-1] */

typedef struct S_800C9088_10 {
    s8 unk_00;
} S_800C9088_10;   /* ptr_s1 in func_800C9088 */

typedef struct S_800C9088_11 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C9088_11;   /* *(u8 **)state_base in func_800C9088 */

typedef struct S_800C9088_12 {
    s32 unk_00;
} S_800C9088_12;   /* table + ((S_800C9088_5 *)indices)->unk_00 * 8 in func_800C9088 */

typedef struct S_800C9088_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800C9088_13;   /* table + (*(u16 *)((u8 *)ptr_s1 + -0x1D)) * 8 in func_800C9088 */



typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {
    MATRIX matrix;
    u16 saved_arg3;
    u16 pad;
    u32 reserved;
} MATRIX_LOCAL;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064B90(void *, void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065034(void *, void *, void *);
extern s32 func_80065480(s32, s32, s32);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065AB0(u16, void *);
extern void func_80065C50(u16, void *);
extern void func_80065DF0(u16, void *);
extern void func_8006658C(void *, void *);
extern void func_8006671C(void *);
extern u8 D_80083160[];

/* Transform, shade, and enqueue visible textured quads for the model. */
void func_800C9088(void *parent_matrix, void *translation, void *model, s16 depth_bias)
{
    u8 *record_end = parent_matrix;
    u8 *packet_code = translation;
    u8 *object = model;
    register u8 *scratch ASM_REG("$18");
    u8 *indices;
    register u8 *positions ASM_REG("$20");
    u8 *normals;
    register u8 *packet ASM_REG("$19");
    u8 *base_color;
    u8 *state;
    u8 *descriptor;
    u8 *vertex0;
    u8 *vertex1;
    u8 *queued_packet;
    u8 *vertex2;
    u8 *vertex3;
    s32 vertex_xy;
    u32 vertex_index;
    u32 last_index;
    s32 vertex2_xy;
    s32 vertex3_xy;
    u32 z_index;
    u16 vertex_z;
    u16 vertex3_z;
    u8 *vertex2_pos;
    u8 *vertex3_pos;
    register u8 *screen_pos ASM_REG("$2");
    s32 depth;
    s32 winding;
    s32 flags;
    u16 scale_x;
    MATRIX_LOCAL saved_transform;
    s32 screen_xy0, screen_xy1, screen_xy2;


    saved_transform.saved_arg3 = depth_bias;
    func_800649A0();

    scale_x = ((S_800C9088_0 *)object)->unk_1C;
    scratch = (u8 *)0x1F800000;
    ((S_800C9088_1 *)scratch)->unk_30 = scale_x;
    ((S_800C9088_1 *)scratch)->unk_34 = ((S_800C9088_0 *)object)->unk_1E;
    ((S_800C9088_1 *)scratch)->unk_38 = ((S_800C9088_0 *)object)->unk_20;
    ((S_800C9088_1 *)scratch)->unk_40 = ((S_800C9088_2 *)packet_code)->unk_02;
    ((S_800C9088_1 *)scratch)->unk_44 = ((S_800C9088_2 *)packet_code)->unk_06;
    ((S_800C9088_1 *)scratch)->unk_48 = ((S_800C9088_2 *)packet_code)->unk_0A;

    func_80064AE0(&saved_transform.matrix);

    ((S_800C9088_1 *)scratch)->unk_60 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_58 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_50 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_5E = 0;
    ((S_800C9088_1 *)scratch)->unk_5C = 0;
    ((S_800C9088_1 *)scratch)->unk_5A = 0;
    ((S_800C9088_1 *)scratch)->unk_56 = 0;
    ((S_800C9088_1 *)scratch)->unk_54 = 0;
    ((S_800C9088_1 *)scratch)->unk_52 = 0;

    func_80065AB0(((S_800C9088_0 *)object)->unk_16, scratch + 0x50);
    func_80065DF0(((S_800C9088_0 *)object)->unk_1A, scratch + 0x50);
    func_80065C50(((S_800C9088_0 *)object)->unk_18, scratch + 0x50);

    packet_code = (u8 *)0x80080000;
    if (((S_800C9088_0 *)object)->unk_14 & 1) {
        ((S_800C9088_1 *)scratch)->unk_30 = -((S_800C9088_1 *)scratch)->unk_30;
    }
    if (((S_800C9088_0 *)object)->unk_14 & 2) {
        ((S_800C9088_1 *)scratch)->unk_34 = -((S_800C9088_1 *)scratch)->unk_34;
    }

    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064B90(scratch + 0x50, scratch + 0x40);
    func_80064840(scratch + 0x50, record_end, scratch + 0xD0);
    func_80064840(&saved_transform.matrix, scratch + 0xD0, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    state = ((S_800C9088_2 *)packet_code)->unk_3160;
    base_color = object + 0xC;
    ((S_800C9088_1 *)scratch)->unk_20.s = state + 0xB0;
    packet = ((S_800C9088_3 *)state)->unk_8D0;
    packet_code = packet + 7;
    ((S_800C9088_0 *)object)->unk_14 |= 0x8000;

    descriptor = ((S_800C9088_0 *)object)->unk_08;
    indices = ((S_800C9088_4 *)descriptor)->unk_00;
    positions = ((S_800C9088_4 *)descriptor)->unk_04;
    normals = ((S_800C9088_4 *)descriptor)->unk_08;
    record_end = indices + 0x1F;


next_record:
    vertex_xy = ((S_800C9088_12 *)(positions + ((S_800C9088_5 *)indices)->unk_00 * 8))->unk_00;
    ASM_KEEP(vertex_xy);
    vertex_index = (*(u16 *)((u8 *)record_end + -0x1D));
    ASM_KEEP(vertex_index);
    ((S_800C9088_1 *)scratch)->unk_70 = vertex_xy;
    vertex_xy = ((S_800C9088_6 *)(positions + vertex_index * 8))->unk_00;
    vertex_index = (*(u16 *)((u8 *)record_end + -0x1B));
    ASM_KEEP(vertex_index);
    vertex2_pos = (u8 *)(vertex_index * 8 + (u32)positions);
    ((S_800C9088_1 *)scratch)->unk_78 = vertex_xy;
    last_index = (*(u16 *)((u8 *)record_end + -0x19));
    vertex2_xy = ((S_800C9088_7 *)vertex2_pos)->unk_00;
    vertex3_pos = (u8 *)(last_index * 8 + (u32)positions);
    ((S_800C9088_1 *)scratch)->unk_80 = vertex2_xy;
    z_index = ((S_800C9088_5 *)indices)->unk_00;
    vertex3_xy = ((S_800C9088_8 *)vertex3_pos)->unk_00;

    vertex_z = ((S_800C9088_9 *)(positions + z_index * 8))->unk_04;
    ((S_800C9088_1 *)scratch)->unk_74 = vertex_z;

    vertex_z = ((S_800C9088_13 *)(positions + (*(u16 *)((u8 *)record_end + -0x1D)) * 8))->unk_04;
    vertex0 = scratch + 0x70;
    ((S_800C9088_1 *)scratch)->unk_7C = vertex_z;

    z_index = (*(u16 *)((u8 *)record_end + -0x1B));
    vertex1 = scratch + 0x78;
    vertex_z = ((S_800C9088_9 *)(positions + z_index * 8))->unk_04;
    vertex2 = scratch + 0x80;
    ((S_800C9088_1 *)scratch)->unk_84 = vertex_z;

    z_index = (*(u16 *)((u8 *)record_end + -0x19));
    vertex3 = scratch + 0x88;
    ((S_800C9088_1 *)scratch)->unk_88 = vertex3_xy;
    vertex3_z = ((S_800C9088_9 *)(positions + z_index * 8))->unk_04;

    screen_pos = packet + 8;
    ((S_800C9088_1 *)scratch)->unk_8C = vertex3_z;
    ASM_JALDELAY_PIN(vertex3_z);
    depth = func_80065590(vertex0, vertex1,
                              vertex2, vertex3,
                              screen_pos, packet + 0x14,
                              packet + 0x20, packet + 0x2C,
                              scratch + 0x90, scratch + 0x94);
    ((S_800C9088_1 *)scratch)->unk_C0 = depth;

    flags = ((S_800C9088_0 *)object)->unk_14 & 3;
    if (flags == 1) {
        goto mirrored_x;
    }
    if (flags < 2) {
        if (flags == 0) {
            goto unmirrored;
        }
        goto mirrored_xy;
    }
    if (flags == 2) {
        goto mirrored_y;
    }
    goto mirrored_xy;

unmirrored:
    screen_xy0 = (*(s32 *)((u8 *)packet_code + 1));
    screen_xy1 = (*(s32 *)((u8 *)packet_code + 0xD));
    screen_xy2 = (*(s32 *)((u8 *)packet_code + 0x19));
    goto check_winding;
mirrored_x:
    screen_xy0 = (*(s32 *)((u8 *)packet_code + 0xD));
    screen_xy1 = (*(s32 *)((u8 *)packet_code + 1));
    screen_xy2 = (*(s32 *)((u8 *)packet_code + 0x19));
    goto check_winding;
mirrored_y:
    screen_xy0 = (*(s32 *)((u8 *)packet_code + 0x19));
    screen_xy1 = (*(s32 *)((u8 *)packet_code + 0xD));
    screen_xy2 = (*(s32 *)((u8 *)packet_code + 1));
    goto check_winding;

mirrored_xy:
    screen_xy0 = (*(s32 *)((u8 *)packet_code + 0x19));
    screen_xy1 = (*(s32 *)((u8 *)packet_code + 1));
    screen_xy2 = (*(s32 *)((u8 *)packet_code + 0xD));
check_winding:
    winding = func_80065480(screen_xy0, screen_xy1, screen_xy2);
    ((S_800C9088_1 *)scratch)->unk_114 = winding;
    if (((S_800C9088_1 *)scratch)->unk_114 > 0) {
        register u16 raw_depth_bias ASM_REG("$8");
        register s32 signed_depth_bias ASM_REG("$3");

        raw_depth_bias = saved_transform.saved_arg3;
        ASM_KEEP(raw_depth_bias);
        signed_depth_bias = (s16)raw_depth_bias;
        ((S_800C9088_1 *)scratch)->unk_C0 -= signed_depth_bias;
        if ((u32)((S_800C9088_1 *)scratch)->unk_C0 < 0x1E0) {
            func_80065034(normals + (*(u16 *)((u8 *)record_end + -0xF)) * 8,
                          base_color, packet + 4);
            func_80065034(normals + (*(u16 *)((u8 *)record_end + -0xD)) * 8,
                          base_color, packet + 0x10);
            func_80065034(normals + (*(u16 *)((u8 *)record_end + -0xB)) * 8,
                          base_color, packet + 0x1C);
            func_80065034(normals + (*(u16 *)((u8 *)record_end + -9)) * 8,
                          base_color, packet + 0x28);

            (*(s32 *)((u8 *)packet_code + 5)) = (*(s32 *)((u8 *)record_end + -0x17));
            (*(u16 *)((u8 *)packet_code + 7)) += ((S_800C9088_0 *)object)->unk_12;
            (*(s32 *)((u8 *)packet_code + 0x11)) = (*(s32 *)((u8 *)record_end + -0x13));
            if (((S_800C9088_0 *)object)->unk_10 != 0) {
                (*(u16 *)((u8 *)packet_code + 0x13)) =
                    ((*(u16 *)((u8 *)packet_code + 0x13)) & 0xFF9F) +
                    ((S_800C9088_0 *)object)->unk_10;
            }
            (*(u16 *)((u8 *)packet_code + 0x1D)) = (*(u16 *)((u8 *)record_end + -5));
            (*(u16 *)((u8 *)packet_code + 0x29)) = (*(u16 *)((u8 *)record_end + -3));

            func_8006671C(packet);
            flags = ((S_800C9088_0 *)object)->unk_14;
            if (flags & 8) {
                if (flags & 4) {
                    ((S_800C9088_2 *)packet_code)->unk_00 |= 2;
                }
            }

            queued_packet = packet;
            ASM_KEEP_DEP_NV(queued_packet, packet_code);
            packet_code += 0x34;
            func_8006658C((u8 *)((S_800C9088_1 *)scratch)->unk_20.u +
                              ((S_800C9088_1 *)scratch)->unk_C0 * 4,
                          queued_packet);
            packet += 0x34;
            ((S_800C9088_0 *)object)->unk_14 &= 0x7FFF;
        }
    }

    if (((S_800C9088_10_pre *)record_end)[-1].unk_00 != 1 || ((S_800C9088_10 *)record_end)->unk_00 >= 0) {
        record_end += 0x20;
        indices += 0x20;
        goto next_record;
    }

    func_80064A40();
    {
        register u8 *state_base ASM_REG("$8") = D_80083160;
        ASM_KEEP(state_base);
        ((S_800C9088_11 *)(*(u8 **)state_base))->unk_8D0 = packet;
    }
}
