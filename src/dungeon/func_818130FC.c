#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800280FC_4 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x24];
    void * unk_38;
} S_800280FC_4;   /* arg1 in func_800280FC */

typedef struct S_800280FC_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800280FC_5;   /* *var_v1 in func_800280FC */

typedef struct S_800280FC_6 {
    s32 unk_00;
    void * unk_04;
} S_800280FC_6;   /* ((S_800280FC_4 *)arg1)->unk_10 in func_800280FC */

typedef struct S_800280FC_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800280FC_7;   /* ((S_800280FC_5 *)(*var_v1))->unk_04 in func_800280FC */

typedef struct S_800280FC_8 {
    s32 unk_00;
    void * unk_04;
} S_800280FC_8;   /* ((S_800280FC_4 *)arg1)->unk_38 in func_800280FC */

typedef struct S_800280FC_9 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800280FC_9;   /* ((S_800280FC_6 *)(((S_800280FC_4 *)arg1)->unk_10))->unk_04 in func_800280FC */

typedef struct S_800280FC_10 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800280FC_10;   /* ((S_800280FC_8 *)(((S_800280FC_4 *)arg1)->unk_38))->unk_04 in func_800280FC */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80027AD0();
extern M2C_UNK func_8004CBFC();
extern M2C_UNK D_80078AB4;
extern M2C_UNK D_80078AD8;
extern M2C_UNK D_80079324;

typedef struct S_800280FC_0 {
    M2C_UNK ** unk_00;
    M2C_UNK ** unk_04;
    s32 unk_08;
    s32 * unk_0C;
    u8 pad_10[0x4];
    s32 * unk_14;
} S_800280FC_0;   /* arg1 in func_800280FC */

typedef struct S_800280FC_1 {
    u8 pad_00[0x4C];
    s32 unk_4C;
} S_800280FC_1;   /* arg0 in func_800280FC */

typedef struct S_800280FC_2 {
    s32 unk_00;
    void * unk_04;
} S_800280FC_2;   /* *var_v1 in func_800280FC */

typedef struct S_800280FC_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800280FC_3;   /* temp_v0 in func_800280FC */

void func_800280FC(void *arg0, void *arg1) {
    s16 var_a0;
    s16 var_a2;
    s32 var_a1;
    void **var_v1;
    S_800280FC_3 *temp_v0;

    *((S_800280FC_0 *)arg1)->unk_00 = &D_80078AB4;
    *((S_800280FC_0 *)arg1)->unk_04 = &D_80078AD8;
    func_8004CBFC(arg0 + 0x2C, &D_80079324, ((S_800280FC_0 *)arg1)->unk_08);
    *((S_800280FC_0 *)arg1)->unk_0C = 0;
    ((S_800280FC_6 *)(((S_800280FC_4 *)arg1)->unk_10))->unk_00 = 0;
    ((S_800280FC_9 *)(((S_800280FC_6 *)(((S_800280FC_4 *)arg1)->unk_10))->unk_04))->unk_08 = 0x58;
    *((S_800280FC_0 *)arg1)->unk_14 = ((S_800280FC_1 *)arg0)->unk_4C + 0x18;
    func_80027AD0(arg0, 0, 1);
    var_a1 = 6;
    var_a2 = 0x58;
    var_a0 = 0x90;
    var_v1 = arg1 + 0x18;
    do {
        ((S_800280FC_2 *)(*var_v1))->unk_00 = 0;
        ((S_800280FC_7 *)(((S_800280FC_5 *)(*var_v1))->unk_04))->unk_08 = var_a2;
        var_a1 += 1;
        temp_v0 = ((S_800280FC_2 *)(*var_v1))->unk_04;
        var_v1 = (void **)((s8 *)((void **)((s8 *)var_v1 + 4)));
        temp_v0->unk_0A = var_a0;
        var_a0 += 0x10;
    } while (var_a1 < 0xE);
    ((S_800280FC_10 *)(((S_800280FC_8 *)(((S_800280FC_4 *)arg1)->unk_38))->unk_04))->unk_08 = 0x4C;
    ((S_800280FC_8 *)(((S_800280FC_4 *)arg1)->unk_38))->unk_00 = 0;
}
