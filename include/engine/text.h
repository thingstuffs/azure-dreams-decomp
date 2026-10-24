#ifndef ENGINE_TEXT_H
#define ENGINE_TEXT_H
/* Prototypes of the functions defined in src/engine/text/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_8004D98C;

/* alloc_parsed_string.c */
void *alloc_parsed_string(char *text, int parse_arg);
void *func_8004E928(char *text, int parse_arg);

/* build_positioned_text_glyphs.c */
void *build_positioned_text_glyphs(u8 *glyph_buf, u8 *text, s32 style);

/* decode_glyph_fields.c */
void *decode_glyph_fields(void *record_ptr, s32 code);

/* decode_glyph_id_to_byte_rectangle.c */
void initialize_styled_glyph_rectangle(s32 data_id, s32 style_flags, struct S_8004D98C *effect);

/* draw_double_byte_text.c */
void draw_double_byte_text(u8 *text, s16 start_x, s16 start_y);

/* fill_string_tail_and_detect_zero.c */
s32 fill_string_tail_and_detect_zero(u8 *buffer, s32 pair_count);

/* fill_string_tail_and_detect_zero_second.c */
char *pad_double_byte_field_and_append_marker(u8 *dst, s32 field_width);

/* format_decimal_field_space_padded.c */
void format_decimal_field_space_padded(s32 value, s32 width, char *buf);

/* format_int_zero_padded.c */
char *format_int_zero_padded(int value, unsigned short width, char *buf);
char *func_8004E5E8(int value, unsigned short width, char *buf);

/* format_reversed_unsigned_decimal.c */
char *format_reversed_unsigned_decimal(u32 value, s32 width, char *buf, s32 pad);

/* get_glyph_vram_rectangle.c */
void get_glyph_vram_rectangle(s32 rect_id, s16 *vram_rect);

/* pad_both_key_states_clear.c */
s32 pad_both_key_states_clear(void);

/* remap_flagged_string_bytes.c */
u8 *remap_flagged_string_bytes(u8 *string);

/* set_glyph_style_index.c */
void set_style_for_tagged_glyph_entries(u8 *entries, s32 process_arg);

/* set_object_and_global_removal_flag.c */
void set_object_and_global_removal_flag(unsigned short *object_fields);

/* set_object_and_global_removal_flag_second.c */
void propagate_linked_removal_request(void *link_field);

/* string_has_non_whitespace.c */
s32 string_has_non_whitespace(u8 *text);

/* write_char_pair.c */
char *func_8004EAC4(u8 *buffer, char *code, s32 slot_index);
char *write_char_pair(u8 *buffer, char *code, s32 slot_index);

#endif
