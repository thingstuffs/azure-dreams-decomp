#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172334_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_80172334_0;   /* arg0 in func_80172334 */



M2C_UNK func_80047784();         /* extern */
extern s16 D_80083228;
typedef struct {
    s8 pad[0xA];
    u16 field_0xA;
} D_80083460_t;
extern D_80083460_t D_80083460;
extern u8 D_80175F20;

void func_80172334(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    u16 temp_v0;

    temp_v0 = ((S_80172334_0 *)arg0)->unk_A6 + 1;
    ((S_80172334_0 *)arg0)->unk_A6 = temp_v0;
    if ((u32) (temp_v0 & 0xFFFF) >= 0x3DU) {
        D_80083460_t *ctr = &D_80083460;
        u8 *table = &D_80175F20;

        ((S_80172334_0 *)arg0)->unk_A6 = 0x3CU;
        ctr->field_0xA = ctr->field_0xA + 1;
        ((S_80172334_0 *)arg0)->unk_8C = 0;
        ((S_80172334_0 *)arg0)->unk_9A = 0x17;
        ((S_80172334_0 *)arg0)->unk_9B = 0;
        (*(u8 **)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + table), 0);
    }
}
