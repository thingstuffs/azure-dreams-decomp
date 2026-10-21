#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80174BEC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174BEC_0_pre;   /* the 0x14 bytes before arg0 in spawn_directional_particles_and_reset_actor, addressed as arg0[-1] */

typedef struct S_80174BEC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174BEC_0;   /* arg0 in spawn_directional_particles_and_reset_actor */

typedef struct S_80174BEC_3 {
    u8 pad_00[0x24];
    s16 unk_24;
    u8 pad_26[0x3A];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
    u8 pad_78[0x1E];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} S_80174BEC_3;   /* motion in spawn_directional_particles_and_reset_actor */

typedef struct S_80174BEC_4 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_80174BEC_4;   /* object in spawn_directional_particles_and_reset_actor */

   /* position in spawn_directional_particles_and_reset_actor */

typedef struct S_80174BEC_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174BEC_7;   /* map in spawn_directional_particles_and_reset_actor */

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u;

typedef struct {
    s16 x;
    u16 y;
} TableEntry;

typedef struct {
    u32 words[4];
} Copy16;

typedef struct {
    u32 words[8];
} __attribute__((packed)) PackedTable;

extern void func_8003DB94(void *, void *, s32);
extern s32 resolve_record_orientation_or_fallback(void *, void *, Vec3u *, s32);
extern s32 get_sprite_attachment_vector(void *, void *, Vec3u *, s32);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, u8, s32);
extern s32 func_80069EF8(void);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void toggle_attacker_target_status_pair(void *, void *);

extern u8 D_80170854[];
extern u8 D_80171040[];
extern u8 D_8017142C[];
extern u8 D_80171E20[];
extern u8 D_801753BC[];
extern u8 D_8017541C[];

