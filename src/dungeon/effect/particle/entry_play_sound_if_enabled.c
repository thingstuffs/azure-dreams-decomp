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

typedef struct S_818154FC_0_pre {
    u16 unk_00;
} S_818154FC_0_pre;   /* the 0x2 bytes before arg0 in func_818154FC, addressed as arg0[-1] */

typedef struct S_818154FC_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x72];
    union { s16 s; u16 u; } unk_7E;   /* accessed as both */
    u8 pad_80[0x2];
    u16 unk_82;
    union { u16 s; s16 u; } unk_84;   /* accessed as both */
    s16 unk_86;
    s16 unk_88;
    u8 pad_8A[0x6];
    u8 * unk_90;
    union { void * s; u8 * u; } unk_94;   /* accessed as both */
    u8 pad_98[0x10];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[0x6];
    s32 unk_B0;
    s32 unk_B4;
    s32 unk_B8;
} S_818154FC_0;   /* arg0 in func_818154FC */

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

typedef struct S_818154FC_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_818154FC_5;   /* arg1 in func_818154FC */

typedef struct S_818154FC_7 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    void * unk_2C;
    s32 unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818154FC_7;   /* work in func_818154FC */

   /* map in func_818154FC */


typedef struct S_818154FC_14 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818154FC_14;

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
s32 get_sprite_attachment_vector(s32, void *, Offset *, s32);     /* extern */
extern void func_800246DC(void *effect, void *position);

