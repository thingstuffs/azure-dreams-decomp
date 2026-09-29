#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80C97514_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80C97514_12;   /* temp_v0_2 in func_80C97514 */


typedef struct S_80C97514_14 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80C97514_14;   /* ((S_80C97514_12 *)temp_v0_2)->unk_08 in func_80C97514 */

typedef struct S_80C97514_15 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80C97514_15;   /* ((Rec_D_80082E80 *)arg3)->unk_60.as_pv in func_80C97514 */


typedef struct S_80C97514_0_pre {
    u16 unk_00;
} S_80C97514_0_pre;   /* the 0x2 bytes before arg0 in func_80C97514, addressed as arg0[-1] */

typedef struct S_80C97514_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s16 unk_A4;
    u8 pad_A6[0x6];
    void * unk_AC;
} S_80C97514_0;   /* arg0 in func_80C97514 */


typedef struct S_80C97514_2 {
    u8 unk_00;
} S_80C97514_2;   /* &D_801753A9 in func_80C97514 */

typedef struct S_80C97514_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80C97514_4;   /* temp_a1 in func_80C97514 */

typedef struct S_80C97514_5 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80C97514_5;   /* temp_v0_2 in func_80C97514 */


typedef struct S_80C97514_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80C97514_7;   /* temp_s0 in func_80C97514 */


typedef struct S_80C97514_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80C97514_9_pre;   /* the 0x14 bytes before temp_v1_3 in func_80C97514, addressed as temp_v1_3[-1] */

typedef struct S_80C97514_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80C97514_9;   /* temp_v1_3 in func_80C97514 */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_8003DB94();     /* extern */
s32 Control_CD(); /* extern */
void func_8003F540(); /* extern */
void *func_8003FC64();                       /* extern */
void func_80041588(); /* extern */
int func_800445E0();                           /* extern */
s32 func_8004491C();           /* extern */
void func_80047738();              /* extern */
s32 func_800498A0();                /* extern */
s32 func_80069EF8();                          /* extern */
void func_8009A028();                      /* extern */
void func_8009A3D0();             /* extern */
void func_800A18E8();                 /* extern */
s32 func_800A504C();                /* extern */
s32 func_800A56E0();                     /* extern */
s32 func_800ADC4C();     /* extern */
s32 func_800C77D0(); /* extern */
M2C_UNK func_80174724();      /* extern */
extern M2C_UNK D_8003E140;
extern s32 D_8006CD58;
extern M2C_UNK D_800DCEEC;
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8014A000;
extern M2C_UNK D_80174BE8;
extern M2C_UNK D_8017530C;
extern s16 D_80175314;
extern M2C_UNK D_80175318;
extern M2C_UNK D_801753A8;
extern M2C_UNK D_801753A9;
extern s32 D_801753AC;

