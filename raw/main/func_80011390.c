#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800247B8();
M2C_UNK func_8003AD08();
M2C_UNK func_8004DA74();
M2C_UNK func_8004E298();
M2C_UNK func_8004E5A0();
M2C_UNK func_8004E5E8();
M2C_UNK func_8004E69C();
M2C_UNK func_80069E38();
M2C_UNK func_80069E78();
extern u8 D_800200A4[0x100];
extern s32 D_80027FD4[0x40];
extern u8 D_800282D8[0x100];
extern u8 D_800282E8[0x100];
extern u8 D_800283A8[0x100];
extern u8 D_80083EA4[0x4000];

void func_80024390(void *arg0) {
    u8 sp10[256];
    u8 sp110[16];
    s32 var_a3;
    s32 *var_a2;
    s32 temp_s0_5;
    s32 temp_s4;
    s32 temp_s5;
    s32 var_a0;
    s32 var_a0_3;
    u32 temp_v1;
    u32 var_a0_2;
    u32 one;
    s32 width;
    s32 temp_hi;
    void *temp_fp;
    void *temp_base;
    void *loop_base;
    void *asset0;
    void *asset1;
    void *asset2;
    void *asset3;
    void *asset4;
    void *asset5;
    void *asset6;
    void *table_base;
    void *temp_s3;
    void *temp_v0;
    void *var_a1;
    s32 *global_table;

    temp_s3 = M2C_FIELD(arg0, void **, 0xB4C);
    func_8003AD08(M2C_FIELD(arg0, s32 *, 0x7C) + 1, &sp10);
    func_80069E38(&sp10, D_800282D8);
    temp_base = D_80083EA4;
    func_80069E38(&sp10, (M2C_FIELD(arg0, s32 *, 0x7C) << 7) + temp_base);
    asset0 = arg0 + 0x84;
    func_8004DA74(asset0, &sp10, 1);
    M2C_FIELD(temp_s3, void **, 0) = asset0;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = 0xA8;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = 0x110;
    temp_s3 = M2C_FIELD(arg0, void **, 0xB50);
    func_80069E78(&sp10, D_800282E8);
    asset1 = arg0 + 0x204;
    func_8004DA74(asset1, &sp10, 1);
    M2C_FIELD(temp_s3, void **, 0) = asset1;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = 0xA0;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = 0x110;
    temp_fp = temp_base - 0xC;
    if (M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x7C) << 7) + temp_fp), s16 *, 8) != 0) {
        table_base = D_800283A8;
        temp_s3 = M2C_FIELD(arg0, void **, 0xB54);
        func_80069E78(&sp10, M2C_FIELD(table_base, M2C_UNK **, 8));
        func_8003AD08(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x7C) << 7) + temp_fp), s32 *, 0x34), &sp110);
        func_80069E38(&sp10, &sp110);
        func_80069E38(&sp10, M2C_FIELD(table_base, M2C_UNK **, 0xC));
        asset2 = arg0 + 0x384;
        func_8004DA74(asset2, &sp10, 1);
        M2C_FIELD(temp_s3, void **, 0) = asset2;
        M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = 0xB8;
        M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = 0x140;
    }
    temp_s3 = M2C_FIELD(arg0, void **, 0xB58);
    func_8004E5A0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x7C) << 7) + temp_fp), s32 *, 0x24), 0xA, &sp10);
    func_8004E69C(&sp10);
    asset3 = arg0 + 0x504;
    func_8004E298(asset3, &sp10, 1);
    M2C_FIELD(temp_s3, void **, 0) = asset3;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = 0x148;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = 0x110;
    temp_v0 = (M2C_FIELD(arg0, s32 *, 0x7C) << 7) + temp_fp;
    temp_hi = M2C_FIELD(temp_v0, u32 *, 0x1C) / 60;
    temp_s5 = temp_hi;
    temp_s3 = M2C_FIELD(arg0, void **, 0xB5C);
    temp_s4 = temp_s5 / 3600;
    var_a0 = 0x3E7;
    if (temp_s4 < 0x3E8) {
        var_a0 = temp_s4;
    }
    func_8004E5A0(var_a0, 3, &sp10);
    func_80069E38(&sp10, D_800200A4);
    temp_s0_5 = temp_s5 / 60;
    func_8004E5E8(temp_s0_5 - (temp_s4 * 0x3C), 2, &sp110);
    func_80069E38(&sp10, &sp110);
    func_80069E38(&sp10, D_800200A4);
    func_8004E5E8(temp_s5 - (temp_s0_5 * 0x3C), 2, &sp110);
    func_80069E38(&sp10, &sp110);
    func_8004E69C(&sp10);
    asset4 = arg0 + 0x684;
    func_8004E298(asset4, &sp10, 1);
    M2C_FIELD(temp_s3, void **, 0) = asset4;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = 0x150;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = 0x120;
    temp_v1 = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x7C) << 7) + temp_fp), u32 *, 0x2C);
    temp_s3 = M2C_FIELD(arg0, void **, 0xB60);
    var_a0_2 = 0x3E7;
    if (temp_v1 < 0x3E8U) {
        var_a0_2 = temp_v1;
    }
    func_8004E5A0((s32) var_a0_2, 3, &sp10);
    func_8004E69C(&sp10);
    asset5 = arg0 + 0x804;
    func_8004E298(asset5, &sp10, 1);
    M2C_FIELD(temp_s3, void **, 0) = asset5;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = 0x100;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = 0x120;
    temp_s3 = M2C_FIELD(arg0, void **, 0xB64);
    func_8004E5A0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x7C) << 7) + temp_fp), s32 *, 0x28), 2, &sp10);
    func_8004E69C(&sp10);
    asset6 = arg0 + 0x984;
    func_8004E298(asset6, &sp10, 1);
    var_a0_3 = 0;
    loop_base = temp_fp;
    global_table = D_80027FD4;
    one = 1;
    width = 0xB0;
    var_a3 = 0x34;
    var_a2 = global_table;
    var_a1 = arg0;
    M2C_FIELD(temp_s3, void **, 0) = asset6;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = 0x188;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = 0x130;
loop_7:
    temp_s3 = M2C_FIELD(var_a1, void **, 0xB68);
    temp_v0 = (void *)(M2C_FIELD(arg0, s32 *, 0x7C) << 7);
    temp_v0 = (void *)((u32)temp_v0 + (u32)loop_base);
    if (M2C_FIELD(temp_v0, s32 *, 0x30) & (one << var_a0_3)) {
        temp_v1 = *(volatile s32 *)var_a2;
        func_800247B8(var_a0_3, var_a1, ++var_a2, var_a3);
        return;
    }
    do {
        temp_v1 = global_table[8];
    } while (0);
    var_a2 += 1;
    var_a1 += 4;
    var_a0_3 += 1;
    M2C_FIELD(temp_s3, s32 *, 0) = (s32) temp_v1;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 8) = var_a3;
    M2C_FIELD(M2C_FIELD(temp_s3, void **, 4), s16 *, 0xA) = width;
    var_a3 += 0x10;
    if (var_a0_3 >= 8) {
        return;
    }
    goto loop_7;
}
