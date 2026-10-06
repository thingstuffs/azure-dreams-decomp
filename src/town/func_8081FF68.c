#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct State8081FF68 {
    u8 pad00[0x4C];
    void *slot[3];
    s32 work;
    union { u16 u; s16 s; } mode;      /* accessed as both */
    union { u16 u; s16 s; } timer;     /* accessed as both */
    union { u16 u; s16 s; } timer2;    /* accessed as both */
    u16 flags;
    u16 count;
} State8081FF68;

extern u8 D_80020224[];
extern s32 D_80012D5C[];
extern s32 D_80024638[];
extern s16 D_80024630[8];
extern s16 D_800244E8[16];
extern u8 D_800244B8[0x30];
extern u8 D_80024488[0x10];
extern u8 D_80024470[];
extern u8 D_800236BC[];
extern u8 D_80023BCC[];
extern u8 D_8007947C[];
extern s16 D_800834C8[8];


extern s16 func_800C2AE8(void *position);
extern void func_80093864(void);
extern s32 func_800A2A18(void *box, void *offset);
extern s16 SD_Call(s32 value);
extern void *func_800B1BEC(s32 setup_value, s32 x, s32 y);
extern void *func_80093C70(void);
extern void func_800B1DBC(void *object);
extern void *func_8003FC64(s32 value);
extern void func_8004491C(void *entry, void *registration_id);
extern void func_8008F074(void *record, void *setup_value, void *setup_param);


typedef struct ReelSlotCursor {
    u8 pad_00[0x4C];
    void *reel;
} ReelSlotCursor;

typedef struct SlotObject {
    u8 pad_00[0x8];
    union { u8 * p; void * p2; } unk_08;   /* accessed as both */
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0x10];
    s16 unk_24;
} SlotObject;

typedef struct SlotPosition {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} SlotPosition;

typedef struct SlotPrimitive {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} SlotPrimitive;

typedef struct SlotSprite {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x8];
    s16 unk_1C;
    s16 unk_1E;
} SlotSprite;

typedef struct SlotPayout {
    void * unk_00;
    u8 pad_04[0x4C];
    void * unk_50;
    s16 unk_54;
} SlotPayout;

typedef struct SlotSpriteData {
    u8 pad_00[0x4];
    s32 unk_04;
} SlotSpriteData;

typedef struct ReelObject {
    u8 pad_00[0x2A];
    s16 unk_2A;
} ReelObject;

typedef struct SlotBody {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} SlotBody;

