#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

typedef struct TownInitialPosition {
    void *data;
    volatile u16 x;
    volatile u16 y;
} TownInitialPosition;

extern void func_80123238(void);
extern TownInitialPosition D_80126AF8[5];
extern s8 D_80128614[];
extern void *D_80129728[];
extern s8 D_801331D0[];

void func_801232DC(void)
{
    register s32 var_s0 ASM_REG("$16");
    TownInitialPosition *var_a0;
    s8 *var_t0;
    s8 *var_a2_data;
    s16 temp_a0_2;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_v1_2;
    s32 object_offset;
    register s32 var_a3 ASM_REG("$7");
    s32 var_a3_2;
    register s32 var_a3_3 ASM_REG("$7");
    register s32 var_a3_4 ASM_REG("$7");
    register s32 final_width ASM_REG("$6");
    register s32 final_x ASM_REG("$5");
    u16 temp_v1;
    void *object;
    void **var_a0_2;
    void **var_a1;
    void **var_a1_2;
    void **var_a2;

    var_s0 = 0x1C;
    func_80123238();
    ASM_KEEP(var_s0);
    var_a3 = 0;
    ASM_KEEP(var_a3);
    {
        register void **object_base ASM_REG("$2");
        object_base = D_80129728;
        ASM_KEEP(object_base);
        var_a1 = &object_base[0x1C];
    }
    var_a0 = D_80126AF8;
    do {
        FIELD(*var_a1, void *, 0) = var_a0->data;
        ASM_KEEP(var_s0);
        object = *var_a1;
        ASM_KEEP(object);
        var_a3 += 1;
        ASM_KEEP(var_a3);
        FIELD(FIELD(object, void *, 4), u16, 8) = var_a0->x;
        var_s0 += 1;
        ASM_KEEP(var_s0);
        object = *var_a1;
        ASM_KEEP(object);
        temp_v1 = var_a0->y;
        var_a0 += 1;
        FIELD(FIELD(object, void *, 4), u16, 0xA) = temp_v1;
        var_a1 += 1;
    } while (var_a3 < 5);

    var_a3_2 = 0;
    var_t0 = D_801331D0;
    {
        register void **object_base ASM_REG("$2");
        object_base = D_80129728;
        ASM_KEEP(object_base);
        object_offset = var_s0 << 2;
        ASM_KEEP(object_offset);
        var_a2 = (void **)(object_offset + (u32)object_base);
    }
    do {
        object = *var_a2;
        ASM_KEEP(object);
        temp_a1 = var_a3_2 >> 3;
        FIELD(object, void *, 0) = var_t0;
        ASM_KEEP(object);
        object = *var_a2;
        ASM_KEEP(object);
        temp_a1 <<= 7;
        FIELD(FIELD(object, void *, 4), s16, 8) = temp_a1 + 0x38;
        temp_a0 = (var_a3_2 & 7) * 0x12;
        FIELD(FIELD(*var_a2, void *, 4), s16, 0xA) = temp_a0 + 0x2C;
        var_a2 += 1;
        FIELD(FIELD(*var_a2, void *, 4), s16, 8) = temp_a1 + 0x3E;
        var_s0 += 3;
        ASM_KEEP(var_s0);
        object = *var_a2;
        ASM_KEEP(object);
        temp_a0_2 = temp_a0 + 0x30;
        object = FIELD(object, void *, 4);
        ASM_KEEP(object);
        var_a2 += 1;
        FIELD(object, s16, 0xA) = temp_a0_2;
        var_t0 += 0xC;
        FIELD(FIELD(*var_a2, void *, 4), s16, 8) = temp_a1 + 0x44;
        var_a3_2 += 1;
        FIELD(FIELD(*var_a2, void *, 4), s16, 0xA) = temp_a0_2;
        var_a2 += 1;
    } while (var_a3_2 < 0x10);

    var_a3_3 = 0;
    ASM_KEEP(var_a3_3);
    {
        register void **object_base ASM_REG("$2");
        object_base = D_80129728;
        ASM_KEEP(object_base);
        object_offset = var_s0 << 2;
        ASM_KEEP(object_offset);
        var_a1_2 = (void **)(object_offset + (u32)object_base);
    }
    var_a2_data = D_801331D0;
    do {
        temp_v1_2 = var_a3_3 >> 3;
        temp_a0_3 = var_a3_3 & 7;
        var_a3_3 += 1;
        ASM_KEEP(var_a3_3);
        FIELD(*var_a1_2, void *, 0) = var_a2_data;
        var_a2_data += 0xC;
        FIELD(FIELD(*var_a1_2, void *, 4), s16, 8) = (temp_v1_2 << 7) + 0x54;
        FIELD(FIELD(*var_a1_2, void *, 4), s16, 0xA) = temp_a0_3 * 0x12 + 0x30;
        var_a1_2 += 1;
    } while (var_a3_3 < 0x10);
    ASM_KEEP(var_s0);

    var_a3_4 = 0;
    ASM_KEEP(var_a3_4);
    final_width = 0x10;
    ASM_KEEP(final_width);
    final_x = 0xE0;
    ASM_KEEP(final_x);
    {
        register void **object_base ASM_REG("$2");
        object_base = D_80129728;
        ASM_KEEP(object_base);
        var_a0_2 = &object_base[0x1C];
        FIELD(object_base[0x61], void *, 0) = D_80128614;
    }
    do {
        FIELD(FIELD(*var_a0_2, void *, 8), s16, 6) = final_width;
        ASM_KEEP(final_width);
        object = *var_a0_2;
        ASM_KEEP(object);
        var_a3_4 += 1;
        ASM_KEEP(var_a3_4);
        FIELD(FIELD(object, void *, 8), s16, 8) = final_x;
        var_a0_2 += 1;
    } while (var_a3_4 < 0x46);
}

/* MECHANISM: The 24-byte frame keeps only s0, with loop counters/data roles pinned at their ABI seams.
   Block-local v0 bases plus split scaled-index names reproduce each hi/lo and pointer-add order.
   One-use object reloads, ASM_KEEP seams, and held s0 liveness reproduce the retail loop schedules. */
