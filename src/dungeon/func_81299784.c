#define func_800AA36C markCategoryItemsFlag400
#define dungeonCreateAttachedSpriteWithOffset func_80151B50
#define func_80173C30 func_80154C30
#define func_8003FD64 func_8003F958
#define D_8017112C D_8015212C
#define func_8004491C func_800444B8
#define D_80083780 D_800875C8
#define D_80174710 D_80155710
#define D_80173E8C D_80154E8C
#define D_80171514 D_80152514
#define func_800A9C18 func_800A88D0
#define D_80083498 D_800871C8
#define func_80045340 func_80044EDC
/* Relink of matched dungeon/func_81251784 at file 0x1271784; imports and data use paired retail relocations. */
#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

void *func_8003F958();
s32 func_800444B8();
void func_800A88D0();
s32 markCategoryItemsFlag400();
void func_80151B50();
M2C_UNK func_80154C30();
extern M2C_UNK D_8015212C;
extern M2C_UNK D_80152514;
extern M2C_UNK D_80154E8C;
extern void *D_80155710;

typedef struct S_80170F84_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80170F84_0;

typedef struct S_80170F84_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x6C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_80170F84_1;

typedef struct S_80170F84_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80170F84_2;

typedef struct S_80170F84_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80170F84_3;

/* Create a dungeon entity and initialize its state and placement. */
void *func_80151F84(s16 entity_id, s32 tile_x, s16 tile_y, u16 initial_height) {
    S_80170F84_1 *entity_state = NULL;
    s16 saved_tile_x;
    s16 saved_height;
    s16 saved_tile_y;
    u16 saved_tile_1c;
    u16 saved_tile_1e;
    S_80170F84_3 *tile_state;
    S_80170F84_2 *world_state;
    void *entity;

    saved_tile_x = tile_x;
    saved_height = initial_height;
    saved_tile_y = tile_y;
    entity = func_8003F958(0x112, ((M2C_UNK *)&D_800871C8.next));
    if (entity != NULL) {
        entity_state = entity + 0x20;
        D_80155710 = entity;
        ((S_80170F84_0 *)entity)->unk_10 = &D_8015212C;
        entity_state->unk_13 = 0x37;
        func_800444B8(entity, func_80044EDC);
        world_state = ((S_80170F84_0 *)entity)->unk_08;
        world_state->unk_0A = saved_height;
        tile_state = ((S_80170F84_0 *)entity)->unk_0C;
        tile_state->unk_24 = saved_tile_x;
        tile_state->unk_25 = saved_tile_y;
        tile_state->unk_2C = &D_80154E8C;
        entity_state->unk_9E = 0;
        func_800A88D0(entity, world_state, tile_state, entity_id);
        entity_state->unk_9A = 0xFF;
        entity_state->unk_9C = -1;
        entity_state->unk_8C = &D_80152514;
        entity_state->unk_1C = (s32) (entity_state->unk_1C | 0x40000);
        tile_state->unk_10 = 0x20;
        tile_state->unk_14 = (u16) (tile_state->unk_14 | 0xC);
        markCategoryItemsFlag400(entity_state, world_state, tile_state, entity_state);
        world_state->unk_0A = (u16) ((u16)D_800875C8.z.w.i);
        world_state->unk_16 = (s16) (world_state->unk_0A - 0x20);
        world_state->unk_0A = (u16) (world_state->unk_0A - 0x190);
        saved_tile_1c = tile_state->unk_1C;
        saved_tile_1e = tile_state->unk_1E;
        tile_state->unk_1C = 0U;
        tile_state->unk_1E = 0U;
        tile_state->unk_14 = (u16) (tile_state->unk_14 | 0x80);
        func_80151B50(entity_state, world_state, tile_state, 1);
        func_80151B50(entity_state, world_state, tile_state, 2);
        tile_state->unk_1C = saved_tile_1c;
        tile_state->unk_1E = saved_tile_1e;
        func_80154C30();
    }
    return entity_state;
}
