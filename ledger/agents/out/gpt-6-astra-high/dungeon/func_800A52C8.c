#include "common.h"
#include "m2c_compat.h"

extern struct {
    s8 pad[0x14];
    u16 field_0x14;
} D_80083460;

typedef struct S_800AAA28_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_800AAA28_0;   /* arg1 in func_800AAA28 */

/* Sets the object's state to 0x15, clears its auxiliary fields, and increments the global counter. */
void func_800AAA28(void *unused, S_800AAA28_0 *object) {
    object->unk_9A = 0x15;
    object->unk_9B = 0;
    object->unk_8C = 0;
    D_80083460.field_0x14 = D_80083460.field_0x14 + 1;
}
