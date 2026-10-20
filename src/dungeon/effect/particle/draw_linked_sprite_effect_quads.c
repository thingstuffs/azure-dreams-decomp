#include "dungeon/effect/particle/draw_linked_sprite_effect_quads.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
/* cfail-repair: tf7-phase1-cache-v3 */
s32 resolve_record_orientation_or_fallback();     /* extern */
void apply_attack_power_and_element_effects(); /* extern */
void *find_eligible_nearby_entry();           /* extern */
s32 play_sound_if_enabled();                     /* extern */

typedef struct S_func_819B2800_0 {
    void *unk_00;
    u16 *unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 unk_0A; u16 unk_A; } unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    union { s16 unk_052; u16 unk_52; } unk_52;
} S_func_819B2800_0;

typedef struct S_func_819B2800_1 {
    s32 unk_00;
    s32 unk_04;
    union {
        s32 unk_08;
        struct { u8 pad_08[2]; u16 unk_0A; } unk_0A;
    } unk_08;
} S_func_819B2800_1;

typedef struct S_func_819B2800_2 {
    u8 pad_00[0x10];
    s32 *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
    u8 pad_24[6];
    s16 unk_2A;
} S_func_819B2800_2;

typedef struct S_func_819B2800_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
} S_func_819B2800_3;

typedef struct S_func_819B2800_4 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u8 pad_12[0xA];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} S_func_819B2800_4;

typedef struct S_func_819B2800_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x7A];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
    u8 pad_F8[0xA];
    s8 unk_102;
} S_func_819B2800_5;

typedef struct S_func_819B2800_6 {
    u8 pad_00[8];
    s32 unk_08;
} S_func_819B2800_6;

typedef struct S_func_819B2800_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_func_819B2800_7;

typedef struct S_func_819B2800_8 {
    u16 unk_00;
} S_func_819B2800_8;

void update_directional_actor_effect(S_func_819B2800_0 *effect, S_func_819B2800_1 *position);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The phase table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_19d2800_entry)(S_func_819B2800_0 *, S_func_819B2800_1 *) = update_directional_actor_effect;

