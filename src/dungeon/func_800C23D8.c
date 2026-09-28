#include "common.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Entity transition state */
typedef struct Entity {
    u8    pad0[0xC];
    void *unkC;      /* 0x0C -> Sub */
    s32   unk10;     /* 0x10 */
    u8    pad14[4];
    s32   unk18;     /* 0x18 state selector */
    u8    pad1C[8];
    s16   unk24;     /* 0x24 countdown */
    u16   unk26;     /* 0x26 */
} Entity;

typedef struct Sub {
    u8  pad0[2];
    s16 f2;   /* 0x02 */
    u8  pad4[2];
    s16 f6;   /* 0x06 */
    u8  pad8[2];
    s16 fA;   /* 0x0A */
} Sub;

/* View over the D_80083178 dispatch/blend record (fields not in game.h struct) */

extern s16 D_800120A2;
extern s16 D_800DD264[];
extern s16 D_800DCE66[5];

extern void func_800C77D0(void *a0, void *a1, s32 a2, s16 a3);

/* Blend toward the entity target, then dispatch the next state. */
void func_800C7B38(void *entity_data) {
    Entity *entity = entity_data;
    GameView *blend = &gameWork.view;
    s32 state = entity->unk18;

    if (state == 0) goto blend_state;
    if (state == 1) goto dispatch_state;
    return;

blend_state:
    if (entity->unk24 > 0) {
        s16 half_ticks;
        entity->unk10 -= entity->unk10 >> 2;
        blend->unk_098 = entity->unk26 + (u16)entity->unk10;
        blend->unk_0AC = (u16)blend->unk_0AC + (D_800DD264[D_800120A2] - blend->unk_0AC) / entity->unk24;
        blend->viewAngle = (u16)blend->viewAngle + (0 - blend->viewAngle) / entity->unk24;
        blend->unk_0A4 = (u16)blend->unk_0A4 + (((Sub *)entity->unkC)->f2 - blend->unk_0A4) / entity->unk24;
        blend->unk_0A6 = (u16)blend->unk_0A6 + (((Sub *)entity->unkC)->f6 - blend->unk_0A6) / entity->unk24;
        half_ticks = (s16)(u16)entity->unk24 / 2;
        if (half_ticks != 0) {
            blend->unk_0A8 = (u16)blend->unk_0A8 + (((Sub *)entity->unkC)->fA - blend->unk_0A8) / half_ticks;
        }
        {
            s16 ticks_left = (u16)entity->unk24 - 1;
            entity->unk24 = ticks_left;
            if (ticks_left > 0) {
                return;
            }
        }
    }
    blend->unk_0AC = (u16)D_800DD264[D_800120A2];
    blend->viewAngle = 0;
    blend->unk_098 = entity->unk26;
    entity->unk18 += 1;
    return;

dispatch_state:
    func_800C77D0((void *)(((s32)D_800E3D7C) - 0x20), ((u8 *)(&D_80083780)), 8, D_800DCE66[0]);
    dungeonStatus.unk_0A = dungeonStatus.unk_0A - 1;
}
