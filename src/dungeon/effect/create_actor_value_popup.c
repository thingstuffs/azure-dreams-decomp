#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/menu.h"
#include "sdk/libc.h"
#include "engine/node/allocation.h"

#include "engine/text.h"
char *func_8004E5A0();
char *func_8004E634();
void *find_first_ended_record();
extern void D_800B45E0();
extern void D_800B490C();
extern u8 *D_800DF24C[];

typedef struct S_800B4C7C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800B4C7C_0;

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
} S_800B4C7C_1;

typedef struct S_800B4C7C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B4C7C_2;

typedef struct S_800B4C7C_4 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B4C7C_4;

typedef struct S_800B4C7C_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
} S_800B4C7C_5;

typedef struct S_800B4C7C_6 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_800B4C7C_6;

/* Creates and positions a text object showing a formatted value or preset message. */
void *create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode) {
    u8 text_buffer[16];
    void *callback;
    s16 glyph_or_index;
    u16 callback_bits;
    s32 callback_kind;
    s32 number;
    s16 space;
    s32 format;
    s16 number_style;
    s16 text_style;
    u16 saved_flags;
    s16 saved_value;
    ObjectNodeHeader *object;
    s8 *text_cursor;
    u16 anchor_x;
    u16 anchor_y;
    u16 anchor_z;
    ObjectPosition *position;
    SpriteFrameState *text_link;
    S_800B4C7C_6 *text_metrics;
    void *text_position;
    void *text;
    void *state;
    void *new_object;
    S_800B4C7C_0 *source_object;
    S_800B4C7C_2 *source_position;
    void *anchor;

    new_object = allocate_list_node(0x212, &scene_object_list_anchor.next);
    saved_flags = flags;
    object = new_object;
    saved_value = value;
    if (object != NULL) {
        position = object->position;
        text_link = object->sprite;
        source_object = source_data - 0x20;
        (*(void **)((u8 *)object + 0x20)) = source_object;
        source_position = source_object->unk_08;
        state = ((void *)object) + 0x20;
        ((S_800B4C7C_1 *)state)->unk_14 = source_position;
        anchor_x = source_position->unk_02;
        position->x.w.i = anchor_x;
        anchor = ((S_800B4C7C_1 *)state)->unk_14;
        ((S_800B4C7C_1 *)state)->unk_18 = anchor_x;
        anchor_y = ((S_800B4C7C_4 *)anchor)->unk_06;
        space = 0x20;
        position->y.w.i = anchor_y;
        text_style = flags & 0xF;
        ((S_800B4C7C_1 *)state)->unk_1A = anchor_y;
        anchor_z = ((S_800B4C7C_4 *)((S_800B4C7C_1 *)state)->unk_14)->unk_0A;
        number_style = text_style;
        position->z.w.i = anchor_z;
        ((S_800B4C7C_1 *)state)->unk_1C = anchor_z;
        text_link->source = ((void *)object) + 0x40;
        text = text_link->source;
        text_link->depth_bias = space;
        if (flags & 0x8000) {
            ((S_800B4C7C_1 *)state)->unk_0E = 1;
        }
        format = flags & 0xF0;
        /*
         * BUG: large EXP becomes a negative s16 and indexes message pointers, causing the reported EXP crash
         * or MISS!! text. Format EXP as unsigned first.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        number = (s16) value;
        if (number >= 0) {
            flags = 0x50;
            text_cursor = (s8 *) text_buffer;
            switch (format) {
            case 0x10:
                glyph_or_index = 0x7F;
                text_buffer[0] = glyph_or_index;
                text_cursor = (s8 *) text_buffer + 1;
                break;
            case 0x20:
                glyph_or_index = 0x80;
                text_buffer[0] = glyph_or_index;
                text_cursor = (s8 *) text_buffer + 1;
                break;
            /*
             * BUG: cases 0x30 and 0x50 leave text_cursor on their prefix, so the decimal formatter overwrites
             * the plus sign or stat glyph. Both should advance past the prefix as the sibling cases do.
             */
            case 0x30:
                text_buffer[0] = 0x2B;
                break;
            case 0x40:
                glyph_or_index = 0x2D;
                text_buffer[0] = glyph_or_index;
                text_cursor = (s8 *) text_buffer + 1;
                break;
            case 0x50:
                text_buffer[0] = 0x81;
                break;
            case 0x60:
                text_buffer[0] = 0x82;
                text_cursor = (s8 *) text_buffer + 1;
                break;
            case 0x80:
                func_8004E634(number, text_cursor);
                text_cursor = (s8 *) text_cursor + strlen(text_cursor);
                *text_cursor++ = 0x45;
                *text_cursor++ = 0x58;
                *text_cursor++ = flags;
                *text_cursor++ = 0;
                build_positioned_text_glyphs(text, text_buffer, text_style);
                break;
            case 0xA0:
                text_buffer[0] = space;
                format = number;
                number = (s32)(text_buffer + 1);
                func_8004E5A0(format, 3, (u8 *)number);
                text_cursor = (s8 *) text_buffer + 6;
                text_buffer[4] = 0x25;
                text_buffer[5] = 0;
                build_positioned_text_glyphs(text, text_buffer, text_style);
                break;
            case 0x90:
                func_8004E5A0(number, 4, text_cursor);
                text_cursor = (s8 *) text_buffer + 6;
                text_buffer[4] = 0x47;
                text_buffer[5] = 0;
                build_positioned_text_glyphs(text, text_buffer, text_style);
                break;
            default:
                break;
            }
            if ((saved_flags & 0xF0) < 0x80U) {
                func_8004E5A0(saved_value, 3, text_cursor);
                build_positioned_text_glyphs(text, text_buffer, number_style);
            }
        } else {
            glyph_or_index = ~value;
            if (glyph_or_index > 0) {
                ((S_800B4C7C_1 *)state)->unk_10 = 0x18;
            }
            build_positioned_text_glyphs(text, D_800DF24C[glyph_or_index], text_style);
        }
        callback_bits = callback_mode;
        callback_kind = (s16) callback_bits;
        if (callback_kind == 1) {
            callback = &D_800B490C;
            (object->update_callback) = callback;
            text_metrics = find_first_ended_record(text);
            text_position = state + 0x20;
        } else {
            callback = &D_800B45E0;
            (object->update_callback) = callback;
            text_metrics = find_first_ended_record(text);
            text_position = state + 0x20;
        }
        offset_record_coordinates(text_position, 0x80 - ((s32) (text_metrics->unk_02 + 0x88) / 2),
            (s16) ((0 - (s8) ((S_800B4C7C_1 *)state)->unk_23) - 4));
        apply_record_flags_through_end(text_position, 0x20);
    }
    return object;
}
