
struct ObjectPosition;
#include "shared/sprite_frame_state.h"
/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/effect/dispatch.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect.h"
#include "dungeon/item.h"
#include "dungeon/player/item.h"
#include "engine/texture.h"

typedef struct S_800C55F4_0 {
    u8 ** unk_00;
    u8 pad_04[0x4];
    u8 ** unk_08;
} S_800C55F4_0;   /* descriptor in transform_mesh_and_append_draw_packets */

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
    union { s32 s; s32 u; } unk_C0;   /* accessed as both */
    s32 unk_C4;
    union { s32 s; s32 u; } unk_C8;   /* accessed as both */
    s32 unk_CC;
    u8 pad_D0[0x44];
    s32 unk_114;
} S_800C55F4_1;   /* scratch in transform_mesh_and_append_draw_packets */

typedef struct S_800C55F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C55F4_2;   /* arg2_alias in transform_mesh_and_append_draw_packets */

typedef struct S_800C55F4_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C55F4_3;   /* arg1_record in transform_mesh_and_append_draw_packets */

typedef struct S_800C55F4_4 {
    u8 unk_00;
    u8 pad_01[0x315F];
    u8 * unk_3160;
} S_800C55F4_4;   /* page_record7 in transform_mesh_and_append_draw_packets */

   /* root in transform_mesh_and_append_draw_packets */

typedef struct S_800C55F4_6 {
    u32 unk_00;
    u16 unk_04;
} S_800C55F4_6;   /* (x << 3) + (u32)table in transform_mesh_and_append_draw_packets */

typedef struct S_800C55F4_8 {
    u8 pad_00[0x30];
    s16 unk_30;
    s16 unk_32;
} S_800C55F4_8;   /* arg0_pin in transform_mesh_and_append_draw_packets */

   /* ((S_800C55F4_9 *)global_base)->unk_00 in transform_mesh_and_append_draw_packets */

extern s32 convert_hsv_to_rgb();
extern void *CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern s32 ReadRotMatrix();
extern void *ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotTransPers(void *, void *, ...);
extern s32 NormalClip();
extern void *RotMatrix(void *, void *);
extern void AddPrim(void *, void *);
extern s32 SetPolyG3();
extern s32 SetDrawMode();

typedef struct Face {
    u8 v0;
    u8 v1;
    u8 v2;
    u8 pad_03[0x8];
    s8 flags;
} Face;

/* Sign-extends the low 16 bits of the input to a 32-bit depth value. */
static __inline__ s32 narrow_depth(s32 value)
{
    return (s16)value;
}

/* Transform mesh triangles, shade visible vertices, and append draw packets to the ordering table. */
void transform_mesh_and_append_draw_packets(u8 *params, u8 *record, void *mesh_data, s32 depth_offset)
{
    u8 saved_matrix[0x20];
    s16 depth_bias = depth_offset;
    u8 *scratch;
    u8 *vector_arg;
    u8 *screen_arg;
    void *perspective_out;
    void *flags_out;
    u8 *descriptor;
    u8 *vertices;
    Face *face;
    u8 *packet_code;
    u8 *render_state;
    u8 *packet;
    u8 *prim;
    u8 packet_flags;
    s32 result;
    s32 face_flags;
    s32 shade_arg;
    u32 vertex_index;
    u32 vertex_depth;
    void *perspective_arg;
    void *flags_arg;
    GameWork *global_base;

    global_base = &g_game_work;
    perspective_out = (void *)0x1F800090;

    descriptor = (*(u8 ***)((u8 *)mesh_data + 8));
    flags_out = (void *)0x1F800094;

    vertices = ((S_800C55F4_0 *)descriptor)->unk_00;
    face = (Face *)((S_800C55F4_0 *)descriptor)->unk_08;

    PushMatrix();

    vector_arg = (u8 *)0x1F800028;
    screen_arg = (u8 *)0x1F800000;
    scratch = (u8 *)0x1F800000;

    ((S_800C55F4_1 *)scratch)->unk_30 = (*(u16 *)((u8 *)mesh_data + 0x1C));
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

    result = RotTransPers(vector_arg, screen_arg,
                           (void *)0x1F800090, (void *)0x1F800094);
    depth_bias = narrow_depth(depth_bias);
    ((S_800C55F4_1 *)scratch)->unk_CC = result - depth_bias;
    ReadRotMatrix(saved_matrix);
    RotMatrix((u8 *)mesh_data + 0x16, scratch + 0x50);
    ScaleMatrix(scratch + 0x50, scratch + 0x30);
    CompMatrix(saved_matrix, scratch + 0x50, scratch + 0xD0);
    SetTransMatrix(scratch + 0xD0);
    SetRotMatrix(scratch + 0xD0);

    render_state = ((u8 *)global_base->draw_buffer);
    ((S_800C55F4_1 *)scratch)->unk_20 = render_state + 0xB0;
    prim = ((GpuContext *)render_state)->packetCursor;
    packet_code = prim + 7;
    ((S_800C55F4_2 *)mesh_data)->unk_14 |= 0x8000;

    for (;;) {
        vertex_index = face->v0;
        ((S_800C55F4_1 *)scratch)->unk_70 = ((S_800C55F4_6 *)((vertex_index << 3) + (unsigned long)vertices))->unk_00;
        vertex_index = face->v1;
        ((S_800C55F4_1 *)scratch)->unk_78 = ((S_800C55F4_6 *)((vertex_index << 3) + (unsigned long)vertices))->unk_00;
        vertex_index = face->v2;
        ((S_800C55F4_1 *)scratch)->unk_80 = ((S_800C55F4_6 *)((vertex_index << 3) + (unsigned long)vertices))->unk_00;
        vertex_index = face->v0;
        ((S_800C55F4_1 *)scratch)->unk_74 = ((S_800C55F4_6 *)((vertex_index << 3) + (unsigned long)vertices))->unk_04;
        vertex_index = face->v1;
        ((S_800C55F4_1 *)scratch)->unk_7C = ((S_800C55F4_6 *)((vertex_index << 3) + (unsigned long)vertices))->unk_04;
        vertex_index = face->v2;
        perspective_arg = perspective_out;
        flags_arg = flags_out;
        ((S_800C55F4_1 *)scratch)->unk_84 = ((S_800C55F4_6 *)((vertex_index << 3) + (unsigned long)vertices))->unk_04;

        {
            s32 depth;

            depth = RotTransPers(scratch + 0x70, prim + 8,
                                        perspective_arg, flags_arg);
            perspective_arg = perspective_out;
            flags_arg = flags_out;
            ((S_800C55F4_1 *)scratch)->unk_C0.s = depth;
            depth = RotTransPers(scratch + 0x78, prim + 0x10,
                                        perspective_arg, flags_arg);
            perspective_arg = perspective_out;
            flags_arg = flags_out;
            ((S_800C55F4_1 *)scratch)->unk_C4 = depth;
            depth = RotTransPers(scratch + 0x80, prim + 0x18,
                                        perspective_arg, flags_arg);
            ((S_800C55F4_1 *)scratch)->unk_C8.s = depth;
        }

        result = NormalClip((*(s32 *)((u8 *)packet_code + 1)),
                               (*(s32 *)((u8 *)packet_code + 9)),
                               (*(s32 *)((u8 *)packet_code + 0x11)));
        ((S_800C55F4_1 *)scratch)->unk_114 = result;

        if (result > 0) {
            s32 third_depth;

            ((S_800C55F4_1 *)scratch)->unk_C0.u -= depth_bias;
            third_depth = ((S_800C55F4_1 *)scratch)->unk_C8.u;
            ((S_800C55F4_1 *)scratch)->unk_C4 -= depth_bias;
            vertex_depth = *(u32 *)(scratch + 0xC0);
            ((S_800C55F4_1 *)scratch)->unk_C8.s = third_depth - depth_bias;
            if (vertex_depth < 0x1E0) {
                s32 shade;
                {
                    shade = 0x100;
                    vector_arg = (u8 *)(((S_800C55F4_8 *)params)->unk_32);
                    shade -= (s32)vector_arg;
                    shade -=
                        (((S_800C55F4_1 *)scratch)->unk_CC - vertex_depth) << 5;
                    if (shade < 0x20) {
                        shade = 0x20;
                    } else if (shade >= 0x100) {
                        shade = 0xFF;
                    }
                    {
                        shade_arg = (u32)shade << 16;
                        shade_arg >>= 16;
                        convert_hsv_to_rgb(((S_800C55F4_8 *)params)->unk_30,
                                      shade_arg, 0xFF, prim + 4);
                    }
                }

                {
                    s32 second_delta;

                    vector_arg = (u8 *)0x100;
                    shade_arg = ((S_800C55F4_8 *)params)->unk_32;
                    second_delta = ((S_800C55F4_1 *)scratch)->unk_CC;
                    shade = ((S_800C55F4_1 *)scratch)->unk_C4;
                    vector_arg -= shade_arg;
                    second_delta -= shade;
                    second_delta <<= 5;
                    shade = (s32)vector_arg - second_delta;
                    if (shade < 0x20) {
                        shade = 0x20;
                    } else if (shade >= 0x100) {
                        shade = 0xFF;
                    }
                    {
                        shade_arg = (s32)(s16)shade;
                        convert_hsv_to_rgb(((S_800C55F4_8 *)params)->unk_30,
                                      shade_arg, 0xFF,
                                      prim + 0xC);
                    }
                }

                {
                    s32 third_delta;

                    vector_arg = (u8 *)0x100;
                    shade_arg = ((S_800C55F4_8 *)params)->unk_32;
                    third_delta = ((S_800C55F4_1 *)scratch)->unk_CC;
                    shade = ((S_800C55F4_1 *)scratch)->unk_C8.s;
                    vector_arg -= shade_arg;
                    third_delta -= shade;
                    third_delta <<= 5;
                    shade = (s32)vector_arg - third_delta;
                    if (shade < 0x20) {
                        shade = 0x20;
                    } else if (shade >= 0x100) {
                        shade = 0xFF;
                    }
                    {
                        shade_arg = (s32)(s16)shade;
                        convert_hsv_to_rgb(((S_800C55F4_8 *)params)->unk_30,
                                      shade_arg, 0xFF,
                                      prim + 0x14);
                    }
                }

                SetPolyG3(prim);
                packet = prim;
                packet_flags = ((S_800C55F4_4 *)packet_code)->unk_00;
                prim += 0x1C;
                ((S_800C55F4_4 *)packet_code)->unk_00 = packet_flags | 2;
                packet_code += 0x1C;
                AddPrim(((S_800C55F4_1 *)scratch)->unk_20 +
                              (((S_800C55F4_1 *)scratch)->unk_C0.s << 2), packet);

                packet_code += 0xC;
                ((S_800C55F4_2 *)mesh_data)->unk_14 &= 0x7FFF;
                SetDrawMode(prim, 0, 0, 0, 0);
                packet = prim;
                prim += 0xC;
                AddPrim(((S_800C55F4_1 *)scratch)->unk_20 +
                              (((S_800C55F4_1 *)scratch)->unk_C0.s << 2), packet);
            }
        }

        face_flags = face->flags;
        if (face_flags >= 0) {
            face++;
            continue;
        }
        break;
    }
    PopMatrix();
    ((GpuContext *)(((u8 *)global_base->draw_buffer)))->packetCursor = prim;
}
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800C5A64_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0xA];
    s16 unk_1C;
} S_800C5A64_1;   /* arg0 in damp_effect_motion_and_fade */

