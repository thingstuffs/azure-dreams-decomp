#include "common.h"
#include "m2c_compat.h"

typedef struct S_81984AB0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81984AB0_1;   /* arg0 in func_81984AB0 */

typedef struct S_81984AB0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_81984AB0_2;   /* ((S_81984AB0_1 *)arg0)->unk_08 in func_81984AB0 */




typedef struct S_81984AB0_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
} S_81984AB0_0;   /* arg0 in func_81984AB0 */

/* Selects a 22-byte entry and resets the object state and flags. */
void func_81984AB0(S_81984AB0_0 *object, s16 entry_index) {
    s32 entry_base;

    object->unk_04 = entry_index;
    object->unk_05 = 0;
    entry_base = ((S_81984AB0_2 *)(((S_81984AB0_1 *)object)->unk_08))->unk_0C;
    object->unk_14 = (u16) (object->unk_14 & 0x9FFF);
    object->unk_00 = (s32) (entry_base + (entry_index * 0x16));
}
