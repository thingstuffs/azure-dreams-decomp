#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 D_8006CD58[];
extern u8 D_8006DE24[];
extern u8 D_80080A84;
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800DCF50;
extern s32 D_800DDAB8[];
extern void *D_80170880[];
extern void *D_80170898[];
extern u8 D_801710EC[];
extern u8 D_80175E40[];
extern u8 D_80175F40[];
extern u16 D_80175F6E;

extern s32 Control_CD();
extern s32 func_8003F270();
extern s32 func_8003F540();
extern s32 func_800445E0();
extern s32 func_80047784();
extern void *func_800A05A4();
extern s32 func_800A2B04();
extern s32 func_800A4ACC();
extern s32 func_800A56E0();
extern s32 func_800A9400();
extern s32 func_800A94A0();
extern s32 func_800BB044();
extern s32 func_80175814();
extern s32 func_80175D7C();


typedef struct S_80173560_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
} S_80173560_0;   /* arg0 in func_80173560 */

typedef struct S_80173560_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_80173560_1;   /* arg3 in func_80173560 */

typedef struct S_80173560_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173560_2_pre;   /* the 0x14 bytes before outer in func_80173560, addressed as outer[-1] */

typedef struct S_80173560_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173560_3;   /* inner in func_80173560 */

typedef struct S_80173560_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80173560_4;   /* arg2 in func_80173560 */


