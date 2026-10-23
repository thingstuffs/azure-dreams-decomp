#include "shared/gpu_packets.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"

typedef void (*Callback)(s32, void *, void *, void *);

extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void RotMatrix(void *, void *);
extern void AddPrim(void *, void *);

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
} S_800D07C8_0;   /* scratch in transform_sprite_parts_to_quads */

   /* global_page->table[0] in transform_sprite_parts_to_quads */

typedef struct S_800D07C8_4 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_800D07C8_4;

typedef struct S_800D07C8_5_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800D07C8_5_pre;

typedef struct S_800D07C8_5 {
    u8 unk_00;
    u8 pad_01[0x10];
    u8 unk_11;
    u8 pad_12[0xC];
    u8 unk_1E;
    u8 pad_1F[0xA];
    u8 unk_29;
    u8 unk_2A;
} S_800D07C8_5;

   /* table[0] in transform_sprite_parts_to_quads */

/* Transform sprite parts into textured quads, queue visible quads, and invoke part callbacks. */
void transform_sprite_parts_to_quads(s32 context, ObjectPosition *position, SpriteFrameState *sprite, s16 depth_bias) {
    u8 matrix[32];
    u8 *scratch = (u8 *)0x1F800000;
    u8 *part_uv;
    u8 *part;
    u8 *packet;
    s16 vertex_x;
    s16 vertex_y;
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
    u8 **table = ((u8 * *)(&g_game_work));
    Callback callback;

    ((S_800D07C8_0 *)scratch)->unk_20.p = table[0] + 0xB0;
    ((S_800D07C8_0 *)scratch)->unk_E4 = position->x.w.i;
    ((S_800D07C8_0 *)scratch)->unk_E8 = position->y.w.i;
    ((S_800D07C8_0 *)scratch)->unk_EC = position->z.w.i;
    ((S_800D07C8_0 *)scratch)->unk_8C = 0;
    ((S_800D07C8_0 *)scratch)->unk_84 = 0;
    ((S_800D07C8_0 *)scratch)->unk_7C = 0;
    ((S_800D07C8_0 *)scratch)->unk_74 = 0;
    packet = ((GpuContext *)(table[0]))->packetCursor;
    sprite->flags |= 0x8000;
    PushMatrix();
    ((S_800D07C8_0 *)scratch)->unk_108 = sprite->offset_x;
    ((S_800D07C8_0 *)scratch)->unk_10A = sprite->offset_y;
    ((S_800D07C8_0 *)scratch)->unk_30 = sprite->scale_x * 2;
    ((S_800D07C8_0 *)scratch)->unk_34 = sprite->scale_y * 2;
    ((S_800D07C8_0 *)scratch)->unk_38 = 0;
    ((S_800D07C8_0 *)scratch)->unk_100 = sprite->angle_x;
    ((S_800D07C8_0 *)scratch)->unk_104 = sprite->angle_z;
    ((S_800D07C8_0 *)scratch)->unk_102 = sprite->angle_y;
    RotMatrix(scratch + 0x100, scratch + 0xD0);
    ReadRotMatrix(matrix);
    CompMatrix(matrix, scratch + 0xD0, scratch + 0x50);
    ScaleMatrix(scratch + 0x50, scratch + 0x30);
    SetTransMatrix(scratch + 0x50);
    SetRotMatrix(scratch + 0x50);

    part = *(u8 * *)&sprite->source;
    ((S_800D07C8_0 *)scratch)->unk_24 = sprite->flags;
    for (;;) {
        part_uv = part + 8;
        if (!(((S_800D07C8_4 *)part)->unk_00.u & 0x20)) {
            ((S_800D07C8_0 *)scratch)->unk_08.s32 = (*(u8 *)((u8 *)part_uv + 0));
            ((S_800D07C8_0 *)scratch)->unk_0C.s32 = (*(u8 *)((u8 *)part_uv + 1));
            ((S_800D07C8_0 *)scratch)->unk_10.s32 = (*(u8 *)((u8 *)part_uv + 2));
            ((S_800D07C8_0 *)scratch)->unk_14.s32 = (*(u8 *)((u8 *)part_uv + 3));
            if ((((S_800D07C8_4 *)part)->unk_00.u ^ ((S_800D07C8_0 *)scratch)->unk_24) & 1) {
                vertex_x = (0 - (s8)(*(u8 *)((u8 *)part_uv + -6))) - ((S_800D07C8_0 *)scratch)->unk_108;
                ((S_800D07C8_0 *)scratch)->unk_80 = vertex_x;
                ((S_800D07C8_0 *)scratch)->unk_70 = vertex_x;
                vertex_x -= ((S_800D07C8_0 *)scratch)->unk_10.u16;
                ((S_800D07C8_0 *)scratch)->unk_88 = vertex_x;
                ((S_800D07C8_0 *)scratch)->unk_78 = vertex_x;
            } else {
                vertex_x = (s8)(*(u8 *)((u8 *)part_uv + -6)) - ((S_800D07C8_0 *)scratch)->unk_108;
                ((S_800D07C8_0 *)scratch)->unk_80 = vertex_x;
                ((S_800D07C8_0 *)scratch)->unk_70 = vertex_x;
                vertex_x = vertex_x + ((S_800D07C8_0 *)scratch)->unk_10.u16;
                ((S_800D07C8_0 *)scratch)->unk_88 = vertex_x;
                ((S_800D07C8_0 *)scratch)->unk_78 = vertex_x;
            }
            if ((((S_800D07C8_4 *)part)->unk_00.u ^ ((S_800D07C8_0 *)scratch)->unk_24) & 2) {
                vertex_y = (0 - (s8)(*(u8 *)((u8 *)part_uv + -5))) - ((S_800D07C8_0 *)scratch)->unk_10A;
                ((S_800D07C8_0 *)scratch)->unk_7A = vertex_y;
                ((S_800D07C8_0 *)scratch)->unk_72 = vertex_y;
                vertex_y -= ((S_800D07C8_0 *)scratch)->unk_14.u16;
                ((S_800D07C8_0 *)scratch)->unk_8A = vertex_y;
                ((S_800D07C8_0 *)scratch)->unk_82 = vertex_y;
            } else {
                vertex_y = (s8)(*(u8 *)((u8 *)part_uv + -5)) - ((S_800D07C8_0 *)scratch)->unk_10A;
                ((S_800D07C8_0 *)scratch)->unk_7A = vertex_y;
                ((S_800D07C8_0 *)scratch)->unk_72 = vertex_y;
                vertex_y = vertex_y + ((S_800D07C8_0 *)scratch)->unk_14.u16;
                ((S_800D07C8_0 *)scratch)->unk_8A = vertex_y;
                ((S_800D07C8_0 *)scratch)->unk_82 = vertex_y;
            }

            depth = (RotAverage4(scratch + 0x70, scratch + 0x78,
                                   scratch + 0x80, scratch + 0x88,
                                   packet + 8, packet + 0x14,
                                   packet + 0x20, packet + 0x2C,
                                   scratch + 0x90, scratch + 0x94) - depth_bias) - 6;
            ((S_800D07C8_0 *)scratch)->unk_C0 = depth;
            if (depth < 0x1E0U) {
                vertex_0_visible = 0;
                if ((u32)(((*(u16 *)(packet + 0x8)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)(packet + 0xA)) + 0x20) & 0xFFFF);
                    vertex_0_visible = screen_y < 0x121U;
                }
                vertex_1_visible = 0;
                if ((u32)(((*(u16 *)(packet + 0x14)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)(packet + 0x16)) + 0x20) & 0xFFFF);
                    vertex_1_visible = screen_y < 0x121U;
                }
                vertex_2_visible = 0;
                first_pair_visible = vertex_0_visible | vertex_1_visible;
                if ((u32)(((*(u16 *)(packet + 0x20)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)(packet + 0x22)) + 0x20) & 0xFFFF);
                    vertex_2_visible = screen_y < 0x121U;
                }
                vertex_3_visible = 0;
                first_three_visible = first_pair_visible | vertex_2_visible;
                if ((u32)(((*(u16 *)(packet + 0x2C)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)(((*(u16 *)(packet + 0x2E)) + 0x20) & 0xFFFF);
                    vertex_3_visible = screen_y < 0x121U;
                }
                if ((first_three_visible | vertex_3_visible) != 0) {
                    sprite->flags &= 0x7FFF;
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
                        (*(s16 *)(packet + 0xE)) = sprite->clut;
                    } else {
                        (*(s16 *)(packet + 0xE)) = sprite->clut + (*(u16 *)((u8 *)part_uv
                            + -2));
                    }
                    (*(s16 *)(packet + 0xC)) = ((S_800D07C8_0 *)scratch)->unk_0C.u16
                        + ((S_800D07C8_0 *)scratch)->unk_08.u16;
                    (*(s16 *)(packet + 0x18)) = ((S_800D07C8_0 *)scratch)->unk_0C.u16
                        + ((S_800D07C8_0 *)scratch)->unk_10.u16;
                    {
                        s32 tpage_base = sprite->tpage_abr;
                        s32 tpage;
                        if (tpage_base != 0) {
                            tpage = tpage_base + ((*(u16 *)((u8 *)part_uv + -4)) & 0xFF9F);
                        } else {
                            tpage = (*(u16 *)((u8 *)part_uv + -4));
                        }
                        (*(u16 *)(packet + 0x1A)) = tpage;
                    }
                    (*(s16 *)(packet + 0x24)) = ((S_800D07C8_0 *)scratch)->unk_14.u16
                        + ((S_800D07C8_0 *)scratch)->unk_08.u16;
                    (*(s16 *)(packet + 0x30)) = ((S_800D07C8_0 *)scratch)->unk_14.u16
                        + ((S_800D07C8_0 *)scratch)->unk_10.u16;
                    if ((*(s16 *)(packet + 0x8)) > (*(s16 *)(packet + 0x2C))) {
                        ((S_800D07C8_5 *)(packet + 7))->unk_11--;
                        ((S_800D07C8_5 *)(packet + 7))->unk_29--;
                    }
                    if ((*(s16 *)(packet + 0xA)) > (*(s16 *)(packet + 0x2E))) {
                        ((S_800D07C8_5 *)(packet + 7))->unk_1E--;
                        ((S_800D07C8_5 *)(packet + 7))->unk_2A--;
                    }
                    color = sprite->color.word;
                    (*(s32 *)(packet + 0x28)) = 0;
                    (*(s32 *)(packet + 0x1C)) = 0;
                    ((S_800D07C8_5_pre *)(packet + 3))->unk_00 = 0xC;
                    (*(s32 *)(packet + 0x10)) = color;
                    (*(s32 *)(packet + 0x4)) = color;
                    part_command = (*(u8 *)((u8 *)part_uv + -7));
                    ((S_800D07C8_5 *)(packet + 7))->unk_00 = part_command;
                    sprite_flags = ((S_800D07C8_0 *)scratch)->unk_24;
                    if (sprite_flags & 8) {
                        draw_command = sprite_flags & 4;
                        if (draw_command == 0) {
                            draw_command = part_command & 0xFD;
                        } else {
                            draw_command = part_command | 2;
                        }
                        ((S_800D07C8_5 *)(packet + 7))->unk_00 = draw_command;
                    }
                    AddPrim(((S_800D07C8_0 *)scratch)->unk_20.p2 + (((S_800D07C8_0 *)scratch)->unk_C0 * 4),
                        packet);
                    packet += 0x34;
                                }
            }
        } else {
            callback = (*(Callback *)((u8 *)part_uv + 0));
            if (callback != 0) {
                callback(context, position, sprite, part);
            }
        }

        if (((S_800D07C8_4 *)part)->unk_00.s >= 0) {
            part += 0xC;
        } else {
            break;
        }
    }
    PopMatrix();
    ((GpuContext *)(table[0]))->packetCursor = packet;
}
