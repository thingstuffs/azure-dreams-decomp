#ifndef TOWN_PERSON_ACTOR_DATA_REFERENCES_G00663_H
#define TOWN_PERSON_ACTOR_DATA_REFERENCES_G00663_H
/* Actor data references. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D58B8. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/entity.h"



typedef s32 unk32;

extern M2C_UNK D_800D58F4;
extern M2C_UNK D_800D5930;

extern M2C_UNK D_800D58B8;
struct SpriteFrameState;

void set_object_referenced_data_pointers(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

/* Functions defined in this translation unit. */
void set_linked_data_pointers_variant_1(TownObjectRecord *record, ObjectPosition *unused_context, struct SpriteFrameState *unused_sprite);
void set_linked_data_pointers_variant_2(TownObjectRecord *object);
void set_linked_data_field_pointer(TownObjectRecord *object);

#endif
