#include "common.h"

#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern void func_80038F48(void *);
extern void func_80039148(void *);
extern void func_8003AB44(u8 *, s16, s16, u8, s32, s32, s32);
extern void func_80038128(void);

typedef void (*Callback)(void);

/* Render text glyphs and advance the cursor according to the display rate. */
void func_80038CB8(void *text)
{
    s32 neg_glyph_count;
    s32 glyph_delay;
    s32 column_or_rate;
    u8 *batch_glyph;
    u8 *next_glyph;
    u8 *glyph;
    u8 *fast_cursor;
    u8 *batch_cursor;

    if (FIELD(text, u8, 0x2E) != 0) {
        fast_cursor = FIELD(text, u8 *, 0x1C);
        if (*(s8 *)fast_cursor <= 0) {
            do {
                if ((*fast_cursor == 0) ||
                    (FIELD(text, s16, 0x20) < (s32)FIELD(text, u8, 0x24))) {
                    func_80038F48(text);
                    if (*(s8 *)FIELD(text, u8 *, 0x1C) <= 0) {
                        func_8003AB44(
                            FIELD(text, u8 *, 0x1C),
                            FIELD(text, s16, 0x20),
                            FIELD(text, s16, 0x22),
                            FIELD(text, u8, 0x2A),
                            (s32)FIELD(text, s16, 0x00),
                            (s32)(s16)(FIELD(text, s16, 0x02) + 2),
                            1);
                        glyph = FIELD(text, u8 *, 0x1C);
                        FIELD(text, s16, 0x20) =
                            (s16)((u16)FIELD(text, s16, 0x20) + 1);
                        next_glyph = glyph + 2;
                        FIELD(text, u8 *, 0x1C) = next_glyph;
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
        if (FIELD(text, s8, 0x28) >= 0) {
            goto render_one;
        }
        batch_cursor = FIELD(text, u8 *, 0x1C);
        if (*(s8 *)batch_cursor > 0) {
            goto reset_rate;
        }
        neg_glyph_count = 0;
render_batch:
        if ((*batch_cursor != 0) &&
            (FIELD(text, s16, 0x20) >= (s32)FIELD(text, u8, 0x24))) {
            goto advance_line;
        }
        func_80038F48(text);
        if (*(s8 *)FIELD(text, u8 *, 0x1C) > 0) {
            goto done;
        }
        neg_glyph_count -= 1;
        func_8003AB44(
            FIELD(text, u8 *, 0x1C),
            FIELD(text, s16, 0x20),
            FIELD(text, s16, 0x22),
            FIELD(text, u8, 0x2A),
            (s32)FIELD(text, s16, 0x00),
            (s32)(s16)(FIELD(text, s16, 0x02) + 2),
            1);
        column_or_rate = FIELD(text, u16, 0x20);
        batch_glyph = FIELD(text, u8 *, 0x1C);
        column_or_rate += 1;
        FIELD(text, s16, 0x20) = (s16)column_or_rate;
        column_or_rate = FIELD(text, s8, 0x28);
        batch_cursor = batch_glyph + 2;
        FIELD(text, u8 *, 0x1C) = batch_cursor;
        if (neg_glyph_count < column_or_rate) {
            goto reset_rate;
        }
        if (*(s8 *)(batch_glyph + 2) <= 0) {
            goto render_batch;
        }
reset_rate:
        FIELD(text, s8, 0x28) =
            *(u8 *)(FIELD(text, u8 *, 0x80) + 3);
        goto done;
advance_line:
        func_80039148(text);
        goto done;
render_one:
        func_80038F48(text);
        if (*(s8 *)FIELD(text, u8 *, 0x1C) <= 0) {
            func_8003AB44(
                FIELD(text, u8 *, 0x1C),
                FIELD(text, s16, 0x20),
                FIELD(text, s16, 0x22),
                FIELD(text, u8, 0x2A),
                (s32)FIELD(text, s16, 0x00),
                (s32)(s16)(FIELD(text, s16, 0x02) + 2),
                1);
            FIELD(text, s16, 0x20) =
                (s16)((u16)FIELD(text, s16, 0x20) + 1);
            glyph_delay = FIELD(text, s8, 0x28);
            FIELD(text, u8 *, 0x1C) = FIELD(text, u8 *, 0x1C) + 2;
            if (glyph_delay != 0) {
                FIELD(text, s16, 0x18) = (s16)glyph_delay;
                FIELD(text, Callback, 0x10) = func_80038128;
            }
        }
done:
        ;
    }
}
