#include "common.h"

extern s32 VSync(s32 mode);
extern s32 func_800542BC(void);

/* Cached upper bits of VSync(1), separate from the slot selector at AFC. */
extern u16 D_80080AFE;

/* Updates the cached upper bits and calls func_800542BC when they change. */
s32 func_80044618(s32 id_mode) {
    u16 cached_id;
    u16 new_id;
    s32 vsync_result;
    u32 id_bits;
    u32 new_id_bits;

    vsync_result = VSync(1);
    cached_id = D_80080AFE;
    id_bits = (u32) vsync_result >> 8;
    if (id_mode == 2) {
        if ((id_bits & 0x1FF) == cached_id) {
            return 2;
        }
        goto update_cache;
    }
    if ((id_bits & 0xFF) != cached_id) {
update_cache:
        new_id_bits = (u32) vsync_result >> 8;
        if (id_mode == 2) {
            new_id = new_id_bits & 0x1FF;
        } else {
            new_id = new_id_bits & 0xFF;
        }
        D_80080AFE = new_id;
        return func_800542BC();
    }
    return 2;
}