extern void advance_sprite_animation_and_textures();

/* Advance and damp effect motion, fade its primitive, and mark it expired when its lifetime ends. */
void damp_effect_motion_and_fade(void *effect, s32 *motion, SpriteFrameState *primitive)
{
    s16 remaining;

    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
    motion[3] -= motion[3] >> 3;
    motion[4] -= motion[4] >> 3;

    advance_sprite_animation_and_textures(primitive);

    primitive->color.c.r -= primitive->color.c.r / ((S_800C5A64_1 *)effect)->unk_10.s;
    primitive->color.c.g -= primitive->color.c.g / ((S_800C5A64_1 *)effect)->unk_10.s;
    primitive->color.c.b -= primitive->color.c.b / ((S_800C5A64_1 *)effect)->unk_10.s;

    remaining = ((S_800C5A64_1 *)effect)->unk_10.u - 1;
    ((S_800C5A64_1 *)effect)->unk_10.s = remaining;
    if ((remaining << 16) <= 0) {
        if ((((S_800C5A64_1 *)effect)->unk_0C == 0) &&
            (((S_800C5A64_1 *)effect)->unk_1C == 0)) {
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

struct Dst;
struct Elem;

extern void select_record_entry_and_value(void *state, void *entries, short index);  /* extern */
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 rand();                                /* extern */
extern s32 play_sound_if_enabled();
extern void damp_effect_motion_and_fade(void *effect, s32 *motion, SpriteFrameState *primitive);

typedef struct S_800C5BBC_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
} S_800C5BBC_3;

/* Spawn a burst of randomized particles and return the first particle. */
void *spawn_randomized_particle_burst(s16 x, s16 y, s16 z, s32 sprite_data, u16 sprite_id, s16 play_sound) {
    s32 alloc_flags;
    s32 particle_index;
    s32 remaining;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    ObjectNodeHeader *particle;
    S_800C5BBC_3 *particle_state;
    void *first_particle;

    first_particle = 0;
    if (play_sound != 0) {
        play_sound_if_enabled(0x608);
    }
    particle_index = 0;
    remaining = (rand() & 0xF) | 0x10;
    if (remaining >= 0) {
        do {
            alloc_flags = 0x12;
            if (particle_index != 0) {
                alloc_flags = 0x212;
            }
            particle = allocate_flagged_object_node(alloc_flags);
            if (particle != 0) {
                particle->update_callback = damp_effect_motion_and_fade;
                register_node(particle, project_sprite_chain);
                position = particle->position;
                position->x.w.i = (u16) x;
                position->y.w.i = y;
                position->z.w.i = z;
                position->velocity_x = (s32) (position->velocity_x + (((rand() & 0x1F) - 0x10) << 0xE));
                position->velocity_y = (s32) (position->velocity_y + (((rand() & 0x1F) - 0x10) << 0xE));
                position->velocity_z = (s32) ((0 - ((rand() & 0xF) + 0x18)) << 0xD);
                sprite = particle->sprite;
                select_record_entry_and_value(sprite, &secondary_sprite, 0);
                sprite->color.word = sprite_data;
                sprite->scale_y = 0x1000;
                sprite->scale_x = 0x1000;
                sprite->tpage_abr = sprite_id;
                sprite->clut = 3;
                sprite->flags = (u16) (sprite->flags | 0xC);
                particle_state = ((void *)particle) + 0x20;
                particle_state->unk_10 = (s16) ((rand() & 0xF) | 0x10);
                particle_state->unk_0C = particle_index;
                if (particle_index == 0) {
                    first_particle = particle;
                    g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
                }
            }
            remaining -= 1;
            particle_index += 1;
        } while (remaining >= 0);
    }
    return first_particle;
}
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800C5D80_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C5D80_0;   /* arg1 in advance_effect_motion_and_fade */

typedef struct S_800C5D80_2 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
} S_800C5D80_2;   /* arg0 in advance_effect_motion_and_fade; pointer addresses record offset 0x2 */

extern void advance_sprite_animation_and_textures();

/* Advance effect motion, fade its color, and mark it finished when its timer expires. */
void advance_effect_motion_and_fade(void *effect_data, S_800C5D80_0 *motion, SpriteFrameState *primitive) {
    s16 ticks_left;
    u8 brightness;

    motion->unk_08 += motion->unk_14;
    motion->unk_14 += 0x2000;
    advance_sprite_animation_and_textures(primitive);
    brightness = primitive->color.c.r
        - ((s32) primitive->color.c.r / (s16) ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12);
    primitive->color.c.r = brightness;
    primitive->color.c.g = brightness;
    primitive->color.c.b = brightness;
    ticks_left = (u16) ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12 - 1;
    ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        if (((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_0E == 0) {

            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
        ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_00 = (u16) (((S_800C5D80_2 *)((u8 *)effect_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* MECHANISM: Separate compound RMWs preserve retail's shared +0x14 load and v1 copy.
   A named D_80083460 base keeps +0xA as a displacement; the corrected u8 quotient
   expression restores the divide sequence, with cdk-G0 providing the retail schedule. */
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

typedef struct CounterBlock {
    u8 pad[0xA];
    u16 count;
} CounterBlock;

void select_record_entry_and_value(void *state, void *entries, short index);        /* extern */
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 play_sound_if_enabled();
extern s32 draw_linked_sprites_clipped();
struct S_800C5D80_0;
extern void advance_effect_motion_and_fade(void *effect_data, struct S_800C5D80_0 *motion, SpriteFrameState *primitive);

typedef struct S_800C5E5C_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
} S_800C5E5C_3;

/* Spawn twelve effects at the given position, optionally playing a sound. */
void spawn_vertical_particle_burst(s16 x, s16 y, s16 z, s32 sprite_id, s16 play_sound) {
    s32 object_type;
    s32 effect_index;
    s32 effect_offset;
    s32 size;
    SpriteFrameState *sprite;
    DungeonGlobalStatus *counter;
    ObjectNodeHeader *effect;
    ObjectPosition *transform;
    S_800C5E5C_3 *effect_state;
    u16 sprite_flags;

    if (play_sound != 0) {
        play_sound_if_enabled(0x816);
    }
    effect_index = 0xB;
    size = 0x20;
    counter = &g_dungeon_status;
    effect_offset = 0xFFFA0000;
    do {
        object_type = 0x12;
        if (effect_index != 0) {
            object_type = 0x212;
            effect = allocate_flagged_object_node(object_type);
        } else {
            effect = allocate_flagged_object_node(object_type);
        }
        if (effect != 0) {
            effect->update_callback = advance_effect_motion_and_fade;
            register_node(effect, draw_linked_sprites_clipped);
            transform = effect->position;
            transform->x.w.i = x;
            transform->y.w.i = y;
            transform->z.w.i = z;
            transform->velocity_z = effect_offset;
            sprite = effect->sprite;
            select_record_entry_and_value(sprite, sprite_id, 0);
            sprite_flags = sprite->flags;
            {
                s32 color;
                color = 0x808080;
                sprite->color.word = color;
            }
            {
                s32 scale;
                scale = 0x1000;
                sprite->scale_y = scale;
                sprite->scale_x = scale;
            }
            effect_state = ((void *)effect) + 0x20;
            sprite->tpage_abr = size;
            sprite_flags |= 0xC;
            sprite->flags = sprite_flags;
            effect_state->unk_10 = size;
            effect_state->unk_0C = effect_index;
            if (effect_index == 0) {
                counter->activity_counts.parts.pending_action_count = (u16) (((u16)counter->activity_counts.parts.pending_action_count) + 1);
            }
        }
        effect_offset += 0x8000;
        effect_index -= 1;
    } while (effect_index >= 0);
}
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

extern u8 floor_generation_state[];
extern u16 current_dungeon_floor;
extern u8 scene_mode_code;
extern s16 actor_event_values[];
extern u8 dungeon_event_pending_flag;
extern u8 familiar_defeat_text[];
extern u8 D_800E0B65[];
extern u8 D_800E0B73[];
extern u8 D_800E0BA1[];

void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */
void request_scene_dispatch_state();
s32 get_entity_class();
void snapshot_inventory_and_familiars();
void *get_unused_text_buffer(void);
u8 *expand_text_control_codes();
void * copy_four_text_bytes();
void clear_byte_and_advance();
void *write_text_byte_and_advance();
void unlink_entity_node();
void update_map_cell_flags_with_item_limit();
void refresh_packed_grid_nibbles();
void * detach_record_and_update_slot_state();
extern s32 play_sound_if_enabled();
void display_text_with_fullwidth_adjustment();
void check_action_boundary_and_set_flag();
s32 generate_random_value(void);
void remove_floor_items_at_tile(s16, s16);
void process_active_slots_at_coordinates(s16, s16);
void teleport_familiar_near_player();
void create_orbiting_teleport_effect();

#define CELL(xx, yy) (cells + 6 * ((xx) + ((yy) << *(s16 *)(fld + 20))))

/* Displays timed messages, clears and lowers a selected room, and handles the player's floor transition. */
void dispatch_action_callback_by_opcode(u8 *w) {
    GameWork *ctx;
    u8 *cells;
    u8 *fld;
    s32 st;
    u8 *sys;
    u8 *room;
    u8 *cnt;
    u8 *cnt2;
    u8 *rooms;
    u8 *rbase;
    u8 *rm;
    u8 *e;
    u8 *ep;
    u8 *o;
    u8 *q;
    ActorRecord *p;
    s16 *tbl;
    s32 phase0;
    s32 phase;
    void *hnd;
    void *r;
    s32 v;
    s32 x, y, x1, y1, k;
    s32 t16;
    s32 mode;
    s16 t;
    s32 rv;
    s32 cc;
    s32 ic;
    s32 ea;
    s32 eb;
    s32 ch;
    u16 f;
    u16 a;

    ctx = &g_game_work;
    phase0 = *(s16 *)w;
    cells = ((u8 *)ctx->map.cells);
    fld = (u8 *)ctx + 0x1DC;
    if (phase0 == 0) {
        st = (s32) ((u8 *)(&g_dungeon_status));
        f = *(u16 *)((u8 *) st + 2);
        if (f & 0x10) {
            *(u16 *)((u8 *) st + 2) = f | 0x200;
        }
        a = *(u16 *)((u8 *) st + 2);
        if (!(a & 0x200)) {
            return;
        }
        if ((((u32)ctx->buttons) & 0x800) && !(*(u16 *)0x80013714 & 8)) {
            return;
        }
        if (*(s32 *)((u8 *) st + 12) != 0) {
            return;
        }
        if (*(s32 *)((u8 *) st + 16) != 0) {
            return;
        }
        if (a & 8) {
            return;
        }
        if (*(s16 *)((u8 *) st + 8) != 0) {
            return;
        }
        if (*(s16 *)((u8 *) st + 20) != 0) {
            return;
        }
        if (((u32)dungeon_floor_flags) & 0x100000) {
            return;
        }
        if (*(s16 *)((u8 *) st + 10) != 0) {
            return;
        }
        if (a & 0x2C01) {
            return;
        }
        *(u16 *)((u8 *) st + 2) = a & 0xFDFF;
        if (*(s16 *)(w + 22) != 0) {
            *(u16 *)(w + 22) = *(u16 *)(w + 22) - 1;
            return;
        }
        play_sound_if_enabled(0x818);
        initialize_timed_motion_step(0x20, 8);
        *(u16 *)(w + 20) = *(u16 *)(w + 20) + 1;
        sys = (u8 *)0x80010000;
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            ic = *(u16 *)((u8 *) st + 10);
            dungeon_event_pending_flag = 1;
            *(u16 *)((u8 *) st + 10) = ic + 1;
        }
        phase = 1;
        hnd = get_unused_text_buffer();
        v = *(s16 *)(w + 20);
        if (v == phase) {
            r = expand_text_control_codes(D_800E0B65, hnd);
            if (!(*(u16 *)(sys + 0x3714) & 1)) {
                r = write_text_byte_and_advance(0x11, r);
                r = write_text_byte_and_advance(0x4C, r);
                r = copy_four_text_bytes(familiar_defeat_text, r);
            }
            clear_byte_and_advance(r);
            display_text_with_fullwidth_adjustment(hnd);
            *(s16 *)(w + 22) = 0x80;
            return;
        }
        if (v != 2) {
            goto L_third;
        }
        r = expand_text_control_codes(D_800E0B73, hnd);
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            r = write_text_byte_and_advance(0x11, r);
            r = write_text_byte_and_advance(0x4C, r);
            r = copy_four_text_bytes(familiar_defeat_text, r);
        }
        clear_byte_and_advance(r);
        display_text_with_fullwidth_adjustment(hnd);
        *(s16 *)(w + 22) = 0x40;
        return;
L_found:
        *(s16 *)(w + 6) = phase;
        t = *(u16 *)(room + 0);
        t = t - 1;
        *(s16 *)(w + 8) = t;
        *(s16 *)(w + 12) = t + *(u16 *)(room + 4) + 2;
        t = *(u16 *)(room + 2);
        t = t - 1;
        *(s16 *)(w + 10) = t;
        *(s16 *)(w + 14) = t + *(u16 *)(room + 6) + 2;
        goto L_zero;
L_third:
        r = expand_text_control_codes(D_800E0BA1, hnd);
        *(s16 *)(w + 22) = 0;
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            r = write_text_byte_and_advance(0x11, r);
            r = write_text_byte_and_advance(0x4C, r);
            r = copy_four_text_bytes(familiar_defeat_text, r);
        }
        clear_byte_and_advance(r);
        display_text_with_fullwidth_adjustment(hnd);
        *(s16 *)w = phase;
        *(u16 *)((u8 *) st + 10) = *(u16 *)((u8 *) st + 10) + 1;
        *(u16 *)(w + 4) = *(u16 *)(w + 4) + 1;
        rv = generate_random_value() & 0xFFFF;
        cnt = floor_generation_state;
        cc = *(s16 *)(cnt + 6);
        phase = rv % cc;
        st = cc;
        if (st > 0) {
            rbase = dungeon_rooms;
            cnt2 = cnt;
            do {
                room = (u8 *)(phase * 20 + (long)rbase);
                if (*(s16 *)(room + 10) != 0) {
                    goto L_found;
                }
                st = st - 1;
                phase = (phase + 1) % *(s16 *)(cnt2 + 6);
            } while (st > 0);
        }
L_zero:
        if (st == 0) {
            *(s16 *)(w + 6) = -1;
        }
        v = *(s16 *)(w + 6);
        *(s16 *)(w + 2) = 0x20;
        *(s16 *)(w + 16) = 1;
        *(s16 *)(w + 4) = 1;
        if (v >= 0) {
            x = *(s16 *)(w + 8);
            x1 = *(s16 *)(w + 12);
            y1 = *(s16 *)(w + 14);
            if (x < x1) {
                do {
                    y = *(s16 *)(w + 10);
                    if (y < y1) {
                        do {
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            process_active_slots_at_coordinates(x, y);
                            remove_floor_items_at_tile(x, y);
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                } while (x < x1);
            }
        } else {
            x = 1;
            y1 = x1 = 63;
            do {
                y = 1;
                if (y < y1) {
                    do {
                        *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                        *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                        process_active_slots_at_coordinates(x, y);
                        remove_floor_items_at_tile(x, y);
                        y = y + 1;
                    } while (y < y1);
                }
                x = x + 1;
            } while (x < x1);
        }
        tbl = actor_event_values;
        phase = *(s16 *)(w + 6);
        e = ((u8 *)dungeon_actor_ring_anchor);
        *(s16 *)(w + 18) = 0;
        do {
            ep = *(u8 * *)&((ObjectNodeHeader *)((u8 *)e - 0x20))->sprite;
            if (phase == (s16)find_padded_rectangle(*(u8 *)(ep + 36), *(u8 *)(ep + 37))) {
                if (*(u8 *)(e + 19) == 0) {
                    dungeon_floor_flags |= 0x2000;
                    create_orbiting_teleport_effect(e, tbl[get_entity_class(e)], 0, 0);
                    p = dungeon_actor_ring_anchor;
                    q = ((u8 *)p->unk_AC);
                    if (q != 0) {
                        create_orbiting_teleport_effect(q, tbl[get_entity_class(q)], 0, 0);
                    }
                    {
                        ActorRecord *p2 = dungeon_actor_ring_anchor;
                        q = ((u8 *)p2->unk_B0);
                    }
                    if (q != 0) {
                        create_orbiting_teleport_effect(q, tbl[get_entity_class(q)], 1, 0);
                    }
                    *(s16 *)(w + 18) = 1;
                } else if (*(u32 *)(e + 20) & 0x4000) {
                    if (*(s16 *)(w + 18) == 0) {
                        teleport_familiar_near_player(e, *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + 172) != e);
                    }
                } else {
                    if (*(s16 *)(w + 18) != 0) {
                        *(s16 *)(e + 108) = 0;
                    }
                    o = e;
                    ea = *(u8 *)(ep + 36);
                    eb = *(u8 *)(ep + 37);
                    mode = 0x3000;
                    e = *(u8 **)(o + 88) + 32;
                    if (*(u32 *)(o + 28) & 0x2000) {
                        mode = 0x300;
                    }
                    update_map_cell_flags_with_item_limit(ea, eb, mode);
                    if ((*(u32 *)(o + 20) & 0x20000000) && *(u8 *)(o + 19) == 30) {
                        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
                    }
                    detach_record_and_update_slot_state(o);
                    unlink_entity_node(o);
                    ((ObjectNodeHeader *)((u8 *)o - 0x20) )->flags|= NODE_REMOVE;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                }
            }
            e = *(u8 **)(e + 92) + 32;
        } while (e != ((u8 *)dungeon_actor_ring_anchor));
        if (phase < 0) {
            return;
        }
        rooms = dungeon_rooms;
        rm = rooms + phase * 20;
        *(s16 *)(rm + 10) = 0;
        return;
    }
    if (phase0 == 1) {
        if (*(s16 *)(w + 6) >= 0) {
            x = *(s16 *)(w + 8);
            x1 = *(s16 *)(w + 12);
            y1 = *(s16 *)(w + 14);
            k = 0;
            if (*(s16 *)(w + 4) > 0) {
                do {
                    y = *(s16 *)(w + 10);
                    if (y < y1) {
                        do {
                            s32 mul8 = 8 - (generate_random_value() & 7);
                            s32 dec = *(s16 *)(w + 4) - 1;
                            *(u16 *)(CELL(x, y) + 2) -= mul8 * (dec - k);
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                    if (x >= x1) {
                        break;
                    }
                    k = k + 1;
                } while (k < *(s16 *)(w + 4));
            }
        } else {
            x = 1;
            y1 = x1 = 63;
            k = 0;
            if (*(s16 *)(w + 4) > 0) {
                do {
                    y = 1;
                    if (y < y1) {
                        do {
                            s32 mul8 = 8 - (generate_random_value() & 7);
                            s32 dec = *(s16 *)(w + 4) - 1;
                            *(u16 *)(CELL(x, y) + 2) -= mul8 * (dec - k);
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                    if (x >= x1) {
                        break;
                    }
                    k = k + 1;
                } while (k < *(s16 *)(w + 4));
            }
        }
        t16 = *(u16 *)(w + 16) - 1;
        *(u16 *)(w + 16) = t16;
        if ((s16) t16 > 0) {
            return;
        }
        *(s16 *)(w + 16) = 1;
        *(u16 *)(w + 4) = *(u16 *)(w + 4) + 1;
        refresh_packed_grid_nibbles();
        if (!((x1 + 16) < *(s16 *)(w + 4))) {
            return;
        }
        if (*(s16 *)(w + 18) == 0) {
            *(s16 *)w = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
            return;
        }
        ctx->view.slot[0].callback = 0;
        ctx->view.slot[2].callback = 0;
        *(u16 *)w = *(u16 *)w + 1;
        return;
    }
    o = (u8 *)0x80010000;
    if (*(u16 *)(o + 0x3714) & 4) {
        request_scene_dispatch_state(3);
        return;
    }
    snapshot_inventory_and_familiars(((u8 *)dungeon_actor_ring_anchor));
    snapshot_inventory_familiar_records();
    check_action_boundary_and_set_flag();
    {
        u8 code;

        ch = *(u32 *)(o + 0x234);
        code = scene_mode_code;
        ch++;
        *(u32 *)(o + 0x234) = ch;
        ch = code;
    }
    current_dungeon_floor = *(u16 *)(o + 0x234);
    request_scene_dispatch_state(ch);
    mark_sprite_resources_for_purge();
    *(u16 *)(w - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
#include "common.h"
#include "shared/object_node.h"

typedef struct {
    s32 unk0[4];
    void *field10;
} Func8003FF2CResult;

extern Func8003FF2CResult *initialize_runtime_node_storage(s32, s32 *, s16, s32 *);
extern void dispatch_action_callback_by_opcode(u8 *w);
extern s32 D_800E58B8[];

/* Create a record and assign dispatch_action_callback_by_opcode to its field10 pointer. */
void create_record_with_effect_callback(void) {
    initialize_runtime_node_storage(0, D_800E58B8, 0x10, ((s32 *)(&scene_object_list_anchor)))->field10 = dispatch_action_callback_by_opcode;
}
#include "common.h"

typedef struct Func800C138CData {
    u8 pad0[8];
    void *context;
    void *data;
} Func800C138CData;

extern void draw_sprite_parts_as_quad_grid(s32 context, void *position, void *sprite, s16 depth_bias);

/* Process each linked state with draw_sprite_parts_as_quad_grid in mode zero. */
s32 process_linked_states_mode_zero(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        draw_sprite_parts_as_quad_grid(state, context, data, 0);
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((Func800C138CData *)next_node)->context;
        data = ((Func800C138CData *)next_node)->data;
    }
}
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct ScratchDepth {
    u8 pad0[0xC0];
    u32 depth;
} ScratchDepth;

typedef struct S_800C6B40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
} S_800C6B40_0;   /* arg2 in draw_sprite_parts_as_quad_grid */

typedef struct S_800C6B40_1 {
    u8 unk_00;
    u8 pad_01[0x3];
    u16 unk_04;
    u16 unk_06;
    union {
        struct { u8 v; } at00;
        struct { void * v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_08;   /* overlapping accesses */
} S_800C6B40_1;

typedef struct {
    u8 pad_00[0x3];
    s8 len;
    union {
        s32 color;
        struct { u8 pad[0x3]; s8 code; } at03;
    } unk_04;   /* overlapping accesses */
    u16 x0;
    u16 y0;
    s8 u0;
    s8 v0;
    s16 clut;
    u16 x1;
    u16 y1;
    s8 u1;
    s8 v1;
    u16 tpage;
    u16 x2;
    u16 y2;
    s8 u2;
    s8 v2;
    u8 pad_1E[0x2];
    u16 x3;
    s16 y3;
    s8 u3;
    s8 v3;
} QuadPrim;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
    u16 origin_x;
    u16 origin_y;
} RotationWork;

extern void *CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void *ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotTransPers(void *, void *, ...);
void RotTransPers4();
extern void *RotMatrix(void *, void *);
extern void AddPrim(void *, void *);
extern s32 sprite_projection_matrix[];

/* Draws sprite parts as a 4-by-4 grid of textured quads, invoking custom part callbacks. */
void draw_sprite_parts_as_quad_grid(s32 context, void *position, void *sprite, s16 depth_bias) {
    u8 *scratch = (u8 *)0x1F800000;
    u8 *state;
    GameWork *render_globals;
    s32 packet_next;
    s16 local_y;
    s16 local_x;
    s32 (*draw_callback)(s32, void *, void *, void *, s32);
    s32 top_visible;
    s32 three_visible;
    s32 top_dx;
    s32 left_dy;
    s32 bottom_dx;
    s32 right_dy;
    s32 height;
    s32 left_dy_fixed;
    s32 right_dy_fixed;
    s32 bottom_left_visible;
    s32 top_dx_fixed;
    s32 bottom_dx_fixed;
    s32 top_left_visible;
    s32 next_right_y;
    s32 right_y;
    s32 column;
    register s32 matrix_or_u;
    s32 texture_v;
    s32 bottom_x;
    s32 top_x;
    s32 left_y;
    s32 bottom_y;
    s32 row;
    register s32 bottom_x_step;
    register s32 top_x_step;
    register s32 left_y_step;
    register s32 u_step;
    register s32 v_step;
    register s32 right_y_step;
    s32 width;
    s32 kseg_base;
    s32 visible_or_result;
    s32 saved_right_y;
    s32 part_flags;
    s32 bottom_right_visible;
    s32 u_end;
    s32 v_end;
    u16 center_x;
    u16 projected_left_x;
    u16 center_y;
    u16 tpage;
    u32 clut;
    u32 flipped_width;
    u32 normal_width;
    u32 clip_y;
    u32 flipped_height;
    u32 normal_height;
    u32 sprite_flags;
    s32 angle_offset;
    u32 origin_x;
    u32 origin_y;
    u16 projected_left_y;
    u16 projected_right_y;
    u16 draw_flags;
    s8 command;
    u32 depth;
    u32 sort_depth;
    u32 bottom_clip_y;
    u8 uv_inset;
    void *part;

    render_globals = &g_game_work;
    state = g_game_work.draw_buffer;
    *(u32 *)(scratch + 0x0EC) = NULL;
    *(u16 *)(scratch + 0x08C) = 0;
    *(u16 *)(scratch + 0x084) = 0;
    *(u16 *)(scratch + 0x07C) = 0;
    *(u16 *)(scratch + 0x074) = 0;
    *(u32 *)(scratch + 0x020) = state + 0xB0;
    *(u16 *)(scratch + 0x000) = (u16)(*(u16 *)((u8 *)position + 2));
    *(u16 *)(scratch + 0x002) = (u16)(*(u16 *)((u8 *)position + 6));
    *(u16 *)(scratch + 0x004) = (u16)(*(u16 *)((u8 *)position + 0xA));
    packet_next = *(s32 *)(state + 0x8D0);
    ((ScratchDepth *)scratch)->depth = RotTransPers(scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);
    matrix_or_u = (s32)sprite_projection_matrix;
    (*(u16 *)((u8 *)sprite + 0x14)) = (u16)((*(u16 *)((u8 *)sprite + 0x14)) | 0x8000);
    depth = ((ScratchDepth *)scratch)->depth;
    *(s32 *)((u8 *)matrix_or_u + 0x1C) = (s32)(depth * 4);
    depth -= 8;
    sort_depth = depth - depth_bias;
    *(u32 *)(scratch + 0x0C0) = sort_depth;
    if (sort_depth < 0x1E0U) {
        PushMatrix();
        *(u16 *)(scratch + 0x0B8) = (u16)(*(u16 *)(scratch + 0x0B8) - 0xA0);
        *(u16 *)(scratch + 0x0BA) = (u16)(*(u16 *)(scratch + 0x0BA) - 0x78);
        *(u32 *)(scratch + 0x030) = render_globals->view.camera_rotation.parts.camera_rotation_x;
        *(u32 *)(scratch + 0x034) = render_globals->view.camera_rotation.parts.camera_rotation_y;
        *(u32 *)(scratch + 0x038) = render_globals->view.camera_rotation.parts.viewAngle;
        ((RotationWork *)(scratch + 0x100))->x = (u16)(*(u16 *)((u8 *)sprite + 0x16));
        ((RotationWork *)(scratch + 0x100))->z = (s16)(((S_800C6B40_0 *)sprite)->unk_1A - (u16)*(u32 *)(scratch + 0x034));
        ((RotationWork *)(scratch + 0x100))->y = (s16)((((u16)*(u32 *)(scratch + 0x038) + 0x100) & 0x1FF)
            + (angle_offset = (s32)((S_800C6B40_0 *)sprite)->unk_18 - 0x100));
        origin_x = ((S_800C6B40_0 *)sprite)->unk_20;
        *(u32 *)(scratch + 0x0E4) = origin_x;
        ((RotationWork *)(scratch + 0x100))->origin_x = origin_x;
        origin_y = (*(u16 *)((u8 *)sprite + 0x22));
        *(u32 *)(scratch + 0x0E8) = origin_y;
        ((RotationWork *)(scratch + 0x100))->origin_y = origin_y;
        RotMatrix(0x1F800100, 0x1F8000D0);
        *(u32 *)(scratch + 0x030) = (void *)((S_800C6B40_0 *)sprite)->unk_1C;
        *(u32 *)(scratch + 0x034) = (void *)(*(u16 *)((u8 *)sprite + 0x1E));
        *(u32 *)(scratch + 0x038) = NULL;
        ScaleMatrix(scratch + 0xD0, scratch + 0x30);
        CompMatrix((s32 *)matrix_or_u, scratch + 0xD0, scratch + 0x50);
        SetTransMatrix(scratch + 0x50);
        SetRotMatrix(scratch + 0x50);
        sprite_flags = ((S_800C6B40_0 *)sprite)->unk_14;
        part = ((S_800C6B40_0 *)sprite)->unk_08;
        *(u16 *)(scratch + 0x024) = (u16)sprite_flags;
        do {
            if (!(((S_800C6B40_1 *)part)->unk_00 & 0x20)) {
                *(u32 *)(scratch + 0x008) = (s32)((S_800C6B40_1 *)part)->unk_08.at00.v;
                *(u32 *)(scratch + 0x00C) = (s32)((S_800C6B40_1 *)part)->unk_08.at01.v;
                *(u32 *)(scratch + 0x010) = (s32)((S_800C6B40_1 *)part)->unk_08.at02.v;
                *(u32 *)(scratch + 0x014) = (s32)((S_800C6B40_1 *)part)->unk_08.at03.v;
                if ((((S_800C6B40_1 *)part)->unk_00 ^ (u32)*(u16 *)(scratch + 0x024)) & 1) {
                    local_x = (0 - (s8)(*(u8 *)((u8 *)part + 2))) - (s32)(u32)*(u16 *)(scratch + 0x108);
                    flipped_width = *(u16 *)(scratch + 0x010);
                    *(u16 *)(scratch + 0x080) = local_x;
                    *(u16 *)(scratch + 0x070) = local_x;
                    local_x -= flipped_width;
                    *(u16 *)(scratch + 0x088) = local_x;
                    *(u16 *)(scratch + 0x078) = local_x;
                } else {
                    local_x = (s8)(*(u8 *)((u8 *)part + 2)) - (s32)(u32)*(u16 *)(scratch + 0x108);
                    normal_width = *(u16 *)(scratch + 0x010);
                    *(u16 *)(scratch + 0x080) = local_x;
                    *(u16 *)(scratch + 0x070) = local_x;
                    local_x += normal_width;
                    *(u16 *)(scratch + 0x088) = local_x;
                    *(u16 *)(scratch + 0x078) = local_x;
                }
                if ((((S_800C6B40_1 *)part)->unk_00 ^ (u32)*(u16 *)(scratch + 0x024)) & 2) {
                    local_y = (0 - (s8)(*(u8 *)((u8 *)part + 3))) - (s32)(u32)*(u16 *)(scratch + 0x10A);
                    flipped_height = *(u16 *)(scratch + 0x014);
                    *(u16 *)(scratch + 0x07A) = local_y;
                    *(u16 *)(scratch + 0x072) = local_y;
                    local_y -= flipped_height;
                    *(u16 *)(scratch + 0x08A) = local_y;
                    *(u16 *)(scratch + 0x082) = local_y;
                } else {
                    local_y = (s8)(*(u8 *)((u8 *)part + 3)) - (s32)(u32)*(u16 *)(scratch + 0x10A);
                    normal_height = *(u16 *)(scratch + 0x014);
                    *(u16 *)(scratch + 0x07A) = local_y;
                    *(u16 *)(scratch + 0x072) = local_y;
                    local_y += normal_height;
                    *(u16 *)(scratch + 0x08A) = local_y;
                    *(u16 *)(scratch + 0x082) = local_y;
                }
                RotTransPers4(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0,
                    scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
                width = *(u32 *)(scratch + 0x010);
                if (width < 0) {
                    width += 3;
                }
                height = *(u32 *)(scratch + 0x014);
                u_step = width >> 2;
                if (height < 0) {
                    height += 3;
                }
                top_dx = (s16)*(u16 *)(scratch + 0x0F4) - (s16)*(u16 *)(scratch + 0x0F0);
                top_dx_fixed = top_dx << 0x10;
                v_step = height >> 2;
                if (top_dx_fixed < 0) {
                    top_dx_fixed += 3;
                }
                projected_left_y = *(u16 *)(scratch + 0x0F2);
                left_dy = (s16)*(u16 *)(scratch + 0x0FA) - (s16)projected_left_y;
                left_dy_fixed = left_dy << 0x10;
                top_x_step = top_dx_fixed >> 2;
                if (left_dy_fixed < 0) {
                    left_dy_fixed += 3;
                }
                bottom_dx = (s16)*(u16 *)(scratch + 0x0FC) - (s16)*(u16 *)(scratch + 0x0F8);
                bottom_dx_fixed = bottom_dx << 0x10;
                left_y_step = left_dy_fixed >> 2;
                if (bottom_dx_fixed < 0) {
                    bottom_dx_fixed += 3;
                }
                projected_right_y = *(u16 *)(scratch + 0x0F6);
                right_dy = (s16)*(u16 *)(scratch + 0x0FE) - (s16)projected_right_y;
                right_dy_fixed = right_dy << 0x10;
                bottom_x_step = bottom_dx_fixed >> 2;
                if (right_dy_fixed < 0) {
                    right_dy_fixed += 3;
                }
                row = 0;
                right_y_step = right_dy_fixed >> 2;
                center_y = *(u16 *)(scratch + 0x0BA);
                texture_v = *(u32 *)(scratch + 0x00C);
                left_y = ((s16)center_y + (s16)projected_left_y) << 0x10;
                right_y = ((s16)center_y + (s16)projected_right_y) << 0x10;
                next_right_y = right_y + right_y_step;
                do {
                    column = 0;
                    bottom_y = next_right_y >> 0x10;
                    bottom_clip_y = (bottom_y + 0x20) & 0xFFFF;
                    center_x = *(u16 *)(scratch + 0x0B8);
                    matrix_or_u = *(u32 *)(scratch + 0x008);
                    projected_left_x = *(u16 *)(scratch + 0x0F0);
                    top_x = ((s16)center_x + (s16)projected_left_x) << 0x10;
                    bottom_x = ((s16)center_x + (s16)*(u16 *)(scratch + 0x0F8)) << 0x10;
                    do {
                        top_left_visible = 0;
                        ((QuadPrim *)packet_next)->x0 = (u16)(top_x >> 0x10);
                        ((QuadPrim *)packet_next)->x1 = (u16)((s32)(top_x + top_x_step) >> 0x10);
                        ((QuadPrim *)packet_next)->x2 = (u16)(bottom_x >> 0x10);
                        ((QuadPrim *)packet_next)->x3 = (u16)((s32)(bottom_x + bottom_x_step) >> 0x10);
                        ((QuadPrim *)packet_next)->y0 = (u16)(left_y >> 0x10);
                        ((QuadPrim *)packet_next)->y1 = (u16)(right_y >> 0x10);
                        ((QuadPrim *)packet_next)->y2 = (u16)((s32)(left_y + left_y_step) >> 0x10);
                        ((QuadPrim *)packet_next)->y3 = (s16)bottom_y;
                        if ((u32)((((QuadPrim *)packet_next)->x0 + 0x20) & 0xFFFF) < 0x181U) {
                            clip_y = (((QuadPrim *)packet_next)->y0 + 0x20) & 0xFFFF;
                            top_left_visible = clip_y < 0x121U;
                        }
                        visible_or_result = 0;
                        if ((u32)((((QuadPrim *)packet_next)->x1 + 0x20) & 0xFFFF) < 0x181U) {
                            clip_y = (((QuadPrim *)packet_next)->y1 + 0x20) & 0xFFFF;
                            visible_or_result = clip_y < 0x121U;
                        }
                        bottom_left_visible = 0;
                        top_visible = top_left_visible | visible_or_result;
                        if ((u32)((((QuadPrim *)packet_next)->x2 + 0x20) & 0xFFFF) < 0x181U) {
                            clip_y = (((QuadPrim *)packet_next)->y2 + 0x20) & 0xFFFF;
                            bottom_left_visible = clip_y < 0x121U;
                        }
                        bottom_right_visible = 0;
                        three_visible = top_visible | bottom_left_visible;
                        if ((u32)((((QuadPrim *)packet_next)->x3 + 0x20) & 0xFFFF) < 0x181U) {
                            bottom_right_visible = bottom_clip_y < 0x121U;
                        }
                        if ((three_visible | bottom_right_visible) != 0) {
                            uv_inset = ((S_800C6B40_0 *)sprite)->unk_0C.at03.v;
                            u_end = (matrix_or_u + u_step) - uv_inset;
                            if (matrix_or_u >= u_end) {
                                u_end = matrix_or_u + 1;
                            }
                            v_end = (texture_v + v_step) - uv_inset;
                            if (texture_v >= v_end) {
                                v_end = texture_v + 1;
                            }
                            if (u_end >= 0x100) {
                                u_end = 0xFF;
                            }
                            if (v_end >= 0x100) {
                                v_end = 0xFF;
                            }
                            ((QuadPrim *)packet_next)->u0 = (s8)matrix_or_u;
                            ((QuadPrim *)packet_next)->v0 = (s8)texture_v;
                            ((QuadPrim *)packet_next)->u1 = (s8)u_end;
                            ((QuadPrim *)packet_next)->v1 = (s8)texture_v;
                            ((QuadPrim *)packet_next)->u2 = (s8)matrix_or_u;
                            ((QuadPrim *)packet_next)->v2 = (s8)v_end;
                            ((QuadPrim *)packet_next)->u3 = (s8)u_end;
                            ((QuadPrim *)packet_next)->v3 = (s8)v_end;
                            ((QuadPrim *)packet_next)->len = 9;
                            clut = ((S_800C6B40_0 *)sprite)->unk_12;
                            ((S_800C6B40_0 *)sprite)->unk_14 = (u16)(((S_800C6B40_0 *)sprite)->unk_14 & 0x7FFF);
                            clut += ((S_800C6B40_1 *)part)->unk_06;
                            ((QuadPrim *)packet_next)->clut = (s16)clut;
                            if (((S_800C6B40_0 *)sprite)->unk_10 != 0) {
                                tpage = ((S_800C6B40_0 *)sprite)->unk_10 + (((S_800C6B40_1 *)part)->unk_04 & 0xFF9F);
                            } else {
                                tpage = ((S_800C6B40_1 *)part)->unk_04;
                            }
                            ((QuadPrim *)packet_next)->tpage = tpage;
                            ((QuadPrim *)packet_next)->unk_04.color = (s32)((S_800C6B40_0 *)sprite)->unk_0C.at00.v;
                            ((QuadPrim *)packet_next)->unk_04.at03.code = 0x2C;
                            draw_flags = *(u16 *)(scratch + 0x024);
                            if (draw_flags & 8) {
                                if (!(draw_flags & 4)) {
                                    command = 0x2C;
                                    ((QuadPrim *)packet_next)->unk_04.at03.code = command;
                                } else {
                                    command = 0x2E;
                                    ((QuadPrim *)packet_next)->unk_04.at03.code = command;
                                }
                            }
                            AddPrim((u8 *)*(u32 *)(scratch + 0x020) + ((u32)*(u32 *)(scratch + 0x0C0) * 4),
                                packet_next);
                            packet_next += 0x28;
                        }
                        column += 1;
                        matrix_or_u += u_step;
                        top_x += top_x_step;
                        bottom_x += bottom_x_step;
                    } while (column < 4);
                    row += 1;
                    texture_v += v_step;
                    left_y += left_y_step;
                    saved_right_y = next_right_y;
                    next_right_y += right_y_step;
                    right_y = saved_right_y;
                } while (row < 4);
            } else {
                draw_callback = (s32 (*)(s32, void *, void *, void *, s32))((S_800C6B40_1 *)part)->unk_08.at00u.v;
                if (draw_callback != NULL) {
                    visible_or_result = draw_callback(context, position, sprite, part, packet_next);
                    kseg_base = 0x80000000;
                    if (visible_or_result > 0) {
                        part = (void *)(visible_or_result | kseg_base);
                    } else {
                        packet_next = visible_or_result;
                    }
                }
            }
            part_flags = (s8)((S_800C6B40_1 *)part)->unk_00;
            part += 0xC;
        } while (part_flags >= 0);
        PopMatrix();
    }
    *(s32 *)(*(u32 *)&render_globals->draw_buffer + 0x8D0) = packet_next;
}
#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 z;
} DungeonCoord;

typedef struct {
    u8 pad0[8];
    void *image;
    s32 color;
    s16 width;
    s16 pad12;
    s16 blend;
    u16 blend2;
    s16 shade;
    s16 pad1A;
    s16 size;
    s16 limit;
    u16 flags;
    u16 depth;
} DungeonRender;

typedef struct {
    void *parent;
    u8 pad4[9];
    s8 angle;
    u8 pad14[2];
    s16 mode;
    s16 value;
    u8 pad20[4];
    s16 height;
    s16 frame;
    s16 speed;
    s16 limit;
} DungeonState;

typedef struct {
    u8 pad0[8];
    ObjectPosition *coord;
    DungeonRender *render;
    void *callback;
    u8 pad20[12];
    DungeonState state;
} DungeonObject;

extern void copy_words_forward(void *, void *, s32);
extern void *allocate_list_node(s32, void *);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 rsin(s32);
extern s32 rcos(s32);
extern s32 draw_linked_sprites_clipped();
extern u8 D_800777E8[];
extern void update_timed_tile_effect();
extern void update_pulsing_color_fade();
extern u8 D_800D0774[];
extern u8 D_800DF3B4[];

/* Creates a dungeon effect with a central object and up to eleven surrounding children. */
DungeonObject *create_central_and_child_effects(s16 tile_x, s16 tile_y, u16 z, s16 height, s16 speed) {
    s32 color;
    DungeonObject *parent;
    DungeonObject *child;
    DungeonState *state;
    ObjectPosition * center;
    ObjectPosition *child_coord;
    DungeonRender *render;
    void *image_data;
    s16 shade;
    s32 remaining;
    s32 angle;
    void *callback_fn;

    parent = allocate_list_node(0x12, ((u8 *)(&scene_object_list_anchor)));
    if (parent != NULL) {
        s16 frame;
        u16 state_limit;
        parent->callback = update_timed_tile_effect;
        register_node(parent, draw_linked_sprites_clipped);
        color = 0x404040;
        state = &parent->state;
        remaining = 0xB;
        shade = -0xAA7;
        center = parent->coord;
        center->x.w.i = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
        angle = 0xEA7;
        center->y.w.i = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
        center->z.w.i = z;
        render = parent->render;
        render->image = D_800777E8;
        render->limit = 0x1800;
        render->size = 0x1800;
        render->width = 0x20;
        render->depth = 0xFFFB;
        render->color = color;
        render->flags = 0xFFFF;
        render->blend = (s16) (render->blend | 0xC);
        frame = 0x37;
        state->mode = tile_x;
        state_limit = 0x14;
        state->value = tile_y;
        state->height = height;
        state->limit = state_limit;
        state->speed = speed;
        callback_fn = update_pulsing_color_fade;
        do {
            child = allocate_list_node(0x12, parent);
            if (child != NULL) {
                DungeonObject *init_child;
                void *child_resource;
                init_child = child;
                child_resource = D_800D0774;
                child->callback = callback_fn;
                register_node(init_child, child_resource);
                child_coord = child->coord;
                child_coord->x.w.i = (s16) (center->x.w.i + (rcos(angle) >> 7));
                child_coord->y.w.i = (s16) (center->y.w.i + (rsin(angle) >> 7));
                child_coord->z.w.i = *(u16 *)&center->z.w.i;
                render = child->render;
                render->blend2 = 0xFC00;
                render->shade = shade;
                render->size = 0x410;
                if (state->height < 0) {
                    render->width = 0x40;
                }
                state = &child->state;
                image_data = (void *) ((u8 *) child + 0x24);
                state->height = height;
                render->image = image_data;
                copy_words_forward(image_data, D_800DF3B4, 3);
                state->angle = (s8) (frame & 0xBF);
                state->frame = frame;
                state->parent = parent;
            }
            shade += 0x155;
            angle -= 0x155;
            remaining -= 1;
            frame -= 5;
        } while (remaining > 0);
    }
    return parent;
}
#include "common.h"
#include "shared/game_work.h"

extern s16 sample_terrain_surface_height(u16, u16, s16);
extern u8 camera_height_tracking[];
extern u8 camera_transition_timer[];
extern u16 effect_saved_position[];

/* Update target tracking and smoothly approach its position and transition value. */
void update_target_tracking_and_transition(void *tracker) {
    GameView *state = &g_game_work.view;
    s16 frames_left;
    s16 next_frames;
    s16 target_height;
    u16 *target_pos;
    void *tracked_object;

    tracked_object = *(void **)((char *)tracker + 0x34);
    if ((tracked_object != 0) && (*(u16 *)((char *)tracked_object + 0x1E) & 0x8000)) {
        u16 *saved_pos = effect_saved_position;
        *(void **)((char *)tracker + 0x34) = 0;
        saved_pos[1] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 2);
        saved_pos[3] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 6);
        saved_pos[5] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 0xA);
        *(void **)((char *)tracker + 0xC) = saved_pos;
    }
    frames_left = *(s16 *)((char *)tracker + 0x24);
    if (frames_left > 0) {
        state->view_offset.parts.view_offset_z = (u16)state->view_offset.parts.view_offset_z +
            (*(s16 *)((char *)tracker + 0x26) - state->view_offset.parts.view_offset_z) / frames_left;
    } else {
        camera_transition_timer[0] = 0;
    }
    next_frames = *(s16 *)((char *)tracker + 0x24) - 1;
    *(s16 *)((char *)tracker + 0x24) = next_frames;
    if (next_frames < -0x80) {
        *(s16 *)((char *)tracker + 0x24) = -0x80;
    }
    *(u16 *)((char *)tracker + 4) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 2);
    *(u16 *)((char *)tracker + 6) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 6);
    target_pos = *(u16 **)((char *)tracker + 0xC);
    target_height = sample_terrain_surface_height(target_pos[1], target_pos[3], (s16)(target_pos[5] - 0x20));
    *(s16 *)((char *)tracker + 8) = target_height;
    if (target_height >= 0x201) {
        *(s16 *)((char *)tracker + 8) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 0xA);
    }
    state->camera_position.parts.camera_position_x = (u16)state->camera_position.parts.camera_position_x + ((s32)((s16)*(u16 *)((char *)tracker + 4) - state->camera_position.parts.camera_position_x) >> 2);
    state->camera_position.parts.camera_position_y = (u16)state->camera_position.parts.camera_position_y + ((s32)((s16)*(u16 *)((char *)tracker + 6) - state->camera_position.parts.camera_position_y) >> 2);
    if (camera_height_tracking[0] != 0) {
        state->camera_position.parts.camera_position_z = (u16)state->camera_position.parts.camera_position_z + ((s32)(*(s16 *)((char *)tracker + 8) - state->camera_position.parts.camera_position_z) >> 2);
    }
    camera_height_tracking[0] = (s8)(state->camera_position.parts.camera_position_z != *(s16 *)((char *)tracker + 8));
    state->view_offset.parts.view_offset_x = (s32)(((u16)state->view_offset.parts.view_offset_x) << 0x10) >> 0x12;
    state->view_offset.parts.view_offset_y = (s32)(((u16)state->view_offset.parts.view_offset_y) << 0x10) >> 0x12;
}
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"

extern void update_target_tracking_and_transition(void *tracker);
extern u8 camera_transition_timer[];

/* Selects a nearby target, initializes its state slot, and returns change flags. */
s32 select_nearby_target_and_initialize_slot(void *tracked_object, void *target_data, s32 target_id, s32 slot_value) {
    ObjectPosition *target = target_data;
    s32 distance;
    s32 target_coord;
    s32 change_flags;
    void *previous_target;
    GameView *state;
    u8 *slot;
    s16 new_target_id;

    distance = view_reference_entity.x.w.i;
    target_coord = target->x.w.i;
    distance -= target_coord;
    if (distance < 0)
        distance = -distance;
    new_target_id = target_id;
    if (distance >= 0xC1) {
        return 0;
    }
    distance = view_reference_entity.y.w.i;
    target_coord = target->y.w.i;
    distance -= target_coord;
    if (distance < 0)
        distance = -distance;
    if (distance >= 0xC1) {
        return 0;
    }

    state = &g_game_work.view;
    slot = (u8 *)state + 0xB8;
    previous_target = *(void **)(slot + 0xC);
    *(void **)(slot + 0x34) = tracked_object;
    *(void **)(slot + 0xC) = target;
    *(s32 *)(slot + 0x28) = 0;
    *(void **)slot = slot + 4;
    change_flags = previous_target != target;
    if (*(s32 *)(slot + 0x14) != 9)
        change_flags |= 2;
    *(s32 *)(slot + 0x14) = 9;
    *(s32 *)(slot + 0x18) = 0;
    *(s16 *)(slot + 0x26) = slot_value;
    state->slot[0].callback = update_target_tracking_and_transition;
    if (change_flags & 1)
        camera_transition_timer[0] = new_target_id;
    *(s16 *)(slot + 0x24) = target_id;
    return change_flags;
}
#include "common.h"
#include "shared/entity_objects.h"

extern u16 effect_saved_position[];
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);

/* Sets up the object at the supplied position if both planar distances are at most 192. */
void setup_object_within_planar_range(void *object, s32 x, s32 y, s32 height, s32 mode, s32 settings)
{
    s32 saved_mode;

    saved_mode = mode;
    mode = view_reference_entity.x.w.i - x;
    if (mode < 0) {
        mode = -mode;
    }
    if (mode < 193) {
        mode = view_reference_entity.y.w.i - y;
        if (mode < 0) {
            mode = -mode;
        }
        if (mode < 193) {
            u16 *position = effect_saved_position;

            position[1] = x;
            position[3] = y;
            position[5] = height;
            select_nearby_target_and_initialize_slot(object, position, (s16)saved_mode, settings);
        }
    }
}
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"

typedef struct S_800C7930_1 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C7930_1;   /* source in apply_camera_offset_and_select_target */

typedef struct S_800C7930_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800C7930_2;   /* work in apply_camera_offset_and_select_target */

typedef struct S_800C7930_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C7930_3;   /* destination in apply_camera_offset_and_select_target */

extern u16 effect_saved_position[];
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);

/* Apply table offsets to a position near the camera and pass it to select_nearby_target_and_initialize_slot. */
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value)
{
    s32 delta;
    s32 source_coord;
    s32 x_offset_index;
    s32 y_offset_index;
    s32 adjusted_x;
    u16 y_offset;
    u16 source_x;
    S_800C7930_2 *work;
    register ObjectPosition *camera;
    u8 *destination;
    register u8 *x_offsets;
    register u8 *y_offsets;
    void *object = object_addr;
    S_800C7930_1 *source = source_pos;

    camera = &view_reference_entity;

    delta = camera->x.w.i;
    source_coord = source->unk_02.s;
    source_x = source->unk_02.u;
    delta -= source_coord;
    if (delta < 0) {
        delta = -delta;
    }
    if (delta < 0xC1) {
        delta = camera->y.w.i;
        source_coord = source->unk_06.s;
        delta -= source_coord;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < 0xC1) {
            work = (u8 *)object + 0x20;
            destination = effect_saved_position;
            x_offsets = (u8 *)direction_x_offsets;
            x_offset_index = (work->unk_2A >> 8) & 0xE;
            adjusted_x = (s16)*(u16 *)(x_offsets + x_offset_index) / 2;
            ((S_800C7930_3 *)destination)->unk_02 = ((s32)(source_x - -adjusted_x));
            y_offsets = (u8 *)direction_y_offsets;
            y_offset_index = (work->unk_2A >> 8) & 0xE;
            y_offset = *(u16 *)(y_offsets + y_offset_index);
            ((S_800C7930_3 *)destination)->unk_06 = source->unk_06.u + (s16)y_offset / 2;
            ((S_800C7930_3 *)destination)->unk_0A = source->unk_0A;
            select_nearby_target_and_initialize_slot(object, destination, (s16)helper_arg, slot_value);
        }
    }
    return 0;
}
#include "common.h"
#include "shared/entity_objects.h"

