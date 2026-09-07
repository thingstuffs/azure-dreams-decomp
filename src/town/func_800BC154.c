#include "common.h"
#include "m2c_compat.h"



#define M2C_BREAK() M2C_ERROR(0)
#define M2C_SYNC() M2C_ERROR(0)

M2C_UNK func_80033AA8();
M2C_UNK func_80033AE8();
M2C_UNK func_8003E4FC();
M2C_UNK func_8003F320();
M2C_UNK func_800B7934();
extern u8 D_80010000[];
extern M2C_UNK D_800D1BF4;
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

typedef struct S_800B98B4_0 {
    u8 unk_00;
    u8 unk_01;
} S_800B98B4_0;   /* temp_v1 in func_800B98B4 */

typedef struct S_800B98B4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B98B4_1;   /* var_s1 in func_800B98B4 */

typedef struct S_800B98B4_2 {
    u8 unk_00;
} S_800B98B4_2;   /* temp_v2 in func_800B98B4 */

void func_800B98B4(void) {
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s3;
    s32 var_s2;
    u8 temp_v0;
    S_800B98B4_0 *temp_v1;
    S_800B98B4_2 *temp_v2;

    func_8003E4FC(6, &D_800D1BF4, 0);
    var_s2 = 0;
    func_8003F320();
    func_80033AE8(0x12C3);
    var_s3 = D_800D2644;
    var_s1 = D_800D2EA4;
    var_s0 = (u8 *)0x80010000;
    do {
        temp_v0 = M2C_FIELD(var_s0, u8 *, 0x33A4 + (var_s2 * 2));
        if (temp_v0 != 0) {
            temp_v1 = (void *)((u32)(temp_v0 << 5) + (u32)var_s3);
            if (temp_v1->unk_01 != 0) {
                func_800B7934(((S_800B98B4_1 *)var_s1)->unk_00, ((S_800B98B4_1 *)var_s1)->unk_01, temp_v1->unk_00);
            }
            temp_v2 = (void *)((u32)(M2C_FIELD(var_s0, u8 *, 0x33A4 + (var_s2 * 2)) << 5) + (u32)var_s3);
            if (temp_v2->unk_00 == 1) {
                func_80033AA8(0x12C3);
            }
        }
        var_s1 += 8;
        var_s2 += 1;
    } while (var_s2 < 0x21);
}
