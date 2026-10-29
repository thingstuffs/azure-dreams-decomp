#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/naplass.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"

typedef struct S_80172840_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172840_0;   /* arg3 in advance_move_action_particles */

typedef struct S_80172840_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172840_1;   /* arg0 in advance_move_action_particles */

typedef struct S_80172840_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172840_3;   /* record in advance_move_action_particles */


typedef struct S_80172840_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172840_6;   /* D_800814A8[0] in advance_move_action_particles */

typedef struct S_80172840_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172840_7;   /* spawn in advance_move_action_particles */

typedef struct S_80172840_8 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80172840_8;   /* spawn_fields in advance_move_action_particles */

typedef struct S_80172840_10 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172840_10;   /* base in advance_move_action_particles */

typedef struct S_80172840_12 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} S_80172840_12;   /* ((S_80172840_7 *)spawn)->unk_08 in advance_move_action_particles */

extern int abs(int);
extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern s32 generate_random_value(void);
extern void *create_actor_spell_effect(void *, void *, s32, void *);

extern u8 secondary_sprite[0x20];
extern u8 naplass_action_continuation_address[0x10];
extern u8 D_80173EC0[0x10];
extern u8 naplass_frame_set_1[0x10];

/* Updates a move action, spawning particles and resetting state when it ends. */
/* Starts a targeted spell, emits batches of ten particles ahead during casting, then restores movement and
 * status. */
