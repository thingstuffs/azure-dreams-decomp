#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "town/player/coordinates.h"
#include "town/event.h"
#include "town/event/object.h"
#include "town/player/motion.h"
#include "town/player/position.h"

struct TownObj;
struct TownVec;

typedef struct Obj800AD0E4 {
    u8 pad0[0xA];
    u16 field_A;
} Obj800AD0E4;

extern void initialize_scene_action_record(Obj800AD0E4 *, void *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void initialize_actor_action_state(Obj800AD0E4 *, ObjectPosition *, s32);
extern void initialize_action_object(Obj800AD0E4 *, void *, s32);
extern void apply_velocity_friction(ObjectPosition *);
extern void set_height_and_slope_velocity(ObjectPosition *obj, s32 base_value, struct TownVec **vec_ptr);

/* Update the object and dispatch actions based on its value, timer, and state flags. */
void update_object_and_dispatch_actions(Obj800AD0E4 *timer_obj, ObjectPosition *object, SpriteFrameState *sprite) {
    GameWork *state = &g_game_work;
    s16 next_value;
    u16 timer;

    resolve_collision_axis_order(object);
    apply_velocity_friction(object);
    next_value = query_capped_surface_height(object, &position_query_scratch);

    if ((next_value - (s16)object->z.unsigned_parts.integer) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(timer_obj, object, (s32)sprite);
            return;
        }
    } else if (town_action_state_flag == 0) {
        set_height_and_slope_velocity(object, next_value, &position_query_scratch);
    }

    timer = timer_obj->field_A - 1;
    timer_obj->field_A = timer;
    if ((s16)timer < 0) {
        initialize_scene_action_record(timer_obj, object, (s32)sprite);
        return;
    }

    if (((u32)state->buttons) & 0xF000) {
        initialize_motion_action(timer_obj, object, sprite);
        return;
    }

    if (((u32)state->pressed_buttons) & 0x10) {
        initialize_actor_action_state(timer_obj, object, (s32)sprite);
        return;
    }

    update_positions_from_origin(object);
}
