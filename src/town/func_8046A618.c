#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 (*Callback)(s32);


extern s32 func_8001A86C(s32);
extern s32 func_8001A9B4(s32);

/* Updates the selected entry using a callback-selected lookup when state is 2. */
s32 func_8001B618(void *object, s32 entry_index) {
    if (D_8001E950->unk_05 == 2) {
        if ((*(Callback *)((s8 *)*(void **)((s8 *)D_80016000 + 0x20) + 0x2D4))(0) == 2) {
            *(s32 *)((entry_index << 4) + *(s32 *)((u8 *)object + 0x10) + 8) =
                func_8001A86C(D_8001E950->unk_04);
        } else {
            *(s32 *)((entry_index << 4) + *(s32 *)((u8 *)object + 0x10) + 8) =
                func_8001A9B4(D_8001E950->unk_04);
        }
        return 0;
    }
    return 1;
}
