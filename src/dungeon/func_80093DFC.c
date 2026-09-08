#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern s32 func_80099194();
extern s32 func_800992E8();
extern s32 D_800DD72C[];
extern s32 D_800DD784[];
extern u8 *D_800E3D7C[];
/* Applies eligible type-based adjustments before and after processing an entry. */
s32 func_8009955C(void *entry, s32 value) {
    u8 pre_type;
    s32 post_type, pre_adjustment, post_adjustment, result;
    if (!(F(D_800E3D7C[0], s32, 0x1C) & 0x10)) {
        pre_type = F(entry, u8, 1);
        pre_adjustment = D_800DD72C[pre_type];
        if (pre_adjustment && (pre_type != 15 || F(entry, u8, 0) < 14)) {
            value = func_80099194(pre_adjustment, value, pre_type);
        }
    }
    result = func_800992E8(entry, value);
    if (!(F(D_800E3D7C[0], s32, 0x1C) & 0x10)) {
        post_type = F(entry, u8, 1);
        post_adjustment = D_800DD784[post_type];
        if (post_adjustment) {
            if (post_type == 15 && F(entry, u8, 0) >= 14) {
                return result;
            }
            result = func_80099194(post_adjustment, result, post_type);
        }
    }
    return result;
}
