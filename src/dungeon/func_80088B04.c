#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"






M2C_UNK func_80048A44(); /* extern */
s32 func_80094F74();  /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD040[];
extern u8 D_800DD058[];

/* Updates movement toward a target tile and advances the actor's animation state. */
void func_8008E264(void *actor, EntityRec *motion, void *sprite, EntityRec *model) {
    s16 ticks_left;
    s32 coord_or_ticks;
    s32 motion_value;
    u32 state_index;
    u8 state;
    s32 launch_state;

    state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8;
    state_index = state;
    switch (state_index) {
    case 0:
    case 8:
    case 10:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            launch_state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8;
            if (launch_state == 0) {
                motion->flags14 = 0xFFF00000;
            } else {
                motion_value = 8;
                if (launch_state != motion_value) {
                    motion_value = 0xFFEC0000;
                } else {
                    motion_value = 0xFFF80000;
                }
                motion->flags14 = motion_value;
            }
            func_80099F70(model->unk_5C);
            func_80099F04(model->unk_5C);
            dungeonStatus.flags = (u16) (dungeonStatus.flags | 0x812);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_98 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_98 & 0xFFF3);
            (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD040;
            func_80048A44(sprite, D_800DD040[((s32) (gameWork.view.viewAngle + model->facing + 0x100) >> 9) & 7], 0, 1);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 + 1);
            func_800A56E0(0x50A);
            return;
        }
    case 2: case 3: case 4: case 5: case 6: case 7:
    default:
        return;
    case 1:
    case 9:
    case 11:
        if (dungeonStatus.unk_04 != 0) {
            motion_value = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            coord_or_ticks = motion->x.w.i;
            coord_or_ticks -= 0x20;
            motion_value = (motion_value - coord_or_ticks) << 0x10;
            motion->unk_0C = motion_value / dungeonStatus.unk_04;
            coord_or_ticks = motion->y.w.i;
            motion_value = ((Rec_D_80082E80 *)sprite)->unk_25;
            coord_or_ticks -= 0x20;
            motion_value <<= 6;
            motion_value -= coord_or_ticks;
            coord_or_ticks = dungeonStatus.unk_04;
            motion_value <<= 0x10;
            motion->unk_10 = motion_value / coord_or_ticks;
        }
        ticks_left = (u16) dungeonStatus.unk_04 - 1;
        dungeonStatus.unk_04 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            dungeonStatus.unk_04 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            if ((u8) ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 >= 0xAU) {
                (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD058;
                func_80048A44(sprite, D_800DD058[((s32) (gameWork.view.viewAngle + model->facing + 0x100) >> 9) & 7], 0, 1);
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 + 1);
                dungeonStatus.unk_04 = 1;
                return;
            }
            if ((func_80094F74(actor, motion, sprite, model) << 0x10) > 0) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = &D_8008ACDC;
            }
            return;
        }
        return;
    case 12:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            dungeonStatus.unk_04 = 0;
            if ((func_80094F74(actor, motion, sprite, model) << 0x10) > 0) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = &D_8008ACDC;
            }
            return;
        }
        return;
    }
}
