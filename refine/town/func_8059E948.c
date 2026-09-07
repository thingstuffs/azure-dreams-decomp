#include "common.h"

typedef struct TownRoot {
    u8 pad_00[0x40];
    u8 *state;
} TownRoot;

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
extern void *D_80016000;
extern TownEntry D_80019088[7];

/* Advance through town events and dispatch the next eligible entry. */
void func_80016948(void)
{
    TownEntry *event_entry;
    u8 *event_state;
    s32 checked_count;

    event_state = ((TownRoot *)D_80016000)->state + 0x68;
    event_state[6] += 1;
    event_state[6] %= 7;
    func_800168E0();

    if (func_800168A0() != 0) {
        checked_count = 0;
        do {
            if ((func_80018964(D_80019088[event_state[6]].check) == 0) !=
                (D_80019088[event_state[6]].enabled != 0)) {
                event_entry = &D_80019088[event_state[6]];
                func_8001886C(event_entry->event);
                goto finish;
            }

            event_state[6] += 1;
            event_state[6] %= 7;
            checked_count += 1;
        } while (checked_count < 7);

finish:
        if (event_state[6] != 5) {
            func_8001886C(0x60E);
        }
        func_8001886C(0x606);
    }
}
