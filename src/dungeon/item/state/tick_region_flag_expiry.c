#include "common.h"
#include "shared/object_flags.h"
typedef struct { u16 unk00; } Pre;
typedef struct { u8 pad[8]; u16 unk08; s16 unk0A; s16 unk0C; } State;
typedef struct { u8 pad[0xC]; u16 unk0C; u8 pad2[6]; } Entry;
extern void display_formatted_context_message(void *);
extern u16 dungeon_status_flags_alias;
extern s32 D_800E18C8;
extern Entry dungeon_rooms[];
/* Counts active dungeon ticks, optionally reports expiry and clears room flag 2, then removes the timer. */
void tick_region_flag_expiry(void *state)
{
    s32 countdown;
    s32 entry_index;
    if (dungeon_status_flags_alias & 0x10) {
        countdown = ((State *)state)->unk08 - 1;
        ((State *)state)->unk08 = countdown;
        if ((countdown << 16) <= 0) {
            if (((State *)state)->unk0A == 1) {
                display_formatted_context_message(&D_800E18C8);
                entry_index = ((State *)state)->unk0C;
                dungeon_rooms[entry_index].unk0C = dungeon_rooms[entry_index].unk0C & 0xFFFD;
            }
            ((Pre *)state)[-1].unk00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
