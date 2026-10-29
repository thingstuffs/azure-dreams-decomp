#ifndef TOWN_EVENT_OBJECT_H
#define TOWN_EVENT_OBJECT_H
/* Prototypes of the functions defined in src/town/event/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"

struct S_8009B120_0;
struct S_8009C0D8_1;
struct SpriteFrameState;

/* check_object_type_and_data_tag.c */
s32 check_object_type_and_data_tag(struct S_8009B120_0 *record);

/* dispatch_object_event_or_retire.c */
void dispatch_object_event_or_retire(void *object, s32 event, s32 event_data);

/* initialize_moving_object.c */
void initialize_moving_object(struct S_8009C0D8_1 *context, Rec_func_80094268_arg0 *object);

/* initialize_object_action_with_default_data.c */
void initialize_object_action_with_default_data(void *object, void *action, struct SpriteFrameState *state);

/* initialize_object_and_maybe_play_sound.c */
void initialize_object_and_maybe_play_sound(u8 *context, s8 *object, s32 *state);

/* initialize_timed_object_action.c */
void initialize_timed_object_action(void *context, void *source, void *record);

/* select_object_value_by_height_band.c */
void select_object_value_by_height_band(Rec_func_80094268_arg0 *object, void *context, EntityRec *position, Rec_D_80082E80 *output);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/sprite_frame_state.h"

#endif
