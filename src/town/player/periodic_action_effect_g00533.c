/* periodic action effect. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009408C. */
#include "town/player/periodic_action_effect_g00533.h"
#include "town/player.h"
#include "engine/window.h"

/* Updates actor height, emits periodic effects, and handles the active state. */
void update_actor_with_periodic_effect(TownObjectRecord *actor, ObjectPosition *position, s32 context) {
    GameWork *state = &g_game_work;
    s16 surface_height;
    s16 action_timer;
    s32 *effect_pos;
    s32 state_flags;
    u16 effect_timer;

    resolve_collision_axis_order(position);
    step_perpendicular_to_input(position);
    surface_height = query_capped_surface_height(position, &position_query_scratch);
    if ((surface_height - position->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(actor, position, context);
            return;
        }
    } else if (town_action_state_flag == 0) {
        set_height_and_slope_velocity(position, surface_height, &position_query_scratch);
    }
    effect_timer = ((u16)actor->unk_0A) - 1;
    actor->unk_0A = effect_timer;
    if ((effect_timer << 0x10) <= 0) {
        actor->unk_0A = (u16)(scale_random_by_limit(4) + 3);
        D_800FE4E0 = position->x.v;
        effect_pos = &D_800FE4E0;
        ((S_800917EC_2 *)effect_pos)->unk_04 = position->y.v;
        ((S_800917EC_2 *)effect_pos)->unk_08 =
            position->z.v + 0xFFB00000;
        spawn_radial_effect_objects(effect_pos, D_800D043C,
                      (scale_random_by_limit(2) & 0xFFFF) + 2);
    }
    state_flags = state->buttons;
    if ((state_flags & 0xF000) && (state_flags & 0x20)) {
        action_timer = ((u16)actor->unk_3E) - 1;
        actor->unk_3E = (u16)action_timer;
        play_periodic_sound(action_timer, 8);
        store_input_angle(actor);
        accelerate_toward_input_angle(position);
        return;
    }
    init_flagged_action_fallback(actor, position, context);
}

/* Resets the handler when state flags are set, then invokes the base handler. */
void reset_action_handler_on_flag(s32 **handler_slot, ObjectPosition *context, SpriteFlagsView *state) {
    if (state->flags & 0x6000) {
        dispatch_selected_entry_if_nonzero((s32 *) &D_800D0158, (TownObjectRecord *) handler_slot, state);
        *handler_slot = &update_actor_with_periodic_effect;
    }
    update_actor_with_periodic_effect(handler_slot, context, state);
}