/* Advances a timed effect, spawns its visuals, and applies it to nearby targets. */
void update_directional_actor_effect(S_func_819B2800_0 *effect, S_func_819B2800_1 *position) {
    s16 offset[3];
    u16 next_phase;
    u16 timer;
    s32 effect_code;
    s16 direction;
    s32 phase_or_delay;
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
    s32 target;
    S_func_819B2800_4 *visual;
    u8 *data_bytes;
    S_func_819B2800_6 *model;
    S_func_819B2800_5 *actor;
    S_func_819B2800_2 *object_data;
    S_func_819B2800_3 *location;

    timer = ((volatile S_func_819B2800_0 *) effect)->unk_50;
    object_data = ((volatile S_func_819B2800_0 *) effect)->unk_00;
    phase_or_delay = effect->unk_0A.unk_0A;
    effect->unk_50 = (u16) (timer - 1);
    location = (S_func_819B2800_3 *) ((u8 *) object_data - 0x20);
    switch (phase_or_delay) {
    case 0:
        ((S_func_819B2800_5 *) ((s32*)((int *)(&D_800814A8)))[0])->unk_102 = 1;
        ((S_func_819B2800_5 *) ((s32*)((int *)(&D_800814A8)))[0])->unk_F4 = 0;
        position->unk_00 = (s32) ((S_func_819B2800_1 *) location->unk_08)->unk_00;
        position->unk_04 = (s32) ((S_func_819B2800_1 *) location->unk_08)->unk_04;
        position->unk_08.unk_08 = (s32) ((S_func_819B2800_1 *) location->unk_08)->unk_08.unk_08;
        effect->unk_0A.unk_0A = (s16) ((u16) effect->unk_0A.unk_0A + 1);
    case 1:
        if (!(*effect->unk_04 & 0x80)) {
            return;
        }
        actor = (void *) ((s32*)((int *)(&D_800814A8)))[0];
        effect->unk_50 = 0xAU;
        actor->unk_A6 = (u16) (actor->unk_A6 - 1);
        actor->unk_A8 = (u8) effect->unk_08;
        object_data = (S_func_819B2800_2 *) allocate_list_node(0x302, ((u8 *)(&D_80083498)));
        if (object_data != 0) {
            model = location->unk_0C;
            if (resolve_record_orientation_or_fallback(model->unk_08, model, offset, 0) == 0) {
                offset[2] = 0;
                offset[1] = 0;
                offset[0] = 0;
            }
            visual = (S_func_819B2800_4 *) ((u8 *) object_data + 0x20);
            object_data->unk_10 = update_animated_target_effect;
            register_node(object_data, draw_linked_sprite_effect_quads);
            pos_x = ((S_func_819B2800_1 *) location->unk_08)->unk_00 + (offset[0] << 0x10);
            position->unk_00 = pos_x;
            visual->unk_1C = pos_x;
            pos_y = ((S_func_819B2800_1 *) location->unk_08)->unk_04 + (offset[1] << 0x10);
            position->unk_04 = pos_y;
            visual->unk_20 = pos_y;
            pos_z = ((S_func_819B2800_1 *) location->unk_08)->unk_08.unk_08 + (offset[2] << 0x10);
            position->unk_08.unk_08 = pos_z;
            visual->unk_24 = pos_z;
            object_data->unk_20 = effect;
        }
        next_phase = effect->unk_0A.unk_A;
        next_phase++;
        effect->unk_0A.unk_A = next_phase;
        return;
    case 2:
        if ((s16) effect->unk_50 > 0) {
            return;
        }
        if (func_80053EF0(4) != 2) {
            effect_code = 0x300;
        } else {
            effect_code = 0x4300;
        }
        play_sound_if_enabled(effect_code);
        next_phase = effect->unk_0A.unk_A;
        phase_or_delay = 0xD;
        effect->unk_50 = phase_or_delay;
        next_phase++;
        effect->unk_0A.unk_A = next_phase;
        return;
    case 3:
        if ((s16) effect->unk_50 == 2) {
            func_800419EC(0x18, 0x10);
        }
        if ((s16) effect->unk_50 > 0) {
            return;
        }
        object_data = (S_func_819B2800_2 *) allocate_list_node(0x302, ((u8 *)(&D_80083498)));
        data_bytes = (u8 *) object_data;
        if (object_data != 0) {
            visual = (S_func_819B2800_4 *) ((u8 *) object_data + 0x20);
            object_data->unk_10 = update_actor_movement_animation_collision;
            register_node(data_bytes, draw_fading_radial_effect_grid);
            data_bytes = ((u8 *)(&D_80082E80));
            direction = ((u16) ((S_func_819B2800_5 *) ((s32*)((int *)(&D_800814A8)))[0])->unk_2A >> 9) & 7;
            offset[0] = direction;
            visual->unk_0C = (s16) (((S_func_819B2800_3 *) ((u8 *)(&D_80082E80)))->unk_24 + dir_step_x[direction]);
            visual->unk_0E = (s16) (((S_func_819B2800_3 *) ((u8 *)(&D_80082E80)))->unk_25 + dir_step_y[offset[0]]);
            visual->unk_10 = (u16) position->unk_08.unk_0A.unk_0A;
            object_data->unk_20 = effect;
        }
        next_phase = effect->unk_0A.unk_A;
        phase_or_delay = 0x10;
        effect->unk_50 = phase_or_delay;
        next_phase++;
        effect->unk_0A.unk_A = next_phase;
        return;
    case 4:
        if ((s16) effect->unk_50 == 8) {
            target = ((s32*)((int *)(&D_800814A8)))[0];
            position = (void *) target;
            if (target != 0) {
                location = (S_func_819B2800_3 *) ((u8 *)(&D_80082E80));
next_target:
                target = find_eligible_nearby_entry(location->unk_24, location->unk_25, position, (void *) target);
                if (target != 0) {
                    if (!(((S_func_819B2800_5 *) target)->unk_1C & 0x2000)) {
                        apply_attack_power_and_element_effects((void *) target, 0x10, effect->unk_09, 0xC, (s32) object_data->unk_2A,
                            object_data, 2);
                    }
                    goto next_target;
                }
            }
        }
        if (!(D_80082E80.unk_014 & 0x8000)) {
            if ((s16) effect->unk_50 >= 0) {
                return;
            }
        }
        if (effect->unk_52.unk_052 & 0x8000) {
            effect->unk_52.unk_52 = (u16) (effect->unk_52.unk_52 & 0x7FFF);
            return;
        }
        g_dungeon_status.unk_0C = 0;
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
        ((S_func_819B2800_8 *) ((u8 *) effect - 2))->unk_00 = (u16) (((S_func_819B2800_8 *) ((u8 *) effect - 2))->unk_00
            | 0x8000);
        object_flag_block.flags |= 0x8000;
        return;
    }
}
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_node.h"

