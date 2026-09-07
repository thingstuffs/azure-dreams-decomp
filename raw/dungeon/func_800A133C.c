#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

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

extern s32 func_800A6A6C();
extern DungeonGroup D_80073414[];

typedef struct {
    u8 pad[0x5720];
    u8 data[1];
} RamPage;

void func_800A6A9C(void)
{
    u8 *var_a2;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    s32 var_t0;
    s32 temp_t1;
    s32 mask;
    RamPage *ram;
    s16 *temp_v1;
    s16 *temp_v1_2;

    var_t0 = 0;
    mask = -0x401;
    ram = (RamPage *)0x80010000;
    var_a2 = (u8 *)D_80073414;
    do {
        ASM_KEEP(var_a2);
        var_a1 = 0;
        if (FIELD(var_a2, u8, 2) != 0) {
            temp_t1 = var_t0 * 8;
            var_a3 = 0;
            do {
                temp_v1 = (s16 *)(var_a3 +
                    (s32)FIELD(var_a2, DungeonItem *, 0xC));
                *temp_v1 = *temp_v1 & mask;
                var_a0 = var_a1 / 8;
                if (((s32)*(u8 *)(temp_t1 + var_a0 + (s32)ram + 0x5720) >>
                     (var_a1 & 7)) & 1) {
                    temp_v1_2 = (s16 *)(var_a3 +
                        (s32)FIELD(var_a2, DungeonItem *, 0xC));
                    *temp_v1_2 |= 0x400;
                }
                var_a3 += 0x14;
            } while (++var_a1 < (s32)FIELD(var_a2, u8, 2));
        }
        var_t0 += 1;
        var_a2 += sizeof(DungeonGroup);
    } while (var_t0 < 0x13);
    func_800A6A6C();
}

/* MECHANISM: The 0x18 frame has only the $ra save; explicit mask/page locals
   fix preheader order, and preincrement loads count before the inner increment.
   Loop-top ASM_KEEP holds the unrebased group base, yielding v0-high/a2-low
   split addressing with +2/+0xC fields; index-first RAM arithmetic fixes addu. */
