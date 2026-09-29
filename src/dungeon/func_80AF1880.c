#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_801717F4[];
extern u8 D_801759C0[];


typedef struct S_80173080_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173080_0;   /* arg0 in func_80173080 */



typedef struct S_80173080_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173080_3;   /* arg1 in func_80173080 */

/* Advance the timed action sequence and restore the actor when it finishes. */
void func_80173080(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u16 timer;
    s32 state;

    state = ((S_80173080_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173080_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, actor->facing, 1);
            return;
        }
        ((S_80173080_3 *)motion)->unk_14 = 0;
        ((S_80173080_3 *)motion)->unk_10 = 0;
        ((S_80173080_3 *)motion)->unk_0C = 0;
        ((S_80173080_0 *)action)->unk_96.u = 0;
        ((S_80173080_0 *)action)->unk_9B++;
        return;
    case 1:
        timer = ((S_80173080_0 *)action)->unk_96.u + 1;
        ((S_80173080_0 *)action)->unk_96.u = timer;
        if (((s16)timer == 4) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            u8 *direction_table = D_801759C0;

            (*(u8 * *)((u8 *)sprite + (0x2C))) = direction_table;
            func_80047784(sprite,
                         direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                         0);
            ((S_80173080_0 *)action)->unk_96.u = 0;
            ((S_80173080_0 *)action)->unk_9B++;
            return;
        }
        return;
    case 2:
        timer = ((S_80173080_0 *)action)->unk_96.u + 1;
        ((S_80173080_0 *)action)->unk_96.u = timer;
        if (((s16)timer == 7) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, sprite, actor->facing, 1);
            ((S_80173080_0 *)action)->unk_96.u = 0;
            ((S_80173080_0 *)action)->unk_9B++;
        }
        if (((S_80173080_0 *)action)->unk_96.s == 5) {
            func_800A56E0(0x808);
            return;
        }
        return;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            func_800AD594(actor, 0x100);
            ((S_80173080_0 *)action)->unk_8C = D_801717F4;
            dungeonStatus.unk_0C = 0;
            func_800A4ACC(actor);
            actor->unk_46 &= 0x7FFF;
        }
        return;
    }
}