/* A sprite effect record (the object header precedes it): world position of the centre, the size and the
 * texture window of the quad it draws.  The coordinates sit in 4-byte slots with only the second halfword used. */
typedef struct SpriteEffect {
    u8 pad_00[0x1E];
    u16 x;              /* 0x1E */
    u8 pad_20[2];
    u16 y;              /* 0x22 */
    u8 pad_24[2];
    u16 z;              /* 0x26 */
    u8 pad_28[0x18];
    u8 tex_u;           /* 0x40 */
    u8 pad_41;
    u8 tex_v;           /* 0x42 */
    u8 pad_43;
    u8 tex_width;       /* 0x44 */
    u8 pad_45;
    u8 tex_height;      /* 0x46 */
    u8 pad_47[7];
    u16 size;           /* 0x4E: world-space width */
    u16 tpage;          /* 0x50 */
    u16 clut;           /* 0x52 */
} SpriteEffect;

/* The two projected points (centre and one edge): x/y in 4-byte slots. */
typedef struct ScreenPoints {
    u16 x0;
    s16 y0;
    u16 x1;
    s16 y1;
} ScreenPoints;

/* Textured quad, four vertices with separate halfword coordinates (cf. PolyFT4). */
typedef struct SpriteQuad {
    u32 tag;
    s32 color;
    u16 x0;
    u16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    u16 x1;
    u16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    u16 x2;
    u16 y2;
    u8 u2;
    u8 v2;
    u8 pad_1E[2];
    u16 x3;
    u16 y3;
    u8 u3;
    u8 v3;
} SpriteQuad;

extern s32 func_80065420();
extern void func_80066640();
extern void func_800666F4();

/* Retail 819B2C40 (draw_linked_sprite_effect_quads): projects each linked sprite effect and queues a textured quad centred on
 * its screen position into the ordering table.  The chain runs through the previous header's unk_18 link. */
s32 draw_linked_sprite_effect_quads(SpriteEffect *first_item) {
    u16 world_pos[4];
    ScreenPoints screen_points;
    s32 projection_scratch;
    SpriteEffect *node = first_item;
    GameWork *render_state = &g_game_work;
    void *screen_base = &screen_points;
    ObjectNodeHeader *next_node;

    for (;;) {
        SpriteEffect *item = node;
        void *screen_point;
        s32 point_index;
        u32 depth_index;
        s32 half_width;
        u16 center_z;

        world_pos[0] = item->x;
        world_pos[1] = item->y;
        center_z = item->z;
        world_pos[2] = center_z;
        world_pos[2] = center_z - ((s32)(item->size << 16) >> 17);

        point_index = 0;
        screen_point = screen_base;
        do {
            depth_index = func_80065420(world_pos, screen_point, &projection_scratch, &projection_scratch) - 8;
            screen_point = (u8 *)screen_point + 4;
            point_index++;
            world_pos[2] += item->size;
        } while (point_index < 2);

        half_width = (screen_points.y0 - screen_points.y1) >> 1;
        if (depth_index < 0x1E0U) {
            GpuContext *packet_pool;
            SpriteQuad *packet;
            u8 tex_v;
            u8 tex_u;
            u8 tex_width;
            u16 screen_coord;
            u32 ot_slot;
            u32 depth_offset;
            u32 addr_mask = 0;
            u32 color_or_tag_mask = 0;

            packet_pool = render_state->unk_000;
            packet = (SpriteQuad *)packet_pool->packetCursor;
            packet_pool->packetCursor = (u8 *)packet + 0x34;
            packet->color = 0xA0A0A0;
            func_800666F4(packet);
            func_80066640(packet, 1);

            packet->tpage = item->tpage;
            packet->clut = item->clut;
            screen_coord = screen_points.x0 + half_width;
            packet->x1 = screen_coord;
            packet->x0 = screen_coord;
            screen_coord = screen_points.x0 - half_width;
            packet->x3 = screen_coord;
            packet->x2 = screen_coord;
            screen_coord = screen_points.y0;
            packet->y2 = screen_coord;
            packet->y0 = screen_coord;
            screen_coord = screen_points.y1;
            packet->y3 = screen_coord;
            packet->y1 = screen_coord;

            tex_u = item->tex_u;
            addr_mask = 0xFFFFFF;
            packet->u1 = tex_u;
            packet->u0 = tex_u;
            tex_width = item->tex_width;
            tex_u += tex_width;
            packet->u3 = tex_u;
            packet->u2 = tex_u;
            tex_v = item->tex_v;
            depth_offset = depth_index << 2;
            packet->v2 = tex_v;
            packet->v0 = tex_v;
            tex_v += item->tex_height;
            color_or_tag_mask = 0xFF000000;
            packet->v3 = tex_v;
            packet->v1 = tex_v;

            packet->tag =
                (packet->tag & color_or_tag_mask) |
                (*(u32 *)((u8 *)(depth_offset + (u32)render_state->unk_000) + 0xB0) & addr_mask);
            ot_slot = depth_offset + (u32)render_state->unk_000;
            *(u32 *)((u8 *)ot_slot + 0xB0) =
                (*(u32 *)((u8 *)ot_slot + 0xB0) & color_or_tag_mask) |
                ((u32)packet & addr_mask);
        }

        next_node = ((ObjectNodeHeader *)node - 1)->chain_next;
        if (next_node == 0) {
            break;
        }
        node = (SpriteEffect *)(next_node + 1);
    }

    return 0;
}
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8002466C_0 {
    void * unk_00;
    u8 pad_04[0x18];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_20;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_24;   /* overlapping accesses */
    u8 pad_28[0x18];
    s16 unk_40;
    s16 unk_42;
    s16 unk_44;
    s16 unk_46;
    union { u16 s; s16 u; } unk_48;   /* accessed as both */
    u16 unk_4A;
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
} S_8002466C_0;   /* arg0 in update_animated_target_effect */

