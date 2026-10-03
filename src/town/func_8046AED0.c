#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct Message {
    s16 x;
    s16 y;
} Message;

extern Message *func_80019AFC(s32, u8);
extern void func_8001E578(s32);

/* Dispatch the enabled town message coordinates and advance the town state. */
s32 func_8001BED0(void) {
    Message *message;

    if (D_8001E950->dispatchState == 1) {
        message = func_80019AFC(0, D_8001E950->unk_05);
        D_80016000->unk_20->callback_2F8(message->x, message->y);
        D_8001E950->dispatchState++;
        func_8001E578(0x408);
        return 1;
    }
    return 0;
}
