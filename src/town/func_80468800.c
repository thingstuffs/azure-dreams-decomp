#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct S_func_80019800_1 {
    s16 unk_00;
    s16 unk_02;
} S_func_80019800_1;

extern void *func_80019AFC();

/* Checks the active event and dispatches the 0x27/0x200 handler when matched. */
s32 func_80019800(void) {
    S_func_80019800_1 *event;

    if ((u8) D_8001E950->dispatchState < 2U) {
        event = func_80019AFC(D_8001E950->dispatchState,
                              D_8001E950->unk_05);
        if (event->unk_00 == 0x27) {
            if (event->unk_02 == 0x200) {
                D_80016000->unk_20->callback_2F8(0x27, 0x200);
            }
        }
        return 1;
    }
    return 0;
}