/* Advance an item action through targeting, audio playback, and animation cleanup. */
void func_80173560(void *action, void *motion, void *sprite_arg, void *actor_arg) {
    static void *const state_labels[] = {
        &&prepare_item, &&start_audio, &&wait_audio, &&finish_animation, &&reset_action
    };
    static void *const item_labels[] = {
        &&item_at_0e, &&item_at_0b, &&item_at_08, &&item_default
    };
    void *sprite = sprite_arg;
    void *actor = actor_arg;
    s32 state;
    register s32 action_value ASM_REG("$2");
    s32 has_item;
    register s32 sound_id ASM_REG("$4");
    s32 item_addr;
    register s32 item_or_audio_base ASM_REG("$17");
    s32 item_id;
    s32 direction;
    s32 cd_param;
    s32 item_type;
    s32 item_index;
    s32 audio_index;
    register s32 audio_result ASM_REG("$2");
    void *resource;
    void *target;

    state = ((S_80173560_0 *)action)->unk_9B.n;
    ASM_KEEP(state);
    if ((u32)state >= 5) {
        return;
    }
    item_or_audio_base = 0;
    ASM_KEEP(item_or_audio_base);
    (void)state_labels;
    goto *D_80170880[state];

prepare_item:
    action_value = ((S_80173560_1 *)actor)->unk_46 & 0x3FFF;
    state = action_value - 1;
    if ((u32)state >= 7) {
        goto item_default;
    }
    (void)item_labels;
    goto *D_80170898[state];

item_at_0e:
    item_or_audio_base = 1;
    item_addr = (s32)((u8 *)actor + 0xE);
    goto item_ready;

item_at_0b:
    item_or_audio_base = 1;
    item_addr = (s32)((u8 *)actor + 0xB);
    goto item_ready;

item_at_08:
    item_or_audio_base = 1;
    item_addr = (s32)((u8 *)actor + 8);
    goto item_ready;

item_default:
    item_addr = 0;
item_ready:
    action_value = ((S_80173560_0 *)action)->unk_98;
    has_item = item_or_audio_base;
    ((S_80173560_0 *)action)->unk_98 = action_value & 0xFF7F;
    state = *(u8 *)item_addr;
    if (has_item != 0) {
        state |= 0x80;
    }
    D_80175F6E = state;
    if (has_item != 0) {
        target = D_800814A8;
        ((S_80173560_1 *)actor)->unk_60 = target;
        goto copy_target_pos;
    }

    item_index = *(u8 *)item_addr;
    item_type = D_8006DE24[item_index * 20 + 0x12];
    if (item_type == 2) {
        target = ((S_80173560_1 *)actor)->unk_60;
        if (target != 0) {
copy_target_pos:
            {
                register void *target_pos ASM_REG("$3") = ((S_80173560_2_pre *)target)[-1].unk_00;
                ((S_80173560_1 *)actor)->unk_72.u = ((S_80173560_3 *)target_pos)->unk_24;
                ((S_80173560_1 *)actor)->unk_73.u = ((S_80173560_3 *)target_pos)->unk_25;
            }
        }
    } else {
        register s32 target_x ASM_REG("$2");
        s32 target_y;
        resource = func_800A05A4(actor, ((S_80173560_4 *)sprite)->unk_24,
                            ((S_80173560_4 *)sprite)->unk_25, ((S_80173560_1 *)actor)->unk_2A, 0x10);
        ((S_80173560_1 *)actor)->unk_60 = resource;
        target_x = ((S_80173560_1 *)actor)->unk_72.s;
        target_y = ((S_80173560_1 *)actor)->unk_73.s;
        if (target_x < 0) {
            target_x = -target_x;
        }
        if (target_y < 0) {
            target_y = -target_y;
        }
        ((S_80173560_1 *)actor)->unk_72.u = target_x;
        ((S_80173560_1 *)actor)->unk_73.u = target_y;
    }

    if (func_800A94A0(actor, (void *)item_addr, item_or_audio_base, (u8 *)action + 0x98) == 0) {
        return;
    }
    if (item_or_audio_base != 0) {
        D_800DCF50 = *(u8 *)item_addr;
        ((S_80173560_1 *)actor)->unk_13 |= 0x80;
    }
    direction = ((D_80083228 + ((S_80173560_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
    func_80047784(sprite, ((u8 *)((S_80173560_4 *)sprite)->unk_2C)[direction], 2);
    ((S_80173560_4 *)sprite)->unk_14 |= 0x800;
    if (item_or_audio_base != 0 && !(((S_80173560_1 *)actor)->unk_13 & 0x80)) {
        func_80175814(actor);
        func_80175D7C(actor);
    } else {
        ((S_80173560_1 *)actor)->unk_13 &= 0x7F;
        *(u16 *)&D_80175E40[0x12E] &= 0xFF7F;
        func_800BB044(actor);
    }
    ((S_80173560_0 *)action)->unk_9B.n++;
    ASM_SCHED_BARRIER();
    item_addr = (s32)&D_80175F6E;
    if (*(u16 *)item_addr & 0x80) {
        if (func_8003F270() != 0) {
            return;
        }
        func_800A56E0(0x300);
        action_value = (s16)func_800A9400(*(u16 *)item_addr & 0x7F);
        ((S_80173560_0 *)action)->unk_96.s = D_80175F40[action_value] - 0x10;
        ((S_80173560_0 *)action)->unk_9B.n++;
        return;
    }
    action_value = ((S_80173560_0 *)action)->unk_9B.v;
    action_value += 2;
    ((S_80173560_0 *)action)->unk_9B.n = action_value;
    return;

start_audio:
    ((S_80173560_0 *)action)->unk_96.u -= D_80080A84;
    if (((S_80173560_0 *)action)->unk_96.s < 3) {
        ((S_80173560_4 *)sprite)->unk_14 &= 0xF7FF;
    }
    if (((S_80173560_0 *)action)->unk_96.s > 0) {
        return;
    }
    item_id = D_80175F6E & 0x7F;
    item_or_audio_base = (s32)D_800DDAB8;
    audio_result = func_800A9400(item_id);
    sound_id = 0x1300;
    ASM_USE(sound_id);
    audio_index = audio_result << 16;
    audio_index >>= 16;
    func_800A56E0(sound_id);
    func_8003F540(0, D_8006CD58[0],
                  ((s32 *)(((audio_index << 17) >> 14) + item_or_audio_base))[0],
                  ((s32 *)(((audio_index << 17) >> 14) + item_or_audio_base))[1]);
    cd_param = func_800445E0();
    Control_CD(0x15, cd_param, 0);
    ((S_80173560_0 *)action)->unk_9B.n++;

wait_audio:
    if (func_8003F270() != 0) {
        ((S_80173560_4 *)sprite)->unk_14 |= 0x800;
        return;
    }
    ((S_80173560_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80173560_0 *)action)->unk_9B.n++;

finish_animation:
    if (!(((S_80173560_0 *)action)->unk_98 & 0x80)) {
        ((S_80173560_4 *)sprite)->unk_05--;
    }

reset_action:
    if (((S_80173560_4 *)sprite)->unk_04 == 4) {
        if (!(((S_80173560_4 *)sprite)->unk_14 & 0x1000)) {
            goto check_high_flags;
        }
    } else {
check_high_flags:
        if (!(((S_80173560_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
    }
    ((S_80173560_0 *)action)->unk_98 |= 0x80;
    if (!(((S_80173560_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80173560_4 *)sprite)->unk_24, ((S_80173560_4 *)sprite)->unk_25);
    resource = D_80175E40;
    if (((S_80173560_4 *)sprite)->unk_2C != resource) {
        (*(void * *)((u8 *)sprite + (0x2C))) = resource;
        direction = ((D_80083228 + ((S_80173560_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
        func_80047784(sprite, D_80175E40[direction], 0);
    }
    {
        s32 *action_status = &D_80083460;
        if (action_status[3] != 0) {
            return;
        }
        ((u16 *)action_status)[5]--;
    }
    ((S_80173560_0 *)action)->unk_8C = D_801710EC;
    func_800A4ACC(actor);
    ((S_80173560_1 *)actor)->unk_6D--;
    ((S_80173560_1 *)actor)->unk_46 &= 0x7FFF;
    ((S_80173560_0 *)action)->unk_98 &= 0xFFBF;
    ((S_80173560_1 *)actor)->unk_73.u = 0;
    ((S_80173560_1 *)actor)->unk_72.u = 0;
    func_800A56E0(0xB4);
}
