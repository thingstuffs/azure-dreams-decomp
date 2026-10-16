/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef void (*TownFunc3)(const u8 *, const u8 *, s32);
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
extern s32 D_00001020;
extern TownState *D_00001040[];
extern TownData *D_00001034[];
extern s32 *D_0000103C[];
extern u8 D_00000694[];
extern u8 D_000006BC[];
extern u8 D_00000FE4[];

/* Sets up town data and resolves record indices through the lookup table. */
void townSetupDataAndResolveRecordIndices(void) {
    u8 *record_tag;
    u8 *data;

    if (D_00001020 != 0) {
        D_00001040[0]->func_64(D_00000694, D_000006BC, 0x4B);
        D_00001040[0]->func_70(1);
    }
    D_00001020 = 1;
    func_80000DC8();
    D_00001034[0]->ptr_10 = D_00000FE4;
    data = D_00001034[0]->ptr_10;
    if (data[1] != 0x80) {
        s32 end_tag;
        end_tag = 0x80;
        record_tag = data + 1;
loop_0:
        {
            *(s32 *)(record_tag + 0xB) = D_0000103C[0][*(s32 *)(record_tag + 0xB)];
            record_tag += 0x14;
        }
        if (*record_tag != end_tag)
            goto loop_0;
    }
}
