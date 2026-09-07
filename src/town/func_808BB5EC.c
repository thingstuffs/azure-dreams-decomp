/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef void (*TownFunc3)(s32, s32, s32);
typedef void (*TownFunc1)(s32);
typedef struct {
    u8 unk0[0x64];
    TownFunc3 func_64;
    u8 unk68[8];
    TownFunc1 func_70;
} TownState;
typedef struct {
    u8 unk0[0x10];
    u8 *ptr_10;
} TownData;
extern void func_80000DC8(void);
extern s32 D_00001020[];
extern s32 D_00001020_store[] asm("D_00001020");
extern TownState *D_00001040[];
extern TownData *D_00001034[];
extern s32 *D_0000103C[];
extern u8 D_00000694[];
extern u8 D_000006BC[];
extern u8 D_00000FE4[];

void func_808BB5EC(void) {
    register u8 *var_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *temp_a0;

    if (D_00001020[0] != 0) {
        D_00001040[0]->func_64(D_00000694, D_000006BC, 0x4B);
        D_00001040[0]->func_70(1);
    }
    D_00001020_store[0] = 1;
    func_80000DC8();
    D_00001034[0]->ptr_10 = D_00000FE4;
    temp_a0 = D_00001034[0]->ptr_10;
    if (temp_a0[1] != 0x80) {
        s32 end;
        end = 0x80;
        var_a0 = temp_a0 + 1;
        do {
            *(s32 *)(var_a0 + 0xB) = D_0000103C[0][*(s32 *)(var_a0 + 0xB)];
            var_a0 += 0x14;
        } while (*var_a0 != end);
    }
}
