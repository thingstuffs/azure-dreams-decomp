#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801729A8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801729A8_0;   /* arg0 in func_801729A8 */


typedef struct S_801729A8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801729A8_3;   /* arg1 in func_801729A8 */


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_8017102C[];
extern u8 D_801752DC[];

/* Advances a timed actor animation and performs its completion cleanup. */
void func_801729A8(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 next_state;
    s32 start_state;
    u16 timer;

    state = ((S_801729A8_0 *)action)->unk_9B;
    start_state = 1;
    switch (state) {
    case 0:
        ((S_801729A8_0 *)action)->unk_9B = start_state;
                        /* fall through */
    case 1:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_801729A8_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
            return;
        }

        ((S_801729A8_3 *)motion)->unk_14 = 0;
        ((S_801729A8_3 *)motion)->unk_10 = 0;
        ((S_801729A8_3 *)motion)->unk_0C = 0;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801752DC;
        func_80047784(sprite,
            D_801752DC[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        next_state = ((S_801729A8_0 *)action)->unk_9B;
        ((S_801729A8_0 *)action)->unk_96.s = 0;
        next_state++;
        ((S_801729A8_0 *)action)->unk_9B = next_state;
        return;
    case 2:
        timer = ((S_801729A8_0 *)action)->unk_96.s + 1;
        ((S_801729A8_0 *)action)->unk_96.s = timer;
        if ((s16)timer == 7 || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
        }
        if (((S_801729A8_0 *)action)->unk_96.u == 6) {
            func_800A56E0(0x808);
        }
        if (((S_801729A8_0 *)action)->unk_96.u == 8) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        }
        if (((S_801729A8_0 *)action)->unk_96.u == 15 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            next_state = ((S_801729A8_0 *)action)->unk_9B;
            next_state++;
            ((S_801729A8_0 *)action)->unk_9B = next_state;
        }
        return;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            func_800AD594(actor, 0x100);
            ((S_801729A8_0 *)action)->unk_8C = D_8017102C;
            dungeonStatus.unk_0C = 0;
            func_800A4ACC(actor);
            ((EntityRec *)actor)->unk_46 &= 0x7FFF;
        }
        return;
    default:
        return;
    }
}
