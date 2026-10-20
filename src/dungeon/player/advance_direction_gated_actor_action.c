#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[8];
    s32 field08;
    u8 pad0c[0x80];
    void *field8c;
    u8 pad90[6];
    u16 countdown;
    u8 pad98[3];
    u8 state;
    u8 pad9c[0x30];
    u8 *table;
    u8 padd0[0x3e];
    s16 field10e;
    s32 field110;
    s32 field114;
} S_8003E2D8;

typedef struct {
    u8 pad00[8];
    s32 field08;
    u8 pad0c[8];
    u16 flags;
    u8 pad16[0x16];
    void *field2c;
} S_arg2;

typedef struct {
    u8 pad00[0x2a];
    s16 coord;
} S_arg3;

extern u8 D_800DD148[];
extern u8 D_800DD150[];

extern s32 resolve_record_orientation_or_fallback(s32, void *, void *, s32);
extern void set_sprite_animation_frame(void *, u8, s16, s32);
extern void begin_parameterized_actor_action(void *, void *, void *, u8 *, s32);
extern void begin_deferred_player_item_effect(void *, void *, void *);
extern void create_radial_effect_controller(s32);

/* Advance the actor's directional animation state and delayed transition. */
void advance_direction_gated_actor_action(S_8003E2D8 *controller, void *context, S_arg2 *actor, S_arg3 *facing) {
    s32 state;
    s32 query_result;
    s32 direction;

    state = controller->state;
    switch (state) {
    case 0:
        if ((s32)((((s32)g_game_work.view.camera_rotation.parts.viewAngle + facing->coord + 0x100) >> 9) & 7) == 2) {
            u8 *animation_table;

            animation_table = controller->table;
            actor->field2c = animation_table;
            direction = (((s32)g_game_work.view.camera_rotation.parts.viewAngle + facing->coord + 0x100) >> 9) & 7;
            set_sprite_animation_frame(actor, animation_table[direction], controller->field10e, 1);
            controller->state++;
        } else {
            facing->coord = (u16)facing->coord + 0x200;
        }
        break;
    case 1:
        if (D_80013714 & 8) {
            if (actor->flags & 0x6000) {
                if (actor->field2c == D_800DD148) {
                    controller->state = 0x10;
                } else {
                    controller->field8c =handle_player_input;
                }
            }
        } else if ((resolve_record_orientation_or_fallback(actor->field08, actor, &query_result, 0) != 0) || (actor->flags & 0x8000)) {
            create_radial_effect_controller(controller->field114);
            controller->state++;
        }
        break;
    case 2:
        if ((actor->flags & 0x8000) || (g_dungeon_status.activity_counts.parts.pending_action_count < 2)) {
            if (controller->field110 != 0) {
                begin_deferred_player_item_effect(controller, context, actor);
                return;
            }
            actor->field2c = D_800DD150;
            set_sprite_animation_frame(actor, D_800DD150[(((s32)g_game_work.view.camera_rotation.parts.viewAngle + facing->coord + 0x100) >> 9) & 7], 2, 1);
            controller->field8c =handle_player_input;
        }
        break;
    case 0x10:
    {
        u16 countdown;

        countdown = controller->countdown - 1;
        controller->countdown = countdown;
        if ((s32)(countdown << 16) <= 0) {
            begin_parameterized_actor_action(controller, context, actor, D_800DD150, 0);
        }
        break;
    }
    }
}
