#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"


typedef struct S_800CCA14_0 {
    u8 pad_00[0x10];
    u8 * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x1];
    s8 unk_27;
} S_800CCA14_0;   /* temp_v0 in dungeonCreateFivePartTargetEffect */

typedef struct S_800CCA14_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CCA14_1;   /* count_base in dungeonCreateFivePartTargetEffect */

typedef struct S_800CCA14_2 {
    u8 pad_00[0x10];
    u8 * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    s8 unk_26;
    s8 unk_27;
} S_800CCA14_2;   /* temp_v0_2 in dungeonCreateFivePartTargetEffect */


void *initializeSceneObjectInBuffer();      /* extern */
s32 dungeonFindObjectNearTileHeight();                   /* extern */
void func_8009CE1C(); /* extern */
extern void * dungeonCreateTileCenterQuadEffect(s16 tile_x, s16 tile_y, s16 z, s16 tail_value, s16 render_mode, u16 tail_config);
ObjectBlock *dungeonCreateGridEffectObject();     /* extern */
extern u8 D_800CC370;
extern u8 D_800CC9BC;
extern u8 D_800E5908;
extern u8 D_8014A000;

/* Creates a five-part effect at the given position and applies its target effect. */
void dungeonCreateFivePartTargetEffect(u16 x, u16 y, s16 z) {
    s32 direction;
    s32 first_base_angle;
    s32 first_angle;
    s32 base_angle;
    s32 angle;
    s32 target;
    s32 part_index;
    u16 part_x;
    u16 part_y;
    u16 part_z;
    S_800CCA14_0 *effect;
    S_800CCA14_2 *part;

    effect = initializeSceneObjectInBuffer(0, (D_800E5908 * 0xC8) + (u8 *)&D_8014A000, 0xA);
    effect->unk_10 = &D_800CC9BC;
    effect->unk_20 = x;
    effect->unk_22 = y;
    effect->unk_24 = z;
    effect->unk_27 = 8;
    dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) + 1);
    part_index = 3;
    do {
        part = initializeSceneObjectInBuffer(0, (((D_800E5908 * 5) + part_index) * 0x28) + ((u8 *)&D_8014A000 + 0x28), 0xA);
        part->unk_10 = &D_800CC370;
        part_x = (u16) effect->unk_20;
        direction = part_index * 2;
        part->unk_20 = part_x;
        part_y = (u16) effect->unk_22;
        part_index -= 1;
        part->unk_22 = part_y;
        part_z = (u16) effect->unk_24;
        part->unk_27 = 8;
        part->unk_26 = direction;
        part->unk_24 = part_z;
    } while (part_index >= 0);
    base_angle = (part_index << 0x1A) >> 0x10;
    first_base_angle = base_angle;
    dungeonCreateGridEffectObject((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, first_base_angle, 0);
    part_index = 3;
    dungeonCreateGridEffectObject((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, base_angle, 1);
    do {
        angle = (part_index << 0x1A) >> 0x10;
        first_angle = angle;
        dungeonCreateTileCenterQuadEffect((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, first_angle, 0, 0);
        dungeonCreateTileCenterQuadEffect((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, angle, 1, 1);
        part_index -= 1;
    } while (part_index >= 0);
    target = dungeonFindObjectNearTileHeight(effect->unk_20, effect->unk_22, (s16) effect->unk_24);
    if (target != 0) {
        func_8009CE1C(target, 0xC, (*(u8 *)((u8 *)&D_800E3D7C->unk_10 + 1)), 9, 0x400, 0, 3);
    }
}
