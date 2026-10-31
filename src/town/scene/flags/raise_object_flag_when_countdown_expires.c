#include "common.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/scene/flags.h"

   /* the 0x2 bytes before arg0 in raise_object_flag_when_countdown_expires, addressed as arg0[-1] */

typedef struct S_80811034_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80811034_0;   /* arg0 in raise_object_flag_when_countdown_expires */


extern s32 scene_object_flags;

/* Decrement the countdown and set record and global flags when it expires. */
void raise_object_flag_when_countdown_expires(void *record_arg) {
    S_80811034_0 *record = record_arg;
    u16 countdown;

    countdown = record->unk_02 - 1;
    record->unk_02 = countdown;
    if ((countdown << 0x10) <= 0) {
        (*(u16 *)((u8 *)record + -2)) = (u16) (((ObjectStatusPrefix16 *)record)[-1].flags | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
