#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8017558C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    s16 unk_94;
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 unk_B0;
    u8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
    u8 pad_B5[0x1];
    u16 unk_B6;
    u16 unk_B8;
    u16 unk_BA;
} S_8017558C_0;   /* arg0 in func_8017558C */


typedef struct S_8017558C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 * unk_0C;
    u8 * unk_10;
} S_8017558C_4;   /* temp_v0_3 in func_8017558C */

typedef struct S_8017558C_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_8017558C_5;   /* temp_v0_4 in func_8017558C */

typedef struct S_8017558C_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8017558C_6;   /* temp_a0 in func_8017558C */

typedef struct S_8017558C_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017558C_7;   /* temp_v1_2 in func_8017558C */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_800E2438[];
extern u8 D_80170A84[];
extern s32 D_80045C34[3];
extern u8 D_800E2440[];
extern u8 D_800E2448[];
extern u8 D_800E23E0[];
extern u8 D_800E2488[];
extern u8 D_80171A80[];
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();               /* extern */
M2C_UNK func_8009D8A4();                            /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800BCB04();                   /* extern */
M2C_UNK func_801708B8();      /* extern */
M2C_UNK func_80174C64(); /* extern */

/* Update the actor action sequence, including its effect, animations, and position restoration. */
void func_8017558C(void *action, EntityRec *position, Rec_D_80082E80 *sprite, EntityRec *actor) {
    s16 height_delta;
    s16 height;
    s16 view_dir;
    s32 *effect_sprite;
    u16 timer;
    u16 finish_timer;
    u16 effect_timer;
    u16 start_timer;
    u16 windup_timer;
    u16 restore_timer;
    u16 saved_angle;
    u16 pause_timer;
    u8 phase;
    s32 restore_phase;
    s32 next_phase;
    void *effect;
    S_8017558C_5 *effect_state;
    S_8017558C_7 *effect_position;

    s32 global_flags;

    phase = ((S_8017558C_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (sprite->unk_14.at00_u16.v & 0x8000) {
            {
                s32 finish_phase;
                func_8009D8A4();
                finish_phase = 5;
                global_flags = D_800E296C;
                ((S_8017558C_0 *)action)->unk_96 = finish_phase;
                D_800E296C = global_flags | 0x800000;
                ((S_8017558C_0 *)action)->unk_9B = finish_phase;
            }
            sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v | 0x6000);
            return;
        }
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        height_delta = func_800BCB04(((u16)position->x.w.i), ((u16)position->y.w.i), (s16) (((u16)actor->unk_88)
            - 0x20));
        height = ((u16)actor->unk_88);
        height_delta -= height;
        if (((S_8017558C_0 *)action)->unk_92.s < height_delta) {
            ((S_8017558C_0 *)action)->unk_92.u = ((S_8017558C_0 *)action)->unk_92.u + 0xC;
            if (height_delta >= (s16) ((S_8017558C_0 *)action)->unk_92.u) {
                goto check_height;
            }
        }
        ((S_8017558C_0 *)action)->unk_92.u = (u16) height_delta;
check_height:
        if (((S_8017558C_0 *)action)->unk_92.s == 0) {
            sprite->unk_2C.as_pu8 = D_800E2438;
            func_80047784(sprite, D_800E2438[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            func_800A56E0(0x800);
            ((S_8017558C_0 *)action)->unk_96 = 2U;
            ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
            sprite->unk_06.as_s16 = 6;
            ((S_8017558C_0 *)action)->unk_A6 = (u16) actor->facing;
        }
        effect_timer = ((S_8017558C_0 *)action)->unk_96 + 1;
        ((S_8017558C_0 *)action)->unk_96 = effect_timer;
        if ((s16) effect_timer != 1) {
            return;
        }
        effect = func_8003FD64(0x12, action - 0x20);
        if (effect == NULL) {
            return;
        }
        ((S_8017558C_0 *)action)->unk_AC = effect;
        ((S_8017558C_4 *)effect)->unk_10 = D_80170A84;
        func_8004491C(effect, D_80045C34);
        effect_state = effect + 0x20;
        effect_state->unk_38 = 5;
        effect_state->unk_40 = action;
        effect_state->unk_44 = position;
        effect_sprite = ((S_8017558C_4 *)effect)->unk_0C;
        ((S_8017558C_6 *)effect_sprite)->unk_10 = 0x40;
        ((S_8017558C_6 *)effect_sprite)->unk_14 = (u16) (((S_8017558C_6 *)effect_sprite)->unk_14 | 0xC);
        effect_position = ((S_8017558C_4 *)effect)->unk_08;
        effect_position->unk_02 = (u16) ((u16)position->x.w.i);
        effect_position->unk_06 = (u16) ((u16)position->y.w.i);
        effect_position->unk_0A = (u16) ((u16)actor->unk_88);
        effect_sprite = ((S_8017558C_4 *)effect)->unk_0C;
        ((S_8017558C_6 *)effect_sprite)->unk_1E = 0xA00;
        ((S_8017558C_6 *)effect_sprite)->unk_1C = 0xA00;
        ((S_8017558C_6 *)effect_sprite)->unk_0E = 0;
        ((S_8017558C_6 *)effect_sprite)->unk_0D = 0;
        ((S_8017558C_6 *)effect_sprite)->unk_0C = 0;
        ((S_8017558C_6 *)effect_sprite)->unk_08 = D_800E2488;
        return;
    case 1:
        start_timer = ((S_8017558C_0 *)action)->unk_96 - 1;
        ((S_8017558C_0 *)action)->unk_96 = start_timer;
        if ((start_timer << 0x10) > 0) {
            if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
                return;
            }
        }
        sprite->unk_2C.as_pu8 = D_800E2440;
        func_80047784(sprite, D_800E2440[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        ((S_8017558C_0 *)action)->unk_96 = 3U;
        ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
        ((S_8017558C_0 *)action)->unk_B6 = (u16) ((u16)position->x.w.i);
        ((S_8017558C_0 *)action)->unk_B8 = (u16) ((u16)position->y.w.i);
        ((S_8017558C_0 *)action)->unk_BA = (u16) ((u16)actor->unk_88);
        return;
    case 2:
        windup_timer = ((S_8017558C_0 *)action)->unk_96 - 1;
        ((S_8017558C_0 *)action)->unk_96 = windup_timer;
        if ((windup_timer << 0x10) > 0) {
            return;
        }
        next_phase = ((S_8017558C_0 *)action)->unk_9B;
        ((S_8017558C_0 *)action)->unk_96 = 0x1EU;
        ((S_8017558C_0 *)action)->unk_A8 = 0;
        ((S_8017558C_0 *)action)->unk_B1 = 0U;
        ((S_8017558C_0 *)action)->unk_B2 = 0;
        ((S_8017558C_0 *)action)->unk_B4 = 0;
        ((S_8017558C_0 *)action)->unk_B3 = 0;
        next_phase += 1;
        ((S_8017558C_0 *)action)->unk_9B = next_phase;
        return;
    case 3:
        func_80174C64(action, position, sprite, actor);
        return;
    case 4:
        restore_phase = ((S_8017558C_0 *)action)->unk_B1;
        if (restore_phase == 1) {
            goto wait_pause;
        }
        if ((s32) restore_phase < 2) {
            if (restore_phase == 0) {
                goto restore_position;
            }
            return;
        }
        if (restore_phase == 2) {
            goto finish_restore;
        }
        return;
restore_position:
        restore_timer = ((S_8017558C_0 *)action)->unk_96 + 1;
        ((S_8017558C_0 *)action)->unk_96 = restore_timer;
        if ((s16) restore_timer == 1) {
            position->x.w.i = (u16) ((S_8017558C_0 *)action)->unk_B6;
            position->y.w.i = (u16) ((S_8017558C_0 *)action)->unk_B8;
            actor->unk_88 = (u16) ((S_8017558C_0 *)action)->unk_BA;
            saved_angle = ((S_8017558C_0 *)action)->unk_A6;
            actor->facing = (s16) saved_angle;
            view_dir = ((s32) (gameWork.view.viewAngle + (s16) saved_angle + 0x100) >> 9) & 7;
            func_80047738(sprite, sprite->unk_2C.as_pu8[view_dir], sprite->unk_04.as_s8);
            ((S_8017558C_0 *)action)->unk_94 = view_dir;
        }
        if ((s16) ((S_8017558C_0 *)action)->unk_96 < 0x10) {
            return;
        }
        ((S_8017558C_0 *)action)->unk_96 = 0U;
        ((S_8017558C_0 *)action)->unk_B1 = (u8) (((S_8017558C_0 *)action)->unk_B1 + 1);
        sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v & 0x9F7F);
        return;
wait_pause:
        pause_timer = ((S_8017558C_0 *)action)->unk_96;
        ((S_8017558C_0 *)action)->unk_96 = (u16) (pause_timer + 1);
        if ((s16) pause_timer < 4) {
            return;
        }
        ((S_8017558C_0 *)action)->unk_96 = 0U;
        ((S_8017558C_0 *)action)->unk_B1 = (u8) (((S_8017558C_0 *)action)->unk_B1 + 1);
        sprite->unk_2C.as_pu8 = D_800E2448;
        func_80047784(sprite, D_800E2448[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v & 0x9F7F);
        func_800A56E0(0x801);
        return;
finish_restore:
        if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        func_800A2B04(position, sprite->unk_24, sprite->unk_25);
        actor->flags1C = (s32) (actor->flags1C | 0x40000);
        ((S_8017558C_0 *)action)->unk_98 = (u16) (((S_8017558C_0 *)action)->unk_98 | 8);
        if (sprite->unk_2C.as_pu8 == D_800E23E0) {
            return;
        }
        sprite->unk_2C.as_pu8 = D_800E23E0;
        func_80047784(sprite, D_800E23E0[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        ((S_8017558C_0 *)action)->unk_96 = 5U;
        ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
        if (((S_8017558C_0 *)action)->unk_B0 != 0) {
            return;
        }
        func_801708B8(action, position, sprite);
        return;
    case 5:
        finish_timer = ((S_8017558C_0 *)action)->unk_96;
        ((S_8017558C_0 *)action)->unk_96 = (u16) (finish_timer - 1);
        if ((finish_timer << 0x10) > 0) {
            return;
        }
        sprite->unk_06.as_s16 = 0;
        func_800AD594(actor, 0x1000);
        ((S_8017558C_0 *)action)->unk_8C = D_80171A80;
        dungeonStatus.unk_0C = 0;
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        return;
    }
}
