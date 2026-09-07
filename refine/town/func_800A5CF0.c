#include "common.h"

typedef struct S_800A3450_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A3450_0;   /* object in func_800A3450 */

typedef struct S_800A3450_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A3450_1;   /* copy in func_800A3450 */

typedef struct S_800A3450_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A3450_2;   /* arg0 in func_800A3450 */

typedef struct S_800A3450_3 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x1E];
    s16 unk_42;
} S_800A3450_3;   /* result in func_800A3450 */


extern void *func_8003FD64(s32, void *);
extern u8 D_80083498[];
extern u8 D_800A34E0[];
extern u8 D_800A3508[];


/* Creates an object with copied input data, preset references, and an initial value. */
void *func_800A3450(S_800A3450_2 *source_data, s16 initial_value)
{
    S_800A3450_0 *object;
    S_800A3450_1 *object_data;
    register void *result ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    object = func_8003FD64(0x136, D_80083498);
    result = 0;
    if (object != 0) {
        object_data = object->unk_08;
        object_data->unk_00 = source_data->unk_00;
        object_data->unk_04 = source_data->unk_04;
        result = object;
        object_data->unk_08 = source_data->unk_08;
        ((S_800A3450_3 *)result)->unk_10 = D_800A34E0;
        ((S_800A3450_3 *)result)->unk_20 = D_800A3508;
        ((S_800A3450_3 *)result)->unk_42 = initial_value;
    }
    return result;
}
