#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_800ADB8C;
extern M2C_UNK D_800ADBCC;

typedef struct S_800ADC4C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s8 * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800ADC4C_0;   /* temp_v0 in func_800ADC4C */

typedef struct S_800ADC4C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800ADC4C_1;   /* temp_v1 in func_800ADC4C */

typedef struct S_800ADC4C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800ADC4C_2;   /* arg0 in func_800ADC4C */

typedef struct S_800ADC4C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800ADC4C_3;   /* temp_v0_2 in func_800ADC4C */

/* Create an object with the supplied position and render settings, and clear its status flag. */
void *func_800ADC4C(S_800ADC4C_2 *source_pos, s32 render_param, s16 initial_state, s8 *status) {
    S_800ADC4C_0 *object;
    S_800ADC4C_3 *render_data;
    S_800ADC4C_1 *position;

    object = func_8003FD64(0x12, &D_80083498);
    if (object != NULL) {
        object->unk_10 = &D_800ADB8C;
        func_8004491C(object, &D_800ADBCC);
        position = object->unk_08;
        position->unk_02 = (u16) source_pos->unk_02;
        position->unk_06 = (u16) source_pos->unk_06;
        position->unk_0A = (u16) source_pos->unk_0A;
        render_data = object->unk_0C;
        render_data->unk_08 = render_param;
        render_data->unk_0C = 0x808080;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        object->unk_28 = initial_state;
        object->unk_20 = status;
        *status = 0;
    }
    return object;
}