typedef struct S_8002466C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8002466C_1;   /* owner in update_animated_target_effect */

typedef struct S_8002466C_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002466C_2;   /* ctx1 in update_animated_target_effect */

typedef struct S_8002466C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002466C_3;   /* coords1 in update_animated_target_effect */

typedef struct S_8002466C_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002466C_4;   /* ctx2 in update_animated_target_effect */

typedef struct S_8002466C_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002466C_5;   /* coords2 in update_animated_target_effect */

typedef struct S_8002466C_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8002466C_6;   /* obj in update_animated_target_effect */

typedef struct S_8002466C_7 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002466C_7;   /* draw in update_animated_target_effect */

typedef struct S_8002466C_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8002466C_8;   /* disp in update_animated_target_effect */

typedef struct S_8002466C_9 {
    u8 pad_00[0x4C];
    s16 unk_4C;
} S_8002466C_9;   /* ent in update_animated_target_effect */

typedef struct S_8002466C_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8002466C_10;   /* ((S_8002466C_6 *)obj)->unk_08 in update_animated_target_effect */


extern s16 GetTPage(s32, s32, s32, s32);
extern s16 GetClut(s32, s32);
extern s32 resolve_record_orientation_or_fallback(void *, void *, s16 *, s32);
extern s32 func_800644B8(s32);
extern s32 rand(void);

extern u8 D_800DEA68[];

