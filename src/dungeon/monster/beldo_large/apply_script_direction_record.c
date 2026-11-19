#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "dungeon/monster/beldo_large.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2];
    u16 field_02;
    u8 pad_04[0x2];
    u16 field_06;
} RecordFieldView_8133879C;



extern s16 func_8016F428(void *arg);




/*
 * Faces the linked Beldo actor toward the record's octant, copies the player's facing when
 * coincident, and restores X/Y.
 */
void apply_script_direction_record(void *unused_0, ObjectPosition *record, SpriteFrameState *unused_2) {
    u8 *source_base = (u8 *)(&scene_object_list_anchor.next);
    register ActorRecord *source_data = (ActorRecord *)(source_base + 0x20);
    ObjectNodeHeader *target_base = beldo_script_node;
    ActorRecord *target_data = NODE_BODY(target_base);
    s16 raw_value = func_8016F428(record);
    s32 decoded_value = raw_value;

    if (decoded_value == 9) {
        target_data->facing = source_data->facing;
    } else {
        target_data->facing = (u16)(decoded_value << 9);
    }
    {
        register u16 *default_words = (u16 *)((u8 *)(&view_reference_entity));
        record->x.unsigned_parts.integer = default_words[1];
        record->y.unsigned_parts.integer = default_words[3];
    }
}
