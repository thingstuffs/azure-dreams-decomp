#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800974DC_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x5E];
    u8 unk_102;
} S_800974DC_0;   /* arg0 in func_800974DC */


typedef struct S_800974DC_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800974DC_4_pre;   /* the 0x14 bytes before temp_a2 in func_800974DC, addressed as temp_a2[-1] */

typedef struct S_800974DC_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800974DC_6;   /* ((S_800974DC_4_pre *)temp_a2)[-1].unk_00 in func_800974DC */


void func_8003DB94();
void func_80099F04(); /* extern */
s32 func_8009C12C();
void func_800A2B04(); /* extern */
s32 func_800C77D0(); /* extern */
extern M2C_UNK D_80096384;
extern M2C_UNK D_800DD274[8];
extern u8 D_800DD294[8];

/* Updates airborne movement, landing animation, and alignment to the actor's tile. */
void func_800974DC(void *action, EntityRec *motion, void *sprite, EntityRec *actor) {
    s32 dir_offset;
    u16 ticks_left;
    s32 dir_y;
    u8 phase;
    EntityRec *linked_object;

    phase = ((S_800974DC_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        func_800C77D0((u8 *)actor - 0x20, motion, 8, 0x300);
        (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = D_800DD294;
        func_8003DB94(sprite, *(M2C_UNK *)((u8 *)D_800DD294 + (((s32) (gameWork.view.viewAngle + actor->facing + 0x100)
            >> 7) & 0x1C)), 0);
        dir_offset = ((u16) actor->facing >> 8) & 0xE;
        motion->unk_0C = (s32) (*(s16 *)((u8 *)dirStepX + dir_offset) << 0x11);
        dir_y = *(s16 *)((u8 *)dirStepY + dir_offset);
        motion->flags14 = 0xFFEBC000;
        motion->unk_10 = (s32) (dir_y << 0x11);
        ((S_800974DC_0 *)action)->unk_96.s = 3U;
        ((S_800974DC_0 *)action)->unk_98 = (u16) (((S_800974DC_0 *)action)->unk_98 & 0xFFF7);
        ((S_800974DC_0 *)action)->unk_9B = (u8) (((S_800974DC_0 *)action)->unk_9B + 1);
        return;
    case 1:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_800974DC_0 *)action)->unk_96.s = 0U;
        } else {
            ((S_800974DC_0 *)action)->unk_96.s = (u16) (((S_800974DC_0 *)action)->unk_96.s - 1);
        }
        if (((S_800974DC_0 *)action)->unk_96.u == 0) {
            if (((S_800974DC_0 *)action)->unk_102 == 0) {
                actor->unk_20 = 1;
                if (func_8009C12C(actor, sprite, actor->facing, 1) == 0) {
                    linked_object = actor->target;
                    if (linked_object != NULL) {
                        actor->target = NULL;
                        linked_object->flags1C = (s32) (linked_object->flags1C & 0xEFFFFFFF);
                        ((S_800974DC_6 *)(((S_800974DC_4_pre *)linked_object)[-1].unk_00))->unk_0C = 0x808080;
                    }
                }
            }
        }
        if ((s16) ((S_800974DC_0 *)action)->unk_96.s <= 0) {
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = D_800DD274;
                func_8003DB94(sprite, *(M2C_UNK *)((u8 *)D_800DD274 + (((s32) (gameWork.view.viewAngle + actor->facing
                    + 0x100) >> 7) & 0x1C)), 0);
                ((S_800974DC_0 *)action)->unk_9B = (u8) (((S_800974DC_0 *)action)->unk_9B + 1);
            }
        }
    case 2:
        if (!(((S_800974DC_0 *)action)->unk_A2 & 0x10)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        if ((s16) ((S_800974DC_0 *)action)->unk_96.s > 0) {
            return;
        }
        (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = D_800DD274;
        func_8003DB94(sprite, *(M2C_UNK *)((u8 *)D_800DD274 + (((s32) (gameWork.view.viewAngle + actor->facing + 0x100)
            >> 7) & 0x1C)), 0);
        ((S_800974DC_0 *)action)->unk_9B = 3U;
        return;
    case 3:
    {
        s32 coord;
        u32 delta;
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        ((S_800974DC_0 *)action)->unk_96.s = 2U;
        delta = (u32)((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        coord = motion->x.w.i - 0x20;
        delta -= (u32)coord;
        motion->unk_0C = (s32)(delta * 0x10000U) / (s16) ((S_800974DC_0 *)action)->unk_96.s;
        coord = motion->y.w.i - 0x20;
        delta = ((u32)((Rec_D_80082E80 *)sprite)->unk_25 << 6) - (u32)coord;
        motion->unk_10 = (s32)(delta * 0x10000U) / (s16) ((S_800974DC_0 *)action)->unk_96.s;
        ((S_800974DC_0 *)action)->unk_9B = (u8) (((S_800974DC_0 *)action)->unk_9B + 1);
        return;
    }
    case 4:
        ticks_left = ((S_800974DC_0 *)action)->unk_96.s - 1;
        ((S_800974DC_0 *)action)->unk_96.s = ticks_left;
        if ((ticks_left << 0x10) > 0 && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        func_80099F04(actor->unk_5C);
        dungeonStatus.flags = (u16) (dungeonStatus.flags | 0x412);
        ((S_800974DC_0 *)action)->unk_8C = &D_80096384;
        dungeonStatus.unk_0C = 0;
        ((S_800974DC_0 *)action)->unk_96.s = 0U;
        return;
    }
}
