#include "common.h"


typedef void (*TownCallback)(s16, s16);

typedef struct S_8001975C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001975C_0;   /* *(void **)D_80016000 in func_8001975C */


extern void func_800198AC(s32);
extern s16 *func_80019AFC(u8, u8);
extern s8 D_80016000[];
extern u8 *D_8001E950;

s32 func_8001975C(s32 arg0) {
    s16 *event;
    void *town;
    TownCallback callback;
    s32 result;

    if (D_8001E950[1] == 0) {
        func_800198AC(arg0);
        D_8001E950[1]++;
        result = 1;
        event = func_80019AFC(D_8001E950[1], D_8001E950[5]);
        town = ((S_8001975C_0 *)(*(void **)D_80016000))->unk_20;
        callback = (*(TownCallback *)((u8 *)town + 0x2F8));
        callback(event[0], event[1]);
    } else {
        result = 0;
    }
    return result;
}

/* MECHANISM: true-space identity and a single merged result keep $s0 live
   as both the D_8001E950 page base and the 0/1 return across the callback.
   Typed s16 event fields and separate pointer locals preserve the load widths. */
