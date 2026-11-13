#ifndef TOWN_PERSON_ACTOR_DATA_REFERENCES_G00663_H
#define TOWN_PERSON_ACTOR_DATA_REFERENCES_G00663_H
/* Actor data references. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D58B8. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/entity.h"



/* arg0 in set_linked_data_pointers_variant_2 */


typedef struct S_800C6478_0 {
    u8 pad_00[0x80];
    void * linked_data; /* 0x80 */
} S_800C6478_0;

/* arg0 in set_linked_data_field_pointer */
typedef struct S_800C6478_1 {
    u8 pad_00[0x4];
    s32 * data; /* 0x04 */
} S_800C6478_1;

typedef s32 unk32;


/* arg0 in check_actor_data_references_match */
typedef struct S_800C648C_1 {
    u8 pad_00[0x4];
    s32 data; /* 0x04 */
} S_800C648C_1;

/* ((S_800C645C_1 *)arg0)->linked_data in set_linked_data_pointers_variant_2 */
extern M2C_UNK D_800D58F4;
/* ((S_800C6478_0 *)arg0)->linked_data in set_linked_data_field_pointer */
extern M2C_UNK D_800D5930;

extern M2C_UNK D_800D58B8;
struct SpriteFrameState;

void set_object_referenced_data_pointers(TownObjectRecord *object, void *unused_context, struct SpriteFrameState *unused_sprite);

/* Functions defined in this translation unit. */
void set_linked_data_pointers_variant_1(TownObjectRecord *record, ObjectPosition *unused_context, struct SpriteFrameState *unused_sprite);
void set_linked_data_pointers_variant_2(TownObjectRecord *object);
void set_linked_data_field_pointer(S_800C6478_0 *object);

#endif
