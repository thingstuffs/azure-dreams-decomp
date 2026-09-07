#include "common.h"

typedef struct {
    s32 word0 __attribute__((packed));
    s32 word4 __attribute__((packed));
} PackedPair;

typedef struct {
    u8 pad0[0x14];
    s16 field_14;
    s16 field_16;
} DungeonConfig;

extern PackedPair D_80088CB0;
extern u8 D_80083160[];
extern u8 D_800E50A8[];
extern u8 D_800EA000[];

extern void func_800672D8(PackedPair *, u8 *);
extern void func_8009BF7C(s32, s32);
extern void func_8009D9B4(s32, u8 *, s32, u8 *);
extern void func_8009D9F0(u8, u8 *, s32, u8 *);

void func_8009D8A4(void) {
    PackedPair sp10;
    DungeonConfig *temp_t2;
    u8 *temp_v0;
    u8 *var_a1;
    u8 *var_a3;
    u8 *var_t4;
    u8 *temp_a0;
    s32 var_t5;
    s32 var_t3;
    s16 var_t1;
    register s32 var_a2 ASM_REG("$6");
    s16 temp_v0_3;
    register s32 var_v1 ASM_REG("$3");
    s32 temp_v0_2;
    s32 temp_a0_3;
    s16 temp_v0_5;
    s32 temp_v0_6;
    u16 temp_v1;
    s32 temp_a0_2;
    u8 temp_v1_2;
    register s32 var_v0 ASM_REG("$2");

    sp10 = D_80088CB0;
    var_a1 = D_800E50A8;
    var_a3 = var_a1;
    ASM_KEEP(var_a3);
    temp_v0 = D_80083160;
    temp_t2 = (DungeonConfig *)(temp_v0 + 0x1DC);
    if ((1 << temp_t2->field_16) > 0) {
        var_t1 = 0;
        var_t5 = 0;
        var_t3 = 1;
        var_t4 = D_800EA000;
loop_2:
        var_a2 = 0;
        {
            s16 temp_v0_4 = temp_t2->field_14;
            register u16 temp_a0_3 ASM_REG("$4");
            register s32 held_outer ASM_REG("$8");
            temp_a0_3 = *(volatile u16 *)((u8 *)temp_t2 + 0x14);
            if (!(var_t5 < (var_t3 << temp_v0_4))) {
                goto block_21;
            }
            var_v0 = (u32) var_t1 << 16;
            held_outer = var_v0 >> 16;
            var_v1 = held_outer << temp_a0_3;
loop_4:
            temp_a0 = (u8 *)((long)((var_v1 + (s16) var_a2) * 6) + (long)var_t4);
            temp_v1 = *(u16 *)temp_a0;
            if ((temp_v1 != 0) && (temp_v1 != 3)) {
                register u16 clamp_a0 ASM_REG("$4");
                register s32 clamp_v1 ASM_REG("$3");

                var_v0 = (s16) (*(u16 *)(temp_a0 + 2) + 0x200) / 64;
                clamp_a0 = var_v0;
                ASM_KEEP_NV(var_v0);
                clamp_v1 = var_v0;
                if (clamp_v1 >= 0x10) {
                    func_8009D9B4(15, var_a1, var_a2, var_a3);
                    return;
                }
                if (clamp_v1 <= 0) {
                    clamp_a0 = 1;
                }
                var_v0 = (u32) clamp_a0 << 16;
                ASM_KEEP_NV(var_v0);
                temp_v0_6 = var_v0 >> 16;
                temp_a0_2 = *var_a3;
                if ((s32) var_a2 & 1) {
                    var_v0 = temp_a0_2 | (temp_v0_6 << 4);
                    ASM_TAILSLOT_PIN(var_v0);
                    func_8009D9F0(temp_a0_2, var_a1, var_a2, var_a3);
                    return;
                }
                var_v0 = temp_a0_2 | temp_v0_6;
                ASM_TAILSLOT_PIN(var_v0);
                func_8009D9F0(temp_a0_2, var_a1, var_a2, var_a3);
                return;
            }
            {
                register s32 var_odd ASM_REG("$2");

                temp_v1_2 = *var_a3;
                ASM_USE(temp_v1_2);
                var_odd = var_a2 & 1;
                if (var_odd) {
                    var_v0 = temp_v1_2 & 0xF;
                } else {
                    var_v0 = temp_v1_2 & 0xF0;
                }
                *var_a3 = var_v0;
                ASM_SET(var_odd);
                var_odd = var_a2 & 1;
                if (var_odd) {
                    var_a3 += 1;
                }
                var_v0 = var_a2 + 1;
                ASM_KEEP_NV(var_v0);
            }
            var_a2 = var_v0;
            ASM_KEEP_NV(var_v0);
            var_v0 = (s16) var_v0;
            temp_v0_4 = temp_t2->field_14;
            temp_a0_3 = *(volatile u16 *)((u8 *)temp_t2 + 0x14);
            if (var_v0 >= (var_t3 << temp_v0_4)) {
                goto block_21;
            }
            var_v1 = held_outer << temp_a0_3;
            goto loop_4;
        }
block_21:
        temp_v0_3 = var_t1 + 1;
        var_t1 = temp_v0_3;
        if (var_t1 < (var_t3 << temp_t2->field_16)) {
            goto loop_2;
        }
    }
    func_800672D8(&sp10, var_a1);
    func_8009BF7C(1, 0x20);
}
