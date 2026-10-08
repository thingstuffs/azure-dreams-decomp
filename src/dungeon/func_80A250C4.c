#include "common.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern u8 D_8016E0FC[];
extern int abs(int);

typedef struct S_801728C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    union { u16 s; u16 u; } unk_98;   /* accessed as both */
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801728C4_0;   /* arg0 in func_8016C8C4 */

typedef struct S_801728C4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728C4_2_pre;   /* the 0x14 bytes before mode_global in func_8016C8C4, addressed as mode_global[-1] */

typedef struct S_801728C4_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728C4_3_pre;   /* the 0x14 bytes before parent in func_8016C8C4, addressed as parent[-1] */

typedef struct S_801728C4_3 {
    u8 pad_00[0xC];
    union { void * s; s32 u; } unk_0C;   /* accessed as both */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
} S_801728C4_3;   /* parent in func_8016C8C4 */

typedef struct S_801728C4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_801728C4_4;   /* arg2 in func_8016C8C4 */


typedef struct S_801728C4_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_801728C4_6;   /* global in func_8016C8C4 */

typedef struct S_801728C4_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801728C4_7;   /* entity in func_8016C8C4 */

typedef struct S_801728C4_8 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    s32 unk_A4;
} S_801728C4_8;   /* part in func_8016C8C4 */

typedef struct S_801728C4_10 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801728C4_10;   /* ((S_801728C4_7 *)entity)->unk_08 in func_8016C8C4 */


extern u8 D_8016AE84[];
extern u8 D_8016E820[];
extern u8 D_8016E850[];

