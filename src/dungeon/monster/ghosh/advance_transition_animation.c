#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "engine/object.h"
#include "dungeon/effect/screen.h"
#include "dungeon/monster/ghosh.h"
#include "dungeon/system.h"

typedef struct {
    unsigned char pad8c[0x8c];
    void *action_handler;
    unsigned char pad90[6];
    s16 action_timer;
    unsigned char pad98[3];
    u8 action_phase;
} DungeonState;

typedef struct {
    unsigned char pad0[0xC];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
} Arg1;

typedef struct {
    unsigned char pad0[0x14];
    u16 flags;
    unsigned char pad16[0x16];
    void *unk2c;
} Arg2;

typedef struct {
    unsigned char pad0[0x2A];
    s16 facing;
    unsigned char pad2c[0x1A];
    u16 flags46;
    unsigned char pad48[0x25];
    s8 pending_turn_updates;
} Arg3;

typedef struct {
    unsigned char pad0[0x28];
    u8 unk28;
    unsigned char pad29[0x83];
    u8 *unkac;
} DungeonEntry;

extern u8 ghosh_action_resume_address[];
extern u8 D_801746B4[];
extern u8 D_800F93AA[];

struct SpriteFrameState;
extern void clear_actor_action_markers(u8 *state);
extern void func_8016D11C(void) __attribute__((noreturn));

/* Advances the dungeon transition animation and resets entry resources when it completes. */
void advance_transition_animation(DungeonState *state, Arg1 *motion, SpriteFrameState *animation, Arg3 *actor) {
    s32 stage;

    stage = state->action_phase;
    switch (stage) {
    case 0:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        state->action_timer = 0;
        state->action_phase = state->action_phase + 1;
        if (!(animation->flags & 0x8000)) {
            break;
        }
    case 1:
        state->action_timer = 0;
        state->action_phase = state->action_phase + 1;
        animation->frameTable = D_801746B4;
        select_sprite_entry(animation, D_801746B4[(((s32)g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
    case 2:
        state->action_timer = state->action_timer + 1;
        if ((s16)state->action_timer == 10 || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            state->action_timer = 0;
            state->action_phase = state->action_phase + 1;
        }
        if ((s16)state->action_timer == 8) {
            play_sound_if_enabled(0x804);
        }
        break;
    case 3:
        if (animation->flags & 0xE000) {
            if (dungeon_actor_ring_anchor->hp < 2) {
                s32 entry_index;
                s32 resource_flag;
                void *effect;

                create_scene_brighten_effect();
                effect = D_800F93AA;
                state->action_handler = ghosh_action_resume_address;
                g_dungeon_status.active_actor = 0;
                g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
                *(u16 *)((u8 *)actor + 0x46) &= 0x7FFF;
                *&system_update_flags = system_update_flags | 8;
                queue_pool_service_script(effect);
                entry_index = 0;
                resource_flag = 0x80000000;
                actor->pending_turn_updates = 0;
                state->action_phase = 0;
                for (;;) {
                    DungeonEntry *entry;
                    u32 entry_addr;

                    entry_addr = (u32)(entry_index * 4) + (u32)((DungeonEntry *)dungeon_actor_ring_anchor);
                    entry = (DungeonEntry *)entry_addr;
                    if (entry->unkac != 0) {
                        u32 *resource_header;

                        clear_actor_action_markers(entry->unkac);
                        entry = (DungeonEntry *)((u32)(entry_index * 4) + (unsigned long)((DungeonEntry *)dungeon_actor_ring_anchor));
                        resource_header = (u32 *)(entry->unkac - 0x20);
                        resource_header[4] = resource_header[4] | resource_flag;
                    }
                    entry_index++;
                    if (entry_index >= 2) {
                        return;
                    }
                }
            } else {
                state->action_handler = ghosh_action_resume_address;
                g_dungeon_status.active_actor = 0;
                advance_status_timers(actor);
                actor->flags46 = actor->flags46 & 0x7FFF;
            }
        }
        break;
    }
}
