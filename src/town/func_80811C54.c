#include "common.h"

#define FIELD(p, type, off) (*(type)((u8 *)(p) + (off)))
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

/* Updates slot machine bets, reels, winning lines, and payout effects. */
void func_8052C854(void *machine, void *position)
{
    u8 *self = (u8 *)machine;
    u8 *input;
    u8 *effect_config;
    register u8 *position_or_effect;
    s32 state_or_buttons;
    s32 symbol_index;
    s32 scan_index;
    s32 row_or_digit_sum;
    s16 *payout_digits;
    s32 bet_state;
    u8 *effect_obj;

    input = D_8012F130;
    state_or_buttons = FIELD(self, s16 *, 0x5C);
    position_or_effect = (u8 *)position;
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
    FIELD(self, u16 *, 0x62) = 0;
    FIELD(self, u16 *, 0x64) = 0;
    func_802441A4(input);
    bet_state = 1;
    FIELD(self, s16 *, 0x5C) = bet_state;
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
    FIELD(self, u16 *, 0x64) = 1;
    FIELD(self, u16 *, 0x5E) = 5;
    FIELD(self, s16 *, 0x5C) = 2;
    goto done;

state_1:
    if (FIELD(input, u32 *, 8) & 0x5000) {
        u16 ticks_left = FIELD(self, u16 *, 0x5E);
        FIELD(self, u16 *, 0x5E) = ticks_left - 1;
        if ((s16)ticks_left < 0) {
            FIELD(self, u16 *, 0x5E) = 0;
            goto check_bet_input;
        }
    } else {
        FIELD(self, u16 *, 0x5E) = 5;
    }

check_bet_input:
    if ((FIELD(input, u32 *, 0x10) & 0x1000) ||
        ((FIELD(input, u32 *, 8) & 0x1000) &&
         (FIELD(self, s16 *, 0x5E) <= 0))) {
        if (FIELD(self, u16 *, 0x64) < 3U) {
            if (COUNT_VALUE < 1000U) {
                goto done;
            }
            ++FIELD(self, u16 *, 0x64);
            {
                u32 *balance = &D_80012BCC;
                COUNT_STORE(*balance - 1000);
            }
            goto done;
        }
    }

    if ((FIELD(input, u32 *, 0x10) & 0x4000) ||
        ((FIELD(input, u32 *, 8) & 0x4000) &&
         (FIELD(self, s16 *, 0x5E) <= 0))) {
        if (FIELD(self, u16 *, 0x64) >= 2U) {
            COUNT_STORE(COUNT_VALUE + 1000);
            FIELD(self, u16 *, 0x64)--;
            goto done;
        }
    }

    {
        state_or_buttons = FIELD(input, u32 *, 0x10);
        if (state_or_buttons & 0x40) {
            FIELD(self, u16 *, 0x5E) = 10;
            FIELD(self, s16 *, 0x5C) = 3;
            goto done;
        }
        if (!(state_or_buttons & 0x20) || FIELD(self, u16 *, 0x64) == 0) {
            goto done;
        }
        FIELD(self, u16 *, 0x5E) = 20;
        FIELD(self, s16 *, 0x5C) = 4;
        goto done;
    }

state_2:
    {
        s32 ticks_left = FIELD(self, u16 *, 0x5E) - 1;
        FIELD(self, u16 *, 0x5E) = ticks_left;
        if ((s16)ticks_left > 0) {
            goto done;
        }
        COUNT_STORE(COUNT_VALUE + (s32)FIELD(self, u16 *, 0x64) * 1000);
        func_80232A08(D_80530598[0]);
        FIELD(self, s16 *, 0x5C) = 0;
        goto done;
    }

state_3:
    {
        s32 ticks_left = FIELD(self, u16 *, 0x5E) - 1;
        FIELD(self, u16 *, 0x5E) = ticks_left;
        if ((s16)ticks_left > 0) {
            goto done;
        }
        {
            u8 *reel_slot;
            scan_index = 2;
            symbol_index = 2;
            reel_slot = self + 8;
            do {
                u8 *reel = FIELD(reel_slot, u8 **, 0x4C);
                FIELD(reel, s16 *, 0x24) = symbol_index;
                reel_slot -= 4;
                scan_index--;
            } while (scan_index >= 0);
        }
        FIELD(self, s16 *, 0x5C) = 5;
        goto done;
    }

state_4:
    {
        s16 reel_index = FIELD(self, s16 *, 0x5E);
        u8 *reel = FIELD(
            self + (s32)reel_index * 4,
            u8 **, 0x4C);
        if (FIELD(reel, s16 *, 0x24) != 3) {
            goto done;
        }
        FIELD(self, s16 *, 0x5C) = 6;
        FIELD(self, u16 *, 0x60) = 0;
        goto done;
    }

state_5:
    {
        u16 ticks_left = FIELD(self, u16 *, 0x60);
        FIELD(self, u16 *, 0x60) = ticks_left - 1;
        if ((s16)ticks_left <= 0) {
            FIELD(self, u16 *, 0x60) = 0;
        }
    }

    if ((FIELD(input, u32 *, 0x10) & 0x20) &&
        FIELD(self, s16 *, 0x60) == 0) {
        s16 reel_index = FIELD(self, s16 *, 0x5E);
        u8 *reel = FIELD(
            self + (s32)reel_index * 4,
            u8 **, 0x4C);
        FIELD(reel, s16 *, 0x24) = 4;
        FIELD(self, u16 *, 0x60) = 10;
        FIELD(self, u16 *, 0x5E) = FIELD(self, u16 *, 0x5E) + 1;
    }

    if (FIELD(self, s16 *, 0x5E) != 3) {
        goto done;
    }
    FIELD(self, s32 *, 0x58) = 0;
    {
        /* Padding preserves the retail stack frame, including a dead spill slot. */
        struct MatrixFrame {
            s32 pad[22];
            s32 values[9];
            s32 tailpad[1];
        } matrix_frame;
        u8 *reel_slot_base;
        u8 *strip_base;
        u8 *matrix_cursor;
        u8 *reel_slot;
        s16 *payout_table;
        s32 bet_count;

        scan_index = 2;
        reel_slot_base = self + 8;
        strip_base = D_8053019C[2];
        matrix_cursor = (u8 *)matrix_frame.pad + 24;
        row_or_digit_sum = 2;

matrix_outer:
        {
            u8 *reel_strip;
            s32 *symbol_dst;
            u8 *reel;
            row_or_digit_sum = 2;
            reel_strip = strip_base;
            reel_slot = reel_slot_base;
            symbol_dst = (s32 *)(matrix_cursor + 96);
            do {
                {
                    reel = *(u8 **)(reel_slot + 0x4C);
                    symbol_index = FIELD(reel, s16 *, 0x2A);
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
            reel_slot_base -= 4;
            strip_base -= 12;
            matrix_cursor -= 4;
            scan_index--;
            matrix_cursor -= 8;
        }
        if (scan_index >= 0) {
            goto matrix_outer;
        }

        bet_count = FIELD(self, u16 *, 0x64);
        {
            /* This zero seed preserves reel_slot's reference count and a dead spill slot. */
            s32 slot_offset = reel_slot - self;
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
                            win_flags = FIELD(self, u16 *, 0x62);
                            FIELD(self, u16 *, 0x62) = win_flags | 4;
                            {
                                register s32 line_payout =
                                    (s32)FIELD(self, u16 *, 0x64) * base_payout;
                                FIELD(self, s32 *, 0x58) =
                                    line_payout + FIELD(self, s32 *, 0x58);
                            }
                        }
                        if (matrix_frame.values[4] == 0) {
                            u16 jackpot_flags = win_flags | 5;
                            FIELD(self, u16 *, 0x62) = jackpot_flags;
                        }
                        break;
                    }
                    case 1:
                        if (matrix_frame.values[0] == matrix_frame.values[3] &&
                            matrix_frame.values[0] == matrix_frame.values[6]) {
                            FIELD(self, u16 *, 0x62) |= 0x10;
                            {
                                s32 symbol = matrix_frame.values[0];
                                s32 base_payout = (s32)payout_table[symbol] * 1000;
                                s32 line_payout =
                                    (s32)FIELD(self, u16 *, 0x64) * base_payout;
                                FIELD(self, s32 *, 0x58) =
                                    line_payout + FIELD(self, s32 *, 0x58);
                            }
                            if (matrix_frame.values[0] == 0) {
                                FIELD(self, u16 *, 0x62) |= 1;
                            }
                        }
                        if (matrix_frame.values[2] != matrix_frame.values[5] ||
                            matrix_frame.values[2] != matrix_frame.values[8]) {
                            break;
                        }
                        FIELD(self, u16 *, 0x62) |= 8;
                        {
                            s32 symbol = matrix_frame.values[8];
                            s32 base_payout = (s32)payout_table[symbol] * 1000;
                            s32 line_payout =
                                (s32)FIELD(self, u16 *, 0x64) * base_payout;
                            FIELD(self, s32 *, 0x58) =
                                    line_payout + FIELD(self, s32 *, 0x58);
                        }
                        if (matrix_frame.values[8] == 0) {
                            FIELD(self, u16 *, 0x62) |= 1;
                        }
                        break;
                    case 2:
                        if (matrix_frame.values[0] == matrix_frame.values[4] &&
                            matrix_frame.values[8] == matrix_frame.values[0]) {
                            FIELD(self, u16 *, 0x62) |= 0x40;
                            {
                                s32 symbol = matrix_frame.values[4];
                                s32 base_payout = (s32)payout_table[symbol] * 1000;
                                s32 line_payout =
                                    (s32)FIELD(self, u16 *, 0x64) * base_payout;
                                FIELD(self, s32 *, 0x58) =
                                    line_payout + FIELD(self, s32 *, 0x58);
                            }
                            if (matrix_frame.values[4] == 0) {
                                FIELD(self, u16 *, 0x62) |= 1;
                            }
                        }
                        if (matrix_frame.values[2] != matrix_frame.values[4] ||
                            matrix_frame.values[6] != matrix_frame.values[2]) {
                            break;
                        }
                        FIELD(self, u16 *, 0x62) |= 0x20;
                        {
                            s32 symbol = matrix_frame.values[4];
                            s32 base_payout = (s32)payout_table[symbol] * 1000;
                            s32 line_payout =
                                (s32)FIELD(self, u16 *, 0x64) * base_payout;
                            FIELD(self, s32 *, 0x58) =
                                line_payout + FIELD(self, s32 *, 0x58);
                        }
                        if (matrix_frame.values[4] == 0) {
                            FIELD(self, u16 *, 0x62) |= 1;
                        }
                        break;
                    }
                    scan_index++;
                } while (scan_index < FIELD(self, u16 *, 0x64));
            }
        }
    }

