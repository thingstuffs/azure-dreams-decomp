#include "shared/town_event_state.h"
#include "common.h"

extern s32 D_8001E954[];

s32 townCountEnabledTownEntries(void);
u8 townResetEventSelectionAndAdvance(void);
s32 townChooseValidEntryOrFallback(s32);

void townInitializeEventSelectionState(s32 unused, s32 unused_second, s32 unused_third)
{
    D_8001E950->unk_02 = 0xFF;
    if (townCountEnabledTownEntries() != 0) {
        D_8001E950->unk_04 = townResetEventSelectionAndAdvance();
        D_8001E950->unk_05 = 2;
        D_8001E954[0] = townChooseValidEntryOrFallback(D_8001E950->unk_04);
    } else {
        D_8001E950->unk_05 = 1;
    }
}
