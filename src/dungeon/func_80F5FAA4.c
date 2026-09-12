#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A8.h"
#include "records/Rec_func_801732A4_arg0.h"



typedef struct S_801732A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x4];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
} S_801732A4_2;   /* arg3 in func_801732A4 */

typedef struct S_801732A4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801732A4_3;   /* var_v0 in func_801732A4 */


typedef struct S_801732A4_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_801732A4_5;   /* temp_base_2 in func_801732A4 */

typedef struct S_801732A4_6 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_801732A4_6;   /* temp_base in func_801732A4 */

typedef struct S_801732A4_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
    u8 * unk_2C;
} S_801732A4_7;   /* temp_a0 in func_801732A4 */

typedef struct S_801732A4_8 {
    u8 pad_00[0xBB];
    u8 unk_BB;
} S_801732A4_8;   /* temp_v1_7 in func_801732A4 */

typedef struct Copy24 { u32 words[6]; } Copy24;

extern void *D_80170858[];
void *func_8003FD64();
s32 func_80042900();
void func_80042B68();
s32 func_8004491C();
void func_80047784();
s32 func_8009A180();
s16 func_8009FD40();
s32 func_800A2C34();
M2C_UNK func_800A56E0();
s32 func_800A6D30();
M2C_UNK func_800A9A04();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
M2C_UNK func_800AD4D0();
M2C_UNK func_80171F94();
M2C_UNK func_80173CEC();
extern M2C_UNK D_80045340;
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern u16 D_80083460[];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D7960;
extern M2C_UNK D_80170E68;
extern u8 D_801741DC[];
extern u8 D_801741E4[];
extern u8 D_801741EC[];
extern u8 D_801741F4[];
extern u8 D_801741FC[];

