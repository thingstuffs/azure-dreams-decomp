#include "common.h"

typedef struct {
    u16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[2];
    u8 count;
    u8 pad3[9];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern DungeonGroup D_80073414[];

void func_800A9024(s32 arg0) {
    DungeonGroup *var_a3;
    s32 var_a1;
    register s32 var_a2 ASM_REG("$6");
    s32 var_t0;
    s32 var_v0;
    s32 temp_t1;
    register u32 ram ASM_REG("$11");
    register s32 one ASM_REG("$10");
    register s32 bit ASM_REG("$3");
    u16 *temp_a0;
    u16 temp_v1;
    void *temp_v0;

    var_t0 = 0;
    ram = 0x80010000;
    one = 1;
    ASM_KEEP(ram);
    ASM_KEEP(one);
    var_a3 = D_80073414;
    do {
        ASM_KEEP(var_a3);
        if (((s32)*((u8 *)var_a3 + 1) >> arg0) & 1) {
            var_a1 = 0;
            if (var_a3->count != 0) {
                temp_t1 = var_t0 * 8;
                var_a2 = 0;
                do {
                    temp_a0 = (u16 *)(var_a2 + (s32)var_a3->entries);
                    temp_v1 = *temp_a0;
                    if (!(temp_v1 & 0x200)) {
                        *temp_a0 = temp_v1 | 0x400;
                        var_v0 = var_a1;
                        if (var_a1 < 0) {
                            var_v0 = var_a1 + 7;
                        }
                        temp_v0 = (void *)(temp_t1 + (var_v0 >> 3) + ram);
                        bit = var_a1 & 7;
                        *((u8 *) temp_v0 + 0x5720) = (u8) (*((u8 *) temp_v0 + 0x5720) | (one << bit));
                    }
                    var_a2 += sizeof(DungeonItem);
                } while (++var_a1 < (s32)var_a3->count);
            }
        }
        var_t0 += 1;
        var_a3 += 1;
    } while (var_t0 < 0x13);
}
