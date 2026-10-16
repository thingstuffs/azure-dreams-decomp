#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 Callback(s32);

typedef struct S_8001B828_0 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 pad_05[0x1B];
    void * unk_20;
} S_8001B828_0;   /* obj in townDispatchEventRequest */


extern void townAdvanceDispatchStateToTwo(void);
extern s8 townFindFirstEnabledEntryId(void);
extern s32 townCheckEventValueInList(s32);
extern void *townClearEventResourceStateAndGetBuffer(s32);
extern void *townResolveEventResponseKey();
extern void func_8001E5F0(s32);

extern s32 D_8001601C;
extern u8 D_80017774[];
extern u8 D_8001914C[];


/* Dispatches requests by mode, refreshing the state code before selecting a response. */
void *townDispatchEventRequest(s32 request, void *data, s32 mode) {
    u8 new_code;
    s32 status;
    void *context;
    TownEventState *state;

    if (mode == 0) {
        func_8001E5F0(0x402);
        context = D_8001E950;
        status = townCheckEventValueInList(((S_8001B828_0 *)context)->unk_04);
        if (status == 0) {
            context = D_80016000;
            context = ((S_8001B828_0 *)context)->unk_20;
            status = (*(Callback **)((u8 *)context + 0x2D4))(0);
            if (status != 2) {
                return D_8001914C;
            }
            new_code = townFindFirstEnabledEntryId();
            D_8001E950->unk_04 = new_code;
        }
        state = D_8001E950;
        if (state->unk_04 != 0) {
            return townClearEventResourceStateAndGetBuffer(state->unk_04);
        }
        return D_8001914C;
    }
    if (mode == 1) {
        townAdvanceDispatchStateToTwo();
        return townResolveEventResponseKey(request, data, 1);
    }
    if (mode == 5) {
        return D_80017774;
    }
    if (mode == 4) {
        return &D_8001601C;
    }
    return townResolveEventResponseKey(request, data);
}
