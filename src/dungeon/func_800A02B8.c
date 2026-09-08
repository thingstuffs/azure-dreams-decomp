#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B835C(); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800A5828;
extern M2C_UNK D_800DD854;
extern M2C_UNK D_800DD860;

typedef struct S_800A5A18_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800A5A18_0;   /* temp_v0 in func_800A5A18 */

typedef struct S_800A5A18_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_800A5A18_1;   /* temp_v1 in func_800A5A18 */

typedef struct S_800A5A18_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_800A5A18_2;   /* temp_v1_2 in func_800A5A18 */

/* Creates an object and initializes its attached data and resources. */
void *func_800A5A18(s32 object_id, s32 state_value) {
    s32 resource_params[2];
    void *object;
    S_800A5A18_1 *render_data;
    S_800A5A18_2 *state_data;

    object = func_8003FD64(0x212, &D_80083498);
    if (object != NULL) {
        ((S_800A5A18_0 *)object)->unk_10 = &D_800A5828;
        func_8004491C(object, &D_80045340);
        render_data = ((S_800A5A18_0 *)object)->unk_0C;
        ((S_800A5A18_0 *)object)->unk_08 = object_id;
        render_data->unk_08 = &D_800DD854;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        state_data = object + 0x20;
        state_data->unk_04 = state_value;
        state_data->unk_66 = 4;
        resource_params[0] = 0x01800340;
        resource_params[1] = 0x400040;
        func_800B835C(&D_800DD860, resource_params, 1, 0);
        func_800A56E0(0x60F);
    }
    return object;
}
