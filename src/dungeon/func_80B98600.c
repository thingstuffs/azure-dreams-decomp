#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80171E00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80171E00_3;   /* arg0 in func_80171E00 */


void func_80047784();         /* extern */
typedef struct Ent Ent;
Ent *func_8009C93C(); /* extern */
s32 func_800A0134();                     /* extern */
s32 func_800A04F0();             /* extern */
s32 func_800A2B5C();                          /* extern */
s32 func_800A2CB8();                     /* extern */
s32 func_800C7930(); /* extern */
extern u8 D_80174F28;

/* Check movement conditions and initialize the actor action and directional animation. */
s32 func_80171E00(void *action_state, void *action_ctx, void *sprite, EntityRec *actor) {
    volatile s64 frame_pad;
    u8 *direction_table;
    s32 move_heading;
    u16 flags;

    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    move_heading = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
        actor->facing);
    if ((func_800A2CB8(actor, move_heading) << 0x10) == 0) {
        return 0;
    }
    flags = dungeonStatus.flags;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }
    if ((u32) (((0 - func_800A0134(move_heading, actor)) + 0x3F) & 0xFFFF) >= 0x7FU) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 0x10) != 0) {
        return -1;
    }
    func_800C7930((u8 *)actor - 0x20, action_ctx, 8, 0x300);
    if ((func_800A2B5C(actor) << 0x10) == 0) {
        ((S_80171E00_3 *)action_state)->unk_9A = 0x11;
        ((S_80171E00_3 *)action_state)->unk_9B = 0;
        ((S_80171E00_3 *)action_state)->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        direction_table = &D_80174F28;
        (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
        func_80047784(sprite, direction_table[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        func_8009C93C(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
