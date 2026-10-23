#include "common.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in raise_object_flag_when_linked_state_7, addressed as arg0[-1] */

typedef struct S_8080DD50_0 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8080DD50_0;   /* arg0 in raise_object_flag_when_linked_state_7 */

typedef struct S_8080DD50_1 {
    u8 pad_00[0x36];
    s16 unk_36;
} S_8080DD50_1;   /* ((S_8080DD50_0 *)arg0)->unk_04 in raise_object_flag_when_linked_state_7 */


extern s32 scene_object_flags;

/* Set record and global flags when the linked object has state 7. */
void raise_object_flag_when_linked_state_7(void *record) {
    if (((S_8080DD50_1 *)(((S_8080DD50_0 *)record)->unk_04))->unk_36 == 7) {
        (*(u16 *)((u8 *)record + -2)) = (u16) (((ObjectStatusPrefix16 *)record)[-1].flags | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
