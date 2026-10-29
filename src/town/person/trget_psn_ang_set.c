#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/object_index_slots.h"


typedef struct S_800C4D80_1 {
    u8 pad_00[0xC];
    void *unk_0C;
    void * unk_10;
} S_800C4D80_1;   /* entry in trget_psn_ang_set */

typedef struct S_800C4D80_2 {
    u8 pad_00[0x4];
    void *unk_04;
} S_800C4D80_2;   /* child in trget_psn_ang_set */


typedef struct {
    s32 unused;
    void *object;
} TownEntry;

extern u8 message_motion_type_a[];
extern u8 message_motion_type_b[];
extern u16 town_facing_angles[];

extern void initialize_object_entries(void *,SpriteFrameState *,s32 *);

/* trget_psn_ang_set: set the matching person's angle from the table and refresh its child state. */
void trget_psn_ang_set(s8 object_slot, s8 angle_index)
{
    TownEntry *table;
    s32 object_index;
    void *object_kind;
    u16 angle;
    void *object;
    S_800C4D80_1 *entry;
    S_800C4D80_2 *child;
    Rec_func_80094268_arg0 *object_data;

    table = object_index_slots;
    object_index = object_slot;
    object = table[object_index].object;
    if (object != 0) {
        angle = town_facing_angles[angle_index];
        entry = object;
        object_data = (u8 *)object + 0x20;
        if (object_index == object_data->unk_60) {
            if (object_index == 1) {
                object_kind = entry->unk_10;
                if (object_kind != message_motion_type_a && object_kind != message_motion_type_b) {
                    object_data->unk_10.as_u16 = angle;
                    return;
                }
            }
            child = object_data->unk_80;
            object_data->unk_6E = angle;
            object_data->unk_72.as_u16 = angle;
            initialize_object_entries(object_data, entry->unk_0C,
                          child->unk_04);
        }
    }
}
