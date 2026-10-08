#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);


extern s32 D_8015EF68;
extern u8 D_80161FB8[8];

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_800DA840();


typedef struct S_801729D4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801729D4_0;   /* arg0 in func_801609D4 */

typedef struct S_801729D4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801729D4_2_pre;   /* the 0x14 bytes before root in func_801609D4, addressed as root[-1] */

typedef struct S_801729D4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801729D4_3;   /* source in func_801609D4 */

typedef struct S_801729D4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801729D4_4;   /* arg2 in func_801609D4 */


/* Advance the actor animation state and reset movement when it finishes. */
void func_801609D4(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    u16 position[3];
    u8 *animation;
    s16 reuse_target;
    s32 reuse_test;
    s32 state;
    s32 anim_kind;
    void *target_root;
    void *target_source;
    void *new_target;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;

    state = ((S_801729D4_0 *)action)->unk_9B;
    reuse_target = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            anim_kind = (actor->unk_46 & 0x3FFF) - 1;
            switch (anim_kind) {
            case 6:
                reuse_target = 1;
                /* fall through */
            case 2:
                animation = (u8 *)actor + 0xE;
                break;
            case 5:
                reuse_target = 1;
                /* fall through */
            case 1:
                animation = (u8 *)actor + 0xB;
                break;
            case 4:
                reuse_target = 1;
                /* fall through */
            case 0:
                animation = (u8 *)actor + 8;
                break;
            case 3:
            default:
                animation = 0;
                break;
            }
        } else {
            anim_kind = actor->unk_46 & 0x3FFF;
            switch (anim_kind) {
            case 3:
                animation = (u8 *)actor + 0xE;
                break;
            case 2:
                animation = (u8 *)actor + 0xB;
                break;
            case 1:
                animation = (u8 *)actor + 8;
                break;
            default:
                animation = 0;
                break;
            }
        }

        if (*animation != 0) {
            ((S_801729D4_0 *)action)->unk_98 &= 0xFF7F;
            reuse_test = reuse_target;
            if (reuse_test != 0) {
                target_root = D_800814A8;
                actor->target = target_root;
                target_source = ((S_801729D4_2_pre *)target_root)[-1].unk_00;
                actor->unk_72 = ((S_801729D4_3 *)target_source)->unk_24;
                actor->unk_73 = ((S_801729D4_3 *)target_source)->unk_25;
            } else {
                new_target = func_800A05A4(
                    actor, ((S_801729D4_4 *)sprite)->unk_24, ((S_801729D4_4 *)sprite)->unk_25,
                    actor->facing, 0x10);
                actor->target = new_target;
                abs_x = abs(actor->unk_72);
                abs_y = abs(actor->unk_73);
                actor->unk_72 = abs_x;
                actor->unk_73 = abs_y;
            }
            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (func_800A94A0(actor, animation, reuse_target, (u8 *)action + 0x98) != 0) {
                ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
                func_800A56E0(0x703);
                func_800DA840(position, (s16)((*animation - 1) % 3));
                ((S_801729D4_0 *)action)->unk_9B++;
                return;
            }
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((S_801729D4_4 *)sprite)->unk_24, ((S_801729D4_4 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + (0xA6)))--;
        func_800A4ACC(actor);
        (*(u8 *)&actor->unk_6D)--;
        ((S_801729D4_0 *)action)->unk_8C = &D_8015EF68;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_801729D4_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_801729D4_0 *)action)->unk_9B++;

        /* fall through */
    case 2:
        if ((((S_801729D4_4 *)sprite)->unk_04 == 8 &&
             (((S_801729D4_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_801729D4_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_801729D4_4 *)sprite)->unk_14 |= 0x800;
            ((S_801729D4_0 *)action)->unk_96 = 3;
            ((S_801729D4_0 *)action)->unk_98 |= 0x80;
        }
        ((S_801729D4_0 *)action)->unk_96--;
        if ((s16)((S_801729D4_0 *)action)->unk_96 <= 0) {
            ((S_801729D4_0 *)action)->unk_96 = 0;
            ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
        }
        if (((S_801729D4_4 *)sprite)->unk_14 & 0xE000) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((S_801729D4_4 *)sprite)->unk_24, ((S_801729D4_4 *)sprite)->unk_25);
            if (((S_801729D4_4 *)sprite)->unk_2C != D_80161FB8) {
                (*(void * *)((u8 *)sprite + (0x2C))) = D_80161FB8;
                func_80047784(
                    sprite,
                    D_80161FB8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
            if (((s32)dungeonStatus.unk_0C) == 0) {
                dungeonStatus.unk_0A--;
                ((S_801729D4_4 *)sprite)->unk_14 &= 0xF7FF;
                ((S_801729D4_0 *)action)->unk_8C = &D_8015EF68;
                func_800A4ACC(actor);
                if (actor->unk_6D > 0) {
                    (*(u8 *)&actor->unk_6D)--;
                }
                actor->unk_73 = 0;
                actor->unk_72 = 0;
                actor->unk_46 &= 0x7FFF;
                func_800A56E0(0xB4);
            }
        }

        return;
    }
}