/* Update the animated effect, track its target, and spawn scattered particles. */
void update_animated_target_effect(void *effect)
{
    s16 target_pos[3];
    s16 state;
    s32 last_particle;
    s32 particle_index;
    s32 display_link;
    u16 frames_left;
    void *owner;
    TileObject *approach_target;
    TileObject *follow_target;
    void *particle;
    void *particle_state;
    void *sprite;
    void *particle_data;
    void *display;

    owner = ((S_8002466C_0 *)effect)->unk_00;
    ((S_8002466C_0 *)effect)->unk_48.s = ((S_8002466C_0 *)effect)->unk_48.s + 1;
    ((S_8002466C_1 *)owner)->unk_52 |= 0x8000;
    last_particle = -1;
    state = ((S_8002466C_0 *)effect)->unk_4C.s;
    switch (state) {
    case 0:
        ((S_8002466C_0 *)effect)->unk_50 = GetTPage(0, 1, 0x2C0, 0x100);
        ((S_8002466C_0 *)effect)->unk_52 = GetClut(0xC0, 0x1F7);
        ((S_8002466C_0 *)effect)->unk_46 = 0x1F;
        ((S_8002466C_0 *)effect)->unk_44 = 0x1F;
        ((S_8002466C_0 *)effect)->unk_48.s = 0;
        ((S_8002466C_0 *)effect)->unk_4E = 0x30;
        ((S_8002466C_0 *)effect)->unk_4C.s = ((S_8002466C_0 *)effect)->unk_4C.u + 1;
    case 1:
        last_particle = 0xE;
        approach_target = &D_80082E80;
        if (resolve_record_orientation_or_fallback(((void *)approach_target->unk_008), approach_target, target_pos, 0) != 0) {
            ((S_8002466C_0 *)effect)->unk_1C.at00.v +=
                ((target_pos[0] + D_80083780.x.w.i) -
                 ((S_8002466C_0 *)effect)->unk_1C.at02.v) << 14;
            ((S_8002466C_0 *)effect)->unk_20.at00.v +=
                ((target_pos[1] + D_80083780.y.w.i) -
                 ((S_8002466C_0 *)effect)->unk_20.at02.v) << 14;
            ((S_8002466C_0 *)effect)->unk_24.at00.v +=
                ((target_pos[2] + D_80083780.z.w.i) -
                 ((S_8002466C_0 *)effect)->unk_24.at02.v) << 14;
            ((S_8002466C_0 *)effect)->unk_24.at00.v -=
                func_800644B8((((S_8002466C_0 *)effect)->unk_48.u << 11) / 10) << 9;
        }
        if (((S_8002466C_0 *)effect)->unk_48.u >= 0xA) {
            ((S_8002466C_0 *)effect)->unk_4A = 0x10;
            ((S_8002466C_0 *)effect)->unk_4C.s = ((S_8002466C_0 *)effect)->unk_4C.u + 1;
        }
        break;

    case 2:
        last_particle = 9;
        if (((S_8002466C_0 *)effect)->unk_48.u >= 0xB) {
            last_particle = 4;
        }
        ((S_8002466C_0 *)effect)->unk_4E += 2;
        follow_target = &D_80082E80;
        if (resolve_record_orientation_or_fallback(((void *)follow_target->unk_008), follow_target, target_pos, 0) != 0) {
            ((S_8002466C_0 *)effect)->unk_1C.at00.v +=
                ((target_pos[0] + D_80083780.x.w.i) -
                 ((S_8002466C_0 *)effect)->unk_1C.at02.v) << 15;
            ((S_8002466C_0 *)effect)->unk_20.at00.v +=
                ((target_pos[1] + D_80083780.y.w.i) -
                 ((S_8002466C_0 *)effect)->unk_20.at02.v) << 15;
            ((S_8002466C_0 *)effect)->unk_24.at00.v +=
                ((target_pos[2] + D_80083780.z.w.i) -
                 ((S_8002466C_0 *)effect)->unk_24.at02.v) << 15;
        }
        if (((S_8002466C_0 *)effect)->unk_48.u >= 0xD) {
            ((S_8002466C_0 *)effect)->unk_48.s = 8;
        }
        frames_left = ((S_8002466C_0 *)effect)->unk_4A - 1;
        ((S_8002466C_0 *)effect)->unk_4A = frames_left;
        if (((s32)(frames_left << 16) <= 0) &&
            (((S_8002466C_0 *)effect)->unk_48.u == 0xC)) {
            ((S_8002466C_0 *)effect)->unk_4C.s = ((S_8002466C_0 *)effect)->unk_4C.u + 1;
        }
        break;

    case 3:
        last_particle = 5;
        if (((S_8002466C_0 *)effect)->unk_48.u == 0xF) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
        break;
    }
    particle_index = last_particle;

    ((S_8002466C_0 *)effect)->unk_40 = ((((S_8002466C_0 *)effect)->unk_48.s & 3) << 5) + 0x80;
    ((S_8002466C_0 *)effect)->unk_42 =
        (((s32)(((S_8002466C_0 *)effect)->unk_48.s << 16) >> 18) << 5) + 0x80;
    if (particle_index >= 0) {
        particle_data = build_and_queue_interpolated_vertical_quads_around_five_perimeter_points;
        display = D_800DEA68;
        do {
            particle = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
            if (particle != NULL) {
                ((S_8002466C_6 *)particle)->unk_10 = particle_data;
                register_node(particle, project_sprite_chain);
                sprite = ((S_8002466C_6 *)particle)->unk_0C;
                particle_state = (u8 *)particle + 0x20;
                ((S_8002466C_10 *)(((S_8002466C_6 *)particle)->unk_08))->unk_00 =
                    ((S_8002466C_0 *)effect)->unk_1C.at00.v +
                    (((rand() & 0x3FF) - 0x1FF) << 12);
                ((S_8002466C_10 *)(((S_8002466C_6 *)particle)->unk_08))->unk_04 =
                    ((S_8002466C_0 *)effect)->unk_20.at00.v +
                    (((rand() & 0x3FF) - 0x1FF) << 12);
                ((S_8002466C_10 *)(((S_8002466C_6 *)particle)->unk_08))->unk_08 =
                    ((S_8002466C_0 *)effect)->unk_24.at00.v +
                    (((rand() & 0x3FF) - 0x1FF) << 11);
                ((S_8002466C_7 *)sprite)->unk_1E = 0x1000;
                ((S_8002466C_7 *)sprite)->unk_1C = 0x1000;
                ((S_8002466C_7 *)sprite)->unk_10 = 0x60;
                ((S_8002466C_7 *)sprite)->unk_00 = display;
                ((S_8002466C_7 *)sprite)->unk_14 |= 0xC;
                display_link = ((S_8002466C_8 *)display)->unk_04;
                ((S_8002466C_7 *)sprite)->unk_04 = 0;
                ((S_8002466C_7 *)sprite)->unk_05 = 0;
                ((S_8002466C_7 *)sprite)->unk_0C = 0x808080;
                ((S_8002466C_7 *)sprite)->unk_08 = display_link;
                ((S_8002466C_6 *)particle)->unk_20 = ((S_8002466C_0 *)effect)->unk_00;
                ((S_8002466C_9 *)particle_state)->unk_4C = 0;
            }
            particle_index -= 1;
        } while (particle_index >= 0);
    }
}

