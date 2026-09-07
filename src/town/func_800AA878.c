#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();           /* extern */
s32 func_8004A658();                /* extern */
void *func_8009C390(); /* extern */
M2C_UNK func_800A8070();         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A8070;

typedef struct S_800A7FD8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_800A7FD8_0;   /* temp_v0 in func_800A7FD8 */

typedef struct S_800A7FD8_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_800A7FD8_1;   /* temp_s0 in func_800A7FD8 */

typedef struct S_800A7FD8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A7FD8_2;   /* temp_s1 in func_800A7FD8 */

void func_800A7FD8(s32 arg0) {
    s32 temp_s2;
    S_800A7FD8_1 *temp_s0;
    S_800A7FD8_2 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8009C390(0, 0, &D_800A8070, 0);
    if (temp_v0 != NULL) {
        temp_s2 = ((S_800A7FD8_0 *)temp_v0)->unk_08;
        temp_s1 = ((S_800A7FD8_0 *)temp_v0)->unk_0C;
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_60 = arg0;
        temp_s1->unk_08 = func_8004A658(0xB, 2);
        func_80033CD8(temp_s0, &D_80045340);
        func_800A8070(temp_s0, temp_s2, temp_s1);
    }
}
