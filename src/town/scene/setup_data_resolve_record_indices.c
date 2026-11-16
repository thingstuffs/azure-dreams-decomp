#include "common.h"
#include "town/scene.h"
#include "town/devkit/flag_test_imports.h"

typedef struct TownRecord {
    u8 tag;
    u8 pad1[0x13];
} TownRecord;

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
extern s32 D_00001020;
extern TownState *D_00001040[];
extern TownData *D_00001034[];
extern s32 *D_0000103C[];
extern u8 D_00000694[];
extern u8 D_000006BC[];
extern u8 D_00000FE4[];

/* Sets up town data and resolves record indices through the lookup table. */
void setup_data_and_resolve_record_indices(s32 unused_list_length, s32 unused_record_value) {
    u8 *data;

    if (D_00001020 != 0) {
        D_00001040[0]->func_64(D_00000694, D_000006BC, 0x4B);
        D_00001040[0]->func_70(1);
    }
    D_00001020 = 1;
    func_80000DC8();
    D_00001034[0]->ptr_10 = D_00000FE4;
    data = D_00001034[0]->ptr_10;
    {
        s32 limit;
        s32 check;
        s32 sentinel;
        s32 i;
        TownRecord *rec;
        check = data[1];
        limit = 0x80;
        if (check != limit) {
            sentinel = 0x80;
            rec = (TownRecord *)(data + 1);
            i = 0;
            do {
                *(s32 *)((u8 *)&rec[i] + 0xB) = D_0000103C[0][*(s32 *)((u8 *)&rec[i] + 0xB)];
                i++;
            } while (rec[i].tag != sentinel);
        }
    }
}
