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

/* Initializes the town event once, invokes its callback, and reports whether it ran. */
s32 func_8001975C(s32 init_arg) {
    s16 *event;
    void *town;
    TownCallback callback;
    s32 started;

    if (D_8001E950[1] == 0) {
        func_800198AC(init_arg);
        D_8001E950[1]++;
        started = 1;
        event = func_80019AFC(D_8001E950[1], D_8001E950[5]);
        town = ((S_8001975C_0 *)(*(void **)D_80016000))->unk_20;
        callback = (*(TownCallback *)((u8 *)town + 0x2F8));
        callback(event[0], event[1]);
    } else {
        started = 0;
    }
    return started;
}
