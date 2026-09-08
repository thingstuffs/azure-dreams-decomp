#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80174C44_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174C44_0;   /* arg0 in func_80174C44 */




typedef struct S_80174C44_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80174C44_4;   /* global in func_80174C44 */



extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801724BC[];
extern u8 D_80175E3C[];
extern u8 D_80175E44[];
extern u8 D_80175E4C[];

extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

/* Updates timed movement toward the entity's tile and selects the next behavior. */
void func_80174C44(S_80174C44_0 *controller, Rec_D_800E3D7C *transform, Rec_D_80082E80 *entity, void *actor)
{
    s32 state;
    s32 actor_kind;
    s16 timer;
    u16 old_timer;
    s32 axis_pos;
    s32 axis_step;
    S_80174C44_4 *tracking;

    state = controller->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(actor);
    controller->unk_96.s = 6;
    controller->unk_9B = controller->unk_9B + 1;
    if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
        goto state_0_active;
    }

    transform->unk_14.as_s32 = 0;
    transform->unk_10.at00_s32.v = 0;
    transform->unk_0C.as_s32 = 0;
    actor_kind = ((Rec_D_800E3D7C *)actor)->unk_48.at00_u8.v;
    if (actor_kind == 14) {
        goto kind_14;
    }
    if (actor_kind < 15) {
        goto kind_less_15;
    }
    if (actor_kind != 15) {
        goto done;
    }
    goto kind_15_from_state_0;

state_0_active:
    if ((entity->unk_14.at00_u16.v & 0x8000) == 0) {
        goto done;
    }
    controller->unk_96.s = 0;
    controller->unk_9B = 3;
    goto done;

state_1:
    timer = (u16)controller->unk_96.u - 1;
    controller->unk_96.s = timer;
    if (timer <= 0) {
        goto state_1_nonpositive;
    }

    transform->unk_0C.as_s32 =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    transform->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    goto done;

state_1_nonpositive:
    if (timer != 0) {
        goto done;
    }
    transform->unk_0C.as_s32 =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    transform->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    controller->unk_96.s = 12;
    controller->unk_9B = controller->unk_9B + 1;
    goto done;

state_2:
    if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
        goto state_2_active;
    }

    transform->unk_14.as_s32 = 0;
    transform->unk_10.at00_s32.v = 0;
    transform->unk_0C.as_s32 = 0;
    actor_kind = ((Rec_D_800E3D7C *)actor)->unk_48.at00_u8.v;
    if (actor_kind == 14) {
        goto kind_14;
    }
    if (actor_kind >= 15) {
        goto kind_at_least_15;
    }

kind_less_15:
    if (actor_kind == 13) {
        goto kind_13;
    }
    goto done;

kind_at_least_15:
    if (actor_kind == 15) {
        goto kind_15;
    }
    goto done;

kind_13:
    func_800AAA54(controller, transform, entity, D_80175E3C);
    goto done;

kind_14:
    func_800AAA54(controller, transform, entity, D_80175E44);
    goto done;

kind_15:
    func_800AAA54(controller, transform, entity, D_80175E4C);
    goto done;

kind_15_from_state_0:
    func_800AAA54(controller, transform, entity, D_80175E4C);
    goto done;

state_2_active:
    timer = controller->unk_96.s;
    if (timer != 0) {
        axis_step = entity->unk_24;
        axis_pos = transform->unk_00.at02_s16.v;
        axis_step <<= 6;
        axis_pos -= 0x20;
        axis_step -= axis_pos;
        axis_step = (axis_step << 16) / timer;
        axis_pos = transform->unk_04.at02_s16.v;
        transform->unk_0C.as_s32 = axis_step;
        axis_pos -= 0x20;
        axis_step = (entity->unk_25 << 6) - axis_pos;
        axis_step = (axis_step << 16) / controller->unk_96.s;
        transform->unk_10.at00_s32.v = axis_step;
    }

    old_timer = controller->unk_96.u;
    controller->unk_96.s = old_timer - 1;
    if ((s32)(old_timer << 16) > 0) {
        goto done;
    }
    transform->unk_14.as_s32 = 0;
    transform->unk_10.at00_s32.v = 0;
    transform->unk_0C.as_s32 = 0;
    controller->unk_9B = controller->unk_9B + 1;
    goto done;

state_3:
    transform->unk_14.as_s32 = 0;
    transform->unk_10.at00_s32.v = 0;
    transform->unk_0C.as_s32 = 0;
    func_800A2B04(transform, entity->unk_24, entity->unk_25);
    tracking = &D_80083460;
    if (tracking->unk_10 == (s32)actor - 0x20) {
        tracking->unk_10 &= 0x7FFFFFFF;
    }
    controller->unk_8C = D_801724BC;

done:
    return;
}
