#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_8008ACDC_arg0.h"

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008D94C(void *, void *, void *, void *);
extern s32 func_80094F74(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern u16 D_80013714;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD050[];

typedef struct S_8008DBE8_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
} S_8008DBE8_0;   /* status in func_8008DBE8 */

typedef struct S_8008DBE8_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_8008DBE8_5;   /* late_status in func_8008DBE8 */

/* Move toward the target tile, update the animation, and finish when the timer expires. */
void func_8008DBE8(void *entity, void *motion, void *sprite, void *facing) {
    void *status = &D_80083460;
    void *late_status;
    u32 status_page;
    s32 frames_left;
    s32 x_velocity;
    s32 y_position;
    s32 move_frames;
    s16 timer;
    u16 flags;

    if (((S_8008DBE8_0 *)status)->unk_02 & 0x80) {
        ((S_8008DBE8_0 *)status)->unk_04 = 0;
    }

    timer = ((S_8008DBE8_0 *)status)->unk_04;
    if (timer != 0) {
        x_velocity =
            ((((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16) -
             ((Rec_D_800E3D7C *)motion)->unk_00.at00_s32.v) /
            timer;
        y_position = ((Rec_D_800E3D7C *)motion)->unk_04.at00_s32.v;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = x_velocity;
        move_frames = ((S_8008DBE8_0 *)status)->unk_04;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            ((((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16) -
             y_position) /
            move_frames;
    }

    if (((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 & 0x100) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        frames_left = ((S_8008DBE8_0 *)status)->unk_04;
        if (D_80013714 & 8) {
            if (frames_left != 3) {
                ASM_SCHED_BARRIER(); /* MATCH: Keep the frames_left checks separate and jump to the shared update. */
                goto continue_update;
            }
        } else if (frames_left != 6) {
            goto continue_update;
        }

        func_8008D94C(entity, motion, sprite, facing);
        return;
    }

continue_update:
    flags = ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2;
    if (!(flags & 0x10)) {
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_800DD050) {
            ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 = flags | 1;
            *(u8 **)((u8 *)sprite + 0x2C) = D_800DD050;
            func_80048A44(
                sprite,
                D_800DD050[((D_80083228 + ((Rec_D_800E3D7C *)facing)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0,
                1);
        }
    }

    status_page = 0x80080000;
    ASM_KEEP(status_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    late_status = (void *)(status_page + 0x3460);
    timer = ((S_8008DBE8_5 *)late_status)->unk_04 - 1;
    ((S_8008DBE8_5 *)late_status)->unk_04 = timer;
    if (timer > 0) {
        return;
    }

    ((S_8008DBE8_5 *)late_status)->unk_04 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x4000;
    if ((s16)func_80094F74(entity, motion, sprite, facing) > 0) {
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_8C.as_s32 = (s32)&D_8008ACDC;
    }
}
