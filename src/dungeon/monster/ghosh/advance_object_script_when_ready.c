#include "common.h"
#include "shared/dungeon_status.h"

typedef struct DungeonState {
    u8 pad0[10];
    s16 field_A;
    u8 pad_C[4];
    s32 field_10;
} DungeonState;

extern u8 ghosh_action_resume_address[];
extern void allocate_type_12_object(void);

/* Advances the object's counter and switches its script when the dungeon is ready. */
void advance_object_script_when_ready(void *object, s32 unused_1, s32 unused_2, s32 state_base)
{
    u8 previous_count;
    u8 count;

    previous_count = *(u8 *)((u8 *)object + 0x9B);
    count = previous_count + 1;
    *(u8 *)((u8 *)object + 0x9B) = count;

    if (count == 1) {
        s32 state_code = ((s32)g_dungeon_status.pending_display_owner);

        if (state_code == state_base - 0x20) {
            g_dungeon_status.pending_display_owner = state_code & 0x7FFFFFFF;
            return;
        }
    } else if (count >= 5) {

        *(u8 *)((u8 *)object + 0x9B) = previous_count;
        if (g_dungeon_status.activity_counts.parts.pending_action_count == 0) {
            allocate_type_12_object();
            *(s8 *)((u8 *)object + 0xB4) = 1;
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16)g_dungeon_status.activity_counts.parts.pending_action_count + 1;
            *(u8 *)((u8 *)object + 0x9B) = 0;
            *(u8 **)((u8 *)object + 0x8C) = ghosh_action_resume_address;
        }
    }
}
