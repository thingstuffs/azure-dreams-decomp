#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"


typedef struct S_809A0A34_1 {
    u8 pad_00[0x98];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_809A0A34_1;   /* arg0 in func_809A0A34 */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u8 D_80175E70;

/* Clears the actor flag and conditionally updates its state and directional animation. */
void func_809A0A34(void *controller, M2C_UNK action_context, void *sprite, void *actor) {
    ((EntityRec *)actor)->unk_71 = (u8) (((EntityRec *)actor)->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((S_809A0A34_1 *)controller)->unk_9A = 0x17;
            (*(s32 *)((u8 *)controller + 0x8C)) = 0;
            ((S_809A0A34_1 *)controller)->unk_9B = 0;
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175E70;
            func_80047784(sprite, *((((s32) (gameWork.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7) + &D_80175E70), 0);
            ((EntityRec *)actor)->unk_6D = (u8) (((u8)((EntityRec *)actor)->unk_6D) - 1);
            ((S_809A0A34_1 *)controller)->unk_98 = (u16) (((S_809A0A34_1 *)controller)->unk_98 | 8);
            func_8009C93C(actor, sprite, ((EntityRec *)actor)->facing, 1, 0);
            ((EntityRec *)actor)->unk_84 = 0x7C;
            ((EntityRec *)actor)->unk_85 = 0;
        }
    }
}
