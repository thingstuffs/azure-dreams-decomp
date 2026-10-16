#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"


typedef void (*TownCallback)(s16, s16);

typedef struct S_8001975C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001975C_0;   /* *(void **)D_80016000 in townStartDispatchEvent */


extern void townSelectNextEventState(void);
extern s16 *townSelectEventDataTable(u8, u8);

/* Initializes the town event once, invokes its callback, and reports whether it ran. */
s32 townStartDispatchEvent(s32 init_arg) {
    s16 *event;
    void *town;
    TownCallback callback;
    s32 started;

    if (D_8001E950->dispatchState == 0) {
        townSelectNextEventState();
        D_8001E950->dispatchState++;
        started = 1;
        event = townSelectEventDataTable(D_8001E950->dispatchState, D_8001E950->unk_05);
        town = ((S_8001975C_0 *)(*(void **)((s8 *)(&D_80016000))))->unk_20;
        callback = (*(TownCallback *)((u8 *)town + 0x2F8));
        callback(event[0], event[1]);
    } else {
        started = 0;
    }
    return started;
}
