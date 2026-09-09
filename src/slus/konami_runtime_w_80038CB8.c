#include "common.h"

#include "common.h"

extern void func_80038F48(void *);
extern void func_80039148(void *);
extern void func_8003AB44(u8 *, s16, s16, u8, s32, s32, s32);
extern void func_80038128(void);

typedef void (*Callback)(void);

typedef struct S_func_80038CB8_0 {
    s16 unk_00;
    s16 unk_02;
    u8 pad_04[0xC];
    Callback unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0x2];
    u8 *unk_1C;
    union {
        s16 s;
        u16 u;
    } unk_20;
    s16 unk_22;
    u8 unk_24;
    u8 pad_25[0x3];
    s8 unk_28;
    u8 pad_29[0x1];
    u8 unk_2A;
    u8 pad_2B[0x3];
    u8 unk_2E;
    u8 pad_2F[0x51];
    u8 *unk_80;
} S_func_80038CB8_0;

typedef struct S_func_80038CB8_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_func_80038CB8_1;

/* Render text glyphs and advance the cursor according to the display rate. */
void func_80038CB8(S_func_80038CB8_0 *text)
{
    s32 neg_glyph_count;
    s32 glyph_delay;
    s32 column_or_rate;
    u8 *batch_glyph;
    u8 *next_glyph;
    u8 *glyph;
    u8 *fast_cursor;
    u8 *batch_cursor;

    if (text->unk_2E != 0) {
        fast_cursor = text->unk_1C;
        if (*(s8 *)fast_cursor <= 0) {
            do {
                if ((*fast_cursor == 0) ||
                    (text->unk_20.s < (s32)text->unk_24)) {
                    func_80038F48(text);
                    if (*(s8 *)text->unk_1C <= 0) {
                        func_8003AB44(
                            text->unk_1C,
                            text->unk_20.s,
                            text->unk_22,
                            text->unk_2A,
                            (s32)text->unk_00,
                            (s32)(s16)(text->unk_02 + 2),
                            1);
                        glyph = text->unk_1C;
                        text->unk_20.s =
                            (s16)((u16)text->unk_20.s + 1);
                        next_glyph = glyph + 2;
                        text->unk_1C = next_glyph;
                        fast_cursor = next_glyph;
                        if (*(s8 *)(glyph + 2) <= 0) {
                            continue;
                        }
                    }
                } else {
                    goto advance_line;
                }
                break;
            } while (1);
        }
    } else {
        if (text->unk_28 >= 0) {
            goto render_one;
        }
        batch_cursor = text->unk_1C;
        if (*(s8 *)batch_cursor > 0) {
            goto reset_rate;
        }
        neg_glyph_count = 0;
render_batch:
        if ((*batch_cursor != 0) &&
            (text->unk_20.s >= (s32)text->unk_24)) {
            goto advance_line;
        }
        func_80038F48(text);
        if (*(s8 *)text->unk_1C > 0) {
            goto done;
        }
        neg_glyph_count -= 1;
        func_8003AB44(
            text->unk_1C,
            text->unk_20.s,
            text->unk_22,
            text->unk_2A,
            (s32)text->unk_00,
            (s32)(s16)(text->unk_02 + 2),
            1);
        column_or_rate = text->unk_20.u;
        batch_glyph = text->unk_1C;
        column_or_rate += 1;
        text->unk_20.s = (s16)column_or_rate;
        column_or_rate = text->unk_28;
        batch_cursor = batch_glyph + 2;
        text->unk_1C = batch_cursor;
        if (neg_glyph_count < column_or_rate) {
            goto reset_rate;
        }
        if (*(s8 *)(batch_glyph + 2) <= 0) {
            goto render_batch;
        }
reset_rate:
        text->unk_28 =
            ((S_func_80038CB8_1 *)text->unk_80)->unk_03;
        goto done;
advance_line:
        func_80039148(text);
        goto done;
render_one:
        func_80038F48(text);
        if (*(s8 *)text->unk_1C <= 0) {
            func_8003AB44(
                text->unk_1C,
                text->unk_20.s,
                text->unk_22,
                text->unk_2A,
                (s32)text->unk_00,
                (s32)(s16)(text->unk_02 + 2),
                1);
            text->unk_20.s =
                (s16)((u16)text->unk_20.s + 1);
            glyph_delay = text->unk_28;
            text->unk_1C = text->unk_1C + 2;
            if (glyph_delay != 0) {
                text->unk_18 = (s16)glyph_delay;
                text->unk_10 = func_80038128;
            }
        }
done:
        ;
    }
}
