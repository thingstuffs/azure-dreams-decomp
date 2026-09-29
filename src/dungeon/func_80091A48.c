#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct { u8 pad0[2]; u16 field2; s16 field4; u8 pad6[6]; } D_80083460_t;
extern u8 D_80096384[];
extern void func_80095DD0(void *, void *, void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);

/* Advances timed movement toward a destination and handles completion. */
void func_800971A8(Rec_func_8008ACDC_arg0 *action, EntityRec *motion, Rec_D_80082E80 *destination, EntityRec *actor) {
    u16 delay;
    u8 state;
    s32 vertical_speed;
    state = action->unk_9B.as_u8;
    switch (state) {
    case 0:
    case 8:
    case 10:
        delay = action->unk_96.as_u16 - 1;
        action->unk_96.as_u16 = delay;
        if ((s16)delay > 0)
            return;
        state = action->unk_9B.as_u8;
        vertical_speed = 8;
        if (state == 0) {
            vertical_speed = 0xFFF00000;
        } else if (state == vertical_speed) {
            vertical_speed = 0xFFF80000;
        } else {
            vertical_speed = 0xFFEC0000;
        }
        motion->flags14 = vertical_speed;
        func_80099F70(actor->unk_5C);
        func_80099F04(actor->unk_5C);
        dungeonStatus.flags |= 0x812;
        action->unk_98 &= 0xFFF3;
        action->unk_9B.as_u8++;
        func_800A56E0(0x50A);
        return;
    case 1:
    case 9:
    case 11:
        if (dungeonStatus.unk_04 != 0) {
            s32 target_x, current_x, current_y;
            target_x = destination->unk_24 << 6;
            current_x = motion->x.w.i - 0x20;
            motion->unk_0C = ((target_x - current_x) << 16) / dungeonStatus.unk_04;
            current_y = motion->y.w.i - 0x20;
            motion->unk_10 = (((destination->unk_25 << 6) - current_y) << 16) / dungeonStatus.unk_04;
        }
        dungeonStatus.unk_04--;
        if (dungeonStatus.unk_04 > 0)
            return;
        dungeonStatus.unk_04 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);
        if (action->unk_9B.as_u8 >= 10) {
            dungeonStatus.unk_04 = 1;
            action->unk_9B.as_u8++;
            return;
        }
        if (action->unk_100 >= 0) {
            func_80095DD0(action, motion, destination, actor);
            return;
        }
        action->unk_8C.as_pv = D_80096384;
        return;
    case 12:
        if (destination->unk_14.at00_u16.v & 0x6000) {
            dungeonStatus.unk_04 = 0;
            if (action->unk_100 >= 0) {
                func_80095DD0(action, motion, destination, actor);
                return;
            }
            action->unk_8C.as_pv = D_80096384;
        }
        return;
    default:
        return;
    }
}
