#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
M2C_UNK func_80170B50();
M2C_UNK func_80173C30();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern u16 D_8008378A;
extern M2C_UNK D_8017112C;
extern M2C_UNK D_80171514;
extern M2C_UNK D_80173E8C;
extern void *D_80174710;

typedef struct S_80170F84_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80170F84_0;   /* temp_v0 in func_80170F84 */

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
} S_80170F84_1;   /* var_s4 in func_80170F84 */

typedef struct S_80170F84_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80170F84_2;   /* temp_s1 in func_80170F84 */

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
} S_80170F84_3;   /* temp_s0 in func_80170F84 */

/* Create a dungeon entity and initialize its state and placement. */
void *func_80170F84(s16 entity_id, s32 tile_x, s16 tile_y, u16 initial_height) {
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
    entity = func_8003FD64(0x112, &D_80083498);
    if (entity != NULL) {
        entity_state = entity + 0x20;
        D_80174710 = entity;
        ((S_80170F84_0 *)entity)->unk_10 = &D_8017112C;
        entity_state->unk_13 = 0x37;
        func_8004491C(entity, &D_80045340);
        world_state = ((S_80170F84_0 *)entity)->unk_08;
        world_state->unk_0A = saved_height;
        tile_state = ((S_80170F84_0 *)entity)->unk_0C;
        tile_state->unk_24 = saved_tile_x;
        tile_state->unk_25 = saved_tile_y;
        tile_state->unk_2C = &D_80173E8C;
        entity_state->unk_9E = 0;
        func_800A9C18(entity, world_state, tile_state, entity_id);
        entity_state->unk_9A = 0xFF;
        entity_state->unk_9C = -1;
        entity_state->unk_8C = &D_80171514;
        entity_state->unk_1C = (s32) (entity_state->unk_1C | 0x40000);
        tile_state->unk_10 = 0x20;
        tile_state->unk_14 = (u16) (tile_state->unk_14 | 0xC);
        func_800AA36C(entity_state, world_state, tile_state, entity_state);
        world_state->unk_0A = (u16) D_8008378A;
        world_state->unk_16 = (s16) (world_state->unk_0A - 0x20);
        world_state->unk_0A = (u16) (world_state->unk_0A - 0x190);
        saved_tile_1c = tile_state->unk_1C;
        saved_tile_1e = tile_state->unk_1E;
        tile_state->unk_1C = 0U;
        tile_state->unk_1E = 0U;
        tile_state->unk_14 = (u16) (tile_state->unk_14 | 0x80);
        func_80170B50(entity_state, world_state, tile_state, 1);
        func_80170B50(entity_state, world_state, tile_state, 2);
        tile_state->unk_1C = saved_tile_1c;
        tile_state->unk_1E = saved_tile_1e;
        func_80173C30();
    }
    return entity_state;
}
