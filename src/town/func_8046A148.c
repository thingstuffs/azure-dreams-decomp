#include "shared/town_event_state.h"
#include "common.h"

extern s32 D_8001601C;
extern u8 D_80017774[];
extern s32 D_80017FD4[];
extern s32 D_80017FF4[];

/* Returns a fixed address or a state-indexed value, marking the first table lookup. */
s32 func_8001B148(s32 unused_arg0, s32 unused_arg1, s32 selector)
{
    if (selector == 5) {
        return D_80017774;
    }
    if (selector == 4) {
        return &D_8001601C;
    }
    if (selector == 1) {
        return D_80017FF4[D_8001E950->unk_04];
    }
    if (D_8001E950->unk_06 == 0) {
        D_8001E950->unk_06 = 1;
        return D_80017FD4[D_8001E950->unk_04];
    }
    return D_80017FF4[D_8001E950->unk_04];
}
