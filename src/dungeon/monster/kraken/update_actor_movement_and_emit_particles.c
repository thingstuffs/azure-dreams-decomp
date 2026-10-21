#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/actor_action.h"
#include "shared/dungeon_projectile_views.h"

   /* arg0 in update_actor_movement_and_emit_particles */

   /* obj in update_actor_movement_and_emit_particles */

typedef struct S_80172D1C_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    union { s32 s; s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; s32 u; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_80172D1C_2;   /* arg1 in update_actor_movement_and_emit_particles */

typedef struct S_80172D1C_3 {
    u8 pad_00[0x48];
    s16 unk_48;
} S_80172D1C_3;   /* (u8 *)calc_other in update_actor_movement_and_emit_particles */

typedef struct S_80172D1C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80172D1C_5;   /* part in update_actor_movement_and_emit_particles */

typedef struct S_80172D1C_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172D1C_8;   /* ((S_80172D1C_1 *)obj)->unk_08 in update_actor_movement_and_emit_particles */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry();
extern s32 rand(void);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 D_801711A4[];
extern u8 D_8017406C[];
extern u8 D_8017418C[];
extern u8 D_80174194[];

/* Updates actor movement, emits particles, and settles the actor onto its tile. */
void update_actor_movement_and_emit_particles(void *actor, void *motion, void *sprite, void *entity) {
    void *particle;
    void *particle_sprite;
    void *particle_update;
    u8 *unused_particle_state;
    s32 particle_or_dir_index;
    s32 state;
    s32 unused_value;
    s32 unused_value2;
    s32 sprite_flags;
    s32 timer;
    s32 next_timer;
    s16 state_timer;
    s32 velocity_x;
    s32 velocity_y;
    s32 speed_work;
    s32 component_work;
    s32 component_work_2;
    u8 *particle_work;

    if (((ActorActionTimerView *)actor)->unk_9B == 1) {
        particle_or_dir_index = 6;
        particle_update = D_8017406C;
        do {
            particle = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
            if (particle != 0) {
                particle_work = (u8 *)particle + 0x20;
                register_node(particle, project_sprite_chain);
                particle_sprite = ((ProjectileObject *)particle)->unk_0C;
                ((ProjectileObject *)particle)->unk_10 = particle_update;

                ((S_80172D1C_8 *)(((ProjectileObject *)particle)->unk_08))->unk_02 =
                    ((S_80172D1C_2 *)motion)->unk_02.s + (rand() & 0xF) - 8;
                ((S_80172D1C_8 *)(((ProjectileObject *)particle)->unk_08))->unk_06 =
                    ((S_80172D1C_2 *)motion)->unk_06.s + (rand() & 0xF) - 8;
                ((S_80172D1C_8 *)(((ProjectileObject *)particle)->unk_08))->unk_0A =
                    ((S_80172D1C_2 *)motion)->unk_0A + (rand() & 0xF) - 8;

                ((S_80172D1C_8 *)(((ProjectileObject *)particle)->unk_08))->unk_0C =
                    ((rand() & 0xFF) - 0x80) << 10;
                ((S_80172D1C_8 *)(((ProjectileObject *)particle)->unk_08))->unk_10 =
                    ((rand() & 0xFF) - 0x80) << 10;
                ((S_80172D1C_8 *)(((ProjectileObject *)particle)->unk_08))->unk_14 = (-4 - (rand() & 3)) << 16;

                ((S_80172D1C_3 *)particle_work)->unk_48 = 10;
                sprite_flags = ((SpriteFrameState *)sprite)->unk_28;
                component_work = ((S_80172D1C_5 *)particle_sprite)->unk_14 | 0xC;
                ((S_80172D1C_5 *)particle_sprite)->unk_1E = 0x1800;
                ((S_80172D1C_5 *)particle_sprite)->unk_1C = 0x1800;
                ((S_80172D1C_5 *)particle_sprite)->unk_28 = sprite_flags;
                ((S_80172D1C_5 *)particle_sprite)->unk_14 = component_work;
                component_work_2 = ((SpriteFrameState *)sprite)->clut;
                ((S_80172D1C_5 *)particle_sprite)->unk_10 = 0x20;
                ((S_80172D1C_5 *)particle_sprite)->unk_12 = component_work_2 - 0x80;
                select_sprite_entry(particle_sprite, 0x2D, 0);
                ((S_80172D1C_5 *)particle_sprite)->unk_0C = 0x808080;
            }
            particle_or_dir_index--;
        } while (particle_or_dir_index >= 0);
    }

    particle_or_dir_index = (((EntityRec *)entity)->unk_6A >> 9) & 7;
    state = ((ActorActionTimerView *)actor)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((S_80172D1C_2 *)motion)->unk_14 = 0;
            ((S_80172D1C_2 *)motion)->unk_10.s = 0;
            ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
            begin_actor_display_action(actor, motion, sprite, D_80174194);
            break;
        }
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((ActorActionTimerView *)actor)->unk_96.s = 0;
            ((ActorActionTimerView *)actor)->unk_9B = 2;
            break;
        }

        ((S_80172D1C_2 *)motion)->unk_0C.s = dir_step_x[particle_or_dir_index] << 18;
        ((S_80172D1C_2 *)motion)->unk_10.s = dir_step_y[particle_or_dir_index] << 18;
        ((ActorActionTimerView *)actor)->unk_9B++;
        state_timer = -1;
        if (((EntityRec *)entity)->flags1C & 0x228) {
            state_timer = 8;
        }
        ((ActorActionTimerView *)actor)->unk_96.s = state_timer;
        velocity_x = ((S_80172D1C_2 *)motion)->unk_0C.s;
        ((S_80172D1C_2 *)motion)->unk_0C.s = velocity_x - velocity_x / 4;
        velocity_y = ((S_80172D1C_2 *)motion)->unk_10.s;
        ((S_80172D1C_2 *)motion)->unk_10.s = velocity_y - velocity_y / 4;
        break;

    case 1:
        ((S_80172D1C_2 *)motion)->unk_0C.s -= dir_step_x[particle_or_dir_index] << 14;
        ((S_80172D1C_2 *)motion)->unk_10.s -= dir_step_y[particle_or_dir_index] << 14;
        timer = ((ActorActionTimerView *)actor)->unk_96.s;
        if (timer > 0) {
            ((ActorActionTimerView *)actor)->unk_96.s = ((ActorActionTimerView *)actor)->unk_96.u - 1;
        } else {
            if (((SpriteFrameState *)sprite)->flags & 0x6000) {
                ((ActorActionTimerView *)actor)->unk_96.s = 0;
            }
        }
        if (((ActorActionTimerView *)actor)->unk_96.s != 0) {
            break;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((ActorActionTimerView *)actor)->unk_9B = 0;
            ((S_80172D1C_2 *)motion)->unk_14 = 0;
            ((S_80172D1C_2 *)motion)->unk_10.s = 0;
            ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
            begin_actor_display_action(actor, motion, sprite, D_80174194);
            break;
        }
        ((ActorActionTimerView *)actor)->unk_96.s = 8;
        ((ActorActionTimerView *)actor)->unk_9B++;
        break;

    case 2:
        if (((ActorActionTimerView *)actor)->unk_96.s != 0) {
            speed_work = ((SpriteFrameState *)sprite)->unk_24;
            component_work = ((S_80172D1C_2 *)motion)->unk_02.u;
            speed_work <<= 6;
            component_work -= 0x20;
            speed_work -= component_work;
            speed_work <<= 15;
            speed_work >>= 1;
            ((S_80172D1C_2 *)motion)->unk_0C.u = speed_work;

            speed_work = ((SpriteFrameState *)sprite)->unk_25;
            component_work = ((S_80172D1C_2 *)motion)->unk_06.u;
            speed_work <<= 6;
            component_work -= 0x20;
            speed_work -= component_work;
            speed_work <<= 15;
            component_work = ((S_80172D1C_2 *)motion)->unk_0C.u;
            speed_work >>= 1;
            ((S_80172D1C_2 *)motion)->unk_10.u = speed_work;
            velocity_y = component_work >> 1;
            component_work = component_work + velocity_y;
            ((S_80172D1C_2 *)motion)->unk_0C.s = component_work;
            component_work = speed_work >> 1;
            speed_work += component_work;
            ((S_80172D1C_2 *)motion)->unk_10.s = speed_work;
        }
        next_timer = ((ActorActionTimerView *)actor)->unk_96.u - 1;
        ((ActorActionTimerView *)actor)->unk_96.s = next_timer;
        if ((next_timer << 16) <= 0) {
            ((S_80172D1C_2 *)motion)->unk_14 = 0;
            ((S_80172D1C_2 *)motion)->unk_10.s = 0;
            ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->frameTable = D_8017418C;
            select_sprite_entry(sprite,
                          D_8017418C[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                          0);
            if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)entity - 0x20)) {
                *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
            }
            ((ActorActionTimerView *)actor)->unk_8C = D_801711A4;
        }
    }
}