/* Advances the actor transition through turning, color blending, effects, and model replacement. */
void func_80C97514(void *state, EntityRec *position, Rec_D_80082E80 *entity, void *actor) {
    s32 direction;
    u16 fade_ticks;
    u16 finish_ticks;
    u16 previous_ticks;
    u8 status;
    u8 next_state;
    S_80C97514_4 *effect_data;
    GameWork *scene_color = &gameWork;
    S_80C97514_7 *render_obj;
    S_80C97514_5 *effect;
    void *new_model;
    void *model;

    status = ((S_80C97514_0 *)state)->unk_9B;
    switch (status) {
    case 0:
    next_state = ((S_80C97514_0 *)state)->unk_9B + 1;
    goto advance_state;
    case 1:
    func_80041588(&D_8017530C, &D_801753A8, 0);
    ((S_80C97514_0 *)state)->unk_A4 = 0;
    ((S_80C97514_0 *)state)->unk_9B = (u8) (((S_80C97514_0 *)state)->unk_9B + 1);
    ((Rec_D_80082E80 *)actor)->unk_8A = (u16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v;
    case 2:
    direction = ((s32) (gameWork.view.viewAngle + (s16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v + 0x100) >> 9) & 7;
    if ((*(u8 *)&D_801753A8) == 0) {
        goto turn_actor;
    }
    if (direction == 2) {
        goto start_effect;
    }
turn_actor:
    if (direction == 2) {
        return;
    }
    ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v + 0x200);
    return;
start_effect:
    func_80041588(&D_8017530C, &D_801753A8, 1);
    func_8003F540(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
    Control_CD(0x15, func_800445E0(), NULL);
    (*(s8 *)&D_801753A9) = 0;
    Control_CD(0xFF, &D_8003E140, &D_801753A9);
    func_800C77D0(actor - 0x20, position, 8, 0x300);
    ((S_80C97514_0 *)state)->unk_96 = 0x10U;
    ((S_80C97514_0 *)state)->unk_9B = (u8) (((S_80C97514_0 *)state)->unk_9B + 1);
    func_80174724(state, position, entity);
    case 3:
    previous_ticks = ((S_80C97514_0 *)state)->unk_96;
    fade_ticks = previous_ticks - 1;
    ((S_80C97514_0 *)state)->unk_96 = fade_ticks;
    if ((fade_ticks << 0x10) > 0) {
        goto blend_color;
    }
    status = ((S_80C97514_2 *)(&D_801753A9))->unk_00;
    ((S_80C97514_0 *)state)->unk_96 = previous_ticks;
    if (status == 0) {
        return;
    }
    ((S_80C97514_0 *)state)->unk_9B = (u8) (((S_80C97514_0 *)state)->unk_9B + 1);
    func_800A56E0(0x300);
    return;
blend_color:
    effect_data = ((void **)&D_800DCEEC)[func_800498A0(actor)];
    scene_color->view.unk_090 = (u8) (scene_color->view.unk_090 + ((s32) (effect_data->unk_00 - scene_color->view.unk_090) / (s16) ((S_80C97514_0 *)state)->unk_96));
    scene_color->view.unk_091 = (u8) (scene_color->view.unk_091 + ((s32) (effect_data->unk_01 - scene_color->view.unk_091) / (s16) ((S_80C97514_0 *)state)->unk_96));
    scene_color->view.unk_092 = (u8) (scene_color->view.unk_092 + ((s32) (effect_data->unk_02 - scene_color->view.unk_092) / (s16) ((S_80C97514_0 *)state)->unk_96));
    return;
    case 4:
{
    s32 effect_type;
    s16 effect_index;

    effect = func_8003FC64(0x12);
    if (effect == NULL) {
        return;
    }
    effect->unk_10 = &D_80174BE8;
    func_8004491C(effect, func_80045340);
    ((S_80C97514_0 *)state)->unk_AC = effect;
    ((S_80C97514_14 *)(((S_80C97514_12 *)effect)->unk_08))->unk_00 = (s32) position->x.v;
    ((S_80C97514_14 *)(((S_80C97514_12 *)effect)->unk_08))->unk_04 = (s32) position->y.v;
    ((S_80C97514_14 *)(((S_80C97514_12 *)effect)->unk_08))->unk_08 = (s32) position->z.v;
    render_obj = effect->unk_0C;
    render_obj->unk_1E = 0x1000;
    render_obj->unk_1C = 0x1000;
    render_obj->unk_0C.s = 0x808080;
    effect_type = func_800498A0(actor) - 1;
    effect_index = effect_type;
    if ((effect_type << 0x10) >= 0) {
        goto set_effect;
    }
    effect_index = func_80069EF8() % 3;
set_effect:
    effect_data = (void *)(*((s32 *)&D_80175318 + (s16) effect_index) + (s32)&D_8014A000);
    func_8003DB94(render_obj, effect_data, 0);
    entity->unk_14.at00_u16.v = (u16) (entity->unk_14.at00_u16.v | 0x80);
    ((S_80C97514_0 *)state)->unk_96 = 0U;
    next_state = ((S_80C97514_0 *)state)->unk_9B + 1;
advance_state:
    ((S_80C97514_0 *)state)->unk_9B = next_state;
    return;
}
    case 5:
    render_obj = ((S_80C97514_0 *)state)->unk_AC;
    render_obj = render_obj->unk_0C.u;
    if (!(render_obj->unk_14 & 0xE000)) {
        goto check_transition;
    }
    ((S_80C97514_0 *)state)->unk_9B = (u8) (((S_80C97514_0 *)state)->unk_9B + 1);
    case 6:
check_transition:
    if (((S_80C97514_0 *)state)->unk_9B != 6) {
        return;
    }
    if (func_800ADC4C(position, D_801753AC, D_80175314, &D_800DCF5C) == 0) {
        return;
    }
    ((S_80C97514_0 *)state)->unk_96 = 0x10U;
    ((S_80C97514_0 *)state)->unk_9B = (u8) (((S_80C97514_0 *)state)->unk_9B + 1);
    func_800A18E8(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 3);
    func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
    func_8009A028(actor);
    render_obj = actor - 0x20;
    render_obj->unk_10 = (s32) (render_obj->unk_10 | 0x80000000);
    return;
    case 7:
    new_model = func_800A504C(entity, actor);
    ((Rec_D_80082E80 *)actor)->unk_60.as_pv = new_model;
    if (new_model == NULL) {
        return;
    }
    ((S_80C97514_0 *)state)->unk_96 = 0x10U;
    ((S_80C97514_0 *)state)->unk_9B = (u8) (((S_80C97514_0 *)state)->unk_9B + 1);
    ((S_80C97514_15 *)(((Rec_D_80082E80 *)actor)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v;
    model = ((Rec_D_80082E80 *)actor)->unk_60.as_pv;
    render_obj = ((S_80C97514_9_pre *)model)[-1].unk_00;
    func_80047738(render_obj, render_obj->unk_2C[((s32) (gameWork.view.viewAngle + (s16) ((S_80C97514_9 *)model)->unk_2A + 0x100) >> 9) & 7], render_obj->unk_04);
    render_obj->unk_14 = (u16) (render_obj->unk_14 & 0xFFFE);
    case 8:
    finish_ticks = ((S_80C97514_0 *)state)->unk_96 - 1;
    ((S_80C97514_0 *)state)->unk_96 = finish_ticks;
    if ((finish_ticks << 0x10) > 0) {
        return;
    }
    ((S_80C97514_15 *)(((Rec_D_80082E80 *)actor)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)actor)->unk_8A;
    ((S_80C97514_0_pre *)state)[-1].unk_00 = (u16) (((S_80C97514_0_pre *)state)[-1].unk_00 | 0x8000);
    (*(s32 *)&objectFlagBlock.flags) = (s32) (objectFlagBlock.flags | 0x8000);
    dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    ((Rec_D_80082E80 *)actor)->unk_6D = 0;
    return;
    }
}
