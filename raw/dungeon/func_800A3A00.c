#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct {
    u16 flags;
    u8 pad02[0x12];
} DungeonCell;

typedef struct {
    u8 pad00[2];
    u8 count;
    u8 pad03[9];
    DungeonCell *cells;
    u8 pad10[4];
} DungeonGroup;

typedef struct {
    u8 pad00[0x5720];
    u8 bits[1];
} RamPage;

extern DungeonGroup D_80073414[];

void func_800A9160(void)
{
    DungeonGroup *var_t2;
    register DungeonGroup *var_t0 ASM_REG("$8");
    register s32 temp_t1 ASM_REG("$9");
    register s32 var_a0 ASM_REG("$4");
    s32 var_a1;
    s32 var_a2;
    u8 *var_a3;
    s32 var_t3;
    s32 var_v0;
    register s32 one ASM_REG("$2");
    void *temp_a0;
    RamPage *ram;

    var_t3 = 0;
    ram = (RamPage *)0x80010000;
    var_t2 = D_80073414;
    do {
        ASM_KEEP(var_t2);
        var_a2 = 0;
        if (var_t2->count != 0) {
            temp_t1 = var_t3 * 8;
            var_t0 = var_t2;
            ASM_KEEP(temp_t1);
            ASM_KEEP(var_t0);
            var_a3 = 0;
            do {
                if (!(var_a2 & 7)) {
                    var_v0 = var_a2;
                    if (var_a2 < 0) {
                        var_v0 = var_a2 + 7;
                    }
                    FIELD(temp_t1 + (var_v0 >> 3) + (s32)ram,
                          u8, 0x5720) = 0;
                }
                if (*(u16 *)(var_a3 + (s32)var_t0->cells) & 0x400) {
                    var_a0 = var_a2;
                    if (var_a2 < 0) {
                        var_a0 = var_a2 + 7;
                    }
                    ASM_KEEP(var_a0);
                    temp_a0 = temp_t1 + (var_a0 >> 3) + (s32)ram;
                    var_a1 = var_a2 & 7;
                    ASM_SCHED_BARRIER();
                    one = 1;
                    ASM_KEEP(one);
                    FIELD(temp_a0, u8, 0x5720) =
                        FIELD(temp_a0, u8, 0x5720) |
                        (one << var_a1);
                }
                var_a3 += sizeof(DungeonCell);
            } while (++var_a2 < (s32)var_t0->count);
        }
        var_t3 += 1;
        var_t2 += 1;
    } while (var_t3 < 0x13);
}

/* MECHANISM: Frameless leaf; typed 20-byte groups recover the two local do-loops
   and the outer +20 delay-slot stride. Held current/inner group roles plus an
   index-first 0x80010000 RAM address reproduce t2/t0 and the 0x5720 accesses.
   A preincrement condition emits count-load before index increment and closes. */