extern s32 func_8003F270();
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80045340(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void func_800DA840(void *payload, s16 value_scale);
extern void func_8016E0FC(void);

/* Updates actor action states, movement, and impact effects. */
void func_8016C8C4(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    u16 pos[3];
    u16 delta[3];
    s32 state;
    u32 anim_id;
    u32 action_kind;
    u32 dispatch_index;
    s16 special_mode;
    s32 special_test;
    s32 particle_count;
    s32 current_state;
    u8 *anim;
    u16 timer;
    void *effect;
    void *effect_state;
    void *target_sprite;
    void (*callback)(void);
    void *player_state;
    void *special_target;
    s32 offset_x;
    s32 abs_x;
    s32 abs_y;
    s32 offset_y;
    s32 flags;

    special_mode = 0;
    state = ((S_801728C4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            action_kind = actor->unk_46 & 0x3FFF;
            dispatch_index = action_kind - 1;
            switch (dispatch_index) {
            case 6:
                special_mode = 1;
            case 2:
                anim = (u8 *)actor + 0xE;
                break;
            case 5:
                special_mode = 1;
            case 1:
                anim = (u8 *)actor + 0xB;
                break;
            case 4:
                special_mode = 1;
            case 0:
                anim = (u8 *)actor + 8;
                break;
            default:
                anim = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                anim = (u8 *)actor + 0xE;
                break;
            case 2:
                anim = (u8 *)actor + 0xB;
                break;
            case 1:
                anim = (u8 *)actor + 8;
                break;
            default:
                anim = 0;
                break;
            }
        }
        if (*anim != 0) {
            ((S_801728C4_0 *)action)->unk_98.s &= 0xFF7F;
            special_test = special_mode;
            if (special_test != 0) {
                special_target = ((u8 *)D_800814A8);
                actor->target = special_target;
                target_sprite = ((S_801728C4_2_pre *)special_target)[-1].unk_00;
                actor->unk_72 = ((S_801728C4_3 *)target_sprite)->unk_24;
                actor->unk_73 = ((S_801728C4_3 *)target_sprite)->unk_25;
            } else {
                anim_id = *anim;
                if (D_8006DE24[anim_id].kind == 2) {
                    target_sprite = actor->target;
                    if (target_sprite != 0) {
                        target_sprite = ((S_801728C4_3_pre *)target_sprite)[-1].unk_00;
                        actor->unk_72 = ((S_801728C4_3 *)target_sprite)->unk_24;
                        actor->unk_73 = ((S_801728C4_3 *)target_sprite)->unk_25;
                    }
                } else {
                    actor->target = func_800A05A4(
                        actor, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25,
                        actor->facing, 0x10);
                    abs_x = abs(actor->unk_72);
                    abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }

            pos[0] = ((u16)motion->x.w.i);
            pos[1] = ((u16)motion->y.w.i);
            pos[2] = ((u16)motion->z.w.i);
            if (func_800A94A0(actor, anim, special_mode, (u8 *)action + 0x98) != 0) {
                ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
                func_800A56E0(0x703);
                func_800DA840(pos, (s16)((*anim - 1) % 3));
                current_state = ((S_801728C4_0 *)action)->unk_9B;
                ((S_801728C4_0 *)action)->unk_96 = 30000;
                ((S_801728C4_0 *)action)->unk_9B = current_state + 1;
                return;
            }
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25);
            player_state = ((u8 *)D_800814A8);
            dungeonStatus.unk_0C = 0;
            ((S_801728C4_6 *)player_state)->unk_A6--;
            func_800A4ACC(actor);
            (*(u8 *)&actor->unk_6D)--;
            ((S_801728C4_0 *)action)->unk_8C = D_8016AE84;
            actor->unk_73 = 0;
            actor->unk_72 = 0;
            actor->unk_46 &= 0x7FFF;
            return;
        }
    case 1:
        if (func_8003F270() != 0) {
            ((S_801728C4_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_801728C4_0 *)action)->unk_9B++;
    case 2:
        if (func_8003DE58(((S_801728C4_4 *)sprite)->unk_08, sprite, delta, 0) == 0) {
            delta[0] = delta[1] = delta[2] = 0;
        }
        if ((((S_801728C4_4 *)sprite)->unk_04 == 3 && (((S_801728C4_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_801728C4_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_801728C4_4 *)sprite)->unk_14 |= 0x800;
            ((S_801728C4_0 *)action)->unk_96 = 6;
            ((S_801728C4_0 *)action)->unk_98.u |= 0x80;
            if (!(((S_801728C4_4 *)sprite)->unk_14 & 0x8000)) {
                flags = ((S_801728C4_0 *)action)->unk_98.s;
                ((S_801728C4_0 *)action)->unk_98.u = flags | 0x8000;
                effect = func_8003FD64(0x112, ((u8 *)&D_80083498));
                if (effect != 0) {
                    func_8004491C(effect, func_80045340);
                    effect_state = (u8 *)effect + 0x20;
                    ((S_801728C4_7 *)effect)->unk_10 = func_8016E0FC;
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_02 =
                        ((u16)motion->x.w.i) + delta[0];
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_06 =
                        ((u16)motion->y.w.i) + delta[1];
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_0A =
                        ((u16)motion->z.w.i) + delta[2];
                    ((S_801728C4_8 *)effect_state)->unk_A4 = 0;
                    ((S_801728C4_8 *)effect_state)->unk_96 = 4;
                    target_sprite = ((S_801728C4_7 *)effect)->unk_0C;
                    ((S_801728C4_3 *)target_sprite)->unk_28 = ((S_801728C4_4 *)sprite)->unk_28;
                    ((S_801728C4_3 *)target_sprite)->unk_1E = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_1C = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_14 = ((S_801728C4_4 *)sprite)->unk_14;
                    ((S_801728C4_3 *)target_sprite)->unk_12 = ((S_801728C4_4 *)sprite)->unk_12;
                    ((S_801728C4_3 *)target_sprite)->unk_0C.s = ((S_801728C4_4 *)sprite)->unk_0C;
                    func_80047784(target_sprite, 0x2D, 0);
                }
            }
        }

        timer = ((S_801728C4_0 *)action)->unk_96 - 1;
        ((S_801728C4_0 *)action)->unk_96 = timer;
        if ((s32)(timer << 16) <= 0) {
            ((S_801728C4_0 *)action)->unk_98.u &= 0x7FFF;
            ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
        }

        if (((S_801728C4_0 *)action)->unk_98.u & 0x8000) {
            particle_count = 7;
            callback = (void *)D_8016E0FC;
            do {
                effect = func_8003FD64(0x112, ((u8 *)&D_80083498));
                if (effect != 0) {
                    func_8004491C(effect, func_80045340);
                    ((S_801728C4_7 *)effect)->unk_10 = callback;
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_02 =
                        ((u16)motion->x.w.i) + delta[0] + (func_80069EF8() & 0xF) - 8;
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_06 =
                        ((u16)motion->y.w.i) + delta[1] + (func_80069EF8() & 0xF) - 8;
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_0A =
                        ((u16)motion->z.w.i) + delta[2] + (func_80069EF8() & 0xF) - 8;
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_0C =
                        ((func_80069EF8() & 0xFF) - 0x80) << 11;
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_10 =
                        ((func_80069EF8() & 0xFF) - 0x80) << 11;
                    ((S_801728C4_10 *)(((S_801728C4_7 *)effect)->unk_08))->unk_14 =
                        -(func_80069EF8() & 0xFF) << 12;
                    effect_state = (u8 *)effect + 0x20;
                    ((S_801728C4_8 *)effect_state)->unk_A4 = 0;
                    ((S_801728C4_8 *)effect_state)->unk_96 = 7;
                    target_sprite = ((S_801728C4_7 *)effect)->unk_0C;
                    ((S_801728C4_3 *)target_sprite)->unk_28 = ((S_801728C4_4 *)sprite)->unk_28;
                    ((S_801728C4_3 *)target_sprite)->unk_1E = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_1C = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_14 = ((S_801728C4_4 *)sprite)->unk_14;
                    ((S_801728C4_3 *)target_sprite)->unk_12 = ((S_801728C4_4 *)sprite)->unk_12 - 0x80;
                    ((S_801728C4_3 *)target_sprite)->unk_10 = 0x60;
                    ((S_801728C4_3 *)target_sprite)->unk_0C.u = 0x00808080;
                    ((S_801728C4_3 *)target_sprite)->unk_14 |= 0xC;
                    func_80047784(target_sprite, 0x2F, 0);
                }
                particle_count--;
            } while (particle_count >= 0);
        }

        if (((S_801728C4_4 *)sprite)->unk_14 & 0xE000) {
            ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
            (*(void * *)((u8 *)sprite + 0x2C)) = D_8016E850;
            func_80047784(
                sprite,
                D_8016E850[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801728C4_0 *)action)->unk_9B = ((S_801728C4_0 *)action)->unk_9B + 1;
            return;
        }
        return;
    case 3:
        if (!(((S_801728C4_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25);
        if (((S_801728C4_4 *)sprite)->unk_2C != D_8016E820) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_8016E820;
            func_80047784(
                sprite,
                D_8016E820[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        if (((s32)dungeonStatus.unk_0C) == 0) {
            dungeonStatus.unk_0A--;
            ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
            ((S_801728C4_0 *)action)->unk_8C = D_8016AE84;
            func_800A4ACC(actor);
            if (actor->unk_6D > 0) {
                (*(u8 *)&actor->unk_6D)--;
            }
            actor->unk_73 = 0;
            actor->unk_72 = 0;
            actor->unk_46 &= 0x7FFF;
            func_800A56E0(0xB4);
        }

        return;
    default:
        return;
    }
}
