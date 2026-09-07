#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*TownCallback)(s16, s16);

extern void func_800198AC(void);
extern s16 *func_80019AFC(u8, u8);
extern s8 D_80016000[];
extern u8 *D_8001E950;

s32 func_8001975C(void) {
    s16 *event;
    void *town;
    TownCallback callback;
    s32 result;

    if (D_8001E950[1] == 0) {
        func_800198AC();
        D_8001E950[1]++;
        result = 1;
        event = func_80019AFC(D_8001E950[1], D_8001E950[5]);
        town = FIELD(*(void **)D_80016000, void *, 0x20);
        callback = FIELD(town, TownCallback, 0x2F8);
        callback(event[0], event[1]);
    } else {
        result = 0;
    }
    return result;
}

/* MECHANISM: true-space identity and a single merged result keep $s0 live
   as both the D_8001E950 page base and the 0/1 return across the callback.
   Typed s16 event fields and separate pointer locals preserve the load widths. */
