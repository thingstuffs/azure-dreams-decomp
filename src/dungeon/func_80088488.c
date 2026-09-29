#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_8008ACDC_arg0.h"

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008D94C(void *, void *, void *, void *);
extern s32 func_80094F74(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern s32 D_8008ACDC;
extern u8 D_800DD050[];

typedef struct S_8008DBE8_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_8008DBE8_5;   /* late_status in func_8008DBE8 */

/* Move toward the target tile, update the animation, and finish when the timer expires. */
void func_8008DBE8(void *entity, EntityRec *motion, void *sprite, EntityRec *facing) {
    void *late_status;
    u32 status_page;
    s32 frames_left;
    s32 x_velocity;
    s32 y_position;
    s32 move_frames;
    s16 timer;
    u16 flags;

    if (dungeonStatus.flags & 0x80) {
        dungeonStatus.unk_04 = 0;
    }

    timer = dungeonStatus.unk_04;
    if (timer != 0) {
        x_velocity =
            ((((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16) -
             motion->x.v) /
            timer;
        y_position = motion->y.v;
        motion->unk_0C = x_velocity;
        move_frames = dungeonStatus.unk_04;
        motion->unk_10 =
            ((((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16) -
             y_position) /
            move_frames;
    }

    if (((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 & 0x100) {
        frames_left = dungeonStatus.unk_04;
        if (((*(u16 *)0x80013714 & 8) && frames_left == 3) ||
            (!(*(u16 *)0x80013714 & 8) && frames_left == 6)) {
            func_8008D94C(entity, motion, sprite, facing);
            return;
        }
    }

continue_update:
    flags = ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2;
    if (!(flags & 0x10)) {
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_800DD050) {
            ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 = flags | 1;
            *(u8 **)((u8 *)sprite + 0x2C) = D_800DD050;
            func_80048A44(
                sprite,
                D_800DD050[((gameWork.view.viewAngle + facing->facing + 0x100) >> 9) & 7],
                0,
                1);
        }
    }

    status_page = (u32)&dungeonStatus.unk_00;
    late_status = (void *)status_page;
    timer = ((S_8008DBE8_5 *)late_status)->unk_04 - 1;
    ((S_8008DBE8_5 *)late_status)->unk_04 = timer;
    if (timer > 0) {
        return;
    }

    ((S_8008DBE8_5 *)late_status)->unk_04 = 0;
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x4000;
    if ((s16)func_80094F74(entity, motion, sprite, facing) > 0) {
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_8C.as_s32 = (s32)&D_8008ACDC;
    }
}
