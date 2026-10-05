#include "common.h"

extern s32 func_800A2304(void *input_first, s32 input_second, s32 input_third, u8 input_fourth);
extern s32 D_800A07E8;

/* Install the next object handler when the update call succeeds. */
void func_800A07A4(void *object, s32 unused_value, s32 update_context, u8 unused_flags) {
    s32 linked_record = *(s32 *)((u8 *)object + 0x98);
    u8 status_byte = *(u8 *)((u8 *)object + 0x94);

    if (func_800A2304(object, linked_record, update_context, status_byte) != 0) {
        *(s32 *)((u8 *)object + 0x50) = (s32) &D_800A07E8;
    }
}