extern u16 effect_saved_position[];
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);

/* Process the midpoint of two objects when it is near the reference position. */
void process_nearby_object_midpoint(u8 *start_obj, u8 *end_obj, s16 start_height, s16 end_height, s16 call_param, s32 call_arg) {
    s32 frame_pad[2];
    s32 coord;
    s32 mid_coord;
    s32 x_distance;
    s32 y_adjust;
    s16 *midpoint;

    coord = (start_obj[0x24] << 6) + 0x20;
    mid_coord = (end_obj[0x24] << 6) + 0x20;
    mid_coord = mid_coord - coord;
    mid_coord = mid_coord >> 1;
    coord = coord + mid_coord;
    mid_coord = coord;
    x_distance = view_reference_entity.x.w.i - mid_coord;
    if (x_distance < 0) {
        x_distance = -x_distance;
    }
    if (x_distance < 0xC1) {
        midpoint = effect_saved_position;
        midpoint[1] = mid_coord;
        coord = (start_obj[0x25] << 6) + 0x20;
        mid_coord = (end_obj[0x25] << 6) + 0x20;
        mid_coord = mid_coord - coord;
        y_adjust = (u32)mid_coord >> 31;
        mid_coord = mid_coord + y_adjust;
        mid_coord = mid_coord >> 1;
        coord = coord + mid_coord;
        mid_coord = coord;
        y_adjust = view_reference_entity.y.w.i - mid_coord;
        if (y_adjust < 0) {
            y_adjust = -y_adjust;
        }
        if (y_adjust < 0xC1) {
            midpoint[3] = mid_coord;
            midpoint[5] = start_height + ((end_height - start_height) / 2);
            select_nearby_target_and_initialize_slot(0, midpoint, call_param, call_arg);
        }
    }
}
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Entity transition state */
typedef struct Entity {
    u8    pad0[0xC];
    void *unkC;      /* 0x0C -> Sub */
    s32   unk10;     /* 0x10 */
    u8    pad14[4];
    s32   unk18;     /* 0x18 state selector */
    u8    pad1C[8];
    s16   unk24;     /* 0x24 countdown */
    u16   unk26;     /* 0x26 */
} Entity;

