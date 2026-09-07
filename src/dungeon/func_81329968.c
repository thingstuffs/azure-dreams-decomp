#include "common.h"
#include "m2c_compat.h"

extern s32 D_80174CD8[3];
extern u8 D_80082E80[];
typedef struct {
    u8 data[24];
} Config24;
extern u8 D_8016A87C[];
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_8009A21C(u8, u8, s32);

typedef struct S_80171168_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_80171168_0;   /* *D_80174CD8 in func_80171168 */

typedef struct S_80171168_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80171168_1;   /* temp_s0 in func_80171168 */

typedef struct S_80171168_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80171168_2;   /* temp_s2 in func_80171168 */

void func_80171168(s32 arg0) {
    const Config24 *config;
    Config24 local;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    u8 *local_bytes;
    u8 *global_base;
    u8 call_a0;
    u8 call_a1;
    u8 final_a0;
    u8 final_a1;
    register s16 *temp_a0;
    s32 temp_s3;
    S_80171168_1 *temp_s0;
    S_80171168_2 *temp_s2;

    config = (const Config24 *)D_8016A87C;
    local = *config;
    temp_a0 = (s16 *)local.data;
    var_a2 = 0x3000;
    temp_s2 = *D_80174CD8 + 0x20;
    temp_s0 = ((S_80171168_0 *)(*D_80174CD8))->unk_0C;
    temp_s3 = ((S_80171168_0 *)(*D_80174CD8))->unk_08;
    temp_s0->unk_14 = (u16) (temp_s0->unk_14 & 0xFF7F);
    call_a0 = temp_s0->unk_24;
    call_a1 = temp_s0->unk_25;
    if (temp_s2->unk_1C & 0x2000) {
        var_a2 = 0x300;
    }
    func_8009A3D0(call_a0, call_a1, var_a2);
    global_base = D_80082E80;
    temp_a0 = &temp_a0[arg0];
    local_bytes = (u8 *)temp_a0;
    temp_s0->unk_24 = (u8) (global_base[0x24] + local_bytes[0]);
    temp_s0->unk_25 = (u8) (global_base[0x25] + local_bytes[1]);
    func_800A2B04(temp_s3, temp_s0->unk_24, temp_s0->unk_25);
    final_a0 = temp_s0->unk_24;
    final_a1 = temp_s0->unk_25;
    var_a2_2 = 0x3000;
    if (temp_s2->unk_1C & 0x2000) {
        var_a2_2 = 0x300;
    }
    func_8009A21C(final_a0, final_a1, var_a2_2);
}
