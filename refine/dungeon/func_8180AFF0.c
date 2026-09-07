#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004DCE0();                     /* extern */
M2C_UNK func_8004DCEC();                            /* extern */
M2C_UNK func_8004DD2C();                   /* extern */
extern M2C_UNK D_80026190;
extern s16 D_8002715A;
extern M2C_UNK D_80027160;

typedef struct S_800267F0_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x32];
    s16 unk_46;
} S_800267F0_0;   /* temp_v0 in func_800267F0 */

/* Initializes an available object with the supplied value and sets up shared state. */
void *func_800267F0(s16 initialValue) {
    S_800267F0_0 *object;

    D_8002715A = 0;
    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = &D_80026190;
        object->unk_46 = initialValue;
        func_8004DCE0(2);
        func_8004DCEC();
        func_8004DD2C(&D_80027160);
    }
    return object;
}
