#include "common.h"
#include "records/Rec_D_80083160.h"
typedef s32 M2C_UNK;

typedef struct S_800A5FC0_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A5FC0_0;   /* temp_v1 in func_800A5FC0 */


typedef struct S_800A5FC0_2 {
    s32 unk_00;
    s32 unk_04;
    u16 unk_08;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    s16 unk_0C;
} S_800A5FC0_2;   /* arg0 in func_800A5FC0 */

typedef struct S_800A5FC0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u16 unk_0C;
    s16 unk_0E;
    s32 unk_10;
    u16 unk_14;
    s16 unk_16;
} S_800A5FC0_3;   /* temp_s0 in func_800A5FC0 */

typedef struct S_800A5FC0_4 {
    void * unk_00;
} S_800A5FC0_4;   /* temp_s3 in func_800A5FC0 */

typedef struct S_800A5FC0_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A5FC0_5;   /* ((Rec_D_80083160 *)(&D_80083160))->unk_00.as_pv in func_800A5FC0 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80083160[];
extern M2C_UNK func_8006658C();
extern M2C_UNK func_80066640();
extern M2C_UNK func_800666E0();
extern M2C_UNK func_80067F20();

s32 func_800A5FC0(S_800A5FC0_2 *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    void *temp_s0;
    void *temp_s2;
    S_800A5FC0_0 *temp_v1;
    void **temp_s3;

    temp_v1 = D_80083160[0];
    temp_s2 = temp_v1->unk_8D0;
    temp_v1->unk_8D0 = (void *) (temp_s2 + 0xC);
    temp_s0 = ((S_800A5FC0_5 *)(((Rec_D_80083160 *)(&D_80083160))->unk_00.as_pv))->unk_8D0;
    ((S_800A5FC0_5 *)(((Rec_D_80083160 *)(&D_80083160))->unk_00.as_pv))->unk_8D0 = (void *) (temp_s0 + 0x18);
    temp_s3 = (void **)&D_80083160;
    func_80067F20(temp_s2, 0, 0, arg0->unk_04, 0);
    ((S_800A5FC0_3 *)temp_s0)->unk_04 = (s32) arg0->unk_00;
    func_800666E0(temp_s0);
    func_80066640(temp_s0, 1);
    ((S_800A5FC0_3 *)temp_s0)->unk_10 = 0xE00000;
    ((S_800A5FC0_3 *)temp_s0)->unk_08 = 0;
    ((S_800A5FC0_3 *)temp_s0)->unk_0E = 0;
    ((S_800A5FC0_3 *)temp_s0)->unk_16 = 0xE0;
    temp_v0 = arg0->unk_08 - 1;
    arg0->unk_08 = temp_v0;
    if ((s16) temp_v0 <= 0)
        goto zero_case;
    {
        s32 delta = 0x140 - arg0->unk_0A.s;
        arg0->unk_0A.s = arg0->unk_0A.u + delta / (s16) temp_v0;
    }
    goto common_case;
zero_case:
    arg0->unk_08 = 0U;
    arg0->unk_0A.s = 0x140;
common_case:
    temp_v0_2 = (u16) arg0->unk_0A.s;
    ((S_800A5FC0_3 *)temp_s0)->unk_14 = temp_v0_2;
    ((S_800A5FC0_3 *)temp_s0)->unk_0C = temp_v0_2;
    func_8006658C((u8 *)((S_800A5FC0_4 *)temp_s3)->unk_00 + ((arg0->unk_0C * 4) + 0x70), temp_s0);
    func_8006658C((u8 *)((S_800A5FC0_4 *)temp_s3)->unk_00 + ((arg0->unk_0C * 4) + 0x70), temp_s2);
    return 0;
}
