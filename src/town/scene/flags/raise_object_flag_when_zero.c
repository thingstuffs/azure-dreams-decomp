#include "common.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/scene/flags.h"

   /* the 0x2 bytes before arg0 in raise_object_flag_when_zero, addressed as arg0[-1] */

typedef struct S_8080DD10_0 {
    s16 unk_00;
} S_8080DD10_0;   /* arg0 in raise_object_flag_when_zero */


extern s32 scene_object_flags;

/* Set bit 0x8000 in the preceding flags and global flags when the value is zero. */
void raise_object_flag_when_zero(void *value_ptr) {
    if (((S_8080DD10_0 *)value_ptr)->unk_00 == 0) {
        (*(u16 *)((u8 *)value_ptr + -2)) = (u16) (((ObjectStatusPrefix16 *)value_ptr)[-1].flags | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