typedef struct Sub {
    u8  pad0[2];
    s16 f2;   /* 0x02 */
    u8  pad4[2];
    s16 f6;   /* 0x06 */
    u8  pad8[2];
    s16 fA;   /* 0x0A */
} Sub;

/* View over the D_80083178 dispatch/blend record (fields not in game.h struct) */

extern s16 camera_pitch_index;
extern s16 camera_pitch_presets[];
extern s16 camera_depth_target[5];

extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);

/* Blend toward the entity target, then dispatch the next state. */
void blend_entity_toward_target_state(void *entity_data) {
    Entity *entity = entity_data;
    GameView *blend = &g_game_work.view;
    s32 state = entity->unk18;

    switch (state) {
    case 0:
        if (entity->unk24 > 0) {
            s16 half_ticks;
            s16 *table = camera_pitch_presets;
            entity->unk10 -= entity->unk10 >> 2;
            blend->view_offset.parts.view_offset_z = entity->unk26 + (u16)entity->unk10;
            blend->camera_rotation.parts.camera_rotation_x = (u16)blend->camera_rotation.parts.camera_rotation_x + (table[camera_pitch_index] - blend->camera_rotation.parts.camera_rotation_x) / entity->unk24;
            blend->camera_rotation.parts.viewAngle = (u16)blend->camera_rotation.parts.viewAngle + (0 - blend->camera_rotation.parts.viewAngle) / entity->unk24;
            blend->camera_position.parts.camera_position_x = (u16)blend->camera_position.parts.camera_position_x + (((Sub *)entity->unkC)->f2 - blend->camera_position.parts.camera_position_x) / entity->unk24;
            blend->camera_position.parts.camera_position_y = (u16)blend->camera_position.parts.camera_position_y + (((Sub *)entity->unkC)->f6 - blend->camera_position.parts.camera_position_y) / entity->unk24;
            half_ticks = (s16)(u16)entity->unk24 / 2;
            if (half_ticks != 0) {
                blend->camera_position.parts.camera_position_z = (u16)blend->camera_position.parts.camera_position_z + (((Sub *)entity->unkC)->fA - blend->camera_position.parts.camera_position_z) / half_ticks;
            }
            {
                s16 ticks_left = (u16)entity->unk24 - 1;
                entity->unk24 = ticks_left;
                if (ticks_left > 0) {
                    return;
                }
            }
        }
        {
            s16 *table = camera_pitch_presets;
            blend->camera_rotation.parts.camera_rotation_x = (u16)table[camera_pitch_index];
        }
        blend->camera_rotation.parts.viewAngle = 0;
        blend->view_offset.parts.view_offset_z = entity->unk26;
        entity->unk18 += 1;
        return;
    case 1:
        select_nearby_target_and_initialize_slot((u8 *)dungeon_actor_ring_anchor - 0x20, ((u8 *)(&view_reference_entity)), 8, camera_depth_target[0]);
        g_dungeon_status.activity_counts.parts.pending_action_count = g_dungeon_status.activity_counts.parts.pending_action_count - 1;
    }
}
#include "common.h"

