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

extern volatile s32 D_80012090[];
extern s16 D_8001F6F8[];
extern DungeonGroup D_80073414[];

void func_8001E994(void)
{
    s32 var_t0;
    s32 var_t1;
    s32 var_t4;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    u16 temp_v1;
    s16 *var_t3;
    u8 *var_a3;
    register u8 *var_t2 ASM_REG("$10");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 *var_v0_ptr ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

    var_t0 = 0;
    var_t1 = 1;
    var_t4 = 2;
    ASM_KEEP(var_t0);   /* MATCH pin: retail register colouring depends on it */
    var_v0_ptr = (u8 *)D_8001F6F8;
    ASM_KEEP(var_v0_ptr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    var_t3 = (s16 *)(var_v0_ptr + 2);
    var_v0_ptr = (u8 *)D_80073414;
    ASM_KEEP(var_v0_ptr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    var_a3 = var_v0_ptr + 0x14;
    do {
        ASM_KEEP(var_a3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        var_a2 = 1;
        if (var_a2 < (s32)*(u8 *)(var_a3 + 2)) {
            var_t2 = var_a3;
            var_a1 = 0x14;
            do {
                ASM_KEEP(var_a1);   /* MATCH pin: retail register colouring depends on it */
                temp_v1 =
                    *(u16 *)(var_a1 + *(volatile s32 *)(var_a3 + 0xC));
                if (temp_v1 & 0x10) {
                    goto next_item;
                }
                if (!(temp_v1 & 0x40)) {
                    goto add_item;
                }
                {
                    volatile s32 *state_ptr;

                    state_ptr = (volatile s32 *)0x80010000;
                    if (*(volatile s32 *)((u8 *)state_ptr + 0x2090) !=
                        var_t4) {
                        goto next_item;
                    }
                }
add_item:
                    var_v0 =
                        *(u16 *)(var_a1 + *(s32 *)(var_t2 + 0xC)) & 0x3000;
                    if (var_v0 < 0) {
                        var_v0 += 0xFFF;
                    }
                    var_v0 >>= 0xC;
                    {
                        register s32 temp_v1_2 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

                        temp_v1_2 = var_v0 & 3;
                        var_a0 = 0x80;
                        if (temp_v1_2 != 0) {
                            s32 one;

                            one = 1;
                            ASM_KEEP(one);   /* MATCH pin: load-bearing for the whole function shape */
                            var_a0 = 0x55;
                            if (temp_v1_2 != one) {
                                var_a0 = one;
                                if (temp_v1_2 == var_t4) {
                                    var_a0 = 0x20;
                                }
                            }
                        }
                        var_t0 += var_a0;
                    }
next_item:
                var_a1 += 0x14;
            } while (++var_a2 < (s32)*(u8 *)(var_a3 + 2));
            ASM_KEEP(var_a2);   /* MATCH pin: retail register colouring depends on it */
        }
        *var_t3 = var_t0;
        var_t3++;
        var_t1++;
        var_a3 += 0x14;
    } while (var_t1 < 0x13);
    {
        s16 *var_v1_ptr;
        s32 tail_offset;

        var_v1_ptr = D_8001F6F8;
        ASM_KEEP(var_v1_ptr);   /* MATCH pin: retail immediate-load split depends on it */
        tail_offset = var_t1 << 1;
        *(s16 *)(tail_offset + (s32)var_v1_ptr) = var_t0;
    }
}

/* MECHANISM: Frameless leaf keeps raw group/offset lifetimes at loop seams;
   volatile entries reload and scoped page/one values remove preheader holds,
   while guarded pins encode retail's nine stable loop-register roles. */
