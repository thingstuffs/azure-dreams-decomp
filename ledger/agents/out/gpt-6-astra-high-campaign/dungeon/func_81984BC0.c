#include "common.h"
#include "m2c_compat.h"

typedef struct S_81984BC0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81984BC0_1;   /* arg0 in func_81984BC0 */

typedef struct S_81984BC0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_81984BC0_2;   /* ((S_81984BC0_1 *)arg0)->unk_08 in func_81984BC0 */




typedef struct S_81984BC0_0 {
    s32 unk_00;
} S_81984BC0_0;   /* arg0 in func_81984BC0 */

/* Sets the object entry address using a 22-byte stride. */
void func_81984BC0(S_81984BC0_0 *object, s16 entry_index) {
    object->unk_00 = (s32) (((S_81984BC0_2 *)(((S_81984BC0_1 *)object)->unk_08))->unk_0C + (entry_index * 0x16));
}
