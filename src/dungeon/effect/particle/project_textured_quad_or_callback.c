#include "sdk/libc.h"
#include "shared/audio_commands.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "sdk/libgpu.h"
#include "dungeon/actor/status.h"
/* Effect quad projection, child particle updates, and a moving status-effect sequence. */

struct ObjectPosition;
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct S_800259D8_2;
void update_animated_effect_sprite(void *, void *, struct S_800259D8_2 *);
void (*const dungeon_1894800_entry)(void *, void *, struct S_800259D8_2 *) = update_animated_effect_sprite;
const u8 no_effect_target_prefix[48] = { 0x82, 0x73, 0x82, 0x88, 0x82, 0x85, 0x82, 0x92, 0x82, 0x85, 0x81, 0x40, 0x82, 0x97, 0x82, 0x81, 0x82, 0x93, 0x81, 0x40, 0x82, 0x8E, 0x82, 0x8F, 0x81, 0x40, 0x82, 0x85, 0x82, 0x86, 0x82, 0x86, 0x82, 0x85, 0x82, 0x83, 0x82, 0x94, 0x81, 0x40, 0x82, 0x8F, 0x82, 0x8E, 0x81, 0x40, 0x00, 0x00 };
const u8 D_80024034[4] = { 0x81, 0x44, 0x00, 0x00 };
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"

typedef s32 M2C_UNK;

extern const u8 no_effect_target_prefix[48];
extern const u8 D_80024034[4];
extern u8 D_800E1C8A[38];

extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void adjust_source_value_and_finalize(void *, void *);
#include "dungeon/effect/screen.h"
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 get_random_scaled_value(s16 input_value);

