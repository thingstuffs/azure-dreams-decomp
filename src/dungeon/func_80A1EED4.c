#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801726D4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801726D4_0;   /* arg0 in func_801726D4 */





extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern void *D_800E3DE8;
extern s32 D_80170E84;
extern u8 D_80174840[];

/* Advance the actor animation action and restore actor state when it finishes. */
void func_801726D4(void *action, s32 actor_id, void *sprite, void *actor) {
    s32 state;

    state = ((S_801726D4_0 *)action)->unk_9B;
    ((S_801726D4_0 *)action)->unk_96--;
    switch (state) {
        case 0:
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
                ((S_801726D4_0 *)action)->unk_9B = 0xFF;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
                func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
                return;
            }
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174840;
            func_80047784(sprite,
                D_80174840[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_801726D4_0 *)action)->unk_9B++;
            return;

        case 1:
            if (((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 4) &&
                 (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
                (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
                func_800A56E0(0x814);
                func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
                ((S_801726D4_0 *)action)->unk_9B = 0xFF;
            }
            return;

        case 0xFF:
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
                func_800A2B04(actor_id, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
                func_800AD594(actor, 0x100);
                ((S_801726D4_0 *)action)->unk_8C = &D_80170E84;
                dungeonStatus.unk_0C = 0;
                func_800A4ACC(actor);
                if (((EntityRec *)actor)->unk_6D == 0) {
                    ((EntityRec *)actor)->unk_46 &= 0x7FFF;
                    return;
                }
                D_800E3DE8 = (u8 *)actor - 0x20;
            }
            return;
    }
}
