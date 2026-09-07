#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800357D0_2 {
    void * unk_00;
} S_800357D0_2;   /* arg0 in func_800357D0 */

typedef struct S_800357D0_3 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_800357D0_3;   /* ((S_800357D0_2 *)arg0)->unk_00 in func_800357D0 */


typedef struct S_800357D0_0 {
    void * unk_00;
    u8 pad_04[0x48];
    u8 unk_4C;
    u8 unk_4D;
    u8 pad_4E[0x1A];
    M2C_UNK * unk_68;
} S_800357D0_0;   /* arg0 in func_800357D0 */

typedef struct S_800357D0_1 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_800357D0_1;   /* temp_v1 in func_800357D0 */


extern M2C_UNK func_80035820;

void func_800357D0(S_800357D0_0 *arg0) {
    S_800357D0_1 *temp_v1;

    temp_v1 = arg0->unk_00;
    temp_v1->unk_08 = (u16) (temp_v1->unk_08 + 0x40);
    if ((s16) ((S_800357D0_3 *)(((S_800357D0_2 *)arg0)->unk_00))->unk_08 >= 0x401) {
        arg0->unk_4C = 0xFF;
        arg0->unk_4D = 0xFF;
        arg0->unk_68 = &func_80035820;
    }
}