void advance_move_action_particles(void *action, ObjectPosition *position, SpriteFrameState *sprite, void *actor)
{
    void *particle_callback = D_80173EC0;
    s32 direction_offset;
    u8 *move_slot;
    s32 phase;
    register s32 is_special;
    u16 coords[7];
    s32 direction_x;
    s32 direction_y;
    S_80172840_10 *effect_base;
    s32 abs_x;
    s32 abs_y;
    SpriteFrameState *record;
    s32 counter;
    ObjectNodeHeader *particle;
    u16 source_x;
    u16 offset_x;
    u16 source_y;
    u16 offset_y;
    u16 source_z;
    u16 offset_z;
    s32 color;
    s32 effect_value;
    S_80172840_8 *particle_fields;
    u32 heading;
    u8 *direction_x_ptr;
    is_special = 0;
    direction_x_ptr = dir_step_x;
    heading = ((S_80172840_0 *)actor)->unk_2A.s;
    counter = heading >> 8;
    direction_offset = counter & 0xE;
    direction_x_ptr += direction_offset;
    direction_x = *(s16 *)direction_x_ptr;
    phase = ((S_80172840_1 *)action)->unk_9B;
    direction_y = *(s16 *)((u8 *)dir_step_y + direction_offset);

    switch (phase) {
    case 0:
    {
        s32 move_kind;
        void *move_object;
        s16 special_flag;

        if (((S_80172840_0 *)actor)->unk_1C & ACTOR_PLAYER_SIDE) {
            switch (((S_80172840_0 *)actor)->unk_46 & 0x3FFF) {
            case 7:
                is_special = 1;
            case 3:
                move_slot = (u8 *)actor + 0x0E;
                break;
            case 6:
                is_special = 1;
            case 2:
                move_slot = (u8 *)actor + 0x0B;
                break;
            case 5:
                is_special = 1;
            case 1:
                move_slot = (u8 *)actor + 8;
                break;
            default:
                move_slot = 0;
            }
        } else {
            move_kind = ((S_80172840_0 *)actor)->unk_46 & 0x3FFF;
            switch (move_kind) {
            case 3:
                move_slot = (u8 *)actor + 0x0E;
                break;
            case 2:
                move_slot = (u8 *)actor + 0x0B;
                break;
            case 1:
                move_slot = (u8 *)actor + 8;
                break;
            default:
                move_slot = 0;
            }
        }
        if (*move_slot != 0) {
            ((S_80172840_1 *)action)->unk_98 &= 0xFF7F;
            special_flag = is_special;
            if (special_flag != 0) {
                move_object = ((u8 *)primary_actor_record);
                ((S_80172840_0 *)actor)->unk_60 = move_object;
                record = ((ObjectNodeHeader *)((u8 *)move_object - 0x20))->sprite;
                ((S_80172840_0 *)actor)->unk_72.s = record->tile_x;
                ((S_80172840_0 *)actor)->unk_73.s = record->tile_y;
            } else if (item_action_definitions[*move_slot].kind == 2) {
                move_object = ((S_80172840_0 *)actor)->unk_60;
                if (move_object != 0) {
                    record = ((ObjectNodeHeader *)((u8 *)move_object - 0x20))->sprite;
                    ((S_80172840_0 *)actor)->unk_72.s = record->tile_x;
                    ((S_80172840_0 *)actor)->unk_73.s = record->tile_y;
                }
            } else {
                ((S_80172840_0 *)actor)->unk_60 = scan_actor_along_heading(
                    actor,
                    sprite->tile_x,
                    sprite->tile_y,
                    ((S_80172840_0 *)actor)->unk_2A.u,
                    0x10);
                abs_x = abs(((S_80172840_0 *)actor)->unk_72.u);
                abs_y = abs(((S_80172840_0 *)actor)->unk_73.u);
                ((S_80172840_0 *)actor)->unk_72.s = abs_x;
                ((S_80172840_0 *)actor)->unk_73.s = abs_y;
            }
            coords[0] = ((u16) position->x.w.i);
            coords[1] = ((u16) position->y.w.i);
            coords[2] = ((u16) position->z.w.i);
            if (create_actor_spell_effect(actor, move_slot, is_special,
                              (u8 *)action + 0x98) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            ((S_80172840_1 *)action)->unk_A8.s = -1;
            ((S_80172840_1 *)action)->unk_9B++;
            return;
        }

        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        ((S_80172840_6 *)(((u8 *)primary_actor_record)))->unk_A6--;
        advance_status_timers(actor);
        ((S_80172840_0 *)actor)->unk_6D.s--;
        ((S_80172840_1 *)action)->unk_8C = naplass_action_continuation_address;
        ((S_80172840_0 *)actor)->unk_73.s = 0;
        ((S_80172840_0 *)actor)->unk_72.s = 0;
        ((S_80172840_0 *)actor)->unk_46 &= 0x7FFF;
        return;
    }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_80172840_1 *)action)->unk_9B++;
    case 2:
        if (sprite->unk_04 == 1 &&
            (sprite->flags & 0x1000)) {
            ((S_80172840_1 *)action)->unk_A8.u = 4;
        }
        if ((u32)(*(u8 *)&sprite->unk_04 - 1) < 2U &&
            sprite->frameTable != naplass_frame_set_1) {
            if (resolve_record_orientation_or_fallback(
                    (s32)sprite->source, sprite, &coords[4], 1) == 0) {
                coords[6] = 0;
                coords[5] = 0;
                coords[4] = 0;
            }
            ((S_80172840_1 *)action)->unk_A8.u--;
            if ((s16)((S_80172840_1 *)action)->unk_A8.u >= 0) {
                counter = 9;
                effect_base = secondary_sprite;
                for (; counter >= 0; counter--) {
                    SpriteFrameState *particle_data;
                    particle = allocate_list_node(0x312, &scene_object_list_anchor.next);
                    if (particle != 0) {

                        register_node(particle, project_sprite_chain);
                        particle_data = particle->sprite;
                        {

                            particle->update_callback = particle_callback;
                        }
                        {
                            s32 random_x;
                            s32 origin_x;
                            s32 particle_x;

                            random_x = generate_random_value() & 0x3F;
                            origin_x = ((u16) position->x.w.i);
                            particle_x = coords[4];

                            origin_x += particle_x;
                            particle_x = direction_x << 6;
                            origin_x += particle_x;
                            origin_x += random_x;
                            particle->position->x.w.i =
                                origin_x - 0x1F;
                        }
                        particle->position->y.w.i =
                            ((u16) position->y.w.i) + coords[5] +
                            ((s32)direction_y << 6) + (generate_random_value() & 0x3F) - 0x1F;
                        particle->position->z.v =
                            position->z.v;
                        source_x = ((u16) position->x.w.i);
                        offset_x = coords[4];
                        particle_fields = (S_80172840_8 *)((u8 *)particle + 0x20);
                        particle_fields->unk_0C = source_x + offset_x;
                        source_y = ((u16) position->y.w.i);
                        offset_y = coords[5];
                        color = 0x700000;
                        particle_fields->unk_0E = source_y + offset_y;
                        source_z = ((u16) position->z.w.i);
                        offset_z = coords[6];
                        particle_fields->unk_48 = 4;
                        particle_fields->unk_10 = source_z + offset_z;
                        particle_data->scale_y = 0x600;
                        particle_data->scale_x = 0x600;
                        particle_data->tpage_abr = 0x60;
                        particle_data->unk_00 = effect_base;
                        particle_data->flags |= 0xC;
                        effect_value = effect_base->unk_04;
                        color |= 0x7070;
                        particle_data->unk_04 = 0;
                        particle_data->frame_ticks = 0;
                        particle_data->color.word = color;
                        particle_data->source = effect_value;
                        particle_fields->unk_4C = 0;
                    }
                }
            }
        }
        if ((sprite->unk_04 == 6 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            ((S_80172840_1 *)action)->unk_96 = 3;
            ((S_80172840_1 *)action)->unk_98 |= 0x80;
        }
        ((S_80172840_1 *)action)->unk_96--;
        if ((s16)((S_80172840_1 *)action)->unk_96 <= 0) {
            ((S_80172840_1 *)action)->unk_96 = 0;
            sprite->flags &= 0xF7FF;
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        if (sprite->frameTable != naplass_frame_set_1) {
            sprite->frameTable = naplass_frame_set_1;
            select_sprite_entry(
                sprite,
                naplass_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172840_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
                0);
        }
        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        sprite->flags &= 0xF7FF;
        ((S_80172840_1 *)action)->unk_8C = naplass_action_continuation_address;
        advance_status_timers(actor);
        if (((S_80172840_0 *)actor)->unk_6D.u > 0) {
            ((S_80172840_0 *)actor)->unk_6D.s--;
        }
        ((S_80172840_0 *)actor)->unk_73.s = 0;
        ((S_80172840_0 *)actor)->unk_72.s = 0;
        ((S_80172840_0 *)actor)->unk_46 &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

        return;

    default:
        return;
    }
}
