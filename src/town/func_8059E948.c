#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct TownEntry {
    s16 event;
    s16 check;
    s16 enabled;
    s16 pad_06;
} TownEntry;

extern s32 func_800168A0(void);
extern void func_800168E0(void);
extern void func_8001886C(s32);
extern s32 func_80018964(s32);
extern TownEntry D_80019088[7];

/* Advance through town events and dispatch the next eligible entry. */
void func_80016948(void)
{
    TownEntry *event_entry;
    TownEventCursor *event_state;
    s32 checked_count;

    event_state = &((TownProgressState *)D_80016000->unk_40)->eventCursor;
    event_state->eventIndex += 1;
    event_state->eventIndex %= 7;
    func_800168E0();

    if (func_800168A0() != 0) {
        checked_count = 0;
        do {
            if ((func_80018964(D_80019088[event_state->eventIndex].check) == 0) !=
                (D_80019088[event_state->eventIndex].enabled != 0)) {
                event_entry = &D_80019088[event_state->eventIndex];
                func_8001886C(event_entry->event);
                break;
            }

            event_state->eventIndex += 1;
            event_state->eventIndex %= 7;
            checked_count += 1;
        } while (checked_count < 7);

        if (event_state->eventIndex != 5) {
            func_8001886C(0x60E);
        }
        func_8001886C(0x606);
    }
}