/* Updates slot machine bets, reel stops, winning lines, and coin payouts. */
void func_80022768(State8081FF68 *state, void *position)
{
    GameWork *input = &gameWork;
    u8 *payout_callback;
    s32 index;
    s32 angle;
    s32 angle_delta;
    s32 angle_delta_2;
    s32 reel_mode;
    s32 symbols[3][3];
    void *coin;

    payout_callback = D_80020224;

    if ((u32)((u16)state->mode.u - 2) < 5U) {
        EntityRec *angles = &D_80083780;

        angle = func_800C2AE8(angles);
        if (angle > 0) {
            angles->z.v = 0xFFEE0000;
            angle = func_800C2AE8(angles);
        } else {
            s16 current_angle = angles->z.w.i;
            angle_delta = angle - current_angle;
            index = angle_delta >> 1;
            {
                angle_delta = angle - index;
                angles->z.w.i = angle_delta;
            }
        }
    }

    switch (state->mode.s) {
    case 0:
        state->flags = 0;
        state->count = 0;
        func_80093864();
        state->mode.s = 1;
    case 1:
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

    case 2:
        if ((((u32)input->buttons) & 0x5000) != 0) {
            u16 timer = state->timer.u;
            state->timer.u = (u16)(timer - 1);
            if ((s16)timer < 0) {
                state->timer.u = 0;
            }
        } else {
            state->timer.u = 5;
        }

        if ((((u32)input->unk_010) & 0x1000) != 0 ||
            ((((u32)input->buttons) & 0x1000) != 0 &&
             (s16)state->timer.s <= 0)) {
            if (state->count < 3) {
                SD_Call(0x502);
                if ((u32)D_80012D5C[0] < 100U) {
                    return;
                }
                state->count++;
                D_80012D5C[0] -= 100;
                return;
            }
        }

        if ((((u32)input->unk_010) & 0x4000) != 0 ||
            ((((u32)input->buttons) & 0x4000) != 0 &&
             (s16)state->timer.s <= 0)) {
            if (state->count >= 2) {
                SD_Call(0x502);
                D_80012D5C[0] += 100;
                state->count--;
                return;
            }
        }

        if ((((u32)input->unk_010) & 0x20) != 0) {
            state->timer.u = 10;
            state->mode.s = 3;
            return;
        }

        if ((((u32)input->unk_010) & 0x40) == 0 ||
            state->count == 0) {
            return;
        }
        SD_Call(0x526);
        state->timer.u = 20;
        state->mode.s = 4;
        return;

    case 3:
    {
        u16 timer = (u16)(state->timer.u - 1);
        state->timer.u = timer;
        if ((s16)timer > 0) {
            return;
        }
        D_80012D5C[0] += state->count * 100;
        func_800B1DBC((void *)D_80024638[0]);
        state->mode.s = 0;
        return;
    }

    case 4:
    {
        u16 timer = (u16)(state->timer.u - 1);
        u8 *reel_slot;
        state->timer.u = timer;
        if ((s16)timer > 0) {
            return;
        }
        index = 2;
        reel_mode = index;
        reel_slot = (u8 *)state + 8;
        do {
            void *reel = ((ReelSlotCursor *)reel_slot)->reel;
            reel_slot -= 4;
            index--;
            ((SlotObject *)reel)->unk_24 = (s16)reel_mode;
        } while (index >= 0);
        state->mode.s = 5;
        return;
    }

    case 5:
    {
        s16 reel_index = state->timer.s;
        void *reel = state->slot[reel_index];
        if (((SlotObject *)reel)->unk_24 != 3) {
            return;
        }
        state->mode.s = 6;
        state->timer2.u = 0;
        return;
    }

    case 6:
        SD_Call(0x524);
        {
            u16 timer = state->timer2.u;
            state->timer2.u = timer - 1;
            if ((s16)timer <= 0)
                state->timer2.u = 0;
        }
        if ((((u32)input->unk_010) & 0x40) != 0 &&
            state->timer2.s == 0) {
            void *reel;
            SD_Call(0x522);
            reel = state->slot[state->timer.s];
            ((SlotObject *)reel)->unk_24 = 4;
            state->timer2.u = 10;
            state->timer.u++;
        }
        {
            index = 2;
            if (state->timer.s != 3) {
                return;
            }
            state->work = 0;
            {
                register u8 *reel_slot ASM_REG("$12") = (u8 *)state + 8;
                u8 *reel_table = D_800244B8;
                register u8 *reel_symbols ASM_REG("$10") = reel_table + 0x18;
                s32 *symbol_row = &symbols[2][0];
                u8 *strip;
                u8 *slot_cursor;
                s32 *symbol_out;

outer_top:
                angle = 2;
                strip = reel_symbols;
                slot_cursor = reel_slot;
                symbol_out = symbol_row + 2;
inner_top:
                {
                    reel_mode = (s16)((ReelObject *)(((ReelSlotCursor *)slot_cursor)->reel))->unk_2A;
                    reel_table = (u8 *)(s32)strip[(angle + reel_mode) % 12];
                    *symbol_out = (s32)reel_table;
                    symbol_out--;
                }
                if (--angle >= 0)
                    goto inner_top;
                reel_slot -= 4;
                reel_symbols -= 12;
                symbol_row -= 3;
                if (--index >= 0)
                    goto outer_top;

                {
                    index = 0;
                    if (state->count != 0) {
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
                                    payout = state->count * symbol_payout;
                                    flags = state->flags;
                                    state->flags = flags | 4;
                                    state->work += payout;
                                    if (symbols[1][1] == 0) {
                                        state->flags = flags | 5;
                                    }
                                }
                                break;
                            case 1:
                                if (symbols[0][0] == symbols[1][0] &&
                                    symbols[0][0] == symbols[2][0]) {
                                    state->flags |= 0x10;
                                    symbol = symbols[0][0];
                                    symbol_payout = (s32)payouts[symbol] * 100;
                                    payout = state->count * symbol_payout;
                                    state->work += payout;
                                    if (symbols[0][0] == 0) {
                                        state->flags |= 1;
                                    }
                                }
                                if (symbols[0][2] == symbols[1][2] &&
                                    symbols[0][2] == symbols[2][2]) {
                                    state->flags |= 8;
                                    symbol = symbols[2][2];
                                    symbol_payout = (s32)payouts[symbol] * 100;
                                    payout = state->count * symbol_payout;
                                    state->work += payout;
                                    {
                                        s32 bottom_symbol = symbols[2][2];
                                        if (bottom_symbol == 0) {
                                            state->flags |= 1;
                                        }
                                    }
                                }
                                break;
                            case 2:
                                if (symbols[0][0] == symbols[1][1] &&
                                    symbols[2][2] == symbols[0][0]) {
                                    state->flags |= 0x40;
                                    symbol = symbols[1][1];
                                    symbol_payout = (s32)payouts[symbol] * 100;
                                    payout = state->count * symbol_payout;
                                    state->work += payout;
                                    if (symbols[1][1] == 0) {
                                        state->flags |= 1;
                                    }
                                }
                                if (symbols[0][2] == symbols[1][1] &&
                                    symbols[2][0] == symbols[0][2]) {
                                    state->flags |= 0x20;
                                    symbol = symbols[1][1];
                                    symbol_payout = (s32)payouts[symbol] * 100;
                                    payout = state->count * symbol_payout;
                                    state->work += payout;
                                    if (symbols[1][1] == 0) {
                                        state->flags |= 1;
                                    }
                                }
                                break;
                            }
                            index++;
                        } while (index < state->count);
                    }
                    }
                }
            }
            if (state->work == 0) {
                state->timer.u = 10;
                state->count = 0;
                state->mode.s = 3;
                return;
            }

            if ((state->flags & 1) != 0) {
                coin = func_8003FC64(0x100);
                if (coin != NULL) {
                    ((SlotObject *)coin)->unk_10 = D_80023BCC;
                }
            }

            {
                s32 tens;
                s32 hundreds;
                s32 raw_units;
                s32 raw_tens;
                s32 raw_hundreds;
                s32 tens_digit;
                s32 hundreds_digit;
                s32 thousands_value;
                angle_delta_2 = state->work;
                index = angle_delta_2 / 100;
                tens = index / 10;
                angle_delta = tens * 10;
                raw_units = index - angle_delta;
                angle_delta = raw_units << 16;
                angle = angle_delta >> 16;
                hundreds = tens / 10;
                angle_delta = hundreds * 10;
                raw_tens = tens - angle_delta;
                tens_digit = (s16)raw_tens;
                angle += tens_digit;
                thousands_value = (hundreds / 10) * 10;
                raw_hundreds = hundreds - thousands_value;
                hundreds_digit = (s16)raw_hundreds;
                D_80024630[0] = raw_units;
                D_80024630[1] = raw_tens;
                D_80024630[2] = raw_hundreds;
                {
                    angle += hundreds_digit;
                    angle_delta = angle < 10;
                    if (angle_delta) {
                        if (hundreds_digit > 0) {
                            s32 adjusted = raw_hundreds - 1;
                            D_80024630[2] = adjusted;
                            D_80024630[1] = raw_tens + 10;
                        } else if (tens_digit > 0) {
                            s32 adjusted = raw_tens - 1;
                            D_80024630[1] = adjusted;
                            adjusted = raw_units + 10;
                            D_80024630[0] = adjusted;
                        }
                    }
                }
            }
            state->timer.u = 0;
            state->mode.s = 7;
            return;
        }

    case 7:
        state->timer.u++;
        if ((s16)state->timer.u == 9) {
            func_80093864();
        }
        if ((state->timer.u & 3) != 0) {
            return;
        }
        {
            s16 *digits = D_80024630;
            if ((s16)digits[0] + (s16)digits[1] + (s16)digits[2] == 0) {
                if ((state->flags & 2) == 0) {
                    void *bet_display = (void *)D_80024638[0];
                    state->count = 0;
                    func_800B1DBC(bet_display);
                    state->timer.u = 10;
                    state->mode.s = 3;
                }
                state->flags &= (u16)~2;
                return;
            }

            {
                void *payout_obj;
                u8 *primitive;
                u8 *sprite;
                u8 *payout_state;
                coin = func_8003FC64(0x136);
                if (coin == NULL) {
                    return;
                }
                payout_obj = coin;
                ((SlotObject *)coin)->unk_10 = D_800236BC;
                ((SlotBody *)(((SlotObject *)coin)->unk_08.p))->unk_00 =
                    ((SlotPosition *)position)->unk_00 + (s32)0xFEC00000;
                ((SlotBody *)(((SlotObject *)coin)->unk_08.p))->unk_04 =
                    ((SlotPosition *)position)->unk_04 + (s32)0xFFC00000;
                ((SlotBody *)(((SlotObject *)coin)->unk_08.p))->unk_08 =
                    ((SlotPosition *)position)->unk_08 + (s32)0xFFC00000;
                primitive = ((SlotObject *)coin)->unk_08.p;
                ((SlotPrimitive *)primitive)->unk_10 = 0;
                ((SlotPrimitive *)primitive)->unk_0C = 0;
                ((SlotBody *)(((SlotObject *)coin)->unk_08.p))->unk_14 = 0x40000;
                payout_state = (u8 *)coin + 0x20;
                func_8004491C(payout_obj, func_80045340);
                sprite = ((SlotObject *)coin)->unk_0C;
                ((SlotSprite *)sprite)->unk_1E = 0x1000;
                ((SlotSprite *)sprite)->unk_1C = 0x1000;
                if (digits[2] != 0) {
                    digits[2]--;
                    ((SlotPayout *)payout_state)->unk_54 = 2;
                } else if (digits[1] != 0) {
                    digits[1]--;
                    ((SlotPayout *)payout_state)->unk_54 = 1;
                    ((SlotSprite *)sprite)->unk_12 = (u16)(((SlotSprite *)sprite)->unk_12 - 5);
                } else if (digits[0] != 0) {
                    digits[0]--;
                    ((SlotPayout *)payout_state)->unk_54 = 0;
                    ((SlotSprite *)sprite)->unk_12 = (u16)((*(u16 *)((u8 *)sprite + (0x12))) + 5);
                }
                {
                    u8 *primitive = sprite;
                    u8 *sprite_data = D_8007947C;
                    ((SlotPrimitive *)primitive)->unk_00 = sprite_data;
                    ((SlotPrimitive *)primitive)->unk_08 = ((SlotSpriteData *)sprite_data)->unk_04;
                    ((SlotPrimitive *)primitive)->unk_04 = 0;
                    ((SlotPrimitive *)primitive)->unk_05 = 0;
                    ((SlotPrimitive *)primitive)->unk_0C = 0x00808080;
                }
                ((SlotPayout *)payout_state)->unk_00 = state;
                ((SlotPayout *)payout_state)->unk_50 = payout_callback;
                func_8008F074(payout_state + 8, ((SlotObject *)coin)->unk_08.p2, D_80024488);
            }
        }
    }
}
