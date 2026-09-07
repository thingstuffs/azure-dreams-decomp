#include "common.h"

typedef s32 (*Callback)(s32, void *);

typedef struct Root {
    u8 pad[0x20];
    void *dispatch;
} Root;

typedef struct Dispatch {
    u8 pad[0x2D4];
    Callback callback;
} Dispatch;

extern s32 func_8001A2F0(void);
extern Root *D_80016000;
extern u8 *volatile D_8001E950;
extern void *D_80018094[];
extern void *D_800180B4[];
extern s16 D_80018074[];
extern u8 D_8001914C[];
extern u8 D_80020F85[];
extern u8 D_80020FC7[];

void *func_8001B6F8(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 page ASM_REG("$3");
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

    if (arg2 == 1) {
        volatile u8 *state1;

        state1 = D_8001E950;
        if (state1[4] == 4) {
            if (((Dispatch *)D_80016000->dispatch)->callback(0, table) == 2) {
                if (func_8001A2F0() >= 3) {
                    return D_80020F85;
                }
            }
            return D_80020FC7;
        }
        return table[state1[4]];
    }

    page = 0x80020000;
    ASM_KEEP(page);
    if (*(s16 *)(page - 0x7F8C) != 0) {
        entry = (s16 *)(page - 0x7F8C);
        do {
            if (*entry == arg2) {
                return table[entry[1]];
            }
            entry += 2;
        } while (*entry != 0);
    }
    return D_8001914C;
}

/* MECHANISM: Recovered the in-range B730/B7C8/B818 targets as local CFG joins,
   preserving the 0x18 frame with only $ra saved and keeping arg2 in $a2.
   The cdk-G0 reroute plus a guarded $v1-held 0x8002 page removed the loop-base
   copy and reproduced the zero-test delay slot and table/index register roles. */
