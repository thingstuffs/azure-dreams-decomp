#ifndef TOWN_EVENT_OBJECT_H
#define TOWN_EVENT_OBJECT_H
/* Prototypes of the functions defined in src/town/event/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/town_object.h"
#include "shared/entity.h"

struct Obj800AD0E4;
struct S_8009B120_0;
struct SpriteFrameState;

/* check_object_type_and_data_tag.c */
s32 check_object_type_and_data_tag(struct S_8009B120_0 *record);

/* dispatch_object_event_or_retire.c */
void dispatch_object_event_or_retire(void *object_arg, ObjectPosition *position, struct SpriteFrameState *sprite);

/* initialize_moving_object.c */
void initialize_moving_object(TownObjectRecord *context, TownObjectRecord *object);

/* initialize_object_action_with_default_data.c */
void initialize_object_action_with_default_data(TownObjectRecord *object, ObjectPosition *action, struct SpriteFrameState *state);

/* initialize_object_and_maybe_play_sound.c */
struct ColliderView;
struct SpriteFrameState;
void initialize_object_and_maybe_play_sound(TownObjectRecord *object, struct ColliderView *collider, ObjectPosition *motion, struct SpriteFrameState *unused);

/* initialize_timed_object_action.c */
#include "shared/sprite_frame_state.h"
void initialize_timed_object_action(TownObjectRecord *context, ObjectPosition *source, SpriteFrameState *record);

/* select_object_value_by_height_band.c */
void select_object_value_by_height_band(TownObjectRecord *object, void *context, ObjectPosition *position, struct SpriteFrameState *output);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
/* The timer and position access view remains private to the implementation. */

void update_object_and_dispatch_actions(struct Obj800AD0E4 *timer_obj, ObjectPosition *object, SpriteFrameState *sprite);

#endif