/* Updates an effect through attachment, spawning, tracking, and cleanup. */
void emit_attached_directional_particle_chain(void *effect, S_818154FC_5 *position, SpriteFrameState *sprite) {
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
    void *parent;
    S_818154FC_1 *parent_node;
    MovingPosition *parent_position;
    SpriteFrameState *spawn_sprite;

    parent = ((S_818154FC_0 *)effect)->unk_00;
    point_table = (LocalPoints *)&attached_particle_points;
    points = *point_table;
    point_base = (LocalPoint *)&points;
    state = ((S_818154FC_0 *)effect)->unk_0A.s;
    parent_node = parent - 0x20;
    parent_position = parent_node->unk_08;
    ((S_818154FC_0 *)effect)->unk_82 = (u16) (((S_818154FC_0 *)effect)->unk_82 + 1);
    switch (state) {
    case 0:
        sprite->color.word = 0x00808080;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        select_record_entry_and_value(sprite, directional_sprite_entries, 0);
        angle = ((S_818154FC_3 *)parent)->unk_2A;
        D_80025338[0] = 1;
        ((S_818154FC_0 *)effect)->unk_7E.s = (s16) ((angle >> 9) & 7);
        ((S_818154FC_0 *)effect)->unk_0A.s = (s16) ((u16) ((S_818154FC_0 *)effect)->unk_0A.s + 1);

    case 1:
        {
            u16 position_z;
            u16 final_z;
            s32 delta_z;

            parent_sprite = parent_node->unk_0C;
            if ((get_sprite_attachment_vector(parent_sprite->unk_08, parent_sprite, &offset, 0) != 0)
                || (((S_818154FC_14 *)(parent_node->unk_0C))->unk_14 & 0x8000)) {
                position->unk_00.at02.v = (u16) parent_position->x;
                position->unk_04.at02.v = (u16) parent_position->y;
                position_z = parent_position->z;
                position->unk_08.at02.v = position_z;
                if (!(((S_818154FC_14 *)(parent_node->unk_0C))->unk_14 & 0x8000)) {
                    position->unk_00.at02.v = (u16) (position->unk_00.at02.v + offset.x);
                    position->unk_04.at02.v = (u16) (position->unk_04.at02.v + offset.y);
                    final_z = position->unk_08.at02.v;
                    delta_z = offset.z;
                    final_z += delta_z;
                    position->unk_08.at02.v = final_z;
                } else {
                    final_z = position_z - 0x40;
                    position->unk_08.at02.v = final_z;
                }
                {
                    s32 coord;
                    s32 coord_2;

                    ((S_818154FC_0 *)effect)->unk_B0 = position->unk_00.at00.v;
                    coord_2 = position->unk_04.at00.v;
                    ((S_818154FC_0 *)effect)->unk_B4 = coord_2;
                    coord = position->unk_08.at00.v;
                    ((S_818154FC_0 *)effect)->unk_B8 = coord;
                }
                if (*((S_818154FC_0 *)effect)->unk_04 & 0x80) {
                    ((S_818154FC_0 *)effect)->unk_84.s = 0U;
                    ((S_818154FC_0 *)effect)->unk_0A.s = (s16) ((u16) ((S_818154FC_0 *)effect)->unk_0A.s + 1);
                    play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                }
            }
            return;
        }

    case 2:
        spawn_tick = ((S_818154FC_0 *)effect)->unk_84.s + 1;
        ((S_818154FC_0 *)effect)->unk_84.s = spawn_tick;
        if (spawn_tick & 1) {

            node = allocate_flagged_object_node(0x12);
            if (node != NULL) {
                S_818154FC_7 *work;
                MovingTile *map;
                s32 index;

                work = (S_818154FC_7 *)(((u8 *)node) + 0x20);
                {
                    s16 *entry;

                    index = ((S_818154FC_0 *)effect)->unk_7E.s;
                    entry = (s16 *)((u8 *)point_base + index * 4);
                    work->unk_58 = (s32)entry[0] << 16;
                }
                {
                    u16 *entry;

                    index = ((S_818154FC_0 *)effect)->unk_7E.s;
                    entry = (u16 *)((u8 *)point_base + index * 4);
                    work->unk_5C = (s32)entry[1] << 16;
                }
                work->unk_2C = parent;
                work->unk_30 = ((S_818154FC_3 *)parent)->unk_60.s;
                work->unk_0A =
                    (((S_818154FC_0 *)effect)->unk_84.u - 1) / 2;
                work->unk_15 = ((S_818154FC_0 *)effect)->unk_09;
                work->unk_16 = ((S_818154FC_0 *)effect)->unk_7E.u;

                {
                    u8 *table_base = (u8 *)dir_step_x;

                    index = ((S_818154FC_0 *)effect)->unk_7E.s * 2;
                    map = ((S_818154FC_3_pre *)parent)[-1].unk_00;
                    ((S_818154FC_0 *)effect)->unk_A8 =
                        map->tile_x + table_base[index];
                }
                {
                    u8 *table_base = (u8 *)dir_step_y;

                    index = ((S_818154FC_0 *)effect)->unk_7E.s * 2;
                    ((S_818154FC_0 *)effect)->unk_A9 =
                        map->tile_y + table_base[index];
                }

                if (((S_818154FC_3 *)parent)->unk_60.u != NULL) {
                    s32 tile_distance;
                    s32 compare_one;
                    ObjectPosition *motion;
                    s32 z_step;
                    s32 other_z;

                    work->unk_08 = 1;
                    if (((S_818154FC_3 *)parent)->unk_72 != map->tile_x) {
                        tile_distance = __builtin_abs(((S_818154FC_3 *)parent)->unk_72 - map->tile_x);
                        work->unk_02.s = tile_distance * 2;
                    } else {
                        tile_distance = __builtin_abs(((S_818154FC_3 *)parent)->unk_73 - map->tile_y);
                        work->unk_02.s = tile_distance * 2;
                    }

                    compare_one = 1;
                    motion = ((S_818154FC_15_pre *)(((S_818154FC_3 *)parent)->unk_60.p))[-1].unk_00;
                    if (((S_818154FC_0 *)effect)->unk_84.u == compare_one) {
                        s32 duration;

                        duration = work->unk_02.s;
                        if (duration != 0) {
                            z_step = motion->z.v;
                            other_z = position->unk_08.at00.v;
                            z_step -= other_z;
                            z_step -= 0x200000;
                            other_z = duration - 1;
                            z_step /= other_z;
                            work->unk_60 = z_step;
                            position->unk_14 = z_step;
                        }
                    } else {
                        work->unk_60 = position->unk_14;
                    }
                } else {
                    work->unk_02.s = 8;
                    work->unk_08 = 0;
                }
                if (((S_818154FC_0 *)effect)->unk_84.u == 9) {
                    if (((S_818154FC_3 *)parent)->unk_60.u != NULL) {
                        u16 end_time;

                        end_time = work->unk_02.u;
                        end_time += 0x28;
                        ((S_818154FC_0 *)effect)->unk_86 = end_time;
                    } else {
                        ((S_818154FC_0 *)effect)->unk_86 = 0x1E;
                    }
                }
                spawn_position = node->position;
                node->update_callback = &func_800246DC;
                spawn_position->x.v = ((S_818154FC_0 *)effect)->unk_B0;
                spawn_position->y.v = ((S_818154FC_0 *)effect)->unk_B4;
                spawn_position->z.v = ((S_818154FC_0 *)effect)->unk_B8;
                spawn_sprite = node->sprite;
                spawn_sprite->color.c.b = 0x80;
                spawn_sprite->color.c.g = 0x80;
                spawn_sprite->color.c.r = 0x80;
                spawn_sprite->scale_y = 0x1000;
                spawn_sprite->scale_x = 0x1000;
                if ((s16) ((S_818154FC_0 *)effect)->unk_84.s == 1) {
                    ((S_818154FC_0 *)effect)->unk_90 = node;
                    ((S_818154FC_0 *)effect)->unk_94.s = spawn_position;
                    ((S_818154FC_0 *)effect)->unk_88 = 0x63;
                }
            }
        }
        if (((S_818154FC_0 *)effect)->unk_88 == 0x63) {

            node = ((S_818154FC_0 *)effect)->unk_90;
            spawn_position = ((S_818154FC_0 *)effect)->unk_94.s;
            if (node->flags & 0x8000) {
                ((S_818154FC_0 *)effect)->unk_88 = 0;
            } else {
                position->unk_00.at00.v = spawn_position->x.v;
                position->unk_04.at00.v = spawn_position->y.v;
                position->unk_08.at00.v = spawn_position->z.v;
            }
        }
        if ((s16) ((S_818154FC_0 *)effect)->unk_84.s >= 0xB) {
            u16 old_state;

            old_state = ((S_818154FC_0 *)effect)->unk_0A.u;
            ((S_818154FC_0 *)effect)->unk_84.s = 0;
            old_state++;
            ((S_818154FC_0 *)effect)->unk_0A.u = old_state;
        }
        return;

    case 3:
        if (((S_818154FC_0 *)effect)->unk_88 == 0x63) {

            node = ((S_818154FC_0 *)effect)->unk_90;
            spawn_position = ((S_818154FC_0 *)effect)->unk_94.s;
            if (node->flags & 0x8000) {
                ((S_818154FC_0 *)effect)->unk_88 = 0;
            } else {
                position->unk_00.at00.v = spawn_position->x.v;
                position->unk_04.at00.v = spawn_position->y.v;
                position->unk_08.at00.v = spawn_position->z.v;
            }
        }
        {
            u16 old_counter = ((S_818154FC_0 *)effect)->unk_84.s;
            s16 new_counter = old_counter + 1;

            ((S_818154FC_0 *)effect)->unk_84.s = new_counter;
            if (((S_818154FC_0 *)effect)->unk_86 < new_counter) {
                s32 global_state = D_80025338[0];

                ((S_818154FC_0 *)effect)->unk_84.s = old_counter;
                if (global_state == 0) {
                    g_dungeon_status.active_actor = 0;
                    ((S_818154FC_0_pre *)effect)[-1].unk_00 |= 0x8000;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                } else {
                    D_80025338[0] = 0;
                }
            }
        }

    }
}

