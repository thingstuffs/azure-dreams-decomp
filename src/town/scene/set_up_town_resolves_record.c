/* Relinked copy of town/func_808BB5EC (func_808BB5EC.c); retail differs only at relocation sites; the twin's jump loop is spelled as the indexed do-while of its sibling func_808816D8. */
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
typedef struct TownRecord {
    u8 tag;
    u8 pad1[0x13];
} TownRecord;
extern void func_80000C8C(void);
extern s32 D_00000E48;
extern TownState *D_00000E68[];
extern TownData *D_00000E5C[];
extern s32 *D_00000E64[];
extern u8 D_00000730[];
extern u8 D_00000758[];
extern u8 D_00000E0C[];

/* Sets up town data and resolves record indices through the lookup table. */
void set_up_town_resolves_record(void) {
    u8 *data;

    if (D_00000E48 != 0) {
        D_00000E68[0]->func_64(D_00000730, D_00000758, 0x4B);
        D_00000E68[0]->func_70(1);
    }
    D_00000E48 = 1;
    func_80000C8C();
    D_00000E5C[0]->ptr_10 = D_00000E0C;
    data = D_00000E5C[0]->ptr_10;
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
                *(s32 *)((u8 *)&rec[i] + 0xB) = D_00000E64[0][*(s32 *)((u8 *)&rec[i] + 0xB)];
                i++;
            } while (rec[i].tag != sentinel);
        }
    }
}
