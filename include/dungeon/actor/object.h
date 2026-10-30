#ifndef DUNGEON_ACTOR_OBJECT_H
#define DUNGEON_ACTOR_OBJECT_H

/* Function contracts owned by src/dungeon/actor/object/ (decision 74; maintained by tools/headers). */
#include "common.h"
s32 count_occupied_entity_slots(void *entity);
s32 is_linked_object_flagged_10000(void *object);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct Func8180F0F4_Obj;
s32 find_entity_slot_by_field_e4(s32 target_value);
void *select_object_by_flags_and_keys(struct Func8180F0F4_Obj *first, struct Func8180F0F4_Obj *second, s16 *out_mask);

#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
void initialize_actor_object_action(void *object_state, void *unused_context, Rec_D_80082E80 *properties, EntityRec *status);

#endif
