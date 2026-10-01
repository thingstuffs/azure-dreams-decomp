#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef s32 (*Callback)(s32, void *);

typedef struct Dispatch {
    u8 pad[0x2D4];
    Callback callback;
} Dispatch;

extern s32 func_8001A2F0(void);
extern u8 *D_8001E950;
extern void *D_80018094[];
extern void *D_800180B4[];
extern s16 D_80018074[];
extern u8 D_8001914C[];
extern u8 D_80020F85[];
extern u8 D_80020FC7[];

/* Resolve the key to its table entry, using the slot-4 special case or the paged lookup table. */
void *func_8001B6F8(s32 unused_a, s32 unused_b, s32 key)
{
    s32 index;
    u8 *state0;
    void **table;
    s16 *entry;

    state0 = D_8001E950;
    if (state0[6] == 0) {
        state0[6] = 1;
        table = D_80018094;
    } else {
        table = D_800180B4;
    }

    if (key == 1) {
        u8 *state1;

        state1 = D_8001E950;
        if (state1[4] == 4) {
            if (((Dispatch *)D_80016000->unk_20)->callback(0, table) == 2) {
                if (func_8001A2F0() >= 3) {
                    return D_80020F85;
                }
            }
            return D_80020FC7;
        }
        return table[state1[4]];
    }

    for (index = 0; D_80018074[index] != 0; index += 2) {
        entry = &D_80018074[index];
        if (*entry == key)
            return table[entry[1]];
    }
    return D_8001914C;
}
