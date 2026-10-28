/* Item tile distance and its file-private helper. */
#include "common.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
static s16 set_item_w0(s32 start_x, s32 start_y, s32 end_x, s32 end_y);

/* Returns the larger absolute difference between the low-byte X and Y tile coordinates. */
static s16 set_item_w0(s32 start_x, s32 start_y, s32 end_x, s32 end_y) {
    end_x &= 0xFF;
    start_x &= 0xFF;
    end_x -= start_x;
    end_x = abs(end_x);
    end_y &= 0xFF;
    start_y &= 0xFF;
    end_y -= start_y;
    end_y = abs(end_y);
    if (end_x < end_y) {
        return end_y;
    }
    return end_x;
}

s16 get_tile_chebyshev_distance(Rec_D_80082E80 *start_record, Rec_D_80082E80 *end_record) {
    return set_item_w0(start_record->unk_24, start_record->unk_25, end_record->unk_24, end_record->unk_25);
}
