#include "common.h"

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u8 D_800E3648[];

extern s16 func_800B500C(s32, s32, s16);

/* Find a record in the given direction and clear bit 0x80 if bit 0x40 is unset. */
s32 func_800B5ED0(s32 origin_x, s32 origin_y, u32 direction, s16 search_param) {
    s32 offset_index;
    u8 *offsets;
    s32 shifted_x;
    s32 shifted_y;
    s16 record_index;
    u8 *table;
    u8 *record;
    u8 flags;

    offset_index = direction >> 8;
    offsets = (u8 *)&D_8006CCD8;
    offset_index &= 0xE;
    shifted_x = (*(u16 *)(offsets + offset_index) + origin_x) << 16;
    offsets = (u8 *)&D_8006CCE8;
    shifted_y = (*(u16 *)(offsets + offset_index) + origin_y) << 16;
    record_index = func_800B500C(shifted_x >> 16, shifted_y >> 16, search_param);
    if (record_index >= 0) {
        table = D_800E3648;
        record = table + record_index * 4;
        flags = record[3];
        if (!(flags & 0x40)) {
            if (flags & 0x80) {
                record[3] = flags & 0x7F;
                return record_index;
            }
        }
    }
    return -1;
}
