#include "common.h"

typedef struct S_func_8080F4A4_1 {
    s32 unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
    s16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    s16 unk_22;
    s16 unk_24;
} S_func_8080F4A4_1;

typedef struct S_func_8080F4A4_2 {
    s16 unk_00;
    s16 unk_02;
    void * unk_04;
    u8 pad_08[0x15];
    s8 unk_1D;
    u8 pad_1E[0x36];
    s16 unk_54;
    s16 unk_56;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
} S_func_8080F4A4_2;

typedef struct S_func_8080F4A4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_func_8080F4A4_3;

typedef struct S_func_8080F4A4_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x8];
    u16 unk_10;
} S_func_8080F4A4_4;

typedef struct S_func_8080F4A4_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0x10];
    void * unk_24;
} S_func_8080F4A4_5;

typedef struct S_func_8080F4A4_6 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_8080F4A4_6;

typedef struct S_func_8080F4A4_7 {
    u8 pad_00[0x70];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
} S_func_8080F4A4_7;

typedef struct S_func_8080F4A4_8 {
    u8 pad_00[0x70];
    s16 unk_70;
} S_func_8080F4A4_8;

typedef struct S_func_8080F4A4_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_func_8080F4A4_9;

typedef s32 M2C_UNK;
#ifndef NULL
#define NULL 0
#endif

/* RAW m2c DRAFT -- NOT A LANDABLE CANDIDATE.
 * Row func_8080F4A4, disassembled at the RECOVERED true load base
 * delta=0x7FD9AC00 (true vram 0x8052A0A4), not the synthetic
 * 0x80080000 sweep base the window yaml still declares.
 * Adopting this requires the after-wave overlay-base fix; do
 * not copy into work/overlay_wave/candidates/ (that directory is
 * globbed by tools/gen_noreturn_syms.py).
 */
