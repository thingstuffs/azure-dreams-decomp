#include "common.h"

/* 12-byte struct; entries in D_80086C00[8] */
typedef struct {
    s16 field_0;
    s16 field_2;
    s8 pad4[4];
    u16 field_8;
    u16 field_A;
} S_80086C00;

extern S_80086C00 D_80086C00[8];
extern s32 func_80059D60(void);

/* Advances an entry's state from 1 to 3 when func_80059D60 returns 3, then returns the state. */
s16 func_8005C5D0(s16 entry_index)
{
    S_80086C00 *entries = D_80086C00;
    S_80086C00 *entry = &entries[entry_index];

    if (entry->field_2 == 1) {
        s32 next_state = func_80059D60();
        if (next_state == 3) {
            entry->field_2 = (s16)next_state;
        }
    }
    return D_80086C00[entry_index].field_2;
}
