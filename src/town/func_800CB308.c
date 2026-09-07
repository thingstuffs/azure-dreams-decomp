#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C8A68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800C8A68_0;   /* temp_v0 in func_800C8A68 */

typedef struct S_800C8A68_1 {
    volatile s32 unk_00;
    volatile s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_800C8A68_1;   /* temp_a1 in func_800C8A68 */

typedef struct S_800C8A68_2 {
    volatile s32 unk_00;
    volatile s32 unk_04;
    volatile s32 unk_08;
} S_800C8A68_2;   /* arg0 in func_800C8A68 */

typedef struct S_800C8A68_3 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C8A68_3;   /* temp_s0 in func_800C8A68 */

typedef struct S_800C8A68_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800C8A68_4;   /* temp_s1 in func_800C8A68 */


M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FD64();            /* extern */
s32 func_800C8B3C();                                /* extern */
M2C_UNK func_800C8B5C();      /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800C8B8C;
extern M2C_UNK D_800EE344;

s32 func_800C8A68(S_800C8A68_2 *arg0) {
    S_800C8A68_1 *temp_a1;
    S_800C8A68_3 *temp_s0;
    S_800C8A68_4 *temp_s1;
    void *temp_v0;
    s32 temp_v1;

    temp_v0 = func_8003FD64(0x136, &D_80083498);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_a1 = ((S_800C8A68_0 *)temp_v0)->unk_08;
    temp_s1 = ((S_800C8A68_0 *)temp_v0)->unk_0C;
    temp_s0 = temp_v0 + 0x20;
    temp_a1->unk_00 = arg0->unk_00;
    temp_a1->unk_04 = arg0->unk_04;
    temp_v1 = arg0->unk_08 + 0xFFDC0000;
    temp_a1->unk_0C = 0x100000;
    temp_a1->unk_10 = 0;
    temp_a1->unk_08 = temp_v1;
    ((S_800C8A68_0 *)temp_v0)->unk_10 = &D_800C8B8C;
    temp_s0->unk_90 = 2;
    func_800C8B5C(temp_s0, temp_a1, temp_s1);
    temp_s1->unk_1E = 0x1000;
    temp_s1->unk_1C = 0x1000;
    temp_s1->unk_0C = 0x808080;
    func_8003DB94(temp_s1, &D_800EE344, 0);
    func_80033CD8(temp_s0, &D_80045340);
    return (s32) temp_v0;
}

/* MECHANISM: A guard-clause tail keeps the allocation in s2 for the live return,
   while defining base+0x20 after the child loads yields s3/s2/s1/s0 retail roles.
   Volatile scalar copies plus a named third word reproduce the exact record-store schedule. */
