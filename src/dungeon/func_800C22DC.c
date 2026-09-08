#include "common.h"

extern s16 D_80083780[6];
extern s16 D_800E58F8[];
extern void func_800C77D0();

/* Process the midpoint of two objects when it is near the reference position. */
void func_800C7A3C(volatile u8 *start_obj, volatile u8 *end_obj, s16 start_height, s16 end_height, s16 call_param, s32 call_arg) {
    volatile s32 frame_pad[2];
    s32 coord;
    s32 mid_coord;
    s32 x_distance;
    s32 y_adjust;
    s16 *midpoint;
    s16 *ref_pos;

    coord = (start_obj[0x24] << 6) + 0x20;
    mid_coord = (end_obj[0x24] << 6) + 0x20;
    mid_coord = mid_coord - coord;
    mid_coord = mid_coord >> 1;
    coord = coord + mid_coord;
    mid_coord = coord;
    ref_pos = D_80083780;
    x_distance = ref_pos[1] - mid_coord;
    if (x_distance < 0) {
        x_distance = -x_distance;
    }
    if (x_distance < 0xC1) {
        midpoint = D_800E58F8;
        midpoint[1] = mid_coord;
        coord = (start_obj[0x25] << 6) + 0x20;
        mid_coord = (end_obj[0x25] << 6) + 0x20;
        mid_coord = mid_coord - coord;
        y_adjust = (u32)mid_coord >> 31;
        mid_coord = mid_coord + y_adjust;
        mid_coord = mid_coord >> 1;
        coord = coord + mid_coord;
        mid_coord = coord;
        y_adjust = ref_pos[3] - mid_coord;
        if (y_adjust < 0) {
            y_adjust = -y_adjust;
        }
        if (y_adjust < 0xC1) {
            midpoint[3] = mid_coord;
            midpoint[5] = start_height + ((end_height - start_height) / 2);
            func_800C77D0(0, midpoint, call_param, call_arg);
        }
    }
}
