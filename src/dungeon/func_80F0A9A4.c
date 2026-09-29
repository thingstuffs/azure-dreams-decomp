#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801721A4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_801721A4_1;   /* owner in func_801721A4 */

typedef struct S_801721A4_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_801721A4_2;   /* part in func_801721A4 */



extern void func_80047784(void *, s32, s32);
extern s32 func_800A2BDC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);

extern u8 D_80173D88[9];

/* Start the actor's reaction step: clear its 0x71 busy bit and, when the global 0x2000 mode is off and the ready query says 0, randomise its facing, arm state 0x17, cue 0x811 and point the part at the direction table. */
void func_801721A4(S_801721A4_1 *owner, void *unused, S_801721A4_2 *part, EntityRec *actor)
{

    actor->unk_71 &= 0x7F;
    if (!(dungeonStatus.flags & 0x2000) &&
        ((func_800A2BDC(actor) << 16) == 0)) {
        if (((u32)actor->flags1C) & 0x400) {
            s32 link;

            link = actor->flags14;
            if (!(link & 0x80000000)) {
                link |= 0x80000000;
                actor->flags14 = link;
                (*(u16 *)&actor->facing) +=
                    (func_800A6D30() & 7) << 9;
            }
        }

        owner->unk_9A = 0x17;
        owner->unk_8C = 0;
        owner->unk_9B = 0;
        owner->unk_A6 = 1;
        owner->unk_96 = 0;

        part->unk_14 |= 0xC;
        part->unk_12 -= 0x80;
        dungeonStatus.unk_0A++;
        (*(u8 *)&actor->unk_6D)--;
        part->unk_2C = D_80173D88;
        part->unk_0C = 0xFFFFFF;
        part->unk_10 = 0x60;
        func_800A56E0(0x811);
        func_80047784(part,
            part->unk_2C[
                ((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }
}
