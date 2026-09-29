#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


extern void func_80047784();
extern s32 func_800A2BDC();

extern u8 D_80176670[16];


typedef struct S_80173C40_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173C40_2;   /* arg0 in func_80173C40 */

/* Initialize the entity action and select its directional animation when ready. */
void func_80173C40(void *action, void *unused, void *animation, EntityRec *entity) {

    if (dungeonStatus.flags & 0x2000) {
        entity->unk_71 &= 0x7F;
        return;
    }

    if ((func_800A2BDC(entity) << 16) == 0) {
        s32 direction;

        ((S_80173C40_2 *)action)->unk_9A = 0x17;
        ((S_80173C40_2 *)action)->unk_9B = 0;
        ((S_80173C40_2 *)action)->unk_8C = 0;
        *(u8 **)((u8 *)animation + 0x2C) = D_80176670;

        direction = ((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
        func_80047784(animation, D_80176670[direction], 0);

        ((S_80173C40_2 *)action)->unk_96 = 0;
        entity->flags1C |= 0x10000000;
        dungeonStatus.unk_0A++;
        entity->unk_46 &= 0x7FFF;
    }
}
