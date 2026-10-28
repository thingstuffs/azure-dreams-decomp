#include "common.h"
#include "shared/object_flags.h"
#include "sdk/libc.h"
#include "engine/text.h"

typedef struct S_80020618_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    char *unk_04;
    s16 * unk_08;
    void * unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
} S_80020618_0;   /* arg0 in tick_scene_value_text */

typedef struct S_80020618_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020618_1;   /* owner in tick_scene_value_text */



/* Displays a timed message and signals completion when its owner is ready. */
void tick_scene_value_text(void *message)
{
    s16 state;
    u16 timer;
    S_80020618_1 *owner;

    owner = ((S_80020618_0 *)message)->unk_0C;
    format_decimal_field_space_padded(
        *((S_80020618_0 *)message)->unk_08,
        strlen(((S_80020618_0 *)message)->unk_04),
        ((S_80020618_0 *)message)->unk_04);

    state = ((S_80020618_0 *)message)->unk_00.s;
    switch (state) {
    case 0:
        timer = ((S_80020618_0 *)message)->unk_02 - 1;
        ((S_80020618_0 *)message)->unk_02 = timer;
        if ((timer << 16) <= 0) {
            ((S_80020618_0 *)message)->unk_1C &= 0xFFFD;
            ((S_80020618_0 *)message)->unk_00.u++;
        }
        break;

    case 1:
        if (owner->unk_2A & 1) {
            (*(u16 *)((u8 *)message + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
