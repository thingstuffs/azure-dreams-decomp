#include "common.h"

#define COUNT_VALUE (D_80012BCC)
#define COUNT_STORE(x) (D_80012BCC = (x))
#define COUNT_RELOAD (D_80012BCC)
#define DIGIT0 (D_80530590[0])
#define DIGIT1 (D_80530590[1])
#define DIGIT2 (D_80530590[2])

extern void func_8003BC18(void *, void *);
extern void *func_800373DC(s32);
extern void func_80232A08(void *);
extern void *func_80232868(s32, s32, s32);
extern void func_802441A4(void *);
extern void func_80244588(void);
extern void *func_80252550(void *, void *);
extern void func_8023FA58(void *, void *, void *);
extern u8 D_8003C558[];
extern u32 D_80012BCC;
extern u32 D_80077C68[4];
extern u8 D_80077C64[];
extern u8 D_8012F130[0x20];
extern u16 D_801328F8[];
extern u8 D_80526704[];
extern u8 D_80530154[];
extern u8 D_8053016C[];
extern u8 D_8053019C[][12];
extern s16 D_805301CC[];
extern s16 D_80530590[];
extern void *D_80530598[];
extern u8 D_8052DC78[];
extern u8 D_8052D770[];

typedef struct S_func_80811C54_1 {
    u8 pad_00[0x4C];
    void *unk_4C;
    u8 pad_50[8];
    s32 unk_58;
    s16 unk_5C;
    union { u16 u; s16 s; } unk_5E;
    union { u16 u; s16 s; } unk_60;
    u16 unk_62;
    u16 unk_64;
} S_func_80811C54_1;

typedef struct S_func_80811C54_2 {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[4];
    u32 unk_10;
} S_func_80811C54_2;

typedef struct S_func_80811C54_3 {
    u8 pad_00[0x24];
    s16 unk_24;
    u8 pad_26[4];
    s16 unk_2A;
} S_func_80811C54_3;

typedef struct S_func_80811C54_4 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x60];
    s16 unk_74;
} S_func_80811C54_4;

typedef struct S_func_80811C54_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_80811C54_5;

typedef struct S_func_80811C54_6 {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[2];
    u16 unk_12;
    u8 pad_14[8];
    u16 unk_1C;
    u16 unk_1E;
} S_func_80811C54_6;

typedef struct S_func_80811C54_7 {
    union { s32 s; void *p; } unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x44];
    void *unk_50;
} S_func_80811C54_7;

