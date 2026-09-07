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

void func_80016948(void)
{
    TownEntry *entry;
    u8 *state;
    s32 i;

    state = ((TownRoot *)D_80016000)->state + 0x68;
    state[6] += 1;
    state[6] %= 7;
    func_800168E0();

    if (func_800168A0() != 0) {
        i = 0;
        do {
            if ((func_80018964(D_80019088[state[6]].check) == 0) !=
                (D_80019088[state[6]].enabled != 0)) {
                entry = &D_80019088[state[6]];
                func_8001886C(entry->event);
                goto finish;
            }

            state[6] += 1;
            state[6] %= 7;
            i += 1;
        } while (i < 7);

finish:
        if (state[6] != 5) {
            func_8001886C(0x60E);
        }
        func_8001886C(0x606);
    }
}

/* MECHANISM: The 0x20 frame follows from three live ranges: state in s0,
   loop count in s1, and the eight-byte entry-table base in s2.
   The in-row 0x80016A64 target is a local finish join, not a callee. */