typedef void (*Callback)(s16, s16, s16, s16);

typedef struct CallbackEntry {
    Callback callback;
    s16 stored_arg0;
    s16 stored_arg1;
    s16 stored_arg2;
    s16 stored_arg3;
} CallbackEntry;

extern CallbackEntry *D_800DF640[4];
extern u8 D_800DF64C[9];
extern void submit_indexed_entry_and_finalize(u32);

/* Runs the selected callback list (after submitting its CD entry) with each entry's stored arguments. */
void run_indexed_callback_list(s16 list_index) {
    CallbackEntry *entry;

    submit_indexed_entry_and_finalize(D_800DF64C[list_index]);
    entry = D_800DF640[list_index];
    while (entry->callback != 0) {
        entry->callback(entry->stored_arg0, entry->stored_arg1, entry->stored_arg2, entry->stored_arg3);
        entry++;
    }
}
#include "common.h"
#include "shared/dungeon_status.h"

typedef struct DungeonCell {
    s16 flags;
    u8 pad02[0x12];
} DungeonCell;

typedef struct DungeonGroup {
    u8 pad00[0xC];
    DungeonCell *cells;
    u8 pad10[4];
} DungeonGroup;

typedef struct Object {
    u8 pad00[0x13];
    u8 value13;
    u8 pad14[8];
    u32 flags1C;
    u8 pad20[8];
    u8 value28;
    u8 pad29[0x23];
    u8 *target4C;
    u8 *mode50;
    u8 pad54[0xC];
    u32 value60;
    u16 value64;
} Object;

