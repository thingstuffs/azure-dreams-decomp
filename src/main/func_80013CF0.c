#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026CF0_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026CF0_1;   /* temp_a2 in func_80026CF0 */

typedef struct S_80026CF0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026CF0_2;   /* temp_a2_2 in func_80026CF0 */

typedef struct S_80026CF0_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026CF0_3;   /* ((S_80026CF0_1 *)temp_a2)->unk_04 in func_80026CF0 */

typedef struct S_80026CF0_4 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026CF0_4;   /* ((S_80026CF0_2 *)temp_a2_2)->unk_04 in func_80026CF0 */




M2C_UNK func_8004CBFC();   /* extern */
extern M2C_UNK D_80027E68;

typedef struct S_80026CF0_0 {
    u8 pad_00[0x68];
    void * unk_68;
    void * unk_6C;
} S_80026CF0_0;   /* arg0 in func_80026CF0 */

void func_80026CF0(void *arg0) {
    S_80026CF0_1 *temp_a2;
    S_80026CF0_2 *temp_a2_2;

    temp_a2 = ((S_80026CF0_0 *)arg0)->unk_68;
    ((S_80026CF0_3 *)(temp_a2->unk_04))->unk_08 = 0x40;
    ((S_80026CF0_3 *)(temp_a2->unk_04))->unk_0A = 0x20;
    func_8004CBFC(arg0 + 4, &D_80027E68, temp_a2);
    temp_a2_2 = ((S_80026CF0_0 *)arg0)->unk_6C;
    ((S_80026CF0_4 *)(temp_a2_2->unk_04))->unk_08 = 0xC0;
    ((S_80026CF0_4 *)(temp_a2_2->unk_04))->unk_0A = 0x20;
    func_8004CBFC(arg0 + 0x10, &D_80027E68, temp_a2_2);
}
