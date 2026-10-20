#include "engine/effect/cache_afe.h"

#include "engine/effect/cache_afe.h"

s32 update_vsync_frame_id(s32 id_mode) {
    u16 cached_id;
    u16 new_id;
    s32 vsync_result;
    u32 id_bits;
    u32 new_id_bits;

    vsync_result = VSync(1);
    cached_id = D_80080AFE;
    id_bits = (u32) vsync_result >> 8;
    if (id_mode == 2 ? ((id_bits & 0x1FF) != cached_id) : ((id_bits & 0xFF) != cached_id)) {
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
u16 D_80080AFE = 0;
