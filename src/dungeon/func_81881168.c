#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024D90();                 /* extern */
void *func_8003FD64();                  /* extern */
extern M2C_UNK D_80024728;

typedef struct S_80024968_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024968_0;   /* temp_v0 in func_80024968 */

typedef struct S_80024968_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024968_1;   /* temp_a0 in func_80024968 */

typedef struct S_80024968_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024968_2;   /* arg1 in func_80024968 */

/* Creates an object, copies three values into its data, and initializes it. */
void *func_80024968(s32 resource_id, S_80024968_2 *source_values, s16 setup_value, s32 object_value) {
    S_80024968_1 *target_values;
    S_80024968_0 *object;

    object = func_8003FD64(2, resource_id - 0x20);
    if (object != NULL) {
        target_values = object->unk_08;
        object->unk_10 = &D_80024728;
        target_values->unk_02 = (u16) source_values->unk_02;
        target_values->unk_06 = (u16) source_values->unk_06;
        target_values->unk_0A = (u16) source_values->unk_0A;
        object->unk_20 = object_value;
        func_80024D90(target_values, setup_value);
    }
    return object;
}
