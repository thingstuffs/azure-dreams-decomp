/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80125800_1 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80125800_1;   /* obj in func_80125800 */

typedef struct S_80125800_2 {
    u8 pad_00[0x184];
    void * unk_184;
} S_80125800_2;   /* ((S_80125800_1 *)obj)->unk_58 in func_80125800 */

typedef struct S_80125800_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80125800_3;   /* ((S_80125800_2 *)(((S_80125800_1 *)obj)->unk_58))->unk_184 in func_80125800 */

typedef struct S_80125800_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80125800_4;   /* ((S_80125800_3 *)(((S_80125800_2 *)(((S_80125800_1 *)obj)->unk_58))->unk_184))->unk_04 in func_80125800 */




#define M2C_BREAK() M2C_ERROR("break")
#define M2C_SYNC() M2C_ERROR("sync")

typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
    SpriteFields *dst;
} DisplayPair;

typedef struct TownSlots {
    void **slots[97];
    DisplayPair *display;
} TownSlots;

typedef struct TownObject {
    u8 pad0[4];
    s16 field4;
    s16 field6;
    u8 pad8[7];
    u8 digit;
    u8 row;
    u8 index;
    u8 column;
    u8 pad13[0x45];
    TownSlots *town;
} TownObject;

extern u8 func_80123200(u8 value);
extern void *D_801269D0[10];
extern s16 D_80126B24[8];
extern u8 D_80127B64[16];

typedef struct S_80125800_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x9];
    u8 unk_11;
    u8 unk_12;
} S_80125800_0;   /* obj in func_80125800 */

void func_80125800(TownObject *obj) {
    s32 row8;
    s32 offset;
    s32 slot;
    s32 value;

    row8 = obj->row << 3;
    offset = (row8 + obj->column) * 3;
    slot = offset + 33;
    value = (obj->digit << 4) + row8 + obj->column;
    if (func_80123200((u8)value) != 0) {
        s32 number = value + 1;

        *obj->town->slots[slot] = (void *)D_80127B64;
        slot = offset + 34;
        *obj->town->slots[slot] = D_801269D0[number / 10];
        slot = offset + 35;
        *obj->town->slots[slot] = D_801269D0[number % 10];
    }
    ((S_80125800_4 *)(((S_80125800_3 *)(((S_80125800_2 *)(((S_80125800_1 *)obj)->unk_58))->unk_184))->unk_04))->unk_0A = (s16) ((u16) D_80126B24[((S_80125800_0 *)obj)->unk_12 & 7] + (((s32) (D_80126B24[((S_80125800_0 *)obj)->unk_11 & 7] - D_80126B24[((S_80125800_0 *)obj)->unk_12 & 7]) / (s16) ((S_80125800_0 *)obj)->unk_06) * ((S_80125800_0 *)obj)->unk_04));
}
