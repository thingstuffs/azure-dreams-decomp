#include "shared/town_event_state.h"
#include "common.h"

extern s32 D_8001E954[];

s32 count_enabled_town_entries(void);
u8 reset_event_selection_and_advance(void);
s32 choose_valid_entry_or_fallback(s32);

void initialize_event_selection_state(s32 unused, s32 unused_second, s32 unused_third)
{
    D_8001E950->unk_02 = 0xFF;
    if (count_enabled_town_entries() != 0) {
        D_8001E950->unk_04 = reset_event_selection_and_advance();
        D_8001E950->unk_05 = 2;
        D_8001E954[0] = choose_valid_entry_or_fallback(D_8001E950->unk_04);
    } else {
        D_8001E950->unk_05 = 1;
    }
}
