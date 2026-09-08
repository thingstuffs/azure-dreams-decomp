#include "common.h"

typedef s32 (*Callback)(s32);

extern void *D_80016000[];
extern u8 *D_8001E950;

extern s32 func_8001A86C(s32);
extern s32 func_8001A9B4(s32);

/* Updates the selected entry using a callback-selected lookup when state is 2. */
s32 func_8001B618(void *object, s32 entry_index) {
    if (D_8001E950[5] == 2) {
        if ((*(Callback *)((s8 *)*(void **)((s8 *)D_80016000[0] + 0x20) + 0x2D4))(0) == 2) {
            *(s32 *)((entry_index << 4) + *(s32 *)((u8 *)object + 0x10) + 8) =
                func_8001A86C(D_8001E950[4]);
        } else {
            *(s32 *)((entry_index << 4) + *(s32 *)((u8 *)object + 0x10) + 8) =
                func_8001A9B4(D_8001E950[4]);
        }
        return 0;
    }
    return 1;
}
