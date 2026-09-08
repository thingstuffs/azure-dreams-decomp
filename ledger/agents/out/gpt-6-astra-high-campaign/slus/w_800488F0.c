#include "common.h"

#include "common.h"

extern void func_80048660(u8 *, s32);
extern void func_80048870(u8 *, s32, s32);

/* Advances scroll state and uploads images for eligible records according to operation flags. */
void func_800488F0(u8 *records, s32 *image_ref, s32 operation_flags)
{
    u8 *record;
    s32 *image_ref_ptr;
    s32 *data_offset_ptr;
    s32 advance_scroll;
    s32 upload_image;

    record = records;
    image_ref_ptr = image_ref;
    data_offset_ptr = (s32 *)record;
    advance_scroll = operation_flags & 2;
    upload_image = operation_flags & 1;
    while (1) {
        if ((*record & 0x60) == 0) {
            data_offset_ptr = (s32 *)((s8 *)data_offset_ptr - 4);
            if (advance_scroll != 0) {
                func_80048660(record, *image_ref_ptr);
            }
            if (upload_image != 0) {
                func_80048870(record, *image_ref_ptr, *data_offset_ptr);
            }
        }
        if ((*record & 0x80) != 0) {
            record += 0xC;
            break;
        }
        record += 0xC;
    }
}
