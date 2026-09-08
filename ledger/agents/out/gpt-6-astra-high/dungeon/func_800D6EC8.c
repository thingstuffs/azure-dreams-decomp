#include "common.h"
#include "m2c_compat.h"

typedef struct S_800DC628_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800DC628_2;   /* arg0 in func_800DC628 */

typedef struct S_800DC628_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
} S_800DC628_3;   /* ((S_800DC628_2 *)arg0)->unk_08 in func_800DC628 */




typedef struct S_800DC628_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800DC628_0;   /* arg0 in func_800DC628 */

typedef struct S_800DC628_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u8 pad_10[0x18];
    s16 unk_28;
    u8 pad_2A[0xA];
    s16 unk_34;
    u8 pad_36[0x22];
    s16 unk_58;
} S_800DC628_1;   /* temp_v0 in func_800DC628 */

/* Sets four fields in the object's data to a value and a fifth to its negation. */
void func_800DC628(S_800DC628_0 *object, s16 value) {
    S_800DC628_1 *data;

    data = object->unk_08;
    data->unk_58 = value;
    data->unk_34 = value;
    data->unk_28 = value;
    data->unk_0E = value;
    ((S_800DC628_3 *)(((S_800DC628_2 *)object)->unk_08))->unk_1A = (s16) (0 - value);
}
