#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct State8081FF68 {
    u8 pad00[0x4C];
    void *slot[3];
    s32 work;
    s16 mode;
    u16 timer;
    u16 timer2;
    u16 flags;
    u16 count;
} State8081FF68;

extern u8 D_80020224[];
extern void *D_80020244[8];
extern u8 D_80083160[];
extern u8 D_80083780[];
extern s32 D_80012D5C[];
extern s32 D_80024638[];
extern s16 D_80024630[8];
extern s16 D_800244E8[16];
extern u8 D_800244B8[0x30];
extern u8 D_80024488[0x10];
extern u8 D_80024470[];
extern u8 D_80045340[];
extern u8 D_800236BC[];
extern u8 D_80023BCC[];
extern u8 D_8007947C[];
extern s16 D_800834C8[8];

__asm__(".set D_80020244, 0x80020244");
__asm__(".set D_80024630, 0x80024630");
__asm__(".set D_80024638, 0x80024638");
__asm__(".set D_800244E8, 0x800244e8");
__asm__(".set D_800244B8, 0x800244b8");
__asm__(".set D_80024488, 0x80024488");
__asm__(".set D_800236BC, 0x800236bc");
__asm__(".set D_80023BCC, 0x80023bcc");
__asm__(".set D_8007947C, 0x8007947c");
__asm__(".set D_800834C8, 0x800834c8");

extern s16 func_800C2AE8(void *arg0);
extern void func_80093864(void);
extern s32 func_800A2A18(void *arg0, void *arg1);
extern s16 SD_Call(s32 arg0);
extern void *func_800B1BEC(s32 arg0, s32 arg1, s32 arg2);
extern void *func_80093C70(void);
extern void func_800B1DBC(void *arg0);
extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_8008F074(void *arg0, void *arg1, void *arg2);



typedef struct S_80022768_0 {
    u8 pad_00[0x58];
    s32 unk_58;
    union { u16 u; s16 s; } unk_5C;   /* accessed as both */
    union { u16 u; s16 s; } unk_5E;   /* accessed as both */
    union { u16 u; s16 s; } unk_60;   /* accessed as both */
    u16 unk_62;
    u16 unk_64;
} S_80022768_0;   /* state in func_80022768 */

typedef struct S_80022768_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80022768_1;   /* angles in func_80022768 */

typedef struct S_80022768_2 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x4];
    u32 unk_10;
} S_80022768_2;   /* global in func_80022768 */

typedef struct S_80022768_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_3;   /* slotp in func_80022768 */

typedef struct S_80022768_4 {
    u8 pad_00[0x8];
    union { u8 * p; void * p2; } unk_08;   /* accessed as both */
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0x10];
    s16 unk_24;
} S_80022768_4;   /* obj in func_80022768 */

typedef struct S_80022768_5 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_5;   /* (u8 *)(((s32)index << 2) + (s32)state) in func_80022768 */

typedef struct S_80022768_6 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_6;   /* p in func_80022768 */

typedef struct S_80022768_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80022768_7;   /* arg1 in func_80022768 */

typedef struct S_80022768_8 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_80022768_8;   /* prim in func_80022768 */

typedef struct S_80022768_9 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x8];
    s16 unk_1C;
    s16 unk_1E;
} S_80022768_9;   /* draw in func_80022768 */

typedef struct S_80022768_10 {
    void * unk_00;
    u8 pad_04[0x4C];
    void * unk_50;
    s16 unk_54;
} S_80022768_10;   /* sub in func_80022768 */

typedef struct S_80022768_11 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80022768_11;   /* source in func_80022768 */

typedef struct S_80022768_12 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_12;   /* (u8 *)(((s32)(s16)((S_80022768_0 *)state)->unk_5E.s << 2) +
                          (s32)state) in func_80022768 */

typedef struct S_80022768_13 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80022768_13;   /* ((S_80022768_6 *)p)->unk_4C in func_80022768 */

typedef struct S_80022768_14 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80022768_14;   /* ((S_80022768_4 *)obj)->unk_08.p in func_80022768 */

