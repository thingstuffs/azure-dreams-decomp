#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in tick_timed_sound, addressed as arg0[-1] */

typedef struct S_80026D28_0 {
    u8 pad_00[0x50];
    union { s16 s; u16 u; } unk_50;   /* accessed as both */
    u16 unk_52;
} S_80026D28_0;   /* arg0 in tick_timed_sound */


extern s32 SD_Call();


/* Starts a timed state and sets completion flags when its countdown expires. */
void tick_timed_sound(void *object)
{
    s16 state;
    u16 timer;

    state = ((S_80026D28_0 *)object)->unk_50.s;
    if (state != 0) {
        if (state != 1) {
            return;
        }
    } else {
        SD_Call(0x603);
        ((S_80026D28_0 *)object)->unk_50.u = ((S_80026D28_0 *)object)->unk_50.u + 1;
    }

    timer = ((S_80026D28_0 *)object)->unk_52 - 1;
    ((S_80026D28_0 *)object)->unk_52 = timer;
    if ((timer << 16) <= 0) {
        SD_Call(0x1603);
        ((ObjectStatusPrefix16 *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
