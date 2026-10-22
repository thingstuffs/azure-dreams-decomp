#ifndef FRONTEND_LIBCARD_MESSAGE_CARD_BOOT_MEASURE_DIALOG_CHOICE_WORD_G01029_H
#define FRONTEND_LIBCARD_MESSAGE_CARD_BOOT_MEASURE_DIALOG_CHOICE_WORD_G01029_H
/* card boot measure dialog choice word g01029. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01029 - CL:main/func_8000F25C, CL:main/func_8000F300, CL:main/func_8000F33C, CL:main/func_8000F3B4. */

#include "common.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ s8 unk1;
    /* 0x02 */ s8 pad2[2];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s8 pad8[2];
    /* 0x0A */ s8 unkA;
    /* 0x0B */ s8 unkB;
} Struct_8000F300;

typedef struct {
    s32 words[5];
    u8 flag14;
    u8 pad15;
    u8 pad16;
    u8 count17;
} EntryT;

void set_glyph_style_index(void *record, int index);
void set_style_for_tagged_glyph_entries(u8 *entries, s32 process_arg);
extern s32 D_800280B4[3];

/* Functions defined in this translation unit. */
void card_boot_measure_dialog_choice_word( u8 *text, s32 word_index, s32 *offset_out, s32 *length_out, s32 *prior_chars_out );
void *card_boot_build_slot_marker_packet(s32 unused, Struct_8000F300 *packet, s32 slot_index);
void card_boot_highlight_dialog_text_range(s32 entry_base, s32 start_index, s32 entry_count);
void card_boot_position_dialog_selection_marker(void *context, s32 column, s32 mode, s32 row, s32 row_value);
void card_boot_update_message_choice_highlight(void *object);

#endif
