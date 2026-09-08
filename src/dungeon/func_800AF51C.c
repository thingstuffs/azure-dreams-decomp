#include "common.h"
#include "m2c_compat.h"

extern u8 D_80083498[];
void *func_8003FD64();
M2C_UNK func_8004E298();
M2C_UNK func_8004E5A0();
M2C_UNK func_8004E634();
s32 func_80069E98();
M2C_UNK func_800B1320();
void *func_800B1484();
M2C_UNK func_800B13CC();
extern M2C_UNK D_800B45E0;
extern M2C_UNK D_800B490C;
extern M2C_UNK D_800DF24C[];

typedef struct {
    u8 bytes[16];
    u16 arg3;
} StackLocal;


typedef struct S_800B4C7C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800B4C7C_0;   /* temp_v0_3 in func_800B4C7C */

typedef struct S_800B4C7C_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x5];
    u8 unk_23;
} S_800B4C7C_1;   /* temp_s2 in func_800B4C7C */

typedef struct S_800B4C7C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B4C7C_2;   /* temp_v0_4 in func_800B4C7C */

typedef struct S_800B4C7C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B4C7C_3;   /* temp_a0_2 in func_800B4C7C */

typedef struct S_800B4C7C_4 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B4C7C_4;   /* temp_v1_ptr in func_800B4C7C */

typedef struct S_800B4C7C_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
} S_800B4C7C_5;   /* temp_a1 in func_800B4C7C */

typedef struct S_800B4C7C_6 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_800B4C7C_6;   /* func_800B1484(temp_s3) in func_800B4C7C */

/* Creates and positions a text object showing a formatted value or preset message. */
void *func_800B4C7C(s32 flags, u8 *source_data, s16 value, u16 callback_mode) {
    StackLocal text_stack;
    void *callback;
    s16 glyph_or_index;
    register u16 callback_bits ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 callback_kind ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 number;
    register s32 space ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 format ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register s32 number_style ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 text_style ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *saved_flags;
    s16 saved_value;
    void *object;
    s8 *text_cursor;
    u16 anchor_x;
    u16 anchor_y;
    u16 anchor_z;
    S_800B4C7C_3 *position;
    S_800B4C7C_5 *text_link;
    void *text_position;
    void *text;
    void *state;
    void *new_object;
    register void *text_storage ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_800B4C7C_0 *source_object;
    S_800B4C7C_2 *source_position;
    register void *anchor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    text_stack.arg3 = callback_mode;
    new_object = func_8003FD64(0x212, D_80083498);
    saved_flags = (void *)(u32) flags;
    ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    object = new_object;
    if (object != NULL) {
        saved_value = value;
        ASM_KEEP(saved_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        position = (*(void **)((u8 *)object + 8));
        text_link = (*(void **)((u8 *)object + 0xC));
        source_object = source_data - 0x20;
        (*(void **)((u8 *)object + 0x20)) = source_object;
        source_position = source_object->unk_08;
        state = object + 0x20;
        ((S_800B4C7C_1 *)state)->unk_14 = source_position;
        anchor_x = source_position->unk_02;
        position->unk_02 = anchor_x;
        anchor = ((S_800B4C7C_1 *)state)->unk_14;
        ((S_800B4C7C_1 *)state)->unk_18 = anchor_x;
        anchor_y = ((S_800B4C7C_4 *)anchor)->unk_06;
        space = 0x20;
        position->unk_06 = anchor_y;
        anchor = ((S_800B4C7C_1 *)state)->unk_14;
        text_style = flags & 0xF;
        ((S_800B4C7C_1 *)state)->unk_1A = anchor_y;
        anchor_z = ((S_800B4C7C_4 *)anchor)->unk_0A;
        number_style = text_style;
        position->unk_0A = anchor_z;
        ((S_800B4C7C_1 *)state)->unk_1C = anchor_z;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        text_storage = object + 0x40;
        text = text_storage;
        ASM_KEEP(text);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        text_link->unk_08 = text_storage;
        text_link->unk_06 = space;
        if (flags & 0x8000) {
            ((S_800B4C7C_1 *)state)->unk_0E = 1;
        }
        format = flags & 0xF0;
        number = (s16) value;
        if (number >= 0) {
            flags = 0x50;
            text_cursor = (s8 *) text_stack.bytes;
            switch (format) {
            case 0x10:
                glyph_or_index = 0x7F;
                goto store_and_advance;
            case 0x20:
                glyph_or_index = 0x80;
                goto store_and_advance;
            case 0x30:
                text_stack.bytes[0] = 0x2B;
                goto mode_check;
            case 0x40:
                glyph_or_index = 0x2D;
                goto store_and_advance;
            case 0x50:
                text_stack.bytes[0] = 0x81;
                goto mode_check;
            case 0x60:
                text_stack.bytes[0] = 0x82;
                goto advance_buffer;
store_and_advance:
                text_stack.bytes[0] = glyph_or_index;
advance_buffer:
                text_cursor = (s8 *) text_stack.bytes + 1;
                goto mode_check;
            case 0x80:
                func_8004E634(number, text_cursor);
                text_cursor = (s8 *) text_cursor + func_80069E98(text_cursor);
                *text_cursor++ = 0x45;
                *text_cursor++ = 0x58;
                *text_cursor++ = flags;
                *text_cursor++ = 0;
                func_8004E298(text, text_stack.bytes, text_style);
                goto mode_check;
            case 0xA0:
                text_stack.bytes[0] = space;
                func_8004E5A0(number, 3, text_stack.bytes + 1);
                text_cursor = (s8 *) text_stack.bytes + 6;
                text_stack.bytes[4] = 0x25;
                text_stack.bytes[5] = 0;
                func_8004E298(text, text_stack.bytes, text_style);
                goto mode_check;
            case 0x90:
                func_8004E5A0(number, 4, text_cursor);
                text_cursor = (s8 *) text_stack.bytes + 6;
                text_stack.bytes[4] = 0x47;
                text_stack.bytes[5] = 0;
                func_8004E298(text, text_stack.bytes, text_style);
                goto mode_check;
            default:
                goto mode_check;
            }
mode_check:
            if (((u32) saved_flags & 0xF0) < 0x80U) {
                func_8004E5A0(saved_value, 3, text_cursor);
                func_8004E298(text, text_stack.bytes, number_style);
            }
            goto finish_text;
        }
        glyph_or_index = ~value;
        if (glyph_or_index > 0) {
            ((S_800B4C7C_1 *)state)->unk_10 = 0x18;
        }
        func_8004E298(text, D_800DF24C[glyph_or_index], text_style);
        goto finish_text;
finish_text:
        callback_bits = *(volatile u16 *) &text_stack.arg3;
        callback_kind = (s16) callback_bits;
        if (callback_kind == 1) {
            callback = &D_800B490C;
        } else {
            callback = &D_800B45E0;
        }
        (*(void * volatile *)((u8 *)object + 0x10)) = callback;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        text_position = state + 0x20;
        func_800B1320(text_position, 0x80 - ((s32) (((S_800B4C7C_6 *)(func_800B1484(text)))->unk_02 + 0x88) / 2), (s16) ((0 - (s8) ((S_800B4C7C_1 *)state)->unk_23) - 4));
        func_800B13CC(text_position, 0x20);
    }
    return object;
}
