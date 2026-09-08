#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017364C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017364C_0;   /* arg0 in func_8017364C */

typedef struct S_8017364C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_8017364C_1;   /* arg3 in func_8017364C */

typedef struct S_8017364C_2 {
    u8 * unk_00;
} S_8017364C_2;   /* (u8 *)var_v0 - 0x14 in func_8017364C */




typedef struct S_8017364C_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017364C_6;   /* global_state in func_8017364C */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80170858[];
s32 func_8003F270(void);                 /* extern */
void func_80047784();         /* extern */
s32 func_80069EF8();                                /* extern */
void *func_800A05A4();      /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A94A0();       /* extern */
void func_80171020(); /* extern */
extern M2C_UNK D_8006DE24;
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C;
extern M2C_UNK D_80171760;
extern u8 D_80174E88[9];

/* Updates an actor's ability action, effects, and completion state. */
void func_8017364C(void *action, void *motion, void *sprite, void *actor) {
    static void *const ability_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s16 next_effect;
    s16 effect_count;
    s32 ability_id;
    s32 normal_ability;
    register s32 use_player ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u16 effect_ticks;
    u16 finish_ticks;
    u8 *global_state;
    u8 *ability;
    s32 phase;
    void *target;

    phase = ((S_8017364C_0 *)action)->unk_9B;
    use_player = 0;
    if (phase == 1) {
        goto wait_for_ready;
    }
    if ((s32) phase >= 2) {
        goto check_later_phase;
    }
    if (phase == 0) {
        goto start_ability;
    }
    return;
check_later_phase:
    if (phase == 2) {
        goto update_effect;
    }
    if (phase == 3) {
        goto wait_for_finish;
    }
    return;
start_ability:
    if (!(((S_8017364C_1 *)actor)->unk_1C & 0x2000)) {
        goto select_normal_ability;
    }
    ability_id = ((S_8017364C_1 *)actor)->unk_46 & 0x3FFF;
    if ((u32) (ability_id - 1) >= 7U) {
        goto clear_ability;
    }
    (void)ability_labels;
    goto *D_80170858[(u32)((ability_id) - 1)];
jt_c7:
    use_player = 1;
    goto select_third_ability;
jt_c6:
    use_player = 1;
    goto select_second_ability;
jt_c5:
    use_player = 1;
    goto select_first_ability;
select_normal_ability:
    normal_ability = ((S_8017364C_1 *)actor)->unk_46 & 0x3FFF;
    if (normal_ability == 2) {
        goto select_second_ability;
    }
    if (normal_ability >= 3) {
        goto check_third_ability;
    }
    ability = NULL;
    if (normal_ability == 1) {
        goto select_first_ability;
    }
    goto check_ability;
check_third_ability:
    ability = NULL;
    if (normal_ability != 3) {
        goto check_ability;
    }
jt_c3:
select_third_ability:
    ability = actor + 0xE;
    goto check_ability;
jt_c2:
select_second_ability:
    ability = actor + 0xB;
    goto check_ability;
jt_c1:
select_first_ability:
    ability = actor + 8;
    goto check_ability;
jt_c4:
clear_ability:
    ability = NULL;
check_ability:
    if (*ability == 0) {
        goto cancel_ability;
    }
    *(volatile u16 *)((u8 *)action + 0x98) =
        ((S_8017364C_0 *)action)->unk_98 & 0xFF7F;
    {
        s32 player_target = use_player;
        ASM_KEEP(player_target);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (player_target) {
            target = D_800814A8;
            ((S_8017364C_1 *)actor)->unk_60 = target;
            goto copy_target_position;
        }
    }
check_target_type:
    {
        u8 *ability_table;
        u8 ability_kind;
        u32 ability_entry;

        ability_table = (u8 *)0x80070000;
        ASM_KEEP(ability_table);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ability_kind = *ability;
        ability_table -= 0x21DC;
        ability_entry = ability_kind * 20;
        ability_entry += (u32)ability_table;
        ASM_KEEP(ability_entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (((u8 *)ability_entry)[0x12] != 2) {
            goto find_target;
        }
    }
    target = ((S_8017364C_1 *)actor)->unk_60;
    if (target == NULL) {
        goto activate_ability;
    }
copy_target_position:
    {
        register u8 *target_sprite ASM_REG("$3") =
            ((S_8017364C_2 *)((u8 *)target - 0x14))->unk_00;
        ((S_8017364C_1 *)actor)->unk_72.s = target_sprite[0x24];
        ((S_8017364C_1 *)actor)->unk_73.s = target_sprite[0x25];
    }
    goto target_ready;
find_target:
    *(void * volatile *)((u8 *)actor + 0x60) =
        func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                      ((Rec_D_80082E80 *)sprite)->unk_25,
                      ((S_8017364C_1 *)actor)->unk_2A, 0x10);
    ASM_KEEP(use_player);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        s32 x = ((S_8017364C_1 *)actor)->unk_72.u;
        s32 y = ((S_8017364C_1 *)actor)->unk_73.u;

        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_8017364C_1 *)actor)->unk_72.s = x;
        ((S_8017364C_1 *)actor)->unk_73.s = y;
    }