/* Spawns directional particles, advances the actor animation, and resets its state after a delay. */
void spawn_directional_particles_and_reset_actor(void *state, ObjectPosition *source_pos, void *source_render, ActorRecord *actor)
{
    Vec3u map_offset;
    PackedTable velocity_table;
    s16 frame;
    s32 coord;

    velocity_table = *(PackedTable *)D_80170854;

    switch (((S_80174BEC_0 *)state)->unk_9B) {
    case 0:
        source_pos->velocity_z = 0;
        source_pos->velocity_y = 0;
        source_pos->velocity_x = 0;
        ((S_80174BEC_0 *)state)->unk_96.s = 0;
        ((S_80174BEC_0 *)state)->unk_9B++;
        ((SpriteFrameState *)source_render)->flags &= 0x9FFF;

    case 1:
        frame = ((S_80174BEC_0 *)state)->unk_96.u;
        if (frame == 0 || frame == 7) {
            s16 particle_index;

            if (!(((SpriteFrameState *)source_render)->flags & 0x8000)) {
                play_sound_if_enabled(0x80D);
            }

            particle_index = 0;
            {
                TableEntry *directions;

                directions = (TableEntry *)&velocity_table;
                for (; particle_index < 5; particle_index++) {
                    void *particle;

                    particle = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
                    if (particle == 0)
                        continue;
                    {
                        s32 offset_y;
                        s32 offset_x;
                        s32 velocity_y;
                        s32 velocity_x;
                        s32 offset_z;
                        s32 position_y;
                        u8 *position;
                        u8 *render;
                        u8 *motion;
                        u8 *copy_src;
                        u8 *copy_dst;
                        u8 *copy_end;
                        u8 animation;
                        void *map;
                        u32 direction_offset;

                        motion = (u8 *)particle + 0x20;
                        ((S_80174BEC_3 *)motion)->unk_96 = 0x28 - ((S_80174BEC_0 *)state)->unk_96.s;
                        ((S_80174BEC_3 *)motion)->unk_9B = 0;
                        render = ((S_80174BEC_4 *)particle)->unk_0C;
                        ((S_80174BEC_4 *)particle)->unk_10 = D_80171040;

                        copy_src = source_render;
                        copy_dst = render;
                        copy_end = (u8 *)source_render + 0x30;
                        do {
                            *(Copy16 *)copy_dst = *(Copy16 *)copy_src;
                            copy_src += 0x10;
                            copy_dst += 0x10;
                        } while (copy_src != copy_end);

                        ((SpriteFrameState *)render)->flags &= 0xFFFC;
                        register_node(particle, project_sprite_chain);
                        animation = D_8017541C[0];
                        ((SpriteFrameState *)render)->frameTable = D_8017541C;
                        select_sprite_entry(render, animation, 0);

                        position = ((S_80174BEC_4 *)particle)->unk_08;
                        ((MovingPosition *)position)->unk_02 = ((u16)source_pos->x.w.i);
                        ((MovingPosition *)position)->unk_06 = ((u16)source_pos->y.w.i);
                        ((MovingPosition *)position)->unk_0A = ((u16)source_pos->z.w.i);

                        map = ((S_80174BEC_0_pre *)state)[-1].unk_00;
                        if (get_sprite_attachment_vector(((S_80174BEC_7 *)map)->unk_08, map, &map_offset, 1)) {
                            ((MovingPosition *)position)->unk_02 += map_offset.x;
                            ((MovingPosition *)position)->unk_06 += map_offset.y;
                            ((MovingPosition *)position)->unk_0A += map_offset.z;
                        }

                        offset_x = (func_80069EF8() & 0x1F) - 0x10;
                        offset_y = (func_80069EF8() & 0x1F) - 0x10;
                        coord = ((MovingPosition *)position)->unk_02;
                        coord += offset_x;
                        position_y = ((MovingPosition *)position)->unk_06 + offset_y;
                        ((MovingPosition *)position)->unk_02 = coord;
                        ((MovingPosition *)position)->unk_06 = position_y;
                        offset_z = func_80069EF8() & 0x1F;
                        velocity_x = (s32)(offset_x << 16) >> 4;
                        velocity_y = (s32)(offset_y << 16) >> 4;
                        coord = ((MovingPosition *)position)->unk_0A;
                        coord -= 0x14;
                        coord += offset_z;
                        ((MovingPosition *)position)->unk_0A = coord;
                        ((S_80174BEC_3 *)motion)->unk_A4 = velocity_x;
                        ((S_80174BEC_3 *)motion)->unk_A8 = velocity_y;

                        direction_offset = (((u16)actor->facing) >> 7) & 0x1C;
                        ((S_80174BEC_3 *)motion)->unk_A4 += (s32)((TableEntry *)((u8 *)directions + direction_offset))->x
                        << 19;
                        direction_offset = (((u16)actor->facing) >> 7) & 0x1C;
                        ((S_80174BEC_3 *)motion)->unk_A8 += (u32)((TableEntry *)((u8 *)directions + direction_offset))->y
                        << 19;
                        ((S_80174BEC_3 *)motion)->unk_AC = -((func_80069EF8() & 0x7FFF) * 2);
                        ((S_80174BEC_3 *)motion)->unk_B0 = 0x1000;
                        ((SpriteFrameState *)render)->scale_y = 0x1000;
                        ((SpriteFrameState *)render)->scale_x = 0x1000;
                        ((SpriteFrameState *)render)->color.c.b = 0x80;
                        ((SpriteFrameState *)render)->color.c.g = 0x80;
                        ((SpriteFrameState *)render)->color.c.r = 0x80;
                    }
                }
            }

            particle_index = 0;
            {
                TableEntry *directions;

                directions = (TableEntry *)&velocity_table;
                for (; particle_index < 4; particle_index++) {
                    void *particle;

                    particle = func_8003FC64(0x212);
                    if (particle == 0)
                        continue;
                    {
                        s32 offset_y;
                        s32 offset_x;
                        s32 velocity_y;
                        s32 velocity_x;
                        s32 offset_z;
                        s32 position_z;
                        s32 position_y;
                        u8 *position;
                        u8 *motion;
                        u8 *render;
                        void *map;
                        u32 direction_offset;

                        motion = (u8 *)particle + 0x20;
                        ((S_80174BEC_3 *)motion)->unk_24 = 0x19 - ((S_80174BEC_0 *)state)->unk_96.s;
                        ((S_80174BEC_4 *)particle)->unk_20 = 0;
                        ((S_80174BEC_4 *)particle)->unk_10 = D_8017142C;
                        register_node(particle, project_sprite_chain);

                        render = ((S_80174BEC_4 *)particle)->unk_0C;
                        ((SpriteFrameState *)render)->flags |= 0x0C;
                        ((SpriteFrameState *)render)->tpage_abr = 0x60;
                        ((SpriteFrameState *)render)->flags |= 2;

                        position = ((S_80174BEC_4 *)particle)->unk_08;
                        ((MovingPosition *)position)->unk_02 = ((u16)source_pos->x.w.i);
                        ((MovingPosition *)position)->unk_06 = ((u16)source_pos->y.w.i);
                        ((MovingPosition *)position)->unk_0A = ((u16)source_pos->z.w.i);

                        map = ((S_80174BEC_0_pre *)state)[-1].unk_00;
                        if (resolve_record_orientation_or_fallback(((S_80174BEC_7 *)map)->unk_08, map, &map_offset, 1)) {
                            ((MovingPosition *)position)->unk_02 += map_offset.x;
                            ((MovingPosition *)position)->unk_06 += map_offset.y;
                            ((MovingPosition *)position)->unk_0A += map_offset.z;
                        }

                        offset_x = (func_80069EF8() & 0x1F) - 0x10;
                        offset_y = (func_80069EF8() & 0x1F) - 0x10;
                        coord = ((MovingPosition *)position)->unk_02;
                        coord += offset_x;
                        position_y = ((MovingPosition *)position)->unk_06 + offset_y;
                        ((MovingPosition *)position)->unk_02 = coord;
                        ((MovingPosition *)position)->unk_06 = position_y;
                        offset_z = func_80069EF8() & 0x1F;
                        velocity_x = (s32)(offset_x << 16) >> 4;
                        velocity_y = (s32)(offset_y << 16) >> 4;
                        position_z = ((MovingPosition *)position)->unk_0A;
                        position_z -= 0x14;
                        position_z += offset_z;
                        ((MovingPosition *)position)->unk_0A = position_z;
                        ((S_80174BEC_3 *)motion)->unk_60 = velocity_x;
                        ((S_80174BEC_3 *)motion)->unk_64 = velocity_y;

                        direction_offset = (((u16)actor->facing) >> 7) & 0x1C;
                        ((S_80174BEC_3 *)motion)->unk_60 += (s32)((TableEntry *)((u8 *)directions + direction_offset))->x
                        << 19;
                        direction_offset = (((u16)actor->facing) >> 7) & 0x1C;
                        ((S_80174BEC_3 *)motion)->unk_64 += (u32)((TableEntry *)((u8 *)directions + direction_offset))->y
                        << 19;
                        ((S_80174BEC_3 *)motion)->unk_68 = -((func_80069EF8() & 0x7FFF) * 2);
                        ((S_80174BEC_3 *)motion)->unk_74 = 0x400;
                        ((SpriteFrameState *)render)->scale_x = 0x800;
                        ((SpriteFrameState *)render)->scale_y = 0x800;
                        ((SpriteFrameState *)render)->color.c.g = 0x80;
                        ((SpriteFrameState *)render)->color.c.r = 0x80;
                        ((SpriteFrameState *)render)->color.c.b = 0;
                        ((SpriteFrameState *)render)->clut = 0x7DCF;
                        ((SpriteFrameState *)render)->flags |= 0x100;
                        func_8003DB94(render, effect_sprite_sources, 0);
                    }
                }
            }
        }

        ((S_80174BEC_0 *)state)->unk_96.s++;
        if (((SpriteFrameState *)source_render)->flags & 0xE000) {
            void *active_object;

            ((S_80174BEC_0 *)state)->unk_9B++;
            active_object = actor->target;
            if (active_object != 0) {
                toggle_attacker_target_status_pair(actor, active_object);
            }
        }
        return;

    case 2:
        if (((SpriteFrameState *)source_render)->flags & 0xE000) {
            s32 direction_index;

            source_pos->velocity_z = 0;
            source_pos->velocity_y = 0;
            source_pos->velocity_x = 0;
            set_record_integer_tile_center(source_pos, ((SpriteFrameState *)source_render)->unk_24, ((SpriteFrameState *)source_render)->unk_25);
            if (*(u8 * *)&((SpriteFrameState *)source_render)->frameTable != D_801753BC) {
                ((SpriteFrameState *)source_render)->frameTable = D_801753BC;
                ((SpriteFrameState *)source_render)->flags &= 0xF7FF;
                direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
                select_sprite_entry(source_render, (*(u8 * *)&((SpriteFrameState *)source_render)->frameTable)[direction_index & 7], 0);
                ((S_80174BEC_0 *)state)->unk_96.s = 0x14;
                ((S_80174BEC_0 *)state)->unk_9B++;
            }
        }
        return;

    case 3:
        {
            u16 timer;

            timer = ((S_80174BEC_0 *)state)->unk_96.s;
            ((S_80174BEC_0 *)state)->unk_96.s = timer - 1;
            if ((s16)timer <= 0 || (((SpriteFrameState *)source_render)->flags & 0xE000)) {
                spend_actor_mp(actor, 0x1000);
                ((S_80174BEC_0 *)state)->unk_8C = D_80171E20;
                g_dungeon_status.active_actor = 0;
                (actor->action_flags) &= 0x7FFF;
            }
        }

        return;
    default:
        return;
    }
}