/* MECHANISM: (1) held-base locals approach_target/follow_target for D_80082E80 keep retail's
   lui/addiu/lw 8(a1) triple instead of gcc folding D+8 into one %lo; (2) the
   /10 divide is written inline off the s16 field so gcc emits lh + sll 11, not
   lhu + sll 16 / sra 5 (an s16 temp costs an extra word); (3) the sprite-tail
   order puts the two sb 0 stores after the display link load; (4) particle+0x20:
   particle_state is taken right after the sprite load, ahead of the sprite
   stores, so its addiu survives unfolded and lands after the unk_20 store.
   RESIDUE: 276/280 words byte-identical; the only 4 diffs are this function's
   OWN local j words, all solving true link base 0x8002466C vs the synthetic
   0x819B2E6C - a rowbase base shift, not a C or compiler gap. */

#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

/* The object an effect belongs to: bit 0x8000 of its +0x52 flag word marks it. */
typedef struct EffectOwner {
    u8 pad_00[0x52];
    u16 flags;
} EffectOwner;

/* The effect's own record; the 0x20-byte ObjectNodeHeader sits right before it. */
typedef struct EffectRecord {
    EffectOwner *owner;
} EffectRecord;

/* The sprite entry func_800478B8 updates; +0x14 carries the status bits tested below. */
typedef struct SpriteEntry {
    u8 pad_00[0x14];
    u16 status;
} SpriteEntry;



/* Retail 819B32CC (build_and_queue_interpolated_vertical_quads_around_five_perimeter_points): marks the owner, and once the sprite reaches status 0x6000 marks the
 * effect's own header and the global object flags too. */