/* Advances the actor effect sequence, updating directional animation and its attached effect. */
void func_801732A4(void *actor, void *transform, void *sprite, void *actor_state) {
    static void *const state_labels[] = { &&phase_start, &&phase_update, &&phase_transition, &&phase_spawn, &&phase_finish, &&phase_resume };
    M2C_UNK *effect_state;
    s32 actor_flags;
    s32 action_flags;
    s32 sprite_data;
    s8 region_id;
    u16 count;
    u16 sprite_flags;
    u16 effect_flags;
    u8 phase;
    void *effect_sprite;
    void *new_effect;
    void *effect_transform;
    void *active_effect;
    void *view_state;
    void *player_sprite;

    phase = ((Rec_func_801732A4_arg0 *)actor)->unk_9B;
    if (phase >= 6U) goto done;
    (void)state_labels; goto *D_80170858[(u32)(phase)];
phase_start:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) goto done;
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_801741DC;
    func_80047784(sprite, D_801741DC[((D_80083228 + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7], 0);
    D_80083460[5] = (u16)(D_80083460[5] - 1);
    goto advance_phase;
phase_update:
    sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
    if (sprite_flags & 0x8000) goto check_effect_state;
    if (!(sprite_flags & 0x6000)) goto animation_updated;
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16)(sprite_flags & 0x9FFF);
    count = ((Rec_func_801732A4_arg0 *)actor)->unk_96 + 1;
    ((Rec_func_801732A4_arg0 *)actor)->unk_96 = count;
    if (!(count & 1)) goto check_effect_state;
    func_800A56E0(0x51B);
animation_updated:
check_effect_state:
    effect_state = &D_80083460;
    if (((S_801732A4_3 *)effect_state)->unk_02 & 0x1000) goto done;
    if ((func_80042900(actor_state, 1) << 0x10) != 0) goto check_action;
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_801741E4;
    func_80047784(sprite, D_801741E4[((D_80083228 + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7], 0);
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        if (!(((Rec_func_801732A4_arg0 *)actor)->unk_98 & 0x8000)) goto clear_action;
        count = ((S_801732A4_3 *)effect_state)->unk_0A + 1;
        ASM_SCHED_BARRIER(); /* MATCH: keep this count update separate, with the store in the jump delay slot. */
        ((S_801732A4_3 *)effect_state)->unk_0A = count;
        goto advance_phase;
clear_action:
        ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~0x200);
        goto reset_handler;
    }
    ((S_801732A4_3 *)effect_state)->unk_0A = (u16)(((S_801732A4_3 *)effect_state)->unk_0A + 1);
    goto advance_phase;
check_action:
    if (((S_801732A4_2 *)actor_state)->unk_64 == 0) goto start_action;
    if (func_800AA6B4(actor, transform, sprite, 0) == 0) goto start_action;
    ((Rec_func_801732A4_arg0 *)actor)->unk_98 = (u16)(((Rec_func_801732A4_arg0 *)actor)->unk_98 | 0x8000);
    if (((S_801732A4_2 *)actor_state)->unk_25 != 0) goto save_heading;
    if (((S_801732A4_3 *)effect_state)->unk_02 & 0x2008) goto done;
    func_800AA79C(actor, transform, sprite, actor_state);
    return;
save_heading:
    ((Rec_func_801732A4_arg0 *)actor)->unk_AA = (u16)((((S_801732A4_2 *)actor_state)->unk_6A + 0x800) & 0xFFF);
    return;
start_action:
    actor_flags = ((S_801732A4_2 *)actor_state)->unk_14;
    if (actor_flags & 0x8000) goto check_busy;
    ((S_801732A4_2 *)actor_state)->unk_14 = (s32)(actor_flags | 0x8000);
    ((S_801732A4_2 *)actor_state)->unk_64 = (s16)((u16)((S_801732A4_2 *)actor_state)->unk_64 + 1);
    func_800AD4D0(actor_state);
check_busy:
    if ((func_800A2C34(actor_state) << 0x10) != 0) goto done;
    action_flags = ((S_801732A4_2 *)actor_state)->unk_1C;
    if (!(action_flags & 0x100)) goto check_special_action;
    func_800AA258(actor, transform, sprite, actor_state);
    return;
check_special_action:
    if (!(action_flags & 0x80000)) goto check_pending_action;
    func_800AA888(actor, transform, sprite, actor_state);
    func_80173CEC(actor, transform, sprite, actor_state);
    return;
check_pending_action:
    if (((S_801732A4_2 *)actor_state)->unk_6D == 0) goto done;
    if ((func_800A2C34(actor_state) << 0x10) == 0) goto update_action;
    if ((func_8009A180(actor_state, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) != 0) goto done;
update_action:
    func_800A9A0C(actor_state);
    func_800A9A04(actor_state);
    if ((func_80042900(actor_state, 1) << 0x10) == 0) goto check_ready;
    player_sprite = &D_80082E80;
    region_id = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;
    if (region_id != ((S_801732A4_5 *)player_sprite)->unk_26) goto check_distance;
    if (region_id >= 0) goto check_random;
check_distance:
    if (func_8009FD40(player_sprite, sprite) >= 2) goto check_effect_flag;
check_random:
    if (func_800A6D30() & 7) goto check_effect_flag;
    func_80042B68(actor_state, 1);
check_effect_flag:
    if (!(((Rec_func_801732A4_arg0 *)actor)->unk_98 & 0x8000)) goto check_ready;
    func_80042B68(actor_state, 1);
check_ready:
    if ((func_80042900(actor_state, 1) << 0x10) != 0) goto done;
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_801741E4;
    func_80047784(sprite, D_801741E4[((D_80083228 + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7], 0);
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) goto increment_count;
    if (!(((Rec_func_801732A4_arg0 *)actor)->unk_98 & 0x8000)) goto clear_action;
    {
        actor_flags = D_80083460[5] + 1;
        ASM_SCHED_BARRIER(); /* MATCH: keep this count update separate, with the store in the jump delay slot. */
        D_80083460[5] = actor_flags;
    }
    goto advance_phase;
increment_count:
    {
        actor_flags = D_80083460[5];
        D_80083460[5] = (u16)(actor_flags + 1);
    }
    goto advance_phase;
phase_transition:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) goto done;
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_801741EC;
    func_80047784(sprite, D_801741EC[((D_80083228 + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7], 0);
    goto advance_phase;
phase_spawn:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) goto done;
    view_state = &D_80083160;
    ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 = D_801741F4;
    func_80047784(sprite, D_801741F4[((((S_801732A4_6 *)view_state)->unk_C8 + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7], 0);
    ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
    new_effect = func_8003FD64(0x112, &D_80083498);
    ((Rec_func_801732A4_arg0 *)actor)->unk_A0 = new_effect;
    actor = new_effect;
    if (actor == NULL) goto done;
    func_8004491C(actor, &D_80045340);
    effect_transform = ((Rec_func_801732A4_arg0 *)actor)->unk_08;
    ((Rec_func_801732A4_arg0 *)actor)->unk_10 = &D_800D7960;
    *(Copy24 *)effect_transform = *(Copy24 *)transform;
    ((Rec_func_801732A4_arg0 *)actor)->unk_BB = 0;
    effect_sprite = ((Rec_func_801732A4_arg0 *)actor)->unk_0C;
    ((Rec_func_801732A4_arg0 *)actor)->unk_4A = (u16)((S_801732A4_2 *)actor_state)->unk_2A;
    sprite_data = ((Rec_D_80082E80 *)sprite)->unk_28.at00_s32.v;
    ((S_801732A4_7 *)effect_sprite)->unk_1E = 0x1000;
    ((S_801732A4_7 *)effect_sprite)->unk_1C = 0x1000;
    ((S_801732A4_7 *)effect_sprite)->unk_28 = sprite_data;
    ((S_801732A4_7 *)effect_sprite)->unk_14 = (u16)((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
    ((S_801732A4_7 *)effect_sprite)->unk_12 = (u16)((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v;
    ((S_801732A4_7 *)effect_sprite)->unk_0C = (s32)((Rec_D_80082E80 *)sprite)->unk_0C.at00_s32.v;
    ((S_801732A4_7 *)effect_sprite)->unk_2C = D_801741FC;
    func_80047784(effect_sprite, D_801741FC[((((S_801732A4_6 *)view_state)->unk_C8 + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7], 0);
    return;
phase_finish:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) goto done;
    active_effect = ((Rec_func_801732A4_arg0 *)actor)->unk_A0;
    if (active_effect == NULL) goto finish_effect;
    ((S_801732A4_8 *)active_effect)->unk_BB = 0xFF;
    ((Rec_func_801732A4_arg0 *)actor)->unk_A0 = NULL;
finish_effect:
    D_80083460[5] = (u16)(D_80083460[5] - 1);
    ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~0x200);
    effect_flags = ((Rec_func_801732A4_arg0 *)actor)->unk_98;
    if (!(effect_flags & 0x8000)) goto reset_handler;
    ((Rec_func_801732A4_arg0 *)actor)->unk_98 = (u16)(effect_flags & 0x7FFF);
    ((S_801732A4_2 *)actor_state)->unk_2A = (s16)((Rec_func_801732A4_arg0 *)actor)->unk_AA;
    ((S_801732A4_2 *)actor_state)->unk_6D = (s8)((u8)((S_801732A4_2 *)actor_state)->unk_6D + 1);
advance_phase:
    ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
    return;
reset_handler:
    ((Rec_func_801732A4_arg0 *)actor)->unk_8C = &D_80170E68;
    return;
phase_resume:
    func_80171F94(actor, transform, sprite, actor_state);
done:
    return;
}
