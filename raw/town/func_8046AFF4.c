#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef s32 (*Callback)(s32);

extern s32 func_8001A58C(s32);
extern s32 func_8001A86C(s32);
extern s32 func_8001A9B4(s32);
extern s8 D_80016000[];
extern u8 *D_8001E950;

s32 func_8001BFF4(void *arg0, s32 arg1) {
    u8 mode;

    mode = D_8001E950[5];
    if (mode == 2) {
        if (FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x20),
                        Callback, 0x2D4)(0) == mode) {
            if (func_8001A58C(D_8001E950[4]) != 0) {
                FIELD((u8 *)FIELD(arg0, void *, 0x10) + arg1 * 0x10, s32, 8) =
                    func_8001A86C(D_8001E950[4]);
                return 0;
            } else {
                FIELD((u8 *)FIELD(arg0, void *, 0x10) + arg1 * 0x10, s32, 8) =
                    func_8001A86C(0);
                return 0;
            }
        } else {
            s32 value;

            if (func_8001A58C(D_8001E950[4]) != 0) {
                value = D_8001E950[4];
            } else {
                value = 0;
            }
            FIELD((u8 *)FIELD(arg0, void *, 0x10) + arg1 * 0x10, s32, 8) =
                func_8001A9B4(value);
            return 0;
        }
    }
    return 1;
}

/* MECHANISM: Repeated D_8001E950 accesses hold its page in s1; args occupy s2/s3,
   producing the five-save 0x28 frame. Three identical store/return tails cross-jump
   into one v0 store, while the in-range j targets remain local control flow. */
