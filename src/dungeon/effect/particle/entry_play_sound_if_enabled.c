#include "slus.h"
#include "shared/audio_commands.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/system.h"
#include "dungeon/effect/particle.h"
#include "engine/graphics.h"
#include "dungeon/effect/particle/entry_play_sound_if_enabled.h"

typedef struct S_818154FC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_818154FC_1;

typedef struct S_818154FC_3_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_818154FC_3_pre;

typedef struct S_818154FC_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { s32 s; void * u; u8 * p; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} S_818154FC_3;

typedef struct S_818154FC_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818154FC_4;



   /* map in func_818154FC */



typedef struct S_818154FC_15_pre {
    u8 * unk_00;
    u8 pad_04[0x14];
} S_818154FC_15_pre;

typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    s16 x;
    u16 y;
} LocalPoint;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Offset;

/* cfail-repair: tf7-phase1-cache-v3 */
extern LocalPoints attached_particle_points;
extern u8 directional_sprite_entries[];
extern s16 D_80025338[5];
extern void func_800246DC(void *effect, void *position);

/* Updates an effect through attachment, spawning, tracking, and cleanup. */
void emit_attached_directional_particle_chain(AttachedParticleChainSpellBody *effect, ObjectPosition *position, SpriteFrameState *sprite) {
    Offset offset;
    LocalPoints points;
    LocalPoint *point_base;
    s32 state;
    u16 spawn_tick;
    u16 angle;
    LocalPoints *point_table;
    ObjectPosition *spawn_position;
    ObjectNodeHeader *node;
    S_818154FC_4 *parent_sprite;
    ActorRecord *parent;
    S_818154FC_1 *parent_node;
    MovingPosition *parent_position;
    SpriteFrameState *spawn_sprite;

    parent = effect->spell.caster;
    point_table = &attached_particle_points;
    points = *point_table;
    point_base = (LocalPoint *)&points;
    state = effect->spell.phase;
    parent_node = (void *)parent - 0x20;
    parent_position = parent_node->unk_08;
    effect->unk_82 = (u16) (effect->unk_82 + 1);
    switch (state) {
    case 0:
        sprite->color.word = 0x00808080;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        select_record_entry_and_value(sprite, directional_sprite_entries, 0);
        angle = ((S_818154FC_3 *)parent)->unk_2A;
        D_80025338[0] = 1;
        effect->unk_7E = (angle >> 9) & 7;
        effect->spell.phase++;

    case 1:
        {
            u16 position_z;
            u16 final_z;
            s32 delta_z;

            parent_sprite = parent_node->unk_0C;
            if ((get_sprite_attachment_vector(parent_sprite->unk_08, parent_sprite, &offset, 0) != 0)
                || (((SpriteFrameState *)(parent_node->unk_0C))->flags & 0x8000)) {
                position->x.unsigned_parts.integer = (u16) parent_position->x;
                position->y.unsigned_parts.integer = (u16) parent_position->y;
                position_z = parent_position->z;
                position->z.unsigned_parts.integer = position_z;
                if (!(((SpriteFrameState *)(parent_node->unk_0C))->flags & 0x8000)) {
                    position->x.unsigned_parts.integer = (u16) (position->x.unsigned_parts.integer + offset.x);
                    position->y.unsigned_parts.integer = (u16) (position->y.unsigned_parts.integer + offset.y);
                    final_z = position->z.unsigned_parts.integer;
                    delta_z = offset.z;
                    final_z += delta_z;
                    position->z.unsigned_parts.integer = final_z;
                } else {
                    final_z = position_z - 0x40;
                    position->z.unsigned_parts.integer = final_z;
                }
                {
                    s32 coord;
                    s32 coord_2;

                    effect->unk_B0 = position->x.v;
                    coord_2 = position->y.v;
                    effect->unk_B4 = coord_2;
                    coord = position->z.v;
                    effect->unk_B8 = coord;
                }
                if (*effect->spell.context & 0x80) {
                    effect->unk_84 = 0U;
                    effect->spell.phase++;
                    play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                }
            }
            return;
        }

    case 2:
        spawn_tick = effect->unk_84 + 1;
        effect->unk_84 = spawn_tick;
        if (spawn_tick & 1) {

            node = allocate_flagged_object_node(0x12);
            if (node != NULL) {
                DirectionalParticleChainBody *work;
                MovingTile *map;
                s32 index;

                work = NODE_BODY(node);
                {
                    s16 *entry;

                    index = effect->unk_7E;
                    entry = (s16 *)((u8 *)point_base + index * 4);
                    work->unk_58 = (s32)entry[0] << 16;
                }
                {
                    u16 *entry;

                    index = effect->unk_7E;
                    entry = (u16 *)((u8 *)point_base + index * 4);
                    work->unk_5C = (s32)entry[1] << 16;
                }
                work->unk_2C.p = parent;
                work->unk_30.s = ((S_818154FC_3 *)parent)->unk_60.s;
                work->unk_0A =
                    (effect->unk_84 - 1) / 2;
                work->unk_15 = effect->spell.variant;
                work->unk_16 = effect->unk_7E;

                {
                    u8 *table_base = (u8 *)dir_step_x;

                    index = effect->unk_7E * 2;
                    map = ((S_818154FC_3_pre *)parent)[-1].unk_00;
                    effect->unk_A8 =
                        map->tile_x + table_base[index];
                }
                {
                    u8 *table_base = (u8 *)dir_step_y;

                    index = effect->unk_7E * 2;
                    effect->unk_A9 =
                        map->tile_y + table_base[index];
                }

                if (parent->target != NULL) {
                    s32 tile_distance;
                    s32 compare_one;
                    ObjectPosition *motion;
                    s32 z_step;
                    s32 other_z;

                    work->unk_08 = 1;
                    if (parent->target_tile_x != map->tile_x) {
                        tile_distance = __builtin_abs(parent->target_tile_x - map->tile_x);
                        work->unk_02 = tile_distance * 2;
                    } else {
                        tile_distance = __builtin_abs(parent->target_tile_y - map->tile_y);
                        work->unk_02 = tile_distance * 2;
                    }

                    compare_one = 1;
                    motion = ((S_818154FC_15_pre *)(((S_818154FC_3 *)parent)->unk_60.p))[-1].unk_00;
                    if (effect->unk_84 == compare_one) {
                        s32 duration;

                        duration = (s16)work->unk_02;
                        if (duration != 0) {
                            z_step = motion->z.v;
                            other_z = position->z.v;
                            z_step -= other_z;
                            z_step -= 0x200000;
                            other_z = duration - 1;
                            z_step /= other_z;
                            work->unk_60 = z_step;
                            position->velocity_z = z_step;
                        }
                    } else {
                        work->unk_60 = position->velocity_z;
                    }
                } else {
                    work->unk_02 = 8;
                    work->unk_08 = 0;
                }
                if (effect->unk_84 == 9) {
                    if (parent->target != NULL) {
                        u16 end_time;

                        end_time = work->unk_02;
                        end_time += 0x28;
                        effect->unk_86 = end_time;
                    } else {
                        effect->unk_86 = 0x1E;
                    }
                }
                spawn_position = node->position;
                node->update_callback = &func_800246DC;
                spawn_position->x.v = effect->unk_B0;
                spawn_position->y.v = effect->unk_B4;
                spawn_position->z.v = effect->unk_B8;
                spawn_sprite = node->sprite;
                spawn_sprite->color.c.b = 0x80;
                spawn_sprite->color.c.g = 0x80;
                spawn_sprite->color.c.r = 0x80;
                spawn_sprite->scale_y = 0x1000;
                spawn_sprite->scale_x = 0x1000;
                if (effect->unk_84 == 1) {
                    effect->unk_90 = node;
                    effect->unk_94 = spawn_position;
                    effect->unk_88 = 0x63;
                }
            }
        }
        if (effect->unk_88 == 0x63) {

            node = effect->unk_90;
            spawn_position = effect->unk_94;
            if (node->flags & 0x8000) {
                effect->unk_88 = 0;
            } else {
                position->x.v = spawn_position->x.v;
                position->y.v = spawn_position->y.v;
                position->z.v = spawn_position->z.v;
            }
        }
        if (effect->unk_84 >= 0xB) {
            u16 old_state;

            old_state = effect->spell.phase;
            effect->unk_84 = 0;
            old_state++;
            effect->spell.phase = old_state;
        }
        return;

    case 3:
        if (effect->unk_88 == 0x63) {

            node = effect->unk_90;
            spawn_position = effect->unk_94;
            if (node->flags & 0x8000) {
                effect->unk_88 = 0;
            } else {
                position->x.v = spawn_position->x.v;
                position->y.v = spawn_position->y.v;
                position->z.v = spawn_position->z.v;
            }
        }
        {
            u16 old_counter = effect->unk_84;
            s16 new_counter = old_counter + 1;

            effect->unk_84 = new_counter;
            if (effect->unk_86 < new_counter) {
                s32 global_state = D_80025338[0];

                effect->unk_84 = old_counter;
                if (global_state == 0) {
                    g_dungeon_status.active_actor = 0;
                    NODE_HEADER(effect)->flags |= 0x8000;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                } else {
                    D_80025338[0] = 0;
                }
            }
        }

    }
}