/* Updates slot machine bets, reel stops, winning lines, and coin payouts. */
void func_80022768(void *machine_state, void *position_input)
{
    static void *const state_labels[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3,
        &&sw_4, &&sw_5, &&sw_6, &&sw_7
    };
    State8081FF68 *state = machine_state;
    register void *position ASM_REG("$21") = position_input;
    u8 *input = D_80083160;
    u8 *payout_callback;
    s32 symbols[3][3];

    (void)state_labels;
    payout_callback = D_80020224;

    if ((u32)((u16)((S_80022768_0 *)state)->unk_5C.u - 2) < 5U) {
        s16 *angles = (s16 *)D_80083780;
        register s32 angle ASM_REG("$6");

        angle = func_800C2AE8(angles);
        if (angle > 0) {
            ((S_80022768_1 *)angles)->unk_08.at00.v = 0xFFEE0000;
            angle = func_800C2AE8(angles);
        } else {
            s16 current_angle = ((S_80022768_1 *)angles)->unk_08.at02.v;
            register s32 angle_delta ASM_REG("$2") = angle - current_angle;
            register s32 half_delta ASM_REG("$7");
            half_delta = angle_delta >> 1;
            {
                register s32 smoothed_angle ASM_REG("$2") = angle - half_delta;
                ((S_80022768_1 *)angles)->unk_08.at02.v = smoothed_angle;
            }
        }
    }

    {
        s32 mode = ((S_80022768_0 *)state)->unk_5C.s;
        if ((u32)mode >= 8U) {
            return;
        }
        goto *D_80020244[mode];
    }

sw_0:
    ((S_80022768_0 *)state)->unk_62 = 0;
    ((S_80022768_0 *)state)->unk_64 = 0;
    func_80093864();
    {
        s32 bet_mode = 1;
        do {
            ((S_80022768_0 *)state)->unk_5C.s = bet_mode;
        } while (0);
    }
    {
        s32 *money = D_80012D5C;
        if ((u32)money[0] < 100U) {
            return;
        }
        if (func_800A2A18(D_80024470, position) == 0) {
            return;
        }
        SD_Call(0x523);
        D_80024638[0] = (s32)func_800B1BEC(0, -80, 64);
        D_800834C8[0] = 0;
        func_80093C70();
        money[0] -= 100;
    }
    (*(u16 *)((u8 *)state + (0x64))) = 1;
    (*(u16 *)((u8 *)state + (0x5E))) = 5;
    (*(s16 *)((u8 *)state + (0x5C))) = 2;
    return;

sw_1:
    if ((((S_80022768_2 *)input)->unk_08 & 0x5000) != 0) {
        u16 timer = ((S_80022768_0 *)state)->unk_5E.u;
        ((S_80022768_0 *)state)->unk_5E.u = (u16)(timer - 1);
        if ((s16)timer < 0) {
            ((S_80022768_0 *)state)->unk_5E.u = 0;
        }
    } else {
        ((S_80022768_0 *)state)->unk_5E.u = 5;
    }

    if ((((S_80022768_2 *)input)->unk_10 & 0x1000) != 0 ||
        ((((S_80022768_2 *)input)->unk_08 & 0x1000) != 0 &&
        (s16)((S_80022768_0 *)state)->unk_5E.s <= 0)) {
        if (((S_80022768_0 *)state)->unk_64 < 3) {
            SD_Call(0x502);
            if ((u32)D_80012D5C[0] < 100U) {
                return;
            }
            ((S_80022768_0 *)state)->unk_64++;
            D_80012D5C[0] -= 100;
            return;
        }
    }

    if ((((S_80022768_2 *)input)->unk_10 & 0x4000) != 0 ||
        ((((S_80022768_2 *)input)->unk_08 & 0x4000) != 0 &&
        (s16)((S_80022768_0 *)state)->unk_5E.s <= 0)) {
        if (((S_80022768_0 *)state)->unk_64 >= 2) {
            SD_Call(0x502);
            D_80012D5C[0] += 100;
            ((S_80022768_0 *)state)->unk_64--;
            return;
        }
    }

    if ((((S_80022768_2 *)input)->unk_10 & 0x20) != 0) {
        ((S_80022768_0 *)state)->unk_5E.u = 10;
        ((S_80022768_0 *)state)->unk_5C.s = 3;
        return;
    }

    if ((((S_80022768_2 *)input)->unk_10 & 0x40) == 0 ||
        ((S_80022768_0 *)state)->unk_64 == 0) {
        return;
    }
    SD_Call(0x526);
    ((S_80022768_0 *)state)->unk_5E.u = 20;
    ((S_80022768_0 *)state)->unk_5C.s = 4;
    return;

sw_2:
    {
        u16 timer = (u16)(((S_80022768_0 *)state)->unk_5E.u - 1);
        ((S_80022768_0 *)state)->unk_5E.u = timer;
        if ((s16)timer > 0) {
            return;
        }
        D_80012D5C[0] += ((S_80022768_0 *)state)->unk_64 * 100;
        func_800B1DBC((void *)D_80024638[0]);
        ((S_80022768_0 *)state)->unk_5C.s = 0;
        return;
    }

sw_5:
    {
        u16 timer = (u16)(((S_80022768_0 *)state)->unk_5E.u - 1);
        u8 *reel_slot;
        register s32 reel_index ASM_REG("$7");
        s32 reel_mode;
        ((S_80022768_0 *)state)->unk_5E.u = timer;
        if ((s16)timer > 0) {
            return;
        }
        reel_index = 2;
        reel_mode = reel_index;
        reel_slot = (u8 *)state + 8;
        do {
            void *reel = ((S_80022768_3 *)reel_slot)->unk_4C;
            reel_slot -= 4;
            reel_index--;
            ((S_80022768_4 *)reel)->unk_24 = (s16)reel_mode;
        } while (reel_index >= 0);
        ((S_80022768_0 *)state)->unk_5C.s = 5;
        return;
    }

sw_3:
    {
        s16 reel_index = ((S_80022768_0 *)state)->unk_5E.s;
        void *reel = ((S_80022768_5 *)((u8 *)(((s32)reel_index << 2) + (s32)state)))->unk_4C;
        if (((S_80022768_4 *)reel)->unk_24 != 3) {
            return;
        }
        ((S_80022768_0 *)state)->unk_5C.s = 6;
        ((S_80022768_0 *)state)->unk_60.u = 0;
        return;
    }

sw_4:
    SD_Call(0x524);
    {
        u16 timer = ((S_80022768_0 *)state)->unk_60.u;
        ((S_80022768_0 *)state)->unk_60.u = timer - 1;
        if ((s16)timer <= 0)
            ((S_80022768_0 *)state)->unk_60.u = 0;
    }
    if ((((S_80022768_2 *)input)->unk_10 & 0x40) != 0 &&
        ((S_80022768_0 *)state)->unk_60.s == 0) {
        void *reel;
        SD_Call(0x522);
        reel = ((S_80022768_12 *)((u8 *)(((s32)(s16)((S_80022768_0 *)state)->unk_5E.s << 2) +
            (s32)state)))->unk_4C;
        ((S_80022768_4 *)reel)->unk_24 = 4;
        ((S_80022768_0 *)state)->unk_60.u = 10;
        ((S_80022768_0 *)state)->unk_5E.u++;
    }
    goto sw_6;

sw_6:
    {
        s32 index = 2;
        if (((S_80022768_0 *)state)->unk_5E.s != 3) {
            return;
        }
        ((S_80022768_0 *)state)->unk_58 = 0;
        {
            register u8 *reel_slot ASM_REG("$12") = (u8 *)state + 8;
            register u8 *reel_table ASM_REG("$2") = D_800244B8;
            register u8 *reel_symbols ASM_REG("$10") = reel_table + 0x18;
            s32 *symbol_row = &symbols[2][0];
            register s32 row_index ASM_REG("$6");
            u8 *strip;
            u8 *slot_cursor;
            s32 *symbol_out;

        outer_top:
            row_index = 2;
            strip = reel_symbols;
            slot_cursor = reel_slot;
            symbol_out = symbol_row + 2;
        inner_top:
            {
                register s32 reel_offset ASM_REG("$4");
                reel_offset = (s16)((S_80022768_13 *)(((S_80022768_6 *)slot_cursor)->unk_4C))->unk_2A;
                *symbol_out = strip[(row_index + reel_offset) % 12];
                symbol_out--;
            }
            if (--row_index >= 0) goto inner_top;
            reel_slot -= 4;
            reel_symbols -= 12;
            symbol_row -= 3;
            if (--index >= 0) goto outer_top;

            {
                index = 0;
                if (((S_80022768_0 *)state)->unk_64 == 0)
                    goto count_done;
                {
                    s16 *payout_table = D_800244E8;
                    register s16 *payouts = payout_table;
                    do {
                        s32 payout;
                        s32 symbol_payout;
                        s32 symbol;
                        u16 flags;
                        switch (index) {
                        case 0:
                            if (symbols[0][1] == symbols[1][1] &&
                                symbols[0][1] == symbols[2][1]) {
                                symbol = symbols[0][1];
                                symbol_payout = (s32)payouts[symbol] * 100;
                                payout = ((S_80022768_0 *)state)->unk_64 * symbol_payout;
                                flags = ((S_80022768_0 *)state)->unk_62;
                                ((S_80022768_0 *)state)->unk_62 = flags | 4;
                                ((S_80022768_0 *)state)->unk_58 += payout;
                                if (symbols[1][1] == 0) {
                                    ((S_80022768_0 *)state)->unk_62 = flags | 5;
                                }
                            }
                            break;
                        case 1:
                            if (symbols[0][0] == symbols[1][0] &&
                                symbols[0][0] == symbols[2][0]) {
                                ((S_80022768_0 *)state)->unk_62 |= 0x10;
                                symbol = symbols[0][0];
                                symbol_payout = (s32)payouts[symbol] * 100;
                                payout = ((S_80022768_0 *)state)->unk_64 * symbol_payout;
                                ((S_80022768_0 *)state)->unk_58 += payout;
                                if (symbols[0][0] == 0) {
                                    ((S_80022768_0 *)state)->unk_62 |= 1;
                                }
                            }
                            if (symbols[0][2] == symbols[1][2] &&
                                symbols[0][2] == symbols[2][2]) {
                                ((S_80022768_0 *)state)->unk_62 |= 8;
                                symbol = symbols[2][2];
                                symbol_payout = (s32)payouts[symbol] * 100;
                                payout = ((S_80022768_0 *)state)->unk_64 * symbol_payout;
                                ((S_80022768_0 *)state)->unk_58 += payout;
                                {
                                    s32 bottom_symbol = symbols[2][2];
                                    if (bottom_symbol == 0) {
                                        ((S_80022768_0 *)state)->unk_62 |= 1;
                                    }
                                }
                            }
                            break;
                        case 2:
                            if (symbols[0][0] == symbols[1][1] &&
                                symbols[2][2] == symbols[0][0]) {
                                ((S_80022768_0 *)state)->unk_62 |= 0x40;
                                symbol = symbols[1][1];
                                symbol_payout = (s32)payouts[symbol] * 100;
                                payout = ((S_80022768_0 *)state)->unk_64 * symbol_payout;
                                ((S_80022768_0 *)state)->unk_58 += payout;
                                if (symbols[1][1] == 0) {
                                    ((S_80022768_0 *)state)->unk_62 |= 1;
                                }
                            }
                            if (symbols[0][2] == symbols[1][1] &&
                                symbols[2][0] == symbols[0][2]) {
                                ((S_80022768_0 *)state)->unk_62 |= 0x20;
                                symbol = symbols[1][1];
                                symbol_payout = (s32)payouts[symbol] * 100;
                                payout = ((S_80022768_0 *)state)->unk_64 * symbol_payout;
                                ((S_80022768_0 *)state)->unk_58 += payout;
                                if (symbols[1][1] == 0) {
                                    ((S_80022768_0 *)state)->unk_62 |= 1;
                                }
                            }
                            break;
                        }
                        index++;
                    } while (index < ((S_80022768_0 *)state)->unk_64);
                }
            }
        count_done:
        }
        if (((S_80022768_0 *)state)->unk_58 == 0) {
            ((S_80022768_0 *)state)->unk_5E.u = 10;
            ((S_80022768_0 *)state)->unk_64 = 0;
            ((S_80022768_0 *)state)->unk_5C.s = 3;
            return;
        }

        if ((((S_80022768_0 *)state)->unk_62 & 1) != 0) {
            register void *jackpot_effect ASM_REG("$17") = func_8003FC64(0x100);
            if (jackpot_effect != NULL) {
                ((S_80022768_4 *)jackpot_effect)->unk_10 = D_80023BCC;
            }
        }

        {
            register s32 digit_work ASM_REG("$2") = ((S_80022768_0 *)state)->unk_58;
            s32 tens;
            s32 hundreds;
            s32 raw_units;
            s32 raw_tens;
            s32 raw_hundreds;
            s32 units_digit;
            s32 tens_digit;
            s32 hundreds_digit;
            s32 thousands_value;
            register s32 digit_sum ASM_REG("$6");
            index = digit_work / 100;
            tens = index / 10;
            digit_work = tens * 10;
            raw_units = index - digit_work;
            digit_work = raw_units << 16;
            units_digit = digit_work >> 16;
            ASM_KEEP_NV(units_digit);
            hundreds = tens / 10;
            digit_work = hundreds * 10;
            raw_tens = tens - digit_work;
            digit_work = raw_tens << 16;
            tens_digit = digit_work >> 16;
            digit_sum = units_digit + tens_digit;
            thousands_value = (hundreds / 10) * 10;
            raw_hundreds = hundreds - thousands_value;
            digit_work = raw_hundreds << 16;
            hundreds_digit = digit_work >> 16;
            D_80024630[0] = raw_units;
            D_80024630[1] = raw_tens;
            D_80024630[2] = raw_hundreds;
            {
                digit_sum += hundreds_digit;
                digit_work = digit_sum < 10;
                if (digit_work) {
                    if (hundreds_digit > 0) {
                        s32 adjusted = raw_hundreds - 1;
                        D_80024630[2] = adjusted;
                        adjusted = raw_tens + 10;
                        D_80024630[1] = adjusted;
                    } else if (tens_digit > 0) {
                        s32 adjusted = raw_tens - 1;
                        D_80024630[1] = adjusted;
                        adjusted = raw_units + 10;
                        D_80024630[0] = adjusted;
                    }
                }
            }
        }
        ((S_80022768_0 *)state)->unk_5E.u = 0;
        ((S_80022768_0 *)state)->unk_5C.s = 7;
        return;
    }

sw_7:
    ((S_80022768_0 *)state)->unk_5E.u++;
    if ((s16)((S_80022768_0 *)state)->unk_5E.u == 9) {
        func_80093864();
    }
    if ((((S_80022768_0 *)state)->unk_5E.u & 3) != 0) {
        return;
    }
    {
        s16 *digits = D_80024630;
        if ((s16)digits[0] + (s16)digits[1] + (s16)digits[2] == 0) {
            if ((((S_80022768_0 *)state)->unk_62 & 2) == 0) {
                void *bet_display = (void *)D_80024638[0];
                ((S_80022768_0 *)state)->unk_64 = 0;
                func_800B1DBC(bet_display);
                ((S_80022768_0 *)state)->unk_5E.u = 10;
                ((S_80022768_0 *)state)->unk_5C.s = 3;
            }
            ((S_80022768_0 *)state)->unk_62 &= (u16)~2;
            return;
        }

        {
            void *coin = func_8003FC64(0x136);
            void *payout_obj;
            u8 *primitive;
            u8 *sprite;
            register u8 *payout_state ASM_REG("$18");
            if (coin == NULL) {
                return;
            }
            payout_obj = coin;
            ((S_80022768_4 *)coin)->unk_10 = D_800236BC;
            ((S_80022768_14 *)(((S_80022768_4 *)coin)->unk_08.p))->unk_00 =
                ((S_80022768_7 *)position)->unk_00 + (s32)0xFEC00000;
            ((S_80022768_14 *)(((S_80022768_4 *)coin)->unk_08.p))->unk_04 =
                ((S_80022768_7 *)position)->unk_04 + (s32)0xFFC00000;
            ((S_80022768_14 *)(((S_80022768_4 *)coin)->unk_08.p))->unk_08 =
                ((S_80022768_7 *)position)->unk_08 + (s32)0xFFC00000;
            primitive = ((S_80022768_4 *)coin)->unk_08.p;
            ((S_80022768_8 *)primitive)->unk_10 = 0;
            ((S_80022768_8 *)primitive)->unk_0C = 0;
            ((S_80022768_14 *)(((S_80022768_4 *)coin)->unk_08.p))->unk_14 = 0x40000;
            func_8004491C(payout_obj, D_80045340);
            sprite = ((S_80022768_4 *)coin)->unk_0C;
            ((S_80022768_9 *)sprite)->unk_1E = 0x1000;
            ((S_80022768_9 *)sprite)->unk_1C = 0x1000;
            payout_state = (u8 *)coin + 0x20;
            if (digits[2] != 0) {
                digits[2]--;
                ((S_80022768_10 *)payout_state)->unk_54 = 2;
            } else if (digits[1] != 0) {
                digits[1]--;
                ((S_80022768_10 *)payout_state)->unk_54 = 1;
                ((S_80022768_9 *)sprite)->unk_12 = (u16)(((S_80022768_9 *)sprite)->unk_12 - 5);
            } else if (digits[0] != 0) {
                digits[0]--;
                ((S_80022768_10 *)payout_state)->unk_54 = 0;
                ((S_80022768_9 *)sprite)->unk_12 = (u16)((*(u16 *)((u8 *)sprite + (0x12))) + 5);
            }
            {
                u8 *primitive = sprite;
                u8 *sprite_data = D_8007947C;
                (*(void * *)((u8 *)primitive + (0))) = sprite_data;
                ((S_80022768_8 *)primitive)->unk_08 = ((S_80022768_11 *)sprite_data)->unk_04;
                ((S_80022768_8 *)primitive)->unk_04 = 0;
                ((S_80022768_8 *)primitive)->unk_05 = 0;
                ((S_80022768_8 *)primitive)->unk_0C = 0x00808080;
            }
            ((S_80022768_10 *)payout_state)->unk_00 = state;
            ((S_80022768_10 *)payout_state)->unk_50 = payout_callback;
            func_8008F074(payout_state + 8, ((S_80022768_4 *)coin)->unk_08.p2, D_80024488);
        }
    }
}
