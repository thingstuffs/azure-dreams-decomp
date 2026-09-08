#include "common.h"

extern s32 func_80025198(s32, s32, s32, s32, s32);

/* Forwards the item request with no data override. */
void func_800253A0(s32 owner, s32 context, s32 mode, s32 item_id) {
    func_80025198(owner, context, mode, item_id, 0);
}