void *func_800374FC(s32, void *);            /* extern */
void func_8003BC18(void *, void *);           /* extern */
s32 func_80052374(s32);                             /* extern */
void func_80058F88(s32);                     /* extern */
s32 func_8006A3A4(s32);                             /* extern */
s32 func_8006A470(s32);                             /* extern */
s32 func_80071494();                                /* extern */
s32 func_80232868(s32, s32, s32);       /* extern */
void func_80232A08(s32);                         /* extern */
void func_802441A4();                   /* extern */
void func_80244588();                            /* extern */
void func_802445FC(s32, ...);    /* extern */
void func_80244660(void *, ...); /* extern */
void func_80529438(void *, ...);           /* extern */
extern u32 D_80012BCC[3];
extern u32 D_80012BC8[4];
extern u8 D_8003C558[16];
extern u8 D_80095AA0[16];
extern u8 D_8012F130[0x14];
extern u8 D_801328C8[16];
extern u8 D_801328E8[0x20];
extern s32 D_80132AE8[6];
extern s32 D_802BC5C8[3];
extern s32 D_80530588[3];
extern u8 D_802483B8[];
extern u8 D_80290268[];
extern u8 D_80290270[];
extern u8 D_80290290[];
extern u8 D_80290298[];
extern u8 D_802902A8[];
extern u8 D_8052B054[];
extern u8 D_8052B1EC[];
extern u8 D_8053012C[];
/* Updates the betting game, its animations, and payout or refund coins. */
void func_8052A0A4(S_func_8080F4A4_1 *game) {
    u8 spawn_data[0x80];
#define spawn_mode ((S_func_8080F4A4_2 *)spawn_data)->unk_00
#define spawn_delay ((S_func_8080F4A4_2 *)spawn_data)->unk_02
#define spawn_parent ((S_func_8080F4A4_2 *)spawn_data)->unk_04
#define spawn_variant ((S_func_8080F4A4_2 *)spawn_data)->unk_1D
#define coin_kind ((S_func_8080F4A4_2 *)spawn_data)->unk_54
#define coin_index ((S_func_8080F4A4_2 *)spawn_data)->unk_56
#define spawn_x ((S_func_8080F4A4_2 *)spawn_data)->unk_58
#define spawn_y ((S_func_8080F4A4_2 *)spawn_data)->unk_5C
#define spawn_z ((S_func_8080F4A4_2 *)spawn_data)->unk_60
#define velocity_x ((S_func_8080F4A4_2 *)spawn_data)->unk_64
#define velocity_y ((S_func_8080F4A4_2 *)spawn_data)->unk_68
#define velocity_z ((S_func_8080F4A4_2 *)spawn_data)->unk_6C
#define ones_left ((S_func_8080F4A4_2 *)spawn_data)->unk_70
#define tens_left ((S_func_8080F4A4_2 *)spawn_data)->unk_72
#define hundreds_left ((S_func_8080F4A4_2 *)spawn_data)->unk_74
    M2C_UNK bounce_anim;
    M2C_UNK settle_anim;
    s16 hundreds;
    s16 tens;
    s16 ones;
    s32 next_kind;
    s16 random_kind;
    s16 coins_left;
    s32 next_coin;
    s32 state_or_buttons;
    s32 *sprite_entry;
    s32 column_offset;
    s32 round_handle;
    s32 odds;
    s32 coin_angle;
    s32 sprite_scale;
    s32 payout_multiplier;
    s32 coin_count;
    s32 sprite_index;
    s32 payout_or_index;
    s32 new_bet;
    s32 bounce_speed;
    s32 settle_speed;
    u16 rotation;
    u16 initial_flags;
    s32 payout_steps;
    u16 payout_delay;
    u16 finish_delay;
    u16 refund_steps;
    s16 repeat_delay;
    u16 spin_delay;
    u16 move_delay;
    u16 bounce_frame;
    u16 settle_frame;
    u16 result_delay;
    u16 finish_flags;
    s16 refund_units;
    s32 bounce_y_speed;
    s32 flags_or_z;
    s32 state_or_x;
    S_func_8080F4A4_8 *coin_counts;
    S_func_8080F4A4_3 *input;
    S_func_8080F4A4_4 *animated_sprite;
    S_func_8080F4A4_6 *sprite_data;
    S_func_8080F4A4_7 *game_data;
    S_func_8080F4A4_5 *sprite;

    input = (S_func_8080F4A4_3 *)&D_8012F130;
    animated_sprite = (S_func_8080F4A4_4 *)&D_801328E8;
    state_or_buttons = game->unk_18;
    game_data = (S_func_8080F4A4_7 *)(game->unk_00 + 0x20);
    switch (state_or_buttons) {
    case 0:
        initial_flags = game->unk_20;
        D_802BC5C8[0] = 1;
        game->unk_22 = 3;
        game->unk_1E = 0U;
        game->unk_14 = 0;
        game->unk_20 = (u16) (initial_flags & 0xFFFD);
        func_802441A4(input);
        func_80058F88(0x700);
        flags_or_z = game->unk_20;
        state_or_x = 1;
        game->unk_18 = state_or_x;
        game->unk_20 = (u16) (flags_or_z & 0xFFF7);
        spawn_mode = 0;
        spawn_parent = game;
        coin_kind = 2;
        do {
            coin_index = 9;
spawn_column:
            spawn_y = 0x03E00000;
            velocity_z = 0;
            velocity_y = 0;
            velocity_x = 0;
            column_offset = coin_kind << 0x16;
            state_or_x = 0x05200000 - column_offset;
            spawn_x = state_or_x;
            flags_or_z = 0 - (coin_index << 0x13);
            spawn_z = flags_or_z;
            func_80529438(&spawn_mode, &spawn_x, column_offset);
            next_coin = (u16) coin_index - 1;
            coin_index = next_coin;
            if ((s16) next_coin >= 0) {
                goto spawn_column;
            }
            next_kind = (u16) coin_kind - 1;
            coin_kind = next_kind;
        } while ((s16) next_kind >= 0);
        sprite_index = 2;
        sprite_scale = 0x1000;
        sprite_entry = (s32 *)D_8053012C;
        do {
            sprite = func_800374FC(0x112, &D_801328C8);
            if (sprite != NULL) {
                sprite_data = sprite->unk_0C;
                sprite->unk_10 = (s32 *)D_8052B054;
                func_8003BC18(sprite, &D_8003C558);
                ((S_func_8080F4A4_9 *)sprite->unk_08)->unk_00 = (s32) ((sprite_index << 0x17) + 0x04600000);
                ((S_func_8080F4A4_9 *)sprite->unk_08)->unk_04 = 0x03600000;
                ((S_func_8080F4A4_9 *)sprite->unk_08)->unk_08 = 0xFE000000;
                sprite_data->unk_1E = sprite_scale;
                sprite_data->unk_1C = sprite_scale;
                sprite_data->unk_14 = (u16) (sprite_data->unk_14 | 0xC);
                sprite_data->unk_08 = (s32) *sprite_entry;
                sprite_data->unk_04 = 0;
                sprite_data->unk_05 = 0;
                sprite_data->unk_0C = 0x808080;
                sprite->unk_24 = game;
            }
            sprite_index -= 1;
            sprite_entry -= 1;
        } while (sprite_index >= 0);
        break;
    case 1:
        if (game->unk_22 != 3) {
            round_handle = func_80232868(0, -0x50, 0x40);
            odds = 6 / (s32) (game->unk_22 + 1);
            D_80530588[0] = round_handle;
            game->unk_10 = odds;
            if (func_80052374(odds) == 0) {
                D_80132AE8[5] = 0;
                D_80132AE8[4] = 0;
                D_80132AE8[3] = 0;
                animated_sprite->unk_10 = 0U;
                func_802445FC((s32)D_80290268);
                animated_sprite->unk_00 = (s32)D_802483B8;
                animated_sprite->unk_04 = (s32)D_8052B1EC;
            }
            game_data->unk_70 = 1;
            game_data->unk_72 = 0x10;
            game_data->unk_74 = 0x14;
            game->unk_1A = 5U;
            game->unk_18 = 2;
        }
        break;
    case 2:
        if (input->unk_08 & 0x5000) {
            repeat_delay = game->unk_1A;
            game->unk_1A = (u16) (repeat_delay - 1);
            if (repeat_delay < 0) {
                game->unk_1A = 0U;
            }
        } else {
            game->unk_1A = 5U;
        }
        if (((input->unk_10 & 0x1000) || ((input->unk_08 & 0x1000) && ((s16) game->unk_1A <= 0))) && (game->unk_14 <= 0x1869F) && ((u32) D_80012BCC[0] >= 0x3E8U)) {
            D_80012BC8[1] = D_80012BCC[0] - 0x3E8;
            new_bet = game->unk_14 + 0x3E8;
            goto store_bet;
        }
        if (((input->unk_10 & 0x4000) || ((input->unk_08 & 0x4000) && ((s16) game->unk_1A <= 0))) && (game->unk_14 >= 0x3E8)) {
            D_80012BC8[1] = D_80012BCC[0] + 0x3E8;
            new_bet = game->unk_14 - 0x3E8;
store_bet:
            game->unk_14 = new_bet;
        }
        game->unk_1E = (u16) (game->unk_14 / 1000);
        state_or_buttons = input->unk_10;
        if (state_or_buttons & 0x20) {
            if (game->unk_14 > 0) {
                game->unk_18 = 3;
                game->unk_1A = 9U;
                D_80132AE8[5] = -0x240000;
            }
        } else if (state_or_buttons & 0x40) {
            if (game_data->unk_70 != 0) {
                game_data->unk_70 = 3;
            }
            game->unk_18 = 0xA;
            func_80244660(animated_sprite, &D_80132AE8[0], &D_80095AA0);
        }
        break;
    case 3:
        animated_sprite->unk_10 = (u16) ((animated_sprite->unk_10 + 0x200) & 0xFFF);
        spin_delay = game->unk_1A - 1;
        game->unk_1A = spin_delay;
        if ((spin_delay << 0x10) <= 0) {
            game->unk_1A = 0xAU;
            D_80132AE8[3] = (s32) (0x03600000 - D_80132AE8[0]) / (s16) game->unk_1A;
            D_80132AE8[4] = (s32) (0x02A00000 - D_80132AE8[1]) / (s16) game->unk_1A;
            game->unk_18 = 0xB;
        }
        break;
    case 11:
        animated_sprite->unk_10 = (u16) ((animated_sprite->unk_10 + 0x200) & 0xFFF);
        move_delay = game->unk_1A - 1;
        game->unk_1A = move_delay;
        if ((move_delay << 0x10) <= 0) {
            D_80132AE8[0] = 0x03600000;
            D_80132AE8[1] = 0x02A00000;
            D_80132AE8[5] = 0x180000;
            D_80132AE8[4] = 0;
            D_80132AE8[3] = 0;
            game->unk_18 = 0xC;
        }
        break;
    case 12: {
        s32 landing_z;
        s32 *position_z;
        position_z = &D_80132AE8[2];
        landing_z = (s32)0xFF000000;
        rotation = (animated_sprite->unk_10 + 0x200) & 0xFFF;
        animated_sprite->unk_10 = rotation;
        if ((*position_z >= landing_z) && (rotation == 0)) {
            *position_z = landing_z;
            game->unk_18 = 4;
            func_80244660(animated_sprite, position_z - 2, &D_80095AA0, landing_z);
            func_80244588();
        }
        break;
    }
    case 4:
        if ((input->unk_10 & 0x20) && (game_data->unk_70 == 2)) {
            func_802445FC((s32)D_80290290);
            D_80132AE8[4] = 0x48000;
            D_80132AE8[5] = -0xC0000;
            game->unk_1C = 0U;
            game->unk_18 = 5;
        }
        break;
    case 5:
        D_80132AE8[1] += D_80132AE8[4];
        D_80132AE8[2] += D_80132AE8[5];
        if (D_80132AE8[5] <= 0x9FFFF) {
            D_80132AE8[5] += 0x20000;
        }
        bounce_frame = game->unk_1C;
        game->unk_1C = (u16) (bounce_frame + 1);
        switch ((s16) bounce_frame) {
        case 0x0:
            goto bounce_frame_0;
        case 0x15:
        case 0x25:
        case 0x31:
        case 0x3E:
            goto bounce_anim_98;
        case 0x5:
            goto bounce_frame_5;
        case 0x19:
        case 0x29:
        case 0x35:
            goto bounce_anim_a8;
        case 0x14:
            goto bounce_frame_20;
        case 0x24:
            goto bounce_frame_36;
        case 0x30:
            goto bounce_frame_48;
        case 0x3D:
            goto bounce_frame_61;
        default:
            goto bounce_done;
        }
bounce_frame_0:
        bounce_anim = (s32)D_80290298;
        goto set_bounce_anim;
bounce_frame_5:
        bounce_anim = (s32)D_802902A8;
        goto set_bounce_anim;
bounce_frame_20:
        bounce_y_speed = 0x18000;
        bounce_anim = (s32)D_80290268;
        D_80132AE8[5] = -0xC0000;
        D_80132AE8[4] = bounce_y_speed;
        goto set_bounce_anim;
bounce_anim_a8:
        bounce_anim = (s32)&D_80290298[0x10];
        goto set_bounce_anim;
bounce_anim_98:
        bounce_anim = (s32)&D_80290290[8];
        goto set_bounce_anim;
bounce_frame_36:
        bounce_anim = (s32)D_80290268;
        D_80132AE8[5] = -0x80000;
        D_80132AE8[4] = 0x20000;
        goto set_bounce_anim;
bounce_frame_48:
        bounce_speed = -0x40000;
        goto set_bounce_speed;
bounce_frame_61:
        bounce_speed = -0x38000;
set_bounce_speed:
        D_80132AE8[5] = bounce_speed;
        bounce_anim = (s32)D_80290268;
        goto set_bounce_anim;
set_bounce_anim:
        func_802445FC(bounce_anim);
bounce_done:
        if (game_data->unk_70 == 3) {
            D_80132AE8[5] = -0x50000;
            D_80132AE8[4] = 0;
            D_80132AE8[2] = -0x400000;
            func_802445FC((s32)D_80290268);
            game->unk_1C = 0U;
            game->unk_18 = 6;
        }
        break;
    case 6:
        D_80132AE8[2] += D_80132AE8[5];
        D_80132AE8[5] += 0x10000;
        settle_frame = game->unk_1C;
        game->unk_1C = (u16) (settle_frame + 1);
        switch ((s16) settle_frame) {
        case 0:
        case 11:
        case 19:
            goto settle_anim_98;
        case 5:
            goto settle_anim_a8;
        case 10:
            goto settle_frame_10;
        case 26:
            goto settle_frame_26;
        case 18:
            goto settle_frame_18;
        default:
            goto settle_done;
        }
settle_anim_98:
        settle_anim = (s32)D_80290298;
        goto set_settle_anim;
settle_anim_a8:
        settle_anim = (s32)D_802902A8;
        goto set_settle_anim;
settle_frame_10:
        settle_speed = -0x40000;
        goto set_settle_speed;
settle_frame_18:
        settle_speed = -0x30000;
set_settle_speed:
        D_80132AE8[5] = settle_speed;
settle_frame_26:
        settle_anim = (s32)D_80290268;
        goto set_settle_anim;
set_settle_anim:
        func_802445FC(settle_anim);
settle_done:
        if ((s16) game->unk_1C == 0x1C) {
            game_data->unk_70 = 4;
            D_80132AE8[5] = 0;
            D_80132AE8[2] = -0x400000;
            func_802445FC((s32)D_80290268);
            game->unk_1C = 3U;
            game->unk_18 = 7;
        }
        break;
    case 7:
        D_80132AE8[0] = (func_8006A3A4(0x1000 - (s16) game->unk_1A) * 0xA00) + 0x03600000;
        D_80132AE8[1] = (func_8006A470(0x1000 - (s16) game->unk_1A) * 0xA00) + 0x03600000;
        result_delay = game->unk_1C - 1;
        game->unk_1C = result_delay;
        if ((result_delay << 0x10) == 0) {
            func_802445FC((s32)D_80290270);
        }
        if (game_data->unk_70 == 0) {
            func_802441A4();
            if (game->unk_22 == game->unk_24) {
                game_data->unk_70 = 6;
                game->unk_1A = 0x1EU;
                game->unk_18 = 8;
            } else {
                game->unk_14 = 0;
                game->unk_18 = 0xA;
            }
        }
        break;
    case 8: {
        s32 payout;
        payout_steps = game->unk_1E - 2;
        game->unk_1E = payout_steps;
        if ((s16)payout_steps < 0) {
            game->unk_1E = 0U;
            game->unk_20 = (u16) (game->unk_20 | 8);
        }
        payout_delay = game->unk_1A - 1;
        game->unk_1A = payout_delay;
        if (((payout_delay << 0x10) <= 0) && (game->unk_20 & 8)) {
            payout = game->unk_14;
            payout_multiplier = game->unk_10;
            game->unk_1A = 0xF0U;
            payout *= payout_multiplier;
            payout_or_index = payout / 1000;
            ones = payout_or_index % 10;
            tens = (payout_or_index / 10) % 10;
            ones_left = ones;
            tens_left = tens;
            hundreds = ((payout_or_index / 10) / 10) % 10;
            coin_count = ones;
            coin_count += tens;
            coin_count += hundreds;
            hundreds_left = hundreds;
            if (coin_count < 0xA) {
                if (hundreds > 0) {
                    coin_count += 9;
                    hundreds_left = hundreds - 1;
                    tens_left = tens + 0xA;
                } else if (tens > 0) {
                    coin_count += 9;
                    tens_left = tens - 1;
                    ones_left = ones + 0xA;
                }
            }
            payout_or_index = 0;
            game->unk_20 = (u16) (game->unk_20 & 0xFFF7);
            spawn_mode = 1;
            spawn_parent = game;
            spawn_variant = 0;
            spawn_delay = 8;
            if (coin_count > 0) {
                do {
                    do {
                        random_kind = func_80071494() % 3;
                        coin_kind = random_kind;
                        coin_counts = (S_func_8080F4A4_8 *) (((s32) (random_kind << 0x10) >> 0xF) + (s32) spawn_data);
                        coins_left = coin_counts->unk_70;
                    } while (coins_left <= 0);
                    do { coin_counts->unk_70 = (s16) (coins_left - 1); } while (0);
                    spawn_x = 0x03600000;
                    coin_angle = (s32) (payout_or_index << 0xC) / coin_count;
                    payout_or_index += 1;
                    spawn_y = 0x03600000;
                    spawn_z = 0xFF800000;
                    velocity_x = func_8006A3A4(coin_angle) * 0x140;
                    velocity_y = func_8006A470(coin_angle) * 0x140;
                    velocity_z = 0xFFF80000;
                    func_80529438(&spawn_mode, &spawn_x);
                } while (payout_or_index < coin_count);
            }
            game->unk_18 = 9;
        }
        break;
    }
    case 9:
        finish_delay = game->unk_1A - 1;
        game->unk_1A = finish_delay;
        if ((finish_delay << 0x10) <= 0) {
            func_80232A08(D_80530588[0]);
            game->unk_18 = 0;
            finish_flags = game->unk_20 | 2;
            goto store_finish_flags;
        }
        break;
    case 10:
        if (game->unk_14 != 0) {
            u32 refunded_gold;
            refund_units = (s16) game->unk_1E;
            refunded_gold = D_80012BCC[0] + ((refund_units >= 2) ? 0x7D0 : 0x3E8);
            D_80012BC8[1] = refunded_gold;
        }
        refund_steps = game->unk_1E - 2;
        game->unk_1E = refund_steps;
        if ((refund_steps << 0x10) <= 0) {
            func_80232A08(D_80530588[0]);
            game->unk_1E = 0U;
            game->unk_18 = 0;
            finish_flags = game->unk_20 | 0xA;
store_finish_flags:
            game->unk_20 = finish_flags;
        }
        break;
    }
    game->unk_20 = (u16) (game->unk_20 & 0xFFFE);
}
