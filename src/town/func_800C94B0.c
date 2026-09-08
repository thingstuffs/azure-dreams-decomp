#include "common.h"
#include "m2c_compat.h"

M2C_UNK D_800C6CE4();            /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_8004A658();                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;


typedef struct S_800C6C10_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK (*unk_10)(void *, s32, void *);
} S_800C6C10_0;   /* temp_v0 in func_800C6C10 */

typedef struct S_800C6C10_1 {
    u8 pad_00[0x9C];
    s32 unk_9C;
} S_800C6C10_1;   /* temp_s1 in func_800C6C10 */

typedef struct S_800C6C10_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800C6C10_2;   /* temp_s0 in func_800C6C10 */

s32 func_800C6C10(s32 arg0) {
    s32 temp_s2;
    S_800C6C10_2 *temp_s0;
    S_800C6C10_1 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x136, &D_80083498);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_s1 = temp_v0 + 0x20;
    temp_s2 = ((S_800C6C10_0 *)temp_v0)->unk_08;
    temp_s0 = ((S_800C6C10_0 *)temp_v0)->unk_0C;
    temp_s1->unk_9C = arg0;
    ((S_800C6C10_0 *)temp_v0)->unk_10 = D_800C6CE4;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    temp_s0->unk_0C = 0x808080;
    temp_s0->unk_08 = func_8004A658(0xD, 3);
    func_8004491C(temp_v0, &D_80045340);
    ((S_800C6C10_0 *)temp_v0)->unk_10(temp_s1, temp_s2, temp_s0);
    return (s32)temp_v0;
}
