/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern u16 *D_800D1868[4];

/* Blit an image at its origin-adjusted position into a 128-wide buffer, skipping zero pixels. */
void func_800B7978(s32 dst_x, s32 dst_y, s32 image_id, void *dst) {
    register s16 col;
    register s16 row;
    u16 *src;
    u16 height;
    u16 width;
    u16 value;
    u16 origin_y;
    u8 *base;
    u8 *entry_address;
    s32 table_offset;

    table_offset = image_id << 0x10;
    do {
        base = (u8 *)D_800D1868;
    } while (0);
    table_offset >>= 0xE;
    entry_address = (u8 *)table_offset;
    entry_address = (u8 *)((s32)entry_address + (s32)base);
    src = *(u16 **)entry_address;
    row = 0;
    width = *src++;
    height = *src++;
    value = *src++;
    origin_y = *src++;
    dst_x -= value;
    dst_y -= origin_y;
    while ((row << 0x10) < (height << 0x10)) {
        col = 0;
        while (col < (s16)width) {
            value = *src;
            if (value != 0) {
                ((u16 *)dst)[((row + (s16)dst_y) << 7) + col + (s16)dst_x] = value;
            }
            src++;
            col++;
        }
        row++;
    }
}
