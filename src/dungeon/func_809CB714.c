#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172F14_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F14_1;   /* arg0 in func_80172F14 */





extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170E54;
extern s32 D_80173CC4;

/* Updates directional movement, slows it, and settles the object onto its grid tile. */
void func_80172F14(S_80172F14_1 *controller, Rec_D_800E3D7C *motion, Rec_D_80082E80 *entity, void *source)
{
    s16 timer;
    s32 direction;
    s32 speed_limit;
    s32 tracked_object;
    s32 *global_state;

    direction = (((Rec_D_800E3D7C *)source)->unk_6A.as_u16 >> 9) & 7;

    switch (controller->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C.as_s32 =
            *(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 19;
        motion->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 19;
        controller->unk_9B++;

        if (((Rec_D_800E3D7C *)source)->unk_28 == 0) {
            motion->unk_14.as_s32 = 0;
            motion->unk_10.at00_s32.v = 0;
            motion->unk_0C.as_s32 = 0;
            func_800AAA54(controller, motion, entity, &D_80173CC4);
            return;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            controller->unk_96.s = 0;
            controller->unk_9B = 2;
            return;
        }

        timer = 5;
        if (((Rec_D_800E3D7C *)source)->unk_1C.as_s32 & 0x228) {
            timer = 8;
        }
        controller->unk_96.s = timer;

        {
            s32 velocity = motion->unk_0C.as_s32;
            motion->unk_0C.as_s32 = velocity - velocity / 4;
        }
        {
            s32 velocity = motion->unk_10.at00_s32.v;
            motion->unk_10.at00_s32.v = velocity - velocity / 4;
        }
        /* fall through */

    case 1:
        speed_limit = 0x7FFF;
        {
            s32 velocity = motion->unk_0C.as_s32;
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                magnitude = 0 - magnitude;
            }
            if (speed_limit < magnitude) {
                motion->unk_0C.as_s32 = velocity -
                    (*(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 15);
            }
        }
        {
            s32 velocity = motion->unk_10.at00_s32.v;
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                magnitude = 0 - magnitude;
            }
            if (speed_limit < magnitude) {
                motion->unk_10.at00_s32.v = velocity -
                    (*(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 15);
            }
        }
        ASM_KEEP(direction);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

        if (controller->unk_96.s > 0) {
            controller->unk_96.s = controller->unk_96.u - 1;
            goto check_timer;
        }
        if (entity->unk_14.at00_u16.v & 0x6000) {
            controller->unk_96.s = 0;
        }

        if (((Rec_D_800E3D7C *)source)->unk_28 != 0) {
            {
                s32 tile_pos = entity->unk_24 << 6;
                s32 current_pos = motion->unk_00.at02_s16.v - 0x20;

                motion->unk_0C.as_s32 = (tile_pos - current_pos) << 15;
            }
            {
                s32 tile_pos = entity->unk_25 << 6;
                s32 current_pos = motion->unk_04.at02_s16.v - 0x20;

                motion->unk_10.at00_s32.v = (tile_pos - current_pos) << 15;
            }
        } else {
            motion->unk_0C.as_s32 = 0;
            motion->unk_10.at00_s32.v = 0;
        }

check_timer:
        if (controller->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_28 == 0) {
            motion->unk_14.as_s32 = 0;
            func_800AAA54(controller, motion, entity, &D_80173CC4);
            return;
        }
        controller->unk_96.s = 8;
        controller->unk_9B++;
        return;

    case 2:
        if (controller->unk_96.s != 0) {
            {
                s32 tile_pos = entity->unk_24 << 6;
                s32 current_pos = motion->unk_00.at02_s16.v - 0x20;

                motion->unk_0C.as_s32 = (tile_pos - current_pos) << 16;
            }
            {
                s32 tile_pos = entity->unk_25 << 6;
                s32 current_pos = motion->unk_04.at02_s16.v - 0x20;

                motion->unk_10.at00_s32.v = (tile_pos - current_pos) << 16;
            }
        }

        timer = controller->unk_96.u - 1;
        controller->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, entity->unk_24,
                      entity->unk_25);

        global_state = &D_80083460;
        tracked_object = global_state[4];
        if (tracked_object == (s32)((u8 *)source - 0x20)) {
            global_state[4] = tracked_object & 0x7FFFFFFF;
        }
        controller->unk_8C = &D_80170E54;
        return;

    default:
        return;
    }
}