target_ready:
activate_ability:
    if (func_800A94A0(actor, ability, use_player, action + 0x98) == 0) {
        goto done;
    }
    ((S_8017364C_0 *)action)->unk_96 = 0x13U;
    ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
    return;
cancel_ability:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
    func_800A4ACC(actor);
    ((S_8017364C_1 *)actor)->unk_6D = (u8) (((S_8017364C_1 *)actor)->unk_6D - 1);
    ((S_8017364C_0 *)action)->unk_8C = &D_80171760;
    ((S_8017364C_1 *)actor)->unk_73.u = 0;
    ((S_8017364C_1 *)actor)->unk_72.u = 0;
    ((S_8017364C_1 *)actor)->unk_46 = (u16) (((S_8017364C_1 *)actor)->unk_46 & 0x7FFF);
    return;
wait_for_ready:
    if (func_8003F270() == 0) {
        goto start_effect;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
    return;
start_effect:
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
    func_800A56E0(0x703);
update_effect:
    effect_ticks = ((S_8017364C_0 *)action)->unk_96 - 1;
    ((S_8017364C_0 *)action)->unk_96 = effect_ticks;
    if ((effect_ticks << 0x10) <= 0) {
        goto start_finish;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto check_effect_window;
    }
start_finish:
    ((S_8017364C_0 *)action)->unk_98 = (u16) (((S_8017364C_0 *)action)->unk_98 | 0x80);
    ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
    ((S_8017364C_0 *)action)->unk_96 = 0xFU;
check_effect_window:
    if ((u32) (((S_8017364C_0 *)action)->unk_96 - 9) >= 6U) {
        goto done;
    }
    effect_count = 0;
emit_effect:
    func_80171020(action - 0x20, 0, 0xC0C0, (func_80069EF8() & 0xFF) | 0x80, 0, 0, 0);
    next_effect = effect_count + 1;
    effect_count = next_effect;
    if (next_effect >= 0xA) {
        return;
    }
    goto emit_effect;
wait_for_finish:
    global_state = D_80083460;
    if (((S_8017364C_6 *)global_state)->unk_0C != 0) {
        goto update_finish_timer;
    }
    ((S_8017364C_0 *)action)->unk_96 = 0U;
update_finish_timer:
    finish_ticks = ((S_8017364C_0 *)action)->unk_96 - 1;
    ((S_8017364C_0 *)action)->unk_96 = finish_ticks;
    if ((finish_ticks << 0x10) > 0) {
        goto check_animation;
    }
    ((S_8017364C_0 *)action)->unk_96 = 0U;
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
check_animation:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pm == D_80174E88) {
        goto check_completion;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = D_80174E88;
    func_80047784(sprite, D_80174E88[((s32) (D_80083228 + ((S_8017364C_1 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
check_completion:
    if (((S_8017364C_6 *)global_state)->unk_0C != 0) {
        goto done;
    }
    ((S_8017364C_6 *)global_state)->unk_0A = (u16) (((S_8017364C_6 *)global_state)->unk_0A - 1);
    ((S_8017364C_0 *)action)->unk_8C = &D_80171760;
    func_800A4ACC(actor);
    ((S_8017364C_1 *)actor)->unk_73.u = 0;
    ((S_8017364C_1 *)actor)->unk_72.u = 0;
    ((S_8017364C_1 *)actor)->unk_6D = (u8) (((S_8017364C_1 *)actor)->unk_6D - 1);
    ((S_8017364C_1 *)actor)->unk_46 = (u16) (((S_8017364C_1 *)actor)->unk_46 & 0x7FFF);
    func_800A56E0(0xB4);
done:
    return;
}
