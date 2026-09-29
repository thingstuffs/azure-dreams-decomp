#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_80047784();         /* extern */
s32 func_8009A180();                     /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
M2C_UNK func_800AA258(); /* extern */
s32 func_800AA6B4(); /* extern */
M2C_UNK func_800AA888(); /* extern */
M2C_UNK func_8016FA84();                            /* extern */
M2C_UNK func_8016FCE4(); /* extern */
s32 func_80170224(); /* extern */
M2C_UNK func_8017092C(); /* extern */
M2C_UNK func_80174320();     /* extern */
extern u8 D_80174A2C[];
extern u8 D_80174A64[];


typedef struct S_8016F78C_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    union { u8 n; volatile u8 v; } unk_9A;   /* accessed as both */
} S_8016F78C_0;   /* arg0 in func_8016F78C */

/* Updates actor state, directional animation, and action handling. */
void func_8016F78C(void *actor, M2C_UNK context, void *sprite, EntityRec *entity) {
    u8 stack_pad[8];
    u8 current_state;
    s32 next_state;

    if (dungeonStatus.flags & 0x1000) {
        ((S_8016F78C_0 *)actor)->unk_9A.n = 0xEU;
        func_8016FA84(actor, context, sprite, entity);
        return;
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        if (entity->flags1C & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }
        current_state = ((S_8016F78C_0 *)actor)->unk_9A.v;
        next_state = 0xE;
        if (current_state != next_state) {
            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174A2C) {
                (*(u8 **)((u8 *)sprite + (0x2C))) = D_80174A2C;
                func_80047784(sprite, D_80174A2C[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
            }
            ((S_8016F78C_0 *)actor)->unk_9A.n = next_state;
        }
        ((S_8016F78C_0 *)actor)->unk_98 = (u16) (((S_8016F78C_0 *)actor)->unk_98 & 0xFFF3);
        if ((entity->unk_64 == 0) || (func_800AA6B4(actor, context, sprite, D_80174A64) == 0)) {
            if (entity->flags1C & 0x80000) {
                func_800AA888(actor, context, sprite, entity);
                func_8017092C(actor, context, sprite, entity);
                (*(u8 **)((u8 *)sprite + (0x2C))) = D_80174A2C;
                func_80047784(sprite, D_80174A2C[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
                ((S_8016F78C_0 *)actor)->unk_90 = 0;
                return;
            }
            goto check_action;
        }
    } else {
check_action:
        ((Rec_D_80082E80 *)sprite)->unk_26.as_s8 = func_8009FB34(((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (entity->unk_6D > 0) {
            if (entity->flags1C & 0x20) {
                func_800A9A0C(entity);
                return;
            }
            if (!(entity->unk_46 & 0x8000)) {
                if (!(dungeonStatus.flags & 0x2000) || ((func_8009A180(entity, ((s32)D_800814A8->unk_58) + 0x20) << 0x10) == 0)) {
                    if (D_80013714 & 8) {
                        func_80174320(actor, context, sprite);
                        entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
                        func_800A9A0C(entity);
                        entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
                        return;
                    }
                    if ((func_80170224(actor, context, sprite, 0) << 0x10) != 0) {
                        entity->unk_46 = (u16) (entity->unk_46 | 0x4000);
                        goto finish_action;
                    }
                }
            } else {
finish_action:
                entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
                entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
                func_800A9A0C(entity);
                func_8016FCE4(actor, context, sprite, entity);
            }
        }
    }
}
