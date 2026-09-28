#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_801764A0[];
s16 func_800A2B5C();                          /* extern */
s32 func_800A4ACC();                      /* extern */
s32 func_800C7930(); /* extern */


typedef struct S_8017294C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8017294C_1;   /* arg0 in func_8017294C */


/* Attempt an actor action and initialize its state and directional animation on success. */
void func_8017294C(S_8017294C_1 *action_state, M2C_UNK action_ctx, Rec_D_80082E80 *sprite, void *actor) {
    ((EntityRec *)actor)->unk_71 = (u8) (((EntityRec *)actor)->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_ctx, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            action_state->unk_9A = 0x19;
            action_state->unk_8C = 0;
            action_state->unk_9B = 0;
            sprite->unk_2C.as_pu8 = D_801764A0;
            func_80047784(sprite, D_801764A0[((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7], 0);
            func_800A4ACC(actor);
            ((EntityRec *)actor)->unk_6D = (u8) (((u8)((EntityRec *)actor)->unk_6D) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
        }
    }
}
