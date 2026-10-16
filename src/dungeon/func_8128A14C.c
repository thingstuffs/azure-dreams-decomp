#define D_80082E80 D_80081490
#define func_8009A21C func_8009900C
#define dungeonSetRecordIntegerTileCenter func_800A17D4
#define D_80174710 D_80167710
#define func_8009A3D0 townInitializeIndexedObjectAndLookupValue
/* Relink of matched dungeon/dungeonRepositionGlobalEffectEntity at file 0x127414C; imports and data use paired retail relocations. */
#include "common.h"
#include "shared/tile_object.h"

typedef struct S_8125414C_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8125414C_0;   /* entity in func_8016694C */

typedef struct S_8125414C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8125414C_1;   /* state in func_8016694C */


extern u8 *D_80167710;

extern void townInitializeIndexedObjectAndLookupValue(s32, s32, s32);
extern void func_800A17D4(void *, s32, s32);
extern void func_8009900C(s16 x, s16 y, u16 flags);

/* Repositions the current entity relative to the origin and updates its motion. */
void func_8016694C(s32 offset_index)
{
    s16 offsets[2] = { 1, -1 };
    u8 *object;
    u8 *state;
    u8 *entity;
    void *motion;
    u8 *offset_bytes;
    TileObject *origin;

    object = D_80167710;
    state = object + 0x20;
    entity = *(u8 **)(object + 0xC);
    motion = *(void **)(object + 8);

    ((S_8125414C_0 *)entity)->unk_14 &= 0xFF7F;

    townInitializeIndexedObjectAndLookupValue(entity[0x24], entity[0x25],
                  (((S_8125414C_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    origin = &D_80081490;
    offset_bytes = (u8 *)&offsets[offset_index * 2];
    entity[0x24] = origin->tileX + offset_bytes[0];
    entity[0x25] = origin->tileY + offset_bytes[2];

    func_800A17D4(motion, entity[0x24], entity[0x25]);

    func_8009900C(entity[0x24], entity[0x25],
                  (((S_8125414C_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);
}
