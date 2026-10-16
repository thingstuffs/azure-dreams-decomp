#include "shared/town_event_state.h"
#include "common.h"

extern void townSetEventStateAndDispatchA2(void);
extern s32 townCheckEventValueInList(u8);
extern u8 townFindFirstEnabledEntryId(void);
extern u8 *townResolveEventResponseKey(s32, s32, s32);

extern u8 D_8001786E[];
extern u8 D_8001914C[];
extern s32 D_8001E958;
extern u8 D_8001EEA7[];
extern u8 D_8001F0AA[];
extern u8 D_80021CC0[];

/* Selects a response buffer by request type, refreshing state for the initial request. */
u8 *townSelectResponseBuffer(s32 context, s32 data, s32 request) {
    u8 **state_page;
    u8 *response;

    if (request == 0) {
        state_page = (u8 **)0x80020000;
        townSetEventStateAndDispatchA2();
        if (townCheckEventValueInList((*(u8 **)((u8 *)state_page - 0x16B0))[4]) == 0) {
            (*(u8 **)((u8 *)state_page - 0x16B0))[4] = townFindFirstEnabledEntryId();
        }
        if ((*(u8 **)((u8 *)state_page - 0x16B0))[4] != 0) {
            D_8001E958 = 1;
            return D_80021CC0;
        }
        return D_8001F0AA;
    }

    if (request == 4) {
        return D_8001EEA7;
    }
    if (request == 5) {
        return D_8001786E;
    }
    if (request != 1) {
        response = townResolveEventResponseKey(context, data, request);
    } else {
        response = D_8001914C;
    }
    return response;
}
