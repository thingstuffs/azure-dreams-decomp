/* Relink of matched dungeon/func_80A4B0F0; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_801748F0_0 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} S_801748F0_0;   /* arg0 in func_80168108; pointer addresses record offset 0x2 */


/* Decrement the record counter and set completion flags when it reaches zero or becomes negative. */
void func_80168108(void *record_data) {
    u16 remaining_count;

    remaining_count = ((S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_801748F0_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    }
}