typedef struct Other {
    u8 pad00[0x54];
    u32 flags54;
    u8 pad58[0xC];
    u16 value64;
} Other;

extern DungeonGroup item_category_groups[];
extern u8 pending_player_damage_kind;
extern s32 play_sound_if_enabled();
extern void create_textured_ellipse_effect(void *, Object *);

/* Apply a mode-adjusted quarter-value change when the source and target item flags permit it. */
s32 prepare_quarter_damage_return(Object *object, Other *source) {
    u8 *target_item;
    s16 total_value;
    u8 mode;
    s16 adjustment;

    if (source->flags54 & 0x8000) {
        target_item = object->target4C;
        if (target_item != 0) {
            u8 category_index;
            DungeonGroup *item_category_table;
            DungeonGroup *item_category;
            DungeonCell *item_entries;
            u8 item_index;

            category_index = target_item[1];
            item_category_table = item_category_groups;
            item_category = &item_category_table[category_index];
            item_index = target_item[0];

            item_entries = item_category->cells;
            if (!(item_entries[item_index].flags & 0x8000)) {
                return 0;
            }
        }
        total_value = object->value28 + object->value64;
        if (total_value <= 0) {
            return 0;
        }
        adjustment = (s16)source->value64 >> 2;
        if (adjustment == 0) {
            adjustment = -1;
        }
        if (-total_value >= (s16)adjustment) {
            return 0;
        }
        if (object->mode50 != 0) {
            mode = object->mode50[0];
            if ((u32)(mode - 1) < 2) {
                adjustment = (adjustment - 1) / 2;
            } else if (mode == 10) {
                return 0;
            }
        }
        *(u16 *)&object->value64 = adjustment;
        g_dungeon_status.pending_display_owner = (u8 *)object - 0x20;
        object->value60 = 0;
        create_textured_ellipse_effect(((ObjectNodeHeader *)((u8 *)object - 0x20))->position, object);
        play_sound_if_enabled(0x60F);
        object->flags1C |= 0x20000000;
        if (object->value13 == 0) {
            pending_player_damage_kind = 2;
        }
        return 1;
    }
    return 0;
}
