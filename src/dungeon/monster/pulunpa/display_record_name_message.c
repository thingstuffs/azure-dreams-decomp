#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void func_80099290(s8 *byte_ptr);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern u8 D_80176440[9];
extern u8 D_80176455[9];
/* Builds and displays a message containing the record's name between fixed text. */
void display_record_name_message(s32 record, s32 unused_1, s32 unused_2, s32 unused_3)
{
    s32 text_arg;
    s32 message;
    unsigned int cursor;

    text_arg = get_unused_text_buffer();
    message = text_arg;
    cursor = expand_text_control_codes(D_80176440, message);
    text_arg = record;
    func_80099290(expand_text_control_codes(D_80176455, append_entity_display_text(text_arg, cursor)));
    display_text_with_fullwidth_adjustment(message);
}