/* Updates slot machine bets, reels, winning lines, and payout effects. */
void func_8052C854(void *machine, void *position)
{
    S_func_80811C54_1 *self = (S_func_80811C54_1 *)machine;
    S_func_80811C54_2 *input;
    u8 *effect_config;
    register S_func_80811C54_7 *position_or_effect;
    s32 state_or_buttons;
    s32 symbol_index;
    s32 scan_index;
    s32 row_or_digit_sum;
    s16 *payout_digits;
    s32 bet_state;
    S_func_80811C54_4 *effect_obj;

    input = (S_func_80811C54_2 *)D_8012F130;
    state_or_buttons = self->unk_5C;
    position_or_effect = (S_func_80811C54_7 *)position;
    effect_config = D_80526704;
    if ((u32)state_or_buttons >= 8U) {
        goto done;
    }
    switch (state_or_buttons) {
    case 0: goto state_0;
    case 1: goto state_1;
    case 2: goto state_2;
    case 3: goto state_3;
    case 4: goto state_4;
    case 5: goto state_5;
    case 6: goto state_6;
    case 7: goto state_7;
    }

state_0:
    self->unk_62 = 0;
    self->unk_64 = 0;
    func_802441A4(input);
    bet_state = 1;
    *(s16 *)((u8 *)self + 0x5C) = bet_state;
    if (COUNT_VALUE < 1000U) {
        goto done;
    }
    if (func_80252550(D_80530154, position_or_effect) == 0) {
        goto done;
    }
    D_80530598[0] = func_80232868(0, -80, 64);
    D_801328F8[0] = 0;
    func_80244588();
    COUNT_STORE(COUNT_VALUE - 1000);
    *(u16 *)((u8 *)self + 0x64) = 1;
    *(u16 *)((u8 *)self + 0x5E) = 5;
    *(s16 *)((u8 *)self + 0x5C) = 2;
    goto done;

state_1:
    if (input->unk_08 & 0x5000) {
        u16 ticks_left = self->unk_5E.u;
        self->unk_5E.u = ticks_left - 1;
        if ((s16)ticks_left < 0) {
            self->unk_5E.u = 0;
            goto check_bet_input;
        }
    } else {
        self->unk_5E.u = 5;
    }

check_bet_input:
    if ((input->unk_10 & 0x1000) ||
        ((input->unk_08 & 0x1000) &&
         (self->unk_5E.s <= 0))) {
        if (self->unk_64 < 3U) {
            if (COUNT_VALUE < 1000U) {
                goto done;
            }
            ++*(u16 *)((u8 *)self + 0x64);
            {
                u32 *balance = &D_80012BCC;
                COUNT_STORE(*balance - 1000);
            }
            goto done;
        }
    }

    if ((input->unk_10 & 0x4000) ||
        ((input->unk_08 & 0x4000) &&
         (self->unk_5E.s <= 0))) {
        if (self->unk_64 >= 2U) {
            COUNT_STORE(COUNT_VALUE + 1000);
            (*(u16 *)((u8 *)self + 0x64))--;
            goto done;
        }
    }

    {
        state_or_buttons = input->unk_10;
        if (state_or_buttons & 0x40) {
            self->unk_5E.u = 10;
            self->unk_5C = 3;
            goto done;
        }
        if (!(state_or_buttons & 0x20) || self->unk_64 == 0) {
            goto done;
        }
        self->unk_5E.u = 20;
        self->unk_5C = 4;
        goto done;
    }

state_2:
    {
        s32 ticks_left = self->unk_5E.u - 1;
        self->unk_5E.u = ticks_left;
        if ((s16)ticks_left > 0) {
            goto done;
        }
        COUNT_STORE(COUNT_VALUE + (s32)self->unk_64 * 1000);
        func_80232A08(D_80530598[0]);
        self->unk_5C = 0;
        goto done;
    }

state_3:
    {
        s32 ticks_left = self->unk_5E.u - 1;
        self->unk_5E.u = ticks_left;
        if ((s16)ticks_left > 0) {
            goto done;
        }
        {
            S_func_80811C54_1 *reel_slot;
            scan_index = 2;
            symbol_index = 2;
            reel_slot = (S_func_80811C54_1 *)((u8 *)self + 8);
            do {
                S_func_80811C54_3 *reel = reel_slot->unk_4C;
                reel->unk_24 = symbol_index;
                reel_slot = (S_func_80811C54_1 *)((u8 *)reel_slot - 4);
                scan_index--;
            } while (scan_index >= 0);
        }
        self->unk_5C = 5;
        goto done;
    }

state_4:
    {
        s16 reel_index = self->unk_5E.s;
        S_func_80811C54_3 *reel = ((S_func_80811C54_1 *)((u8 *)self + (s32)reel_index * 4))->unk_4C;
        if (reel->unk_24 != 3) {
            goto done;
        }
        self->unk_5C = 6;
        self->unk_60.u = 0;
        goto done;
    }

state_5:
    {
        u16 ticks_left = self->unk_60.u;
        self->unk_60.u = ticks_left - 1;
        if ((s16)ticks_left <= 0) {
            self->unk_60.u = 0;
        }
    }

    if ((input->unk_10 & 0x20) &&
        self->unk_60.s == 0) {
        s16 reel_index = self->unk_5E.s;
        S_func_80811C54_3 *reel = ((S_func_80811C54_1 *)((u8 *)self + (s32)reel_index * 4))->unk_4C;
        reel->unk_24 = 4;
        self->unk_60.u = 10;
        self->unk_5E.u = self->unk_5E.u + 1;
    }

    if (self->unk_5E.s != 3) {
        goto done;
    }
    self->unk_58 = 0;
    {
        /* Padding preserves the retail stack frame, including a dead spill slot. */
        struct MatrixFrame {
            s32 pad[22];
            s32 values[9];
            s32 tailpad[1];
        } matrix_frame;
        S_func_80811C54_1 *reel_slot_base;
        u8 *strip_base;
        u8 *matrix_cursor;
        S_func_80811C54_1 *reel_slot;
        s16 *payout_table;
        s32 bet_count;

        scan_index = 2;
        reel_slot_base = (S_func_80811C54_1 *)((u8 *)self + 8);
        strip_base = D_8053019C[2];
        matrix_cursor = (u8 *)matrix_frame.pad + 24;
        row_or_digit_sum = 2;

matrix_outer:
        {
            u8 *reel_strip;
            s32 *symbol_dst;
            S_func_80811C54_3 *reel;
            row_or_digit_sum = 2;
            reel_strip = strip_base;
            reel_slot = reel_slot_base;
            symbol_dst = (s32 *)(matrix_cursor + 96);
            do {
                {
                    reel = reel_slot->unk_4C;
                    symbol_index = reel->unk_2A;
                    /* These no-ops preserve loop placement and register allocation. */
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    symbol_index = symbol_index * 3 - symbol_index - symbol_index;
                    /* Keep this expression together to preserve temporary register allocation. */
                    *symbol_dst = reel_strip[(row_or_digit_sum + symbol_index) % 12];
                    symbol_dst--;
                    row_or_digit_sum--;
                }
            } while (row_or_digit_sum >= 0);
            reel_slot_base = (S_func_80811C54_1 *)((u8 *)reel_slot_base - 4);
            strip_base -= 12;
            matrix_cursor -= 4;
            scan_index--;
            matrix_cursor -= 8;
        }
        if (scan_index >= 0) {
            goto matrix_outer;
        }

        bet_count = self->unk_64;
        {
            /* This zero seed preserves reel_slot's reference count and a dead spill slot. */
            s32 slot_offset = (u8 *)reel_slot - (u8 *)self;
            scan_index = slot_offset * 3 - slot_offset - slot_offset - slot_offset;
            if (bet_count > 0) {
                payout_table = D_805301CC;
                do {
                    switch (scan_index) {
                    case 0: {
                        u16 win_flags;
                        if (matrix_frame.values[1] != matrix_frame.values[4] ||
                            matrix_frame.values[1] != matrix_frame.values[7]) {
                            break;
                        }
                        {
                            s32 symbol = matrix_frame.values[1];
                            s32 base_payout = (s32)payout_table[symbol] * 1000;
                            win_flags = self->unk_62;
                            self->unk_62 = win_flags | 4;
                            {
                                register s32 line_payout =
                                    (s32)self->unk_64 * base_payout;
                                self->unk_58 =
                                    line_payout + self->unk_58;
                            }
                        }
                        if (matrix_frame.values[4] == 0) {
                            u16 jackpot_flags = win_flags | 5;
                            self->unk_62 = jackpot_flags;
                        }
                        break;
                    }
                    case 1:
                        if (matrix_frame.values[0] == matrix_frame.values[3] &&
                            matrix_frame.values[0] == matrix_frame.values[6]) {
                            self->unk_62 |= 0x10;
                            {
                                s32 symbol = matrix_frame.values[0];
                                s32 base_payout = (s32)payout_table[symbol] * 1000;
                                s32 line_payout =
                                    (s32)self->unk_64 * base_payout;
                                self->unk_58 =
                                    line_payout + self->unk_58;
                            }
                            if (matrix_frame.values[0] == 0) {
                                self->unk_62 |= 1;
                            }
                        }
                        if (matrix_frame.values[2] != matrix_frame.values[5] ||
                            matrix_frame.values[2] != matrix_frame.values[8]) {
                            break;
                        }
                        self->unk_62 |= 8;
                        {
                            s32 symbol = matrix_frame.values[8];
                            s32 base_payout = (s32)payout_table[symbol] * 1000;
                            s32 line_payout =
                                (s32)self->unk_64 * base_payout;
                            self->unk_58 =
                                    line_payout + self->unk_58;
                        }
                        if (matrix_frame.values[8] == 0) {
                            self->unk_62 |= 1;
                        }
                        break;
                    case 2:
                        if (matrix_frame.values[0] == matrix_frame.values[4] &&
                            matrix_frame.values[8] == matrix_frame.values[0]) {
                            self->unk_62 |= 0x40;
                            {
                                s32 symbol = matrix_frame.values[4];
                                s32 base_payout = (s32)payout_table[symbol] * 1000;
                                s32 line_payout =
                                    (s32)self->unk_64 * base_payout;
                                self->unk_58 =
                                    line_payout + self->unk_58;
                            }
                            if (matrix_frame.values[4] == 0) {
                                self->unk_62 |= 1;
                            }
                        }
                        if (matrix_frame.values[2] != matrix_frame.values[4] ||
                            matrix_frame.values[6] != matrix_frame.values[2]) {
                            break;
                        }
                        self->unk_62 |= 0x20;
                        {
                            s32 symbol = matrix_frame.values[4];
                            s32 base_payout = (s32)payout_table[symbol] * 1000;
                            s32 line_payout =
                                (s32)self->unk_64 * base_payout;
                            self->unk_58 =
                                line_payout + self->unk_58;
                        }
                        if (matrix_frame.values[4] == 0) {
                            self->unk_62 |= 1;
                        }
                        break;
                    }
                    scan_index++;
                } while (scan_index < self->unk_64);
            }
        }
    }

state_6:
    if (self->unk_58 == 0) {
        self->unk_5E.u = 10;
        self->unk_64 = 0;
        self->unk_5C = 3;
        goto done;
    }

    if (self->unk_62 & 1) {
        effect_obj = (S_func_80811C54_4 *)func_800373DC(0x100);
        if (effect_obj != 0) {
            effect_obj->unk_10 = D_8052DC78;
        }
    }

    {
        s32 payout = self->unk_58;
        s32 payout_tens = (scan_index = payout / 1000) / 10;
        s32 hundreds = payout_tens / 10;
        s32 ones = scan_index - payout_tens * 10;
        s32 tens = payout_tens;
        s32 ones_shift_or_split = (tens -= hundreds * 10, ones << 16);
        s16 narrow_tens = (row_or_digit_sum = ones_shift_or_split >> 16, (s16)tens);
        s32 signed_tens = narrow_tens;
        s32 signed_hundreds;
        s32 hundreds_shift;
        s16 *digits = D_80530590;
        row_or_digit_sum += signed_tens;
        hundreds = hundreds % 10;
        hundreds_shift = hundreds << 16;
        payout = hundreds_shift >> 16;
        signed_hundreds = payout;
        row_or_digit_sum += signed_hundreds;

        digits[0] = ones;
        DIGIT1 = narrow_tens;
        DIGIT2 = hundreds;
        ones_shift_or_split = (row_or_digit_sum < 10);
        if (ones_shift_or_split) {
            if (signed_hundreds > 0) {
                s32 remaining_hundreds = hundreds - 1;
                row_or_digit_sum += 9;
                DIGIT2 = remaining_hundreds;
                DIGIT1 = narrow_tens + 10;
                goto start_payout;
            }
            if (narrow_tens > 0) {
                row_or_digit_sum += 9;
                DIGIT1 = narrow_tens - 1;
                digits[0] = ones + 10;
            }
        }
start_payout:
        self->unk_5E.u = 0;
        self->unk_5C = 7;
        goto done;
    }

state_7:
    {
        self->unk_5E.u++;
        if ((s16)self->unk_5E.u == 9) {
            func_802441A4(input);
        }
        if (self->unk_5E.u & 3) {
            goto done;
        }
    }

    payout_digits = (s16 *)D_80530590;
    {
        s32 hundreds_left = DIGIT2;
        if ((s32)payout_digits[0] + DIGIT1 + hundreds_left == 0) {
            if (!(self->unk_62 & 2)) {
                void *bet_effect = D_80530598[0];
                self->unk_64 = 0;
                func_80232A08(bet_effect);
                self->unk_5E.u = 10;
                self->unk_5C = 3;
            }
            self->unk_62 &= 0xFFFD;
            goto done;
        }
    }

    {
        S_func_80811C54_5 *motion;
        S_func_80811C54_6 *sprite;
        s32 tint;
        s32 sprite_offset;

        effect_obj = (S_func_80811C54_4 *)func_800373DC(0x136);

        if (effect_obj == 0) {
            goto done;
        }
        effect_obj->unk_10 = D_8052D770;
        ((S_func_80811C54_5 *)effect_obj->unk_08)->unk_00 =
            position_or_effect->unk_00.s + (s32)0xFEC00000;
        ((S_func_80811C54_5 *)effect_obj->unk_08)->unk_04 =
            position_or_effect->unk_04 + (s32)0xFFC00000;
        ((S_func_80811C54_5 *)effect_obj->unk_08)->unk_08 =
            position_or_effect->unk_08 + (s32)0xFFC00000;
        motion = effect_obj->unk_08;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        ((S_func_80811C54_5 *)effect_obj->unk_08)->unk_14 = 0x40000;
        func_8003BC18(effect_obj, D_8003C558);
        sprite = effect_obj->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        position_or_effect = (S_func_80811C54_7 *)((u8 *)effect_obj + 0x20);

        if (DIGIT2 != 0) {
            DIGIT2--;
            effect_obj->unk_74 = 2;
            goto configure_effect;
        }
        if (DIGIT1 != 0) {
            DIGIT1--;
            effect_obj->unk_74 = 1;
            sprite_offset = sprite->unk_12 - 5;
            goto set_sprite_offset;
        }
        if (DIGIT0 != 0) {
            DIGIT0--;
            effect_obj->unk_74 = 0;
            sprite_offset = sprite->unk_12 + 5;
set_sprite_offset:
            sprite->unk_12 = sprite_offset;
        }

configure_effect:
        tint = 0x00808080;
        sprite->unk_00 = (void *)D_80077C64;
        sprite->unk_08 = D_80077C68[0];
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
        sprite->unk_0C = tint;
        position_or_effect->unk_00.p = self;
        position_or_effect->unk_50 = effect_config;
        func_8023FA58((u8 *)position_or_effect + 8, effect_obj->unk_08, D_8053016C);
    }

done:
    return;
}
