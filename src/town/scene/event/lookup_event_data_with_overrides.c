#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef struct S_80016714_1 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016714_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_08.at00_s32.v * 8 +
              ((Rec_D_80016000 *)D_80016000)->unk_40.as_pu8 in lookup_event_data_with_overrides */

typedef struct S_80016714_2 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016714_2;   /* ((Rec_D_80016000 *)D_80016000)->unk_08.at00_s32.v * 8 +
                  ((Rec_D_80016000 *)D_80016000)->unk_40.as_pu8 in lookup_event_data_with_overrides */


extern u8 D_800189DC[16];
extern u8 scene_event_lookup_context[16];
extern u8 D_8001A3AE[];
extern u8 D_8001A495[];

extern s32 func_800178A8(void *, s32, s32);
extern void *func_80017960(void *, void *, s32, s32);
extern void initialize_state_two_entries_pointer(s32);
extern s32 func_8001868C(s32);

/* Looks up event data and applies special-event state updates and overrides. */
void *lookup_event_data_with_overrides(s32 entry_id, s32 unused, s32 event_id)
{
    void *event_data;
    u8 *event_table;

    event_table = D_800189DC;
    event_data = func_80017960(event_table, scene_event_lookup_context, entry_id, event_id);
    if (event_id == 0xB) {
        initialize_state_two_entries_pointer(F_s34_sero_start);
        if (func_800178A8(event_table, entry_id, 0xB) != 0) {
            return &D_8001A3AE[0];
        }
        ((S_80016714_1 *)(D_80016000->unk_08 * 8 +
              ((u8 *)D_80016000->unk_40)))->unk_04++;
        if (((S_80016714_2 *)(D_80016000->unk_08 * 8 +
                  ((u8 *)D_80016000->unk_40)))->unk_04 >= 5U) {
            initialize_state_two_entries_pointer(F_s34_sero_quickstart);
        }
        return event_data;
    }
    if (event_id == 0x1C) {
        if (func_8001868C(F_sbs34_pad18) == 0) {
            initialize_state_two_entries_pointer(F_sbs34_pad18);
            return &D_8001A495[0];
        }
    }
    return event_data;
}