state_6:
    if (FIELD(self, s32 *, 0x58) == 0) {
        FIELD(self, u16 *, 0x5E) = 10;
        FIELD(self, u16 *, 0x64) = 0;
        FIELD(self, s16 *, 0x5C) = 3;
        goto done;
    }

    if (FIELD(self, u16 *, 0x62) & 1) {
        effect_obj = (u8 *)func_800373DC(0x100);
        if (effect_obj != 0) {
            FIELD(effect_obj, u8 **, 0x10) = D_8052DC78;
        }
    }

    {
        s32 payout = FIELD(self, s32 *, 0x58);
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
        FIELD(self, u16 *, 0x5E) = 0;
        FIELD(self, s16 *, 0x5C) = 7;
        goto done;
    }

state_7:
    {
        FIELD(self, u16 *, 0x5E)++;
        if ((s16)FIELD(self, u16 *, 0x5E) == 9) {
            func_802441A4(input);
        }
        if (FIELD(self, u16 *, 0x5E) & 3) {
            goto done;
        }
    }

    payout_digits = (s16 *)D_80530590;
    {
        s32 hundreds_left = DIGIT2;
        if ((s32)payout_digits[0] + DIGIT1 + hundreds_left == 0) {
            if (!(FIELD(self, u16 *, 0x62) & 2)) {
                void *bet_effect = D_80530598[0];
                FIELD(self, u16 *, 0x64) = 0;
                func_80232A08(bet_effect);
                FIELD(self, u16 *, 0x5E) = 10;
                FIELD(self, s16 *, 0x5C) = 3;
            }
            FIELD(self, u16 *, 0x62) &= 0xFFFD;
            goto done;
        }
    }

    {
        u8 *motion;
        u8 *sprite;
        s32 tint;
        s32 sprite_offset;

        effect_obj = (u8 *)func_800373DC(0x136);

        if (effect_obj == 0) {
            goto done;
        }
        FIELD(effect_obj, u8 **, 0x10) = D_8052D770;
        FIELD(FIELD(effect_obj, u8 **, 8), s32 *, 0) =
            FIELD(position_or_effect, s32 *, 0) + (s32)0xFEC00000;
        FIELD(FIELD(effect_obj, u8 **, 8), s32 *, 4) =
            FIELD(position_or_effect, s32 *, 4) + (s32)0xFFC00000;
        FIELD(FIELD(effect_obj, u8 **, 8), s32 *, 8) =
            FIELD(position_or_effect, s32 *, 8) + (s32)0xFFC00000;
        motion = FIELD(effect_obj, u8 **, 8);
        FIELD(motion, s32 *, 0x10) = 0;
        FIELD(motion, s32 *, 0xC) = 0;
        FIELD(FIELD(effect_obj, u8 **, 8), s32 *, 0x14) = 0x40000;
        func_8003BC18(effect_obj, D_8003C558);
        sprite = FIELD(effect_obj, u8 **, 0xC);
        FIELD(sprite, u16 *, 0x1E) = 0x1000;
        FIELD(sprite, u16 *, 0x1C) = 0x1000;
        position_or_effect = effect_obj + 0x20;

        if (DIGIT2 != 0) {
            DIGIT2--;
            FIELD(effect_obj, s16 *, 0x74) = 2;
            goto configure_effect;
        }
        if (DIGIT1 != 0) {
            DIGIT1--;
            FIELD(effect_obj, s16 *, 0x74) = 1;
            sprite_offset = FIELD(sprite, u16 *, 0x12) - 5;
            goto set_sprite_offset;
        }
        if (DIGIT0 != 0) {
            DIGIT0--;
            FIELD(effect_obj, s16 *, 0x74) = 0;
            sprite_offset = FIELD(sprite, u16 *, 0x12) + 5;
set_sprite_offset:
            FIELD(sprite, u16 *, 0x12) = sprite_offset;
        }

configure_effect:
        tint = 0x00808080;
        FIELD(sprite, void **, 0) = (void *)D_80077C64;
        FIELD(sprite, s32 *, 8) = D_80077C68[0];
        FIELD(sprite, u8 *, 4) = 0;
        FIELD(sprite, u8 *, 5) = 0;
        FIELD(sprite, s32 *, 0xC) = tint;
        FIELD(position_or_effect, void **, 0) = self;
        FIELD(position_or_effect, void **, 0x50) = effect_config;
        func_8023FA58(position_or_effect + 8, FIELD(effect_obj, void **, 8), D_8053016C);
    }

done:
    return;
}
