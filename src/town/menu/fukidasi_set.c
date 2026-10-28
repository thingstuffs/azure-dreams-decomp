#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_trail_views.h"
#include "shared/dungeon_effect_views.h"
#include "shared/object_payload.h"
#include "engine/node.h"

#ifndef NULL
#define NULL 0
#endif

   /* entry in fukidasi_set */

   /* part_data in fukidasi_set */

   /* part in fukidasi_set */

typedef struct S_800A75E4_4 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
    u8 pad_92[0x3];
    s8 unk_95;
    s8 unk_96;
} S_800A75E4_4;   /* body in fukidasi_set */

typedef struct {
    s32 unk0;
    void *value;
} EntryRecord;

extern void *create_town_effect_object();
extern u8 D_800A76F0;
extern s32 D_800D0E24[];
extern s32 D_800D0E3C[];

/* fukidasi_set: create a speech bubble object and initialize its part and body from indexed data. */
void fukidasi_set(s32 entry_index, s32 part_index, s32 body_index, s32 body_value) {
    void *entry_or_body;
    void *entry_data;
    void *object_template;
    ObjectPayloadView *entry;
    ObjectNodeHeader *object;
    S_800A75E4_4 *body;
    ObjectPosition *part;
    s32 *value_slot;
    SpriteFrameState *part_data;

    entry_or_body = NULL;
    entry_data = entry_or_body;
    if (entry_index != 0) {
        entry = object_index_slots[entry_index].object;
        if (entry != NULL) {
            entry_or_body = entry;
            entry_data = entry->unk_08;
        }
    }
    object_template = &D_800A76F0;

    object = create_town_effect_object(entry_or_body, entry_data, object_template, 0);
    if (object != NULL) {
        body = (S_800A75E4_4 *)((u8 *)object + 0x20);
        part = object->position;
        part_data = object->sprite;
        part_data->source = D_800D0E24[part_index];
        register_node_if_unregistered(body, project_sprite_chain);
        part->z.w.i = (u16)part->z.w.i - 0x62;
        body->unk_90 = 0xA;
        body->unk_6C = body_value;
        body->unk_95 = part_index;
        body->unk_96 = body_index;
        value_slot = D_800D0E3C;
        body->unk_50 = value_slot[body_index];
    }
}
