#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern volatile s8 D_800133A7;
extern volatile s8 D_800133A9;
extern volatile s8 D_800133BB;
extern volatile s8 D_800133C5;
extern volatile s8 D_800133C7;
extern volatile s8 D_800133C9;
extern volatile s8 D_800133E7;
typedef struct {
    s32 value[5];
} TownFiveWords;
extern TownFiveWords D_800894D0;

typedef struct S_800B8B00_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
    u8 unk_33A5;
} S_800B8B00_0;   /* temp_v1 in func_800B8B00 */

typedef struct S_800B8B00_1 {
    u8 pad_00[0x33A5];
    u8 unk_33A5;
} S_800B8B00_1;   /* temp_v1_2 in func_800B8B00 */

void func_800B8B00(s32 arg0) {
    s8 var_t0;
    TownFiveWords first;
    s16 temp_a0;
    s32 *var_a1;
    s32 *var_a1_2;
    register s32 var_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 var_a0_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_a2;
    S_800B8B00_0 *temp_v1;
    S_800B8B00_1 *temp_v1_2;
    u8 *page;
    u8 *page2;
    register volatile u8 *store_base ASM_REG("$1");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    var_t0 = arg0;
    first = D_800894D0;
    temp_a0 = arg0 - 1;
    switch (temp_a0) {
    case 0x5:
    case 0x7:
    case 0x8:
    case 0xA:
    case 0xB:
    case 0x29:
    case 0x2A:
        var_t0 = 9;
        var_a0 = 0;
        page = (u8 *)0x80010000;
        var_a2 = 9;
        var_a1 = first.value;
loop_3:
        temp_v1 = (u8 *)((u32)(*var_a1 * 2) + (u32)page);
        if (temp_v1->unk_33A4 != var_a2) {
            var_a0 += 1;
            if (temp_v1->unk_33A5 != var_a2) {
                var_a1 += 1;
                if (var_a0 >= 5) {
                    var_a0_2 = 0;
                    page2 = (u8 *)0x80010000;
                    var_a1_2 = first.value;
loop_7:
                    do {
                        temp_v1_2 = (u8 *)((u32)(*var_a1_2 * 2) + (u32)page2);
                        var_a0_2 += 1;
                        if (temp_v1_2->unk_33A5 == 0) {
                            temp_v1_2->unk_33A5 = var_t0;
                            return;
                        }
                        var_a1_2 += 1;
                    } while (var_a0_2 < 5);
                    return;
                }
                goto loop_3;
            }
        }
    default:
        return;
    case 0x36:
        var_t0 = 0xA;
        /* fallthrough */
    case 0x9:
    case 0x2B:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33A7] = var_t0;
        return;
    case 0x10:
    case 0x11:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33A9] = var_t0;
        return;
    case 0x37:
        var_t0 = 3;
        /* fallthrough */
block_14:
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3F:
    case 0x40:
    case 0x41:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33BB] = var_t0;
        return;
    case 0x38:
        var_t0 = 2;
        goto block_14;
    case 0x3E:
        var_t0 = 1;
        goto block_14;
    case 0x3:
    case 0x4:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33C5] = var_t0;
        return;
    case 0xE:
    case 0xF:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33C7] = var_t0;
        return;
    case 0x6:
    case 0x2C:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33C9] = var_t0;
        return;
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33E7] = var_t0;
        break;
    }
}
