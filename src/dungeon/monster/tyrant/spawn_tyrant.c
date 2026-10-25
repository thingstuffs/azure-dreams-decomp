#include "shared/entity.h"
#include "shared/actor_property_flags.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "dungeon/monster/tyrant/spawn_api_slot_a.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_8107D000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_8107D000_1;

typedef struct S_8107D000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8107D000_2;

typedef struct S_8107D000_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s16 unk_AA;
} S_8107D000_4;

void *allocate_list_node();
s32 register_node();
s16 set_or_clear_actor_status_slot();
s32 generate_random_value();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
extern M2C_UNK D_8014CAA4;
extern M2C_UNK D_8014CF68;
extern M2C_UNK D_8014FFB8;
extern M2C_UNK D_80150000;

/* Creates a Tyrant actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_tyrant_in_slot_a(s16 input0, s16 input1, s16 input2, s16 input3) {
    S_8107D000_1 *record;
    s32 value;
    u16 flags98;
    SpriteFrameState *child_0C;
    ObjectPosition *child_08;
    S_8107D000_4 *record_alias;
    ObjectNodeHeader *allocation;
    s8 saved_input1;
    s16 saved_input3;
    s8 saved_input2;
    void *allocation_arg;
    void *call_a1;

    record = NULL;
    saved_input1 = input1;
    saved_input3 = input3;
    saved_input2 = input2;
    allocation = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (allocation != NULL) {
        record = ((void *)allocation) + 0x20;
        allocation->update_callback = &D_8014CAA4;
        record->unk_13 = MONSTER_TYRANT;
        register_node(allocation, project_sprite_chain);
        child_08 = allocation->position;
        child_08->z.w.i = saved_input3;
        child_0C = allocation->sprite;
        value = input0 & 3;
        child_0C->tile_y = saved_input2;
        record_alias = record;
        child_0C->frameTable = &D_8014FFB8;
        child_0C->tile_x = saved_input1;
        if (value == 1) {
            flags98 = record->unk_98;
            record->unk_14 = (s32) (record->unk_14 | 0x6000);
            record->unk_98 = (u16) (flags98 | 0x4000);
            record->unk_1C = (s32) (record->unk_1C | 0x6000);
        } else if (value >= 2) {
            flags98 = record->unk_98;
            record->unk_14 = (s32) (record->unk_14 | 0x2000);
            record->unk_98 = (u16) (flags98 | 0x4000);
            record->unk_1C = (s32) (record->unk_1C | 0x2000);
        } else if (((input0 & ~3) << 0x10) == 0) {
            if (!(record->unk_14 & 0x200)) {
                value = generate_random_value();
                if (value & 1) {
                    record->unk_1C = (s32) (record->unk_1C | 0x200);
                    set_or_clear_actor_status_slot(record, 1, (generate_random_value() & 0x3F) | 0x20);
                    child_0C->frameTable = &D_80150000;
                }
            }
        }
        allocation_arg = allocation;
        initialize_actor_sprite_and_animation(allocation_arg, child_08, child_0C, input0);
        record_alias->unk_9A = 0xFF;
        record_alias->unk_9C = -1;
        record_alias->unk_8C = &D_8014CF68;
        child_0C->flags = (u16) (child_0C->flags | 0xC);
        record_alias->unk_AA = (s16) ((u16) record->unk_14 & ACTOR_ELEMENT_MASK);
        try_move_actor_to_valid_position(record_alias, child_08, child_0C, record);
    }
    return record;
}
