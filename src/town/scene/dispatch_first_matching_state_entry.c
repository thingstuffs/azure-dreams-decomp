#include "shared/game_work.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern u32 map_runtime_state;
extern s32 D_800D3824[];
extern void build_two_display_entries(s32 data_id, s16 position_offset);
/* Calls build_two_display_entries with the first table entry matching the state's ID. */
void dispatch_first_matching_state_entry(void)
{
    s32 *table_entry;
    s8 *state;
    s32 i;

    for (i = 0; D_800D3824[i * 3] != -1; i++) {
        state = (s8 *) (&map_runtime_state);
        table_entry = &D_800D3824[i * 3];
        if (*((s16 *) (state + 0x1A)) == (*table_entry)) {
            build_two_display_entries(*((s32 *) (((s8 *) table_entry) + 4)), *((s16 *) (((s8 *) table_entry) + 8)));
            return;
        }
    }
}