void build_and_queue_interpolated_vertical_quads_around_five_perimeter_points(EffectRecord *effect, void *unused, SpriteEntry *sprite) {
    EffectOwner *owner = effect->owner;

    owner->flags |= 0x8000;
    func_800478B8(sprite);
    if (sprite->status & 0x6000) {
        ((ObjectNodeHeader *)effect - 1)->flags |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */


typedef struct S_80024B48_0_pre {
    u16 unk_00;
} S_80024B48_0_pre;   /* the 0x2 bytes before arg0 in update_actor_movement_animation_collision, addressed as arg0[-1] */

typedef struct S_80024B48_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x38];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80024B48_0;   /* arg0 in update_actor_movement_animation_collision */


typedef struct S_80024B48_2 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024B48_2;   /* ((S_80024B48_0 *)arg0)->unk_00 in update_actor_movement_animation_collision */

/* Initialize object coordinates and set completion flags after 32 ticks. */
void update_actor_movement_animation_collision(void *object) {
    s32 tile_x;
    s32 tile_y;
    s32 offset_tile_x;
    s32 offset_tile_y;

    ((S_80024B48_2 *)(((S_80024B48_0 *)object)->unk_00))->unk_52 =
        (s16) (((S_80024B48_2 *)(((S_80024B48_0 *)object)->unk_00))->unk_52 | 0x8000);
    ((S_80024B48_0 *)object)->unk_48 = (u16) (((S_80024B48_0 *)object)->unk_48 + 1);
    if (((S_80024B48_0 *)object)->unk_4C != 0) {
        if (((S_80024B48_0 *)object)->unk_4C != 1) {
            return;
        }
    } else {
        tile_x = (s16) ((S_80024B48_0 *)object)->unk_0C;
        tile_y = (s16) ((S_80024B48_0 *)object)->unk_0E;
        ((S_80024B48_0 *)object)->unk_48 = 0U;
        ((S_80024B48_0 *)object)->unk_04 = (s16) ((tile_x << 6) + 0x20);
        ((S_80024B48_0 *)object)->unk_06 = (s16) ((tile_y << 6) + 0x20);
        offset_tile_x = (s16) ((S_80024B48_0 *)object)->unk_0C;
        offset_tile_y = (s16) ((S_80024B48_0 *)object)->unk_0E;
        ((S_80024B48_0 *)object)->unk_0C = (s16) ((offset_tile_x - 7) << 6);
        ((S_80024B48_0 *)object)->unk_0E = (s16) ((offset_tile_y - 7) << 6);
        ((S_80024B48_0 *)object)->unk_4C = (s16) ((u16) ((S_80024B48_0 *)object)->unk_4C + 1);
    }
    if ((s16) ((S_80024B48_0 *)object)->unk_48 >= 0x20) {
        (*(u16 *)((u8 *)object + (-2))) = (u16) (((S_80024B48_0_pre *)object)[-1].unk_00 | 0x8000);
        (object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
    }
}
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct Quad {
    u32 tag;
    u32 color0;
    u32 xy0;
    u32 color1;
    u32 xy1;
    u32 color2;
    u32 xy2;
    u32 color3;
    u32 xy3;
} Quad;

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

extern s32 func_800644B8();
extern s32 func_80064710();
extern s32 func_80065420();
extern s32 func_80066460();
extern void func_80066640();
extern s32 func_80066708();
extern s32 func_80067F20();

/* Draw fading radial grids of shaded quads for the linked effects. */
s32 draw_fading_radial_effect_grid(void *effect_data) {
    u16 vertex[3];
    u32 screen_grid[16][16];
    s32 depth_cue;
    s32 projection_flags;
    u8 *effect;
    u8 *next_effect;
    GameWork *gw = &g_game_work;
    u8 *scratch = (u8 *)0x1f800000;
    s32 grid_last = 15;

    do {
        effect = (u8 *)effect_data;

        {
            s32 seed_index = 7;
            u32 *seed_color;
            seed_color = (u32 *)scratch + 7;
            seed_loop: {
                s32 phase;
                s32 shade;
                s32 upper_channels;
                phase = seed_index + *(s16 *)(effect + 0x48);
                shade = func_800644B8(phase * 1200);
                shade = (shade >> 7) + 32;
                upper_channels = (shade << 8) + (shade << 16);
                shade += upper_channels;
                *seed_color = shade;
                seed_color--;
            } if (--seed_index >= 0) goto seed_loop;
        }

        {
            s32 row;
            for (row = 0; row < 16; row++) {
                s32 row_offset;
                s32 column;
                column = 0;
                row_offset = row << 6;
                do {
                    s32 dx_square;
                    s32 dy_square;
                    s32 distance;
                    s32 shade;
                    s32 faded_shade;
                    s32 column_offset = column << 6;

                    vertex[0] = *(u16 *)(effect + 0x0c) + column_offset;
                    vertex[1] = *(u16 *)(effect + 0x0e) + row_offset;
                    vertex[2] = *(u16 *)(effect + 0x10);
                    func_80065420(vertex, &screen_grid[column][row],
                        &depth_cue, &projection_flags);

                    vertex[0] -= *(u16 *)(effect + 4);
                    dx_square = (s16)vertex[0] * (s16)vertex[0];
                    vertex[1] -= *(u16 *)(effect + 6);
                    dy_square = (s16)vertex[1] * (s16)vertex[1];
                    distance = func_80064710(dx_square + dy_square);
                    shade = func_800644B8(
                        100 * (distance >> 2) -
                        (*(s16 *)(effect + 0x48) << 8));
                    shade = (shade >> 7) + 32;
                    faded_shade = shade * (32 - *(s16 *)(effect + 0x48));
                    depth_cue = shade;
                    if (faded_shade < 0) {
                        faded_shade += 31;
                    }
                    {
                        u8 *color_column;
                        color_column = (u8 *)(column << 2);
                        column++;
                        faded_shade >>= 5;
                        color_column = (u8 *)((u32)color_column + (u32)scratch);
                        depth_cue = faded_shade;
                        *(u32 *)(row_offset + (u32)color_column) =
                            faded_shade + (faded_shade << 8) + (faded_shade << 16);
                    }
                } while (column < 16);
            }
        }

        {
            s32 age = *(s16 *)(effect + 0x48);
            s32 first_cell;
            s32 row;
            s32 row_limit;

            if (age < 7) {
                first_cell = 7 - age;
            } else {
                first_cell = 0;
            }
            row = first_cell;
            row_limit = grid_last - row;

            if (row < row_limit) {
                s32 saved_row_limit = row_limit;
                s32 draw_row = 1;
                do {
                    s32 column;
                    column = first_cell;
                    if (draw_row) {
                        s32 row_offset = row << 6;
                        s32 column_limit;
                        u8 *color_column;

                        do {
                            Quad *quad;
                            u8 *vertex_colors;
                            color_column = (u8 *)((column << 2) + (u32)scratch);

                            {
                                u8 *packet_pool;
                                packet_pool = (u8 *)gw->unk_000;
                                quad = *(Quad **)(packet_pool + 0x8d0);
                                *(Quad **)(packet_pool + 0x8d0) = quad + 1;
                            }

                            vertex_colors = (u8 *)(row_offset + (u32)color_column);
                            quad->color0 = *(u32 *)(vertex_colors + 0);
                            quad->color1 = *(u32 *)(vertex_colors + 64);
                            quad->color2 = *(u32 *)(vertex_colors + 4);
                            quad->color3 = *(u32 *)(vertex_colors + 68);
                            func_80066708(quad);
                            func_80066640(quad, 1);

                            quad->xy0 = screen_grid[column][row];
                            quad->xy1 = screen_grid[column][row + 1];
                            quad->xy2 = screen_grid[column + 1][row];
                            quad->xy3 = screen_grid[column + 1][row + 1];
                            column++;
                            {
                                s32 last_vertex = 15;
                                column_limit = last_vertex - first_cell;
                            }

                            ((P_TAG *)quad)->addr = ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr;
                            ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr = (u32)quad;
                        } while (column < column_limit);
                    }
                    row++;
                } while (row < saved_row_limit);
            }
        }

        {
            u8 *draw_mode;
            s32 texture_page;

            {
                u8 *packet_pool;
                packet_pool = (u8 *)gw->unk_000;
                draw_mode = *(u8 **)(packet_pool + 0x8d0);
                *(u8 **)(packet_pool + 0x8d0) = draw_mode + 12;
            }
            texture_page = func_80066460(0, 2, 0, 0);
            func_80067F20(draw_mode, 0, 0, texture_page & 0xffff, 0);

            ((P_TAG *)draw_mode)->addr = ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr;
            ((P_TAG *)((u8 *)gw->unk_000 + 0xb0))->addr = (u32)draw_mode;
        }

        next_effect = *(u8 **)((u8 *)effect_data - 8);
        if (next_effect == 0) break;
        next_effect += 32;
        effect_data = next_effect;
    } while (1);

    return 0;
}
