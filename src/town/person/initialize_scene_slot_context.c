#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

typedef struct S_800C8600_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C8600_1;   /* arg0 in func_800C8600 */

typedef struct S_800C8600_2 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C8600_2;   /* ((S_800C8600_1 *)arg0)->unk_80 in func_800C8600 */


/* extern */
extern M2C_UNK D_800D62C4;

typedef struct S_800C8600_0 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_800C8600_0;   /* arg0 in func_800C8600 */
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Set the object data pointer and clear its indexed flag before calling apply_object_setup_and_update. */
void func_800C8600(S_800C8600_0 *object, s32 param_1, s32 param_2) {
    ((S_800C8600_2 *)(((S_800C8600_1 *)object)->unk_80))->unk_04 = &D_800D62C4;
    object_index_slots[object->unk_60].unk_00 = 0;
    apply_object_setup_and_update(object, param_1, param_2);
}
