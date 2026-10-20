#include "common.h"

#include "common.h"

typedef struct S_80038394_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x1C];
    s16 unk_30;
} S_80038394_0;   /* arg0 in wait_message_resident_bit */


s32 test_resident_bitmap_bit();                             /* extern */
void update_message_window();

/* Sets the object's handler when its status check succeeds. */
void wait_message_resident_bit(S_80038394_0 *object) {
    if (test_resident_bitmap_bit(object->unk_30) != 0) {
        object->unk_10 = &update_message_window;
    }
}