/* Applies a directional effect and reports the result for flagged entities. */
void apply_random_duration_actor_status(void *entity, s32 direction, void *unused)
{
    void *message_start;
    void *message_end;

    if (try_trigger_target_record_effect(entity, 2, unused) == 0) {
        /*
         * BUG: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success instead prints the no-effect message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if (set_or_clear_actor_status_slot(
                entity, STATUS_WATER_PROTECT,
                ((get_random_scaled_value(direction & 0xFF) + 4) << 24) >> 24) << 16) {
            if (*(s32 *)((u8 *)entity + 0x14) & ACTOR_PARTY_MEMBER) {
                adjust_source_value_and_finalize(entity, D_800E1C8A);
                return;
            }
        } else if (*(s32 *)((u8 *)entity + 0x14) & ACTOR_PARTY_MEMBER) {
            message_end = get_unused_text_buffer();
            message_start = message_end;
            message_end = expand_text_control_codes(&no_effect_target_prefix, message_end);
            message_end = append_entity_display_text(entity, message_end);
            message_end = expand_text_control_codes(&D_80024034, message_end);
            clear_byte_and_advance(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef void (*Callback)(void *, void *, void *, void *);

typedef struct S_81874988_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x8];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
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
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_81874988_0;   /* scratch in project_textured_quad_or_callback */

   /* global_value in project_textured_quad_or_callback */

typedef struct S_81874988_4 {
    u8 pad_00[0x50];
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
} S_81874988_4;   /* arg0 in project_textured_quad_or_callback */

typedef struct S_81874988_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union { u16 u16; u8 u8; } unk_14;   /* accessed as both */
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_1C;   /* overlapping accesses */
    u8 pad_1E[0x2];
    union { u16 u; s16 s; } unk_20;   /* accessed as both */
    union { u16 u; s16 s; } unk_22;   /* accessed as both */
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_81874988_5;   /* packet in project_textured_quad_or_callback */

extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void RotMatrix(void *, void *);

/* Projects a textured quad and queues it for drawing, or invokes its texture callback. */
void project_textured_quad_or_callback(void *quad, ObjectPosition *position, SpriteFrameState *material, s16 depth_bias)
{
    u8 *render_state = g_game_work.draw_buffer;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u32 tex_attr;
    u8 *texture;
    Callback callback;
    s32 depth_index;
    u16 draw_flags;
    s32 tex_adjust;
    u8 tex_flags;
    MATRIX view_matrix;

    ((S_81874988_0 *)scratch)->unk_24.p = render_state + 0xB0;
    ((S_81874988_0 *)scratch)->unk_88 = position->x.w.i;
    ((S_81874988_0 *)scratch)->unk_8C = position->y.w.i;
    ((S_81874988_0 *)scratch)->unk_90 = position->z.w.i;

    packet = ((GpuContext *)render_state)->packetCursor;
    ((GpuContext *)render_state)->packetCursor = packet + 0x28;

    material->flags |= 0x8000;
    PushMatrix();

    ((S_81874988_0 *)scratch)->unk_3C = 0x2000;
    ((S_81874988_0 *)scratch)->unk_38 = 0x2000;
    ((S_81874988_0 *)scratch)->unk_34 = 0x2000;
    ((S_81874988_0 *)scratch)->unk_A4 = material->angle_x;
    ((S_81874988_0 *)scratch)->unk_A8 = material->angle_z;
    ((S_81874988_0 *)scratch)->unk_A6 = material->angle_y;
    RotMatrix(scratch + 0xA4, scratch + 0x74);
    ReadRotMatrix(&view_matrix);
    CompMatrix(&view_matrix, scratch + 0x74, scratch + 0x54);
    ScaleMatrix(scratch + 0x54, scratch + 0x34);
    SetTransMatrix(scratch + 0x54);
    SetRotMatrix(scratch + 0x54);

    texture = material->source;
    ((S_81874988_0 *)scratch)->unk_28 = material->flags;

    if (!(texture[0] & 0x20)) {
        ((S_81874988_0 *)scratch)->unk_0C = texture[8];
        ((S_81874988_0 *)scratch)->unk_10 = texture[9];
        ((S_81874988_0 *)scratch)->unk_14 = texture[0xA];
        ((S_81874988_0 *)scratch)->unk_18 = texture[0xB];

        ((S_81874988_0 *)scratch)->unk_B0 = ((S_81874988_4 *)quad)->unk_50;
        ((S_81874988_0 *)scratch)->unk_B8 = ((S_81874988_4 *)quad)->unk_52;
        ((S_81874988_0 *)scratch)->unk_C0 = ((S_81874988_4 *)quad)->unk_54;
        ((S_81874988_0 *)scratch)->unk_C8 = ((S_81874988_4 *)quad)->unk_56;
        ((S_81874988_0 *)scratch)->unk_B2 = ((S_81874988_4 *)quad)->unk_58;
        ((S_81874988_0 *)scratch)->unk_BA = ((S_81874988_4 *)quad)->unk_5A;
        ((S_81874988_0 *)scratch)->unk_C2 = ((S_81874988_4 *)quad)->unk_5C;
        ((S_81874988_0 *)scratch)->unk_CA = ((S_81874988_4 *)quad)->unk_5E;
        ((S_81874988_0 *)scratch)->unk_B4 = ((S_81874988_4 *)quad)->unk_60;
        ((S_81874988_0 *)scratch)->unk_BC = ((S_81874988_4 *)quad)->unk_62;
        ((S_81874988_0 *)scratch)->unk_C4 = ((S_81874988_4 *)quad)->unk_64;
        ((S_81874988_0 *)scratch)->unk_CC = ((S_81874988_4 *)quad)->unk_66;

        depth_index = RotAverage4(scratch + 0xB0, scratch + 0xB8,
                              scratch + 0xC0, scratch + 0xC8,
                              packet + 8, packet + 0x10,
                              packet + 0x18, packet + 0x20,
                              scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
        ((S_81874988_0 *)scratch)->unk_100 = depth_index;

        if ((u32)depth_index < 0x1E0) {
            if (
                (((u16)(((S_81874988_5 *)packet)->unk_08.u + 0x20) < 0x181) &&
                 ((u16)(((S_81874988_5 *)packet)->unk_0A.u + 0x20) < 0x121)) |
                (((u16)(((S_81874988_5 *)packet)->unk_10 + 0x20) < 0x181) &&
                 ((u16)(((S_81874988_5 *)packet)->unk_12 + 0x20) < 0x121)) |
                (((u16)(((S_81874988_5 *)packet)->unk_18 + 0x20) < 0x181) &&
                 ((u16)(((S_81874988_5 *)packet)->unk_1A + 0x20) < 0x121)) |
                (((u16)(((S_81874988_5 *)packet)->unk_20.u + 0x20) < 0x181) &&
                 ((u16)(((S_81874988_5 *)packet)->unk_22.u + 0x20) < 0x121))
                ) {
                ((S_81874988_5 *)packet)->unk_00.at03.v = 9;
                ((S_81874988_5 *)packet)->unk_04.at03.v = 0x2C;
                material->flags &= 0x7FFF;

                ((S_81874988_0 *)scratch)->unk_14 += ((S_81874988_0 *)scratch)->unk_0C;
                if (((S_81874988_0 *)scratch)->unk_14 & 0x100) {
                    ((S_81874988_0 *)scratch)->unk_14--;
                }
                ((S_81874988_0 *)scratch)->unk_18 += ((S_81874988_0 *)scratch)->unk_10;
                if (((S_81874988_0 *)scratch)->unk_18 & 0x100) {
                    ((S_81874988_0 *)scratch)->unk_18--;
                }
                ((S_81874988_0 *)scratch)->unk_10 <<= 8;
                ((S_81874988_0 *)scratch)->unk_18 <<= 8;

                tex_adjust = material->clut;
                if (tex_adjust) {
                    if (((S_81874988_0 *)scratch)->unk_28 & 0x100) {
                        ((S_81874988_5 *)packet)->unk_0E = tex_adjust;
                    } else {
                        tex_attr = tex_adjust + (*(u16 *)((u8 *)texture + 6));
                        (*(u16 *)((u8 *)packet + 0xE)) = tex_attr;
                    }
                } else {
                    (*(u16 *)((u8 *)packet + 0xE)) = (*(u16 *)((u8 *)texture + 6));
                }

                (*(u16 *)((u8 *)packet + 0xC)) = (*(u16 *)(scratch + 0x10)) +
                                          (*(u16 *)(scratch + 0xC));
                ((S_81874988_5 *)packet)->unk_14.u16 = (*(u16 *)(scratch + 0x10)) +
                                           (*(u16 *)(scratch + 0x14));

                tex_adjust = material->tpage_abr;
                if (tex_adjust) {
                    (*(u16 *)((u8 *)packet + 0x16)) = tex_adjust +
                                   ((*(u16 *)((u8 *)texture + 4)) & 0xFF9F);
                } else {
                    (*(u16 *)((u8 *)packet + 0x16)) = (*(u16 *)((u8 *)texture + 4));
                }

                ((S_81874988_5 *)packet)->unk_1C.at00.v = (*(u16 *)(scratch + 0x18)) +
                                           (*(u16 *)(scratch + 0xC));
                ((S_81874988_5 *)packet)->unk_24.at00.v = (*(u16 *)(scratch + 0x18)) +
                                           (*(u16 *)(scratch + 0x14));

                if (((S_81874988_5 *)packet)->unk_08.s > ((S_81874988_5 *)packet)->unk_20.s) {
                    ((S_81874988_5 *)packet)->unk_14.u8--;
                    ((S_81874988_5 *)packet)->unk_24.at00u.v--;
                }
                if (((S_81874988_5 *)packet)->unk_0A.s > ((S_81874988_5 *)packet)->unk_22.s) {
                    ((S_81874988_5 *)packet)->unk_1C.at01.v--;
                    ((S_81874988_5 *)packet)->unk_24.at01.v--;
                }

                tex_flags = texture[1];
                material->color.c.code = tex_flags;
                draw_flags = ((S_81874988_0 *)scratch)->unk_28;
                if (draw_flags & 8) {
                    material->color.c.code = (draw_flags & 4) ?
                        (tex_flags | 2) : (tex_flags & 0xFD);
                }

                ((S_81874988_5 *)packet)->unk_04.at00.v = *(u32 *)&material->color.word;
                ((S_81874988_5 *)packet)->unk_00.at00.v = (((S_81874988_5 *)packet)->unk_00.at00.v & 0xFF000000) |
                    ((*(u32 *)((u8 *)(((S_81874988_0 *)scratch)->unk_24.p2)
                        + ((S_81874988_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
                (*(u32 *)((u8 *)(((S_81874988_0 *)scratch)->unk_24.p2) + ((S_81874988_0 *)scratch)->unk_100 * 4)) =
                    ((*(u32 *)((u8 *)(((S_81874988_0 *)scratch)->unk_24.p2)
                        + ((S_81874988_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                    ((u32)packet & 0x00FFFFFF);
            }
        }
    } else {
        callback = (*(Callback *)((u8 *)texture + 8));
        if (callback != 0) {
            callback(quad, position, material, texture);
        }
    }
    PopMatrix();
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/object_node.h"

extern void project_textured_quad_or_callback(void *record,struct ObjectPosition *context, SpriteFrameState *data, s16 depth_bias);

/* Retail 81874F04 (project_linked_quad_record).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 project_linked_quad_record(void *record, void *context, void *data) {
    ObjectNodeHeader *node;

    for (;;) {
        project_textured_quad_or_callback(record, context, data, 0);
        node = ((ObjectNodeHeader *)record - 1)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->position;
        data = node->sprite;
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/game_work.h"
typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

s32 rsin(s32);
s32 rcos(s32);
void CompMatrix(void *, void *, void *);
void PushMatrix(void);
void PopMatrix(void);
void ReadRotMatrix(void *);
void ScaleMatrix(void *, void *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
s32 RotAverage4(void *, void *, void *, void *, void *,
                  void *, void *, void *, void *, void *);
void RotMatrix(void *, void *);

/* Draws a textured spherical mesh and adds its visible quads to the ordering table. */
void draw_textured_sphere_mesh(void *mesh, void *position, void *material, u16 depth_bias) {
    s32 view_matrix[8];
    u16 saved_depth_bias;
    u8 *texture;
    s32 column;
    s32 row;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *page;
    u8 *initial_page;
    u32 page_dependency;
    u8 **page_ptr;
    u8 *quad;
    s32 column_count;
    s32 row_count;
    s32 latitude_span;
    s32 latitude_offset;
    s32 next_latitude_offset;
    s32 longitude_offset;
    s32 ring_radius;
    s32 next_ring_radius;
    s32 longitude;
    s32 next_longitude;
    s32 latitude;
    s32 next_latitude;
    s32 depth_index;
    s32 clut;
    s32 tpage;
    s32 uv_end;
    s32 clut_override;
    s32 tpage_override;
    s32 material_flags;
    s32 screen_y;
    s32 corner_0_visible;
    s32 corner_1_visible;
    s32 corner_2_visible;
    s32 corner_3_visible;
    s32 any_corner_visible;
    s32 last_vertex_z;
    u8 texture_flags;
    u8 draw_flags;

    page_ptr = &g_game_work.draw_buffer;
    initial_page = *page_ptr;
    *(u8 **)(scratch + 0x24) = initial_page + 0xB0;
    *(s32 *)(scratch + 0x88) = *(s16 *)((u8 *)position + 2);
    *(s32 *)(scratch + 0x8C) = *(s16 *)((u8 *)position + 6);
    *(s32 *)(scratch + 0x90) = *(s16 *)((u8 *)position + 0xA);
    *(u16 *)((u8 *)material + 0x14) = *(u16 *)((u8 *)material + 0x14) | 0x8000;
    saved_depth_bias = depth_bias;
    PushMatrix();
    *(s32 *)(scratch + 0x3C) = 0x2000;
    *(s32 *)(scratch + 0x38) = 0x2000;
    *(s32 *)(scratch + 0x34) = 0x2000;
    *(u16 *)(scratch + 0xA4) = *(u16 *)((u8 *)material + 0x16);
    *(u16 *)(scratch + 0xA8) = *(u16 *)((u8 *)material + 0x1A);
    *(u16 *)(scratch + 0xA6) = *(u16 *)((u8 *)material + 0x18);
    RotMatrix((u8 *)((u32)scratch | 0xA4), (u8 *)((u32)scratch | 0x74));
    ReadRotMatrix(&view_matrix[0]);
    CompMatrix(&view_matrix[0], (u8 *)((u32)scratch | 0x74), (u8 *)((u32)scratch | 0x54));
    ScaleMatrix((u8 *)((u32)scratch | 0x54), (u8 *)((u32)scratch | 0x34));
    SetTransMatrix((u8 *)((u32)scratch | 0x54));
    SetRotMatrix((u8 *)((u32)scratch | 0x54));
    texture = *(u8 **)((u8 *)material + 8);
    *(u16 *)(scratch + 0x28) = *(u16 *)((u8 *)material + 0x14);
    for (;;) {
        for (row = 0; row < *(s16 *)((u8 *)mesh + 0xC); row++) {
            for (column = 0; column < *(s16 *)((u8 *)mesh + 0xA); column++) {
                *(s32 *)(scratch + 0x0C) = *(u8 *)(texture + 8);
                *(s32 *)(scratch + 0x10) = *(u8 *)(texture + 9);
                *(s32 *)(scratch + 0x14) = *(u8 *)(texture + 10);
                page = *page_ptr;
                *(s32 *)(scratch + 0x18) = *(u8 *)(texture + 11);
                quad = *(u8 **)(page + 0x8D0);
                *(u8 **)(page + 0x8D0) = quad + 0x28;
                column_count = *(s16 *)((u8 *)mesh + 0xA);
                longitude = (column << 0xC) / column_count;
                latitude_span = -*(s16 *)((u8 *)mesh + 0xE);
                row_count = *(s16 *)((u8 *)mesh + 0xC);
                latitude_offset = (latitude_span * row) / row_count;
                next_latitude_offset = (latitude_span * (row + 1)) / row_count;
                longitude_offset = *(s16 *)((u8 *)mesh + 0x10);
                next_longitude = ((column + 1) << 0xC) / column_count;
                longitude = longitude + longitude_offset;
                latitude = latitude_offset + 0x400;
                next_latitude = next_latitude_offset + 0x400;
                if (longitude >= 0x1001) {
                    longitude -= 0x1000;
                }
                if (longitude < 0) {
                    longitude += 0x1000;
                }
                next_longitude = next_longitude + longitude_offset;
                if (next_longitude >= 0x1001) {
                    next_longitude -= 0x1000;
                }
                if (next_longitude < 0) {
                    next_longitude += 0x1000;
                }
                ring_radius = ((*(s32 *)((u8 *)mesh + 0x68) >> 8) * rcos(latitude)) >> 0x14;
                next_ring_radius = ((*(s32 *)((u8 *)mesh + 0x68) >> 8) * rcos(next_latitude)) >> 0x14;
                *(s16 *)(scratch + 0xB0) = (ring_radius * rsin(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xB2) = (ring_radius * rcos(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xB4) = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * rsin(latitude)) >> 0x14);
                *(s16 *)(scratch + 0xB8) = (ring_radius * rsin(next_longitude)) >> 0xC;
                *(s16 *)(scratch + 0xBA) = (ring_radius * rcos(next_longitude)) >> 0xC;
                *(s16 *)(scratch + 0xBC) = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * rsin(latitude)) >> 0x14);
                *(s16 *)(scratch + 0xC0) = (next_ring_radius * rsin(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xC2) = (next_ring_radius * rcos(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xC4) = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * rsin(next_latitude))
                    >> 0x14);
                *(s16 *)(scratch + 0xC8) = (next_ring_radius * rsin(next_longitude)) >> 0xC;
                *(s16 *)(scratch + 0xCA) = (next_ring_radius * rcos(next_longitude)) >> 0xC;
                last_vertex_z = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * rsin(next_latitude)) >> 0x14);
                depth_index = (RotAverage4(scratch + 0xB0, scratch + 0xB8, scratch + 0xC0, scratch + 0xC8, quad + 8,
                    quad + 0x10, quad + 0x18, quad + 0x20, scratch + 0xD0, (*(s16 *)(scratch + 0xCC) = last_vertex_z, (void *)(scratch + 0xD4))) - (s16)saved_depth_bias) - 6;
                *(s32 *)(scratch + 0x100) = depth_index;
                if ((u32)depth_index < 0x1E0U) {
                    corner_0_visible = 0;
                    if ((u32)((*(u16 *)(quad + 8) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0xA) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_0_visible = (u32)screen_y < 0x121U;
                    }
                    corner_1_visible = 0;
                    if ((u32)((*(u16 *)(quad + 0x10) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0x12) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_1_visible = (u32)screen_y < 0x121U;
                    }
                    corner_2_visible = 0;
                    corner_0_visible = corner_0_visible | corner_1_visible;
                    if ((u32)((*(u16 *)(quad + 0x18) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0x1A) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_2_visible = (u32)screen_y < 0x121U;
                    }
                    corner_3_visible = 0;
                    any_corner_visible = corner_0_visible | corner_2_visible;
                    if ((u32)((*(u16 *)(quad + 0x20) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0x22) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_3_visible = (u32)screen_y < 0x121U;
                    }
                    if ((any_corner_visible | corner_3_visible) != 0) {
                        *(u16 *)((u8 *)material + 0x14) = *(u16 *)((u8 *)material + 0x14) & 0x7FFF;
                        SetPolyFT4(quad);
                        uv_end = *(s32 *)(scratch + 0x14) + *(s32 *)(scratch + 0x0C);
                        *(s32 *)(scratch + 0x14) = uv_end;
                        if (uv_end & 0x100) {
                            *(s32 *)(scratch + 0x14) = uv_end - 1;
                        }
                        uv_end = *(s32 *)(scratch + 0x18) + *(s32 *)(scratch + 0x10);
                        *(s32 *)(scratch + 0x18) = uv_end;
                        if (uv_end & 0x100) {
                            *(s32 *)(scratch + 0x18) = uv_end - 1;
                        }
                        *(s32 *)(scratch + 0x10) = *(s32 *)(scratch + 0x10) << 8;
                        *(s32 *)(scratch + 0x18) = *(s32 *)(scratch + 0x18) << 8;
                        clut_override = *(u16 *)((u8 *)material + 0x12);
                        if (clut_override != 0) {
                            if (*(u16 *)(scratch + 0x28) & 0x100) {
                                *(u16 *)(quad + 0xE) = clut_override;
                            } else {
                                clut = clut_override + *(u16 *)(texture + 6);
                                *(u16 *)(quad + 0xE) = clut;
                            }
                        } else {
                            clut = *(u16 *)(texture + 6);
                            *(u16 *)(quad + 0xE) = clut;
                        }
                        *(s16 *)(quad + 0xC) = *(u16 *)(scratch + 0x10) + *(u16 *)(scratch + 0x0C);
                        *(s16 *)(quad + 0x14) = *(u16 *)(scratch + 0x10) + *(u16 *)(scratch + 0x14);
                        tpage_override = *(u16 *)((u8 *)material + 0x10);
                        if (tpage_override != 0) {
                            tpage = tpage_override + (*(u16 *)(texture + 4) & 0xFF9F);
                        } else {
                            tpage = *(u16 *)(texture + 4);
                        }
                        *(u16 *)(quad + 0x16) = tpage;
                        *(s16 *)(quad + 0x1C) = *(u16 *)(scratch + 0x18) + *(u16 *)(scratch + 0x0C);
                        *(s16 *)(quad + 0x24) = *(u16 *)(scratch + 0x18) + *(u16 *)(scratch + 0x14);
                        if (*(s16 *)(quad + 8) > *(s16 *)(quad + 0x20)) {
                            *(u8 *)(quad + 0x14) = *(u8 *)(quad + 0x14) - 1;
                            *(u8 *)(quad + 0x24) = *(u8 *)(quad + 0x24) - 1;
                        }
                        if (*(s16 *)(quad + 0xA) > *(s16 *)(quad + 0x22)) {
                            *(u8 *)(quad + 0x1D) = *(u8 *)(quad + 0x1D) - 1;
                            *(u8 *)(quad + 0x25) = *(u8 *)(quad + 0x25) - 1;
                        }
                        texture_flags = *(u8 *)(texture + 1);
                        *(u8 *)((u8 *)material + 0xF) = texture_flags;
                        material_flags = *(u16 *)(scratch + 0x28);
                        if (material_flags & 8) {
                            if (material_flags & 4) {
                                draw_flags = texture_flags | 2;
                                *(u8 *)((u8 *)material + 0xF) = draw_flags;
                            } else {
                                draw_flags = texture_flags & 0xFD;
                                *(u8 *)((u8 *)material + 0xF) = draw_flags;
                            }
                        }
                        {
                            u32 address_mask = 0x00FFFFFF;
                            u32 tag_mask = 0xFF000000;
                            s32 *ordering_slot;
                            *(s32 *)(quad + 4) = *(s32 *)((u8 *)material + 0xC);
                            ((P_TAG *)&*(s32 *)quad)->addr = ((P_TAG *)&*(s32 *)((*(s32 *)(scratch + 0x100) * 4)
                                + *(s32 *)(scratch + 0x24)))->addr;
                            ordering_slot = (s32 *)((*(s32 *)(scratch + 0x100) * 4) + *(s32 *)(scratch + 0x24));
                            ((P_TAG *)&*ordering_slot)->addr = (u32)((s32)quad);
                        }
                    }
                }
            }
        }
        if (*(s8 *)texture < 0) {
            break;
        }
        texture += 12;
    }
    PopMatrix();
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/object_node.h"

extern void draw_textured_sphere_mesh(void *record, void *context, void *data, u16 depth_bias);

/* Retail 818757D4 (draw_chained_object_records).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 draw_chained_object_records(void *record, void *context, void *data) {
    ObjectNodeHeader *node;

    for (;;) {
        draw_textured_sphere_mesh(record, context, data, 0);
        node = ((ObjectNodeHeader *)record - 1)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->position;
        data = node->sprite;
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/game_work.h"

#define FIELD_U8(base, off)  (*(u8 *)((u8 *)(base) + (off)))
#define FIELD_S16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define FIELD_U16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define FIELD_U32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define FIELD_PTR(base, off) (*(u8 **)((u8 *)(base) + (off)))

extern s32 RotTransPers(void *, void *, void *, void *);

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 project_colored_point(u8 *render_data, u8 *source_vertex)
{
    u8 **context_slot;
    u8 *scratch;
    u8 *context;
    u8 *point_packet;
    u8 *mode_packet;
    u8 *next_node;
    u8 *vertex = source_vertex;
    u16 vertex_x;
    u8 blue;
    u32 depth_index;
    u32 length_mask;
    u32 address_mask;
    u32 *mode_ot_entry;

    context = g_game_work.draw_buffer;
    context_slot = (u8 **)&g_game_work;
    address_mask = 0x00FFFFFF;
    length_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    FIELD_PTR(scratch, 0x18) = FIELD_PTR(context, 0x8D0);
    FIELD_PTR(scratch, 0x20) = context + 0xB0;
    do {
        point_packet = FIELD_PTR(scratch, 0x18);
        vertex_x = FIELD_U16(vertex, 2);
        FIELD_U16(scratch, 0) = vertex_x;
        FIELD_U16(scratch, 2) = FIELD_U16(vertex, 6);
        FIELD_U16(scratch, 4) = FIELD_U16(vertex, 0xA);
        FIELD_PTR(scratch, 0x18) = point_packet + 0xC;

        depth_index = RotTransPers(scratch, point_packet + 8, scratch + 0x90, scratch + 0x94);
        FIELD_U32(scratch, 0xC0) = depth_index;
        if (depth_index < 0x1E0U) {
            FIELD_U32(point_packet, 4) = FIELD_U32(render_data, 8);
            FIELD_U8(point_packet, 4) = (u8)((FIELD_U8(point_packet, 4) * FIELD_S16(render_data, 0x32)) /
                                      FIELD_S16(render_data, 0x34));
            FIELD_U8(point_packet, 5) = (u8)((FIELD_U8(point_packet, 5) * FIELD_S16(render_data, 0x32)) /
                                      FIELD_S16(render_data, 0x34));
            blue = (u8)((FIELD_U8(point_packet, 6) * FIELD_S16(render_data, 0x32)) /
                        FIELD_S16(render_data, 0x34));
            FIELD_U8(point_packet, 3) = 2;
            FIELD_U8(point_packet, 7) = 0x6A;
            FIELD_U8(point_packet, 6) = blue;

            FIELD_U32(point_packet, 0) = (FIELD_U32(point_packet, 0) & length_mask) |
                (*(u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20)) & address_mask);
            {
                u32 *ot_entry;
                u32 ot_tag;
                ot_entry = (u32 *)((FIELD_U32(scratch, 0xC0) * 4) +
                                   (u32)FIELD_PTR(scratch, 0x20));
                ot_tag = *ot_entry;
                *ot_entry = (ot_tag & length_mask) |
                           ((u32)point_packet & address_mask);
            }

            mode_packet = FIELD_PTR(scratch, 0x18);
            FIELD_PTR(scratch, 0x18) = mode_packet + 0xC;
            SetDrawMode(mode_packet, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);

            FIELD_U32(mode_packet, 0) = (FIELD_U32(mode_packet, 0) & length_mask) |
                (*(u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20)) & address_mask);
            mode_ot_entry = (u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20));
            *mode_ot_entry = (*mode_ot_entry & length_mask) | ((u32)mode_packet & address_mask);
        }

        next_node = FIELD_PTR(render_data, -8);
        render_data = next_node + 0x20;
        if (next_node == 0) {
            break;
        }
        vertex = FIELD_PTR(next_node, 8);
    } while (1);
    FIELD_PTR(*context_slot, 0x8D0) = FIELD_PTR(scratch, 0x18);
    return 0;
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/object_flags.h"

/* Adjust height conditionally and set flags when the countdown reaches zero or below. */
void advance_point_effect_toward_terrain(void *state, s16 *position)
{
    s16 *state_words = state;
    s16 countdown;

    sphere_particle_effect_updated = 1;
    if (position[5] < (s16)sample_terrain_surface_height((u16)position[1], (u16)position[3], position[5] + 2)) {
        ((s32 *)position)[2] += *(s32 *)((u8 *)state + 0x48);
    }

    countdown = (u16)state_words[25] - 4;
    state_words[25] = countdown;
    if ((countdown << 16) <= 0) {
        ((u16 *)state_words)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81875B38_1 {
    u8 pad_00[0x8];
    void *unk_08;
} S_func_81875B38_1;

typedef struct S_func_81875B38_2 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x4];
    void *unk_10;
} S_func_81875B38_2;

typedef struct S_func_81875B38_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0x12];
    s32 unk_48;
} S_func_81875B38_5;


/* Returns the typed effect payload at byte offset 0x20 from the supplied node address. */
static __inline__ S_func_81875B38_2 *effect_offset_32(void *p) {
    return (S_func_81875B38_2 *)((u8 *)p + 0x20);
}

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void create_terrain_seeking_point_effect(
    void *source,
    s32 property_34,
    s32 property_28,
    s16 property_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    S_func_81875B38_1 *source_obj = source;
    S_func_81875B38_2 *effect_ptr;
    S_func_81875B38_2 *effect_obj;
    u16 jitter;
    u16 effect_pos;

    effect_ptr = allocate_list_node(0x211, source_obj);
    if (effect_ptr != NULL) {
        effect_ptr->unk_10 = advance_point_effect_toward_terrain;
        jitter = rand() & 0x1F;
        effect_pos = ((MovingPosition *)source_obj->unk_08)->x + jitter;
        effect_pos += x_offset - 0x10;
        ((ObjectPosition *)effect_ptr->unk_08)->x.w.i = effect_pos;

        jitter = rand() & 0x1F;
        effect_pos = ((MovingPosition *)source_obj->unk_08)->y + jitter;
        effect_pos += y_offset - 0x10;
        ((ObjectPosition *)effect_ptr->unk_08)->y.w.i = effect_pos;

        jitter = rand() & 0x1F;
        effect_obj = effect_ptr;
        effect_ptr = effect_offset_32(effect_obj);
        effect_pos = ((MovingPosition *)source_obj->unk_08)->z + jitter;
        effect_pos += z_offset - 0x10;
        ((ObjectPosition *)effect_obj->unk_08)->z.w.i = effect_pos;
        ((S_func_81875B38_5 *)effect_ptr)->unk_14 = property_34;
        ((S_func_81875B38_5 *)effect_ptr)->unk_32 = property_52;
        ((S_func_81875B38_5 *)effect_ptr)->unk_34 = property_52;
        register_node(effect_obj, project_colored_point);
        ((S_func_81875B38_5 *)effect_ptr)->unk_48 = rand() + 0x10000;
        ((S_func_81875B38_5 *)effect_ptr)->unk_08 = property_28;
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/object_flags.h"

extern void create_terrain_seeking_point_effect(void *, s32, s32, s16, s16, s16, s16);

typedef struct {
    u8 bytes[12];
} UnkCopy12;

extern UnkCopy12 D_80026658;

/* Per-state particle step: the c4 state spawns 0x20 randomised sparks in one do-while. */
void spawn_randomized_spark_burst(u8 *data, void *unused, u8 *context)
{
    u8 *p = data;
    s16 old;
    u16 temp;
    u16 h0;
    u16 timer0;
    u16 state0;
    u16 limit0;
    u16 timer1;
    s32 adv;
    u16 state1;
    u16 h1;
    s32 i;
    s32 color;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 velocity;
    s32 state;

    state = *(s16 *)p;
    sphere_particle_effect_updated = 1;

    switch (state) {
    case 0:
        h0 = *(u16 *)(p + 0x1A);
        old = p[0x34];
        *(u16 *)(p + 0x68) = 0;
        *(u16 *)(p + 0x6A) = h0;
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        timer0 = *(u16 *)(p + 0xE) + 0x28;
        *(u16 *)(p + 0xE) = timer0;
        if ((s16)timer0 < 0x800) {
            return;
        }
        limit0 = 0x800;
        state0 = *(u16 *)p;
        *(u16 *)(p + 0xE) = limit0;
        *(u16 *)p = state0 + 1;
        return;

    case 1:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        timer1 = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = timer1;
        if ((s16)timer1 >= 11) {
            state1 = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = state1 + 1;
        }
        h1 = *(u16 *)(p + 0x1A);
        *(u16 *)(p + 0x68) = 0;
        *(s32 *)(p + 0x74) = 0;
        *(s32 *)(p + 0x80) = -0x900;
        *(u16 *)(p + 0x6A) = h1;
        return;

    case 2:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        if (*(s16 *)(p + 0x6A) < 31) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        velocity = *(s32 *)(p + 0x74) + *(s32 *)(p + 0x80);
        *(s32 *)(p + 0x68) += velocity;
        *(s32 *)(p + 0x74) = velocity;
        *(u16 *)(p + 0x1A) = *(u16 *)(p + 0x6A);
        return;

    case 3:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        temp = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = temp;
        if ((s16)temp >= 31) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        return;

    case 4:
        *(UnkCopy12 *)(p + 0x2C) = D_80026658;
        *(u8 **)(context + 8) = p + 0x2C;
        temp = *(u16 *)p;
        *(u16 *)(p + 2) = 0;
        *(u16 *)p = temp + 1;
        *(s16 *)(*(u8 **)(p + 0x40) + 0x88) = 1;

        i = 0;
        do {
            r0 = (rand() & 0xFF) | 0x80;
            i++;
            r1 = (s16)((rand() & 0x7F) - 0x40);
            r2 = (s16)((rand() & 0x7F) - 0x40);
            r3 = (s16)((rand() & 0x3F) - 0x60);
            color = 0xE04040;
            create_terrain_seeking_point_effect(p - 0x20, 0, color, r0, r1, r2, r3);
        } while (i < 0x20);
        return;

    case 5:
        temp = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = temp;
        if ((s16)temp >= 16) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        return;

    case 6:
        if (context[0xC] >= 5) {
            context[0xC] -= 5;
            context[0xD] -= 5;
            context[0xE] -= 5;
        }
        if (context[0xC] < 6) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        return;

    case 7:
        temp = *(u16 *)(p + 2) - 1;
        *(u16 *)(p + 2) = temp;
        if ((s32)(temp << 16) > 0) {
            return;
        }
        *(u16 *)(p - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    default:
        return;
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_81876014_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x36];
    void * unk_44;
    void * unk_48;
    void * unk_4C;
    u16 unk_50;
    s16 unk_52;
    u16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    s16 unk_64;
    s16 unk_66;
} S_81876014_0;   /* arg0 in update_effect_quad_and_completion */

typedef struct S_81876014_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x90];
    s16 unk_9C;
} S_81876014_1;

typedef struct S_81876014_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81876014_2;   /* arg1 in update_effect_quad_and_completion */

typedef struct S_81876014_3 {
    s32 unk_00;
} S_81876014_3;

typedef struct S_81876014_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_81876014_4;   /* arg2 in update_effect_quad_and_completion */

typedef struct S_81876014_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_81876014_5;   /* ((S_81876014_0 *)arg0)->unk_44 in update_effect_quad_and_completion */

typedef struct S_81876014_6 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_81876014_6;   /* ((S_81876014_0 *)arg0)->unk_48 in update_effect_quad_and_completion */

extern s32 rsin(s32);
extern s32 rcos(s32);

/* Update the effect quad, copy its position and color, and flag completion based on owner state. */
void update_effect_quad_and_completion(void *effect, void *position_out, void *color_out) {
    s32 y_factor;
    s16 next_angle;
    u16 angle;
    void *owner;

    owner = ((S_81876014_0 *)effect)->unk_4C;
    sphere_particle_effect_updated = 1;
    if (((S_81876014_1 *)owner)->unk_9C == 0x37) {
        /* vertex 0 of the quad */
        ((S_81876014_0 *)effect)->unk_50 =
            (u16)((((S_81876014_0 *)effect)->unk_0A *
                   rcos(((S_81876014_0 *)effect)->unk_0C)) >> 12);
        y_factor = rsin(((S_81876014_0 *)effect)->unk_0C);
        ((S_81876014_0 *)effect)->unk_58 = (((S_81876014_0 *)effect)->unk_0A * y_factor) >> 12;
        ((S_81876014_0 *)effect)->unk_60 = 0;
        /* x of vertices 1..3 */
        ((S_81876014_0 *)effect)->unk_52 = ((S_81876014_0 *)effect)->unk_50 + 0x10;
        ((S_81876014_0 *)effect)->unk_54 = ((S_81876014_0 *)effect)->unk_50;
        ((S_81876014_0 *)effect)->unk_56 = ((S_81876014_0 *)effect)->unk_50 + 0x10;
        /* y of vertices 1..3 */
        ((S_81876014_0 *)effect)->unk_5A = ((S_81876014_0 *)effect)->unk_58;
        ((S_81876014_0 *)effect)->unk_5C = ((S_81876014_0 *)effect)->unk_58;
        ((S_81876014_0 *)effect)->unk_5E = ((S_81876014_0 *)effect)->unk_58;
        /* z of vertices 1..3 */
        ((S_81876014_0 *)effect)->unk_62 = ((S_81876014_0 *)effect)->unk_60;
        ((S_81876014_0 *)effect)->unk_64 = ((S_81876014_0 *)effect)->unk_60 + 0x10;
        ((S_81876014_0 *)effect)->unk_66 = ((S_81876014_0 *)effect)->unk_60 + 0x10;
        ((S_81876014_2 *)position_out)->unk_00 = ((S_81876014_3 *)(((S_81876014_0 *)effect)->unk_44))->unk_00;
        ((S_81876014_2 *)position_out)->unk_04 = ((S_81876014_5 *)(((S_81876014_0 *)effect)->unk_44))->unk_04;
        ((S_81876014_2 *)position_out)->unk_08 = ((S_81876014_5 *)(((S_81876014_0 *)effect)->unk_44))->unk_08;
        ((S_81876014_4 *)color_out)->unk_0C = ((S_81876014_6 *)(((S_81876014_0 *)effect)->unk_48))->unk_0C;
        ((S_81876014_4 *)color_out)->unk_0D = ((S_81876014_6 *)(((S_81876014_0 *)effect)->unk_48))->unk_0D;
        ((S_81876014_4 *)color_out)->unk_0E = ((S_81876014_6 *)(((S_81876014_0 *)effect)->unk_48))->unk_0E;
        angle = ((S_81876014_0 *)effect)->unk_0C;
        next_angle = angle - 0x64;
        ((S_81876014_0 *)effect)->unk_0C = next_angle;
        if (next_angle < 0) {
            ((S_81876014_0 *)effect)->unk_0C = angle + 0xF9C;
        }
        if (((S_81876014_1 *)owner)->unk_0A < 5) {
            return;
        }
    }
    (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_800259D8_0_pre {
    u16 unk_00;
} S_800259D8_0_pre;   /* the 0x2 bytes before arg0 in update_animated_effect_sprite, addressed as arg0[-1] */

typedef struct S_800259D8_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x68];
    union { u16 u; s16 s; } unk_74;   /* accessed as both */
    union { u16 u; s16 s; } unk_76;   /* accessed as both */
    union { u16 u; s16 s; } unk_78;   /* accessed as both */
    u8 unk_7A;
    u8 pad_7B[0x1];
    union { s16 s; u16 u; } unk_7C;   /* accessed as both */
    u8 pad_7E[0x2];
    s16 unk_80;
    u8 pad_82[0x2];
    union { u16 u; s16 s; } unk_84;   /* accessed as both */
    u8 pad_86[0x2];
    s16 unk_88;
    u8 pad_8A[0x12];
    u16 unk_9C;
    u8 pad_9E[0x2];
    s16 unk_A0;
    u8 pad_A2[0x8];
    u8 unk_AA;
    u8 pad_AB[0x3];
    u8 unk_AE;
    u8 unk_AF;
} S_800259D8_0;   /* arg0 in update_animated_effect_sprite */

typedef struct S_800259D8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800259D8_1;   /* base in update_animated_effect_sprite */

typedef struct S_800259D8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { s8 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x1]; s8 v; } at01u;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x2]; s8 v; } at02u;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800259D8_2;   /* arg2 in update_animated_effect_sprite */

typedef struct S_800259D8_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_3_pre;   /* the 0x14 bytes before obj in update_animated_effect_sprite, addressed as obj[-1] */

typedef struct S_800259D8_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    u8 pad_73[0x15];
    u16 unk_88;
} S_800259D8_3;   /* obj in update_animated_effect_sprite */

typedef struct S_800259D8_4 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800259D8_4;   /* arg1 in update_animated_effect_sprite */

typedef struct S_800259D8_5 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x6];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x1A];
    void * unk_38;
    void * unk_3C;
    void * unk_40;
    void * unk_44;
    void * unk_48;
    void * unk_4C;
} S_800259D8_5;   /* entry in update_animated_effect_sprite */

typedef struct S_800259D8_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800259D8_6;   /* resident_work in update_animated_effect_sprite */

typedef struct S_800259D8_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800259D8_8;   /* work in update_animated_effect_sprite */

typedef struct S_800259D8_10_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_10_pre;   /* the 0x14 bytes before fade_node in update_animated_effect_sprite, addressed as fade_node[-1] */

typedef struct S_800259D8_10 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800259D8_10;   /* fade_node in update_animated_effect_sprite */

typedef struct S_800259D8_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800259D8_11;   /* fade_entry in update_animated_effect_sprite */

typedef struct S_800259D8_12_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_12_pre;   /* the 0x14 bytes before tail_node in update_animated_effect_sprite, addressed as tail_node[-1] */

typedef struct S_800259D8_12 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800259D8_12;   /* tail_node in update_animated_effect_sprite */

typedef struct S_800259D8_13 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800259D8_13;   /* ((S_800259D8_1 *)base)->unk_0C in update_animated_effect_sprite */

typedef struct S_800259D8_14 {
    u16 unk_00;
} S_800259D8_14;   /* ((S_800259D8_0 *)arg0)->unk_04 in update_animated_effect_sprite */

typedef struct S_800259D8_15_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800259D8_15_pre;   /* the 0x18 bytes before ((S_800259D8_3 *)obj)->unk_60 in update_animated_effect_sprite, addressed as ((S_800259D8_3 *)obj)->unk_60[-1] */

typedef struct S_800259D8_15 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800259D8_15;   /* ((S_800259D8_3 *)obj)->unk_60 in update_animated_effect_sprite */

typedef struct DirectionOffset {
    s16 x;
    u16 y;
} DirectionOffset;
typedef union DirectionOffsetCopy {
    DirectionOffset pairs[8];
    u8 bytes[32];
} Copy32;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    s16 x;
    s16 y;
    u16 z;
} Vec3s;

typedef union {
    u16 u;
    s16 s;
} H16;

typedef struct {
    H16 x;
    H16 y;
} Pair;

/* These resident data/code addresses are not present in the catalog for this
 * cold overlay row; the binds retain real link-resolved symbols. */

const Copy32 textured_quad_octant_offsets = {{ {8, 0}, {8, 8}, {0, 8}, {-8, 8}, {-8, 0}, {-8, 65528}, {0, 65528}, {8, 65528} }};
extern Copy12 D_80026634;
extern Copy12 D_80026640;
extern Copy12 D_8002664C;

extern s32 get_sprite_attachment_vector(void *, void *, Vec3s *, s32);
extern s32 check_adjacent_tile_height_clearance(u16, u16, s16, void *);
extern void create_terrain_seeking_point_effect(void *, s32, s32, s16, s16, s16, s16);

extern s32 rcos(s32);
extern s32 rsin(s32);

/* Moves an effect toward its target, emits particles, changes target colors, and applies a timed status. */
void update_animated_effect_sprite(void *effect, void *entity, S_800259D8_2 *sprite)
{
    Vec3s delta;
    Copy32 copy;
    void *obj;
    void *base;
    void *entry;
    void *node;
    SpriteFrameState *work;
    ObjectPosition *dst;
    u32 state;
    u16 old_count;
    s16 count;
    s32 result;
    s32 index;
    s32 value;
    s32 i;

    obj = ((S_800259D8_0 *)effect)->unk_00;
    copy = textured_quad_octant_offsets;
    state = ((S_800259D8_0 *)effect)->unk_0A.s;
    base = (u8 *)obj - 0x20;
    entry = ((S_800259D8_1 *)base)->unk_08;
    switch (state) {
    case 0:
    {
        s32 setup;
        setup = 0x00808080;
        sprite->unk_0C.at00.v = setup;
        setup = 0x1000;
        sprite->unk_1E = setup;
        sprite->unk_1C = setup;
    }
        *(Copy12 *)((u8 *)effect + 0xA2) = D_80026634;
        {
            s32 init_value;
            u16 init_count;
            sprite->unk_08 = (u8 *)effect + 0xA2;
            init_value = (((S_800259D8_3 *)obj)->unk_2A >> 9) & 7;
            ((s16 *)&sphere_particle_effect_updated)[0] = 1;
            init_count = ((S_800259D8_0 *)effect)->unk_0A.u + 1;
            ((S_800259D8_0 *)effect)->unk_80 = init_value;
            ((S_800259D8_0 *)effect)->unk_0A.u = init_count;
        }
    case 1:
        result = get_sprite_attachment_vector(
            ((S_800259D8_13 *)(((S_800259D8_1 *)base)->unk_0C))->unk_08,
            ((S_800259D8_1 *)base)->unk_0C, &delta, 0);
        if (result == 0) {
            if (!(((S_800259D8_13 *)(((S_800259D8_1 *)base)->unk_0C))->unk_14 & 0x8000U)) {
                return;
            }
        }
        {
            u16 z_value;
            ((S_800259D8_4 *)entity)->unk_00.at02.v = ((S_800259D8_5 *)entry)->unk_00.at02.v;
            ((S_800259D8_4 *)entity)->unk_04.at02.v = ((S_800259D8_5 *)entry)->unk_04.at02.v;
            z_value = ((S_800259D8_5 *)entry)->unk_08.at02.v;
            ((S_800259D8_4 *)entity)->unk_08.at02.v = z_value;
            if (!(((S_800259D8_13 *)(((S_800259D8_1 *)base)->unk_0C))->unk_14 & 0x8000U)) {
                ((S_800259D8_4 *)entity)->unk_00.at02.v += delta.x;
                ((S_800259D8_4 *)entity)->unk_04.at02.v += delta.y;
                ((S_800259D8_4 *)entity)->unk_08.at02u.v = ((S_800259D8_4 *)entity)->unk_08.at02.v + delta.z;
            } else {
L0_adjust_z:
                                           /* MATCH: retain the alternate z calculation's scheduling boundary. */
                ((S_800259D8_4 *)entity)->unk_08.at02u.v = z_value - 0x40;
            }
        }
        if (!(((S_800259D8_14 *)(((S_800259D8_0 *)effect)->unk_04))->unk_00 & 0x80U)) {
            return;
        }
        if (!(((S_800259D8_0 *)effect)->unk_7A & 4U)) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            sprite->unk_10 = 0x20;
            sprite->unk_0C.at02.v = 0x80;
            sprite->unk_0C.at01.v = 0x80;
            sprite->unk_0C.at00u.v = 0x80;
            sprite->unk_14 |= 0xC;
            ((S_800259D8_0 *)effect)->unk_7A |= 4;
        }
        if (((S_800259D8_3 *)obj)->unk_60 != 0) {
            void *resident_work;
            entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
            ((S_800259D8_0 *)effect)->unk_74.u = ((S_800259D8_5 *)entry)->unk_00.at02u.v;
            ((S_800259D8_0 *)effect)->unk_76.u = ((S_800259D8_5 *)entry)->unk_04.at02u.v;
            {
                s32 depth_bias;
                s32 resident_value;
                depth_bias = entity_height_offsets[((S_800259D8_15 *)(((S_800259D8_3 *)obj)->unk_60))->unk_13];
                resident_value = ((S_800259D8_5 *)entry)->unk_08.at02.v - depth_bias - 0x60;
                ((S_800259D8_0 *)effect)->unk_78.u = resident_value;
            }
            resident_work = ((S_800259D8_3_pre *)obj)[-1].unk_00;
            ((S_800259D8_0 *)effect)->unk_AE = ((S_800259D8_6 *)resident_work)->unk_24 +
                dir_step_x[((S_800259D8_0 *)effect)->unk_80];
            ((S_800259D8_0 *)effect)->unk_AF = ((S_800259D8_6 *)resident_work)->unk_25 +
                dir_step_y[((S_800259D8_0 *)effect)->unk_80];
            entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
            {
                if (((S_800259D8_3 *)obj)->unk_72 != ((S_800259D8_6 *)resident_work)->unk_24) {
                    s32 resident_delta;
                    s32 resident_copy;
                    resident_delta = ((S_800259D8_4 *)entity)->unk_00.at02.v;
                    resident_delta = resident_delta - ((S_800259D8_5 *)entry)->unk_00.at02.v;
                    resident_copy = *(s16 *)((u8 *)&copy + (((S_800259D8_0 *)effect)->unk_80 << 2));
                    resident_delta = abs(resident_delta);
                    resident_copy = abs(resident_copy);
                    ((S_800259D8_0 *)effect)->unk_7C.s = resident_delta / resident_copy;
                } else {
                    Pair *cp;
                    s32 cidx;
                    s32 resident_delta;
                    s32 resident_copy;
                    resident_delta = ((S_800259D8_4 *)entity)->unk_04.at02.v;
                    cidx = ((S_800259D8_0 *)effect)->unk_80 << 2;
                    resident_delta = resident_delta - ((S_800259D8_5 *)entry)->unk_04.at02.v;
                    cp = (Pair *)&copy;
                    resident_copy = ((Pair *)((u8 *)cp + cidx))->y.u;
                    resident_delta = abs(resident_delta);
                    resident_copy = (s32)((u32)resident_copy << 16) >> 16;
                    resident_copy = abs(resident_copy);
                    ((S_800259D8_0 *)effect)->unk_7C.s = resident_delta / resident_copy;
                }
            }
        } else {
            {
                ((S_800259D8_0 *)effect)->unk_7C.s = 0x80;
                ((S_800259D8_0 *)effect)->unk_74.s = ((S_800259D8_4 *)entity)->unk_00.at02u.v +
                    (((Pair *)((u8 *)&copy + (((S_800259D8_0 *)effect)->unk_80 << 2)))->x.u << 7);
                ((S_800259D8_0 *)effect)->unk_76.s = ((S_800259D8_4 *)entity)->unk_04.at02u.v +
                    (((Pair *)((u8 *)&copy + (((S_800259D8_0 *)effect)->unk_80 << 2)))->y.u *
                     ((S_800259D8_0 *)effect)->unk_7C.u);
                ((S_800259D8_0 *)effect)->unk_78.s = ((S_800259D8_3 *)obj)->unk_88 - 0x50;
            }
        }
        {
            Pair *cp = (Pair *)&copy;
            ((S_800259D8_4 *)entity)->unk_0C =
                ((Pair *)((u8 *)cp + (((S_800259D8_0 *)effect)->unk_80 << 2)))->x.s << 16;
            ((S_800259D8_4 *)entity)->unk_10 =
                ((Pair *)((u8 *)cp + (((S_800259D8_0 *)effect)->unk_80 << 2)))->y.u << 16;
        }
        ((S_800259D8_4 *)entity)->unk_14 =
            ((((S_800259D8_0 *)effect)->unk_78.s << 16) - ((S_800259D8_4 *)entity)->unk_08.at00.v) /
            ((S_800259D8_0 *)effect)->unk_7C.s;
        ((S_800259D8_0 *)effect)->unk_84.u = 0;
        ((S_800259D8_0 *)effect)->unk_9C = 55;
        ((S_800259D8_0 *)effect)->unk_0A.u++;
        i = 0;
        do {
            ObjectNodeHeader *spawn;
            spawn = allocate_flagged_object_node(0x12);
            if (spawn != 0) {
                entry = (u8 *)spawn + 0x20;
                {
                    void *spawn_copy = spawn;
                    u8 *tbl = project_linked_quad_record;
                    ((S_800259D8_5 *)entry)->unk_38 = obj;
                    ((S_800259D8_5 *)entry)->unk_44 = entity;
                    ((S_800259D8_5 *)entry)->unk_48 = sprite;
                    ((S_800259D8_5 *)entry)->unk_4C = effect;
                    spawn->update_callback = (void *)update_effect_quad_and_completion;
                    register_node(spawn_copy, tbl);
                }
                work = spawn->sprite;
                work->flags |= 0xC;
                work->tpage_abr = 0x20;
                dst = spawn->position;
                ((S_800259D8_5 *)entry)->unk_08.at02u.v = (rand() & 7) + 12;
                ((S_800259D8_5 *)entry)->unk_0C = rand() & 0xFFF;
                work->angle_x = (rand() & 0xFF) << 4;
                work->angle_y = (rand() & 0xFF) << 4;
                work->angle_z = (rand() & 0xFF) << 4;
                value = rcos(((S_800259D8_5 *)entry)->unk_0C);
                dst->x.v = (((S_800259D8_5 *)entry)->unk_08.at02u.v * value) << 4;
                value = rsin(((S_800259D8_5 *)entry)->unk_0C);
                dst->y.v = (((S_800259D8_5 *)entry)->unk_08.at02u.v * value) << 4;
                dst->z.w.i = ((S_800259D8_4 *)entity)->unk_08.at02.v;
                work = spawn->sprite;
                {
                    s32 scale1;
                    scale1 = 0x1000;
                    work->scale_y = scale1;
                    work->scale_x = scale1;
                }
                {
                    s32 alpha;
                    alpha = 0x80;
                    work->color.c.b = alpha;
                    work->color.c.g = alpha;
                    work->color.c.r = alpha;
                }
                *(Copy12 *)((u8 *)spawn + 0x4C) = D_80026640;
                work->source = (u8 *)spawn + 0x4C;
            }
            i++;
            if (i < 8) {
                continue;
            }
        } while (i < 8);
        return;

    case 2:
        if (((S_800259D8_0 *)effect)->unk_A0 == 0) {
            ((S_800259D8_0 *)effect)->unk_A0 = 1;
            ((S_800259D8_0 *)effect)->unk_AA += 0x18;
        } else {
            ((S_800259D8_0 *)effect)->unk_AA -= 0x18;
            ((S_800259D8_0 *)effect)->unk_A0 = 0;
        }
        result = check_adjacent_tile_height_clearance(((S_800259D8_4 *)entity)->unk_00.at02u.v, ((S_800259D8_4 *)entity)->unk_04.at02u.v,
                               ((S_800259D8_4 *)entity)->unk_08.at02u.v, ((S_800259D8_3 *)obj)->unk_60);
        if ((result << 16) == 0) {
            node = ((S_800259D8_3 *)obj)->unk_60;
            if (node == 0) {
                sprite->unk_0C.at00u.v -= 4;
                sprite->unk_0C.at01.v -= 4;
                sprite->unk_0C.at02.v -= 4;
                if (sprite->unk_0C.at00u.v == 0) {
                    ((S_800259D8_0 *)effect)->unk_7C.u = 1;
                }
            }
            count = ((S_800259D8_0 *)effect)->unk_7C.u - 1;
            ((S_800259D8_0 *)effect)->unk_7C.u = count;
            if (count > 0) {
                goto L1_calc;
            }
            if (((S_800259D8_3 *)obj)->unk_60 != 0) {
                ((S_800259D8_0 *)effect)->unk_0A.u = 3;
                ((S_800259D8_0 *)effect)->unk_84.u = 0;
                entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
                ((S_800259D8_4 *)entity)->unk_00.at02u.v = ((S_800259D8_5 *)entry)->unk_00.at02u.v;
                ((S_800259D8_4 *)entity)->unk_04.at02u.v = ((S_800259D8_5 *)entry)->unk_04.at02u.v;
                ((S_800259D8_4 *)entity)->unk_08.at02.v = ((S_800259D8_0 *)effect)->unk_78.u;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                return;
            }
        }
        ((S_800259D8_0 *)effect)->unk_0A.u = 7;
        ((S_800259D8_0 *)effect)->unk_84.u = 0;
        sprite->unk_0C.at02.v = 0;
        sprite->unk_0C.at01.v = 0;
        sprite->unk_0C.at00u.v = 0;
        return;

L1_calc:
        ((S_800259D8_4 *)entity)->unk_0C =
            ((((S_800259D8_0 *)effect)->unk_74.s << 16) - ((S_800259D8_4 *)entity)->unk_00.at00.v) / count;
        ((S_800259D8_4 *)entity)->unk_10 =
            ((((S_800259D8_0 *)effect)->unk_76.s << 16) - ((S_800259D8_4 *)entity)->unk_04.at00.v) /
            ((S_800259D8_0 *)effect)->unk_7C.s;
        ((S_800259D8_4 *)entity)->unk_14 =
            ((((S_800259D8_0 *)effect)->unk_78.s << 16) - ((S_800259D8_4 *)entity)->unk_08.at00.v) /
            ((S_800259D8_0 *)effect)->unk_7C.s;
        ((S_800259D8_4 *)entity)->unk_00.at00.v += ((S_800259D8_4 *)entity)->unk_0C;
        ((S_800259D8_4 *)entity)->unk_04.at00.v += ((S_800259D8_4 *)entity)->unk_10;
        ((S_800259D8_4 *)entity)->unk_08.at00.v += ((S_800259D8_4 *)entity)->unk_14;
        return;

    case 3:
        if (((S_800259D8_0 *)effect)->unk_A0 == 0) {
            ((S_800259D8_0 *)effect)->unk_A0 = 1;
            ((S_800259D8_0 *)effect)->unk_AA += 0x18;
        } else {
            ((S_800259D8_0 *)effect)->unk_AA -= 0x18;
            ((S_800259D8_0 *)effect)->unk_A0 = 0;
        }
        {
            ObjectNodeHeader *spawn;
            spawn = allocate_flagged_object_node(0x12);
            if (spawn != 0) {
                entry = (u8 *)spawn + 0x20;
                ((S_800259D8_5 *)entry)->unk_00.at02.v = 0;
                ((S_800259D8_5 *)entry)->unk_38 = obj;
                ((S_800259D8_5 *)entry)->unk_3C = ((S_800259D8_3 *)obj)->unk_60;
                ((S_800259D8_5 *)entry)->unk_40 = effect;
                ((S_800259D8_5 *)entry)->unk_08.at02u.v = 0x0C;
                ((S_800259D8_5 *)entry)->unk_0C = 8;
                ((S_800259D8_5 *)entry)->unk_0E = 0;
                ((S_800259D8_5 *)entry)->unk_10 = 0;
                ((S_800259D8_5 *)entry)->unk_12 = 0;
                ((S_800259D8_5 *)entry)->unk_1C = 0;
                ((S_800259D8_5 *)entry)->unk_1A = 0x40;
                entry = ((S_800259D8_15_pre *)(((S_800259D8_3 *)obj)->unk_60))[-1].unk_00;
                spawn->update_callback = spawn_randomized_spark_burst;
                register_node(spawn, draw_chained_object_records);
                work = spawn->sprite;
                work->tpage_abr = 0x20;
                work->flags |= 0x000C;
                dst = spawn->position;
                dst->x.v = ((S_800259D8_5 *)entry)->unk_00.at00.v;
                dst->y.v = ((S_800259D8_5 *)entry)->unk_04.at00.v;
                index = ((S_800259D8_3 *)obj)->unk_60 != 0;
                index = ((S_800259D8_15 *)(((S_800259D8_3 *)obj)->unk_60))->unk_13;
                dst->z.v = ((S_800259D8_5 *)entry)->unk_08.at00.v -
                    (entity_height_offsets[index] << 15);
                work = spawn->sprite;
                {
                    s16 scale2 = 0x1000;
                    work->scale_y = scale2;
                    work->scale_x = scale2;
                }
                work->color.c.b = 0x80;
                work->color.c.g = 0x80;
                work->color.c.r = 0x80;
                *(Copy12 *)((u8 *)spawn + 0x4C) = D_8002664C;
                work->source = (u8 *)spawn + 0x4C;
            }
        }
        ((S_800259D8_0 *)effect)->unk_0A.u = 4;
        ((S_800259D8_0 *)effect)->unk_84.u = 0;
        return;

    case 4:
        count = ((S_800259D8_0 *)effect)->unk_84.u + 1;
        ((S_800259D8_0 *)effect)->unk_84.u = count;
        if (count < 30) {
            sprite->unk_0C.at00p.v = ((30 - ((S_800259D8_0 *)effect)->unk_84.s) * 0x80) / 30;
            sprite->unk_0C.at01u.v = ((30 - ((S_800259D8_0 *)effect)->unk_84.s) * 0x80) / 30;
            sprite->unk_0C.at02u.v = ((30 - ((S_800259D8_0 *)effect)->unk_84.s) * 0xE0) / 30;
            if (((S_800259D8_0 *)effect)->unk_A0 == 0) {
                ((S_800259D8_0 *)effect)->unk_A0 = 1;
                ((S_800259D8_0 *)effect)->unk_AA += 0x18;
            } else {
                ((S_800259D8_0 *)effect)->unk_AA -= 0x18;
                ((S_800259D8_0 *)effect)->unk_A0 = 0;
            }
            i = 0;
            while (1) {
                value = rand();
                create_terrain_seeking_point_effect((u8 *)effect - 0x20, ((S_800259D8_0 *)effect)->unk_80, 0x00E02020, (value & 0xFF) | 0x80, 0,
                    0, 0);
                i++;
                if (i >= 4) {
                    return;
                }
            }
        }
        ((S_800259D8_0 *)effect)->unk_0A.u++;
        ((S_800259D8_0 *)effect)->unk_84.u = 0;
        sprite->unk_14 |= 0x80;
        return;

    case 5:
        if (((S_800259D8_0 *)effect)->unk_88 == 0) {
            return;
        }
        {
            ((S_800259D8_0 *)effect)->unk_84.u = 0;
            ((S_800259D8_0 *)effect)->unk_0A.u++;
            return;
        }

    case 6:
    {
        void *fade_node;
        void *fade_entry;
        count = ((S_800259D8_0 *)effect)->unk_84.u + 1;
        ((S_800259D8_0 *)effect)->unk_84.u = count;
        fade_node = ((S_800259D8_3 *)obj)->unk_60;
        ((S_800259D8_10 *)fade_node)->unk_1C |= 0x10000000;
        fade_entry = ((S_800259D8_10_pre *)fade_node)[-1].unk_00;
        if (((S_800259D8_0 *)effect)->unk_84.s >= 36) {
            ((S_800259D8_11 *)fade_entry)->unk_0C += 2;
            ((S_800259D8_11 *)fade_entry)->unk_0D += 2;
            ((S_800259D8_11 *)fade_entry)->unk_0E -= 3;
        } else {
            ((S_800259D8_11 *)fade_entry)->unk_0C -= 2;
            ((S_800259D8_11 *)fade_entry)->unk_0D -= 2;
            ((S_800259D8_11 *)fade_entry)->unk_0E += 3;
        }
        if (((S_800259D8_0 *)effect)->unk_84.s < 71) {
            return;
        }
        {
            void *tail_node;
            tail_node = ((S_800259D8_3 *)obj)->unk_60;
            ((S_800259D8_12 *)tail_node)->unk_1C &= 0xEFFFFFFF;
            fade_entry = ((S_800259D8_12_pre *)tail_node)[-1].unk_00;
            ((S_800259D8_11 *)fade_entry)->unk_0E = 0x80;
            ((S_800259D8_11 *)fade_entry)->unk_0D = 0x80;
            ((S_800259D8_11 *)fade_entry)->unk_0C = 0x80;
            apply_random_duration_actor_status(((S_800259D8_3 *)obj)->unk_60, ((S_800259D8_0 *)effect)->unk_09, obj);
        }
        ((S_800259D8_0 *)effect)->unk_84.u = 13;
        ((S_800259D8_0 *)effect)->unk_0A.u++;
        return;
    }

    case 7:
        old_count = ((S_800259D8_0 *)effect)->unk_84.u;
        ((S_800259D8_0 *)effect)->unk_84.u = old_count + 1;
        if ((s16)old_count < 15) {
            return;
        }
        {
            s32 seen;
            seen = ((s16 *)&sphere_particle_effect_updated)[0];
            ((S_800259D8_0 *)effect)->unk_84.u = old_count;
            if (seen == 0) {
                g_dungeon_status.active_actor = 0;
                ((S_800259D8_0_pre *)effect)[-1].unk_00 |= 0x8000;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
        }
        ((s16 *)&sphere_particle_effect_updated)[0] = 0;
        return;
    }

    return;
}
