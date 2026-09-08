#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


/* Input-only liveness extension (no "+r" rewrite): keeps `var` live to this
 * point WITHOUT redefining it. ASM_KEEP's "+r" adds a second def, which flips
 * gcc 2.8.1 sched2's prologue entry-group ordering (the s3 save/copy pair
 * hoists to the front) — proven on this function (v10 vs v11). Candidate for
 * promotion into common.h as ASM_USE. */
#ifdef NON_MATCHING
#else
#endif

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801714B8;
extern u8 D_801760D4;


typedef struct S_80173730_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173730_0;   /* arg0 in func_80173730 */




/* Updates staged movement toward a target tile and finalizes the action. */
void func_80173730(void *action_arg, void *motion_arg, void *target_arg, void *actor_arg)
{
    register void *action ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *motion ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *target ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *actor;
    u8 state;
    s16 timer;

    action = action_arg;
    motion = motion_arg;
    target = target_arg;
    actor = actor_arg;


    state = ((S_80173730_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        func_800AD4D0(actor);
        ((S_80173730_0 *)action)->unk_96.u = 4;
        ((S_80173730_0 *)action)->unk_9B++;
        if (((Rec_D_800E3D7C *)actor)->unk_28 == 0) {
            goto reset_motion;
        }
        if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        ((S_80173730_0 *)action)->unk_96.u = 0;
        ((S_80173730_0 *)action)->unk_9B = 3;
        return;

    case 1:
        timer = ((S_80173730_0 *)action)->unk_96.u - 1;
        ((S_80173730_0 *)action)->unk_96.u = timer;
        if (timer > 0) {
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
                *(s16 *)(&D_8006CCD8 +
                    ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
                *(s16 *)(&D_8006CCE8 +
                    ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
            *(s16 *)(&D_8006CCD8 +
                ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            *(s16 *)(&D_8006CCE8 +
                ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
        ((S_80173730_0 *)action)->unk_96.u = 12;
        ((S_80173730_0 *)action)->unk_9B++;
        return;

    case 2:
        if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
            goto update_motion;
        }
reset_motion:
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800AAA54(action, motion, target, &D_801760D4);
        return;

update_motion:
        {
            s16 motion_timer = ((S_80173730_0 *)action)->unk_96.s;

            if (motion_timer != 0) {
                {
                    s32 target_x = ((Rec_D_80082E80 *)target)->unk_24 << 6;
                    s32 current_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;

                    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
                        ((target_x - current_x) << 16) / motion_timer;
                }
                {
                    s32 target_y = ((Rec_D_80082E80 *)target)->unk_25 << 6;
                    s32 current_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;

                    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = ((target_y - current_y) << 16)
                        / ((S_80173730_0 *)action)->unk_96.s;
                }
            }
        }
        {
            u16 countdown = ((S_80173730_0 *)action)->unk_96.u;

            ((S_80173730_0 *)action)->unk_96.u = countdown - 1;
            if ((countdown << 16) > 0) {
                return;
            }
        }
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        ((S_80173730_0 *)action)->unk_9B++;
        return;

    case 3:
        {
            s32 *tracking_data;
            s32 entity_addr;

            ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)target)->unk_24,
                ((Rec_D_80082E80 *)target)->unk_25);
            tracking_data = &D_80083460;
            entity_addr = *(s32 *)((u8 *)tracking_data + 0x10);
            if (entity_addr == (s32)((u8 *)actor - 0x20)) {
                *(s32 *)((u8 *)tracking_data + 0x10) = entity_addr & 0x7FFFFFFF;
            }
            ((S_80173730_0 *)action)->unk_8C = &D_801714B8;
            ASM_USE(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        }
        return;
    }
}
