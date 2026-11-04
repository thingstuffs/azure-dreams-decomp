#include "shared/game_work.h"
#include "dungeon/system.h"
#include "dungeon/item/message.h"

extern u8 D_80176440[9];
extern u8 D_80176455[9];
/* Builds and displays a message containing the record's name between fixed text. */
void display_record_name_message(void *record)
{
    void *text_arg;
    void *message;
    u8 *cursor;

    text_arg = get_unused_text_buffer();
    message = text_arg;
    cursor = expand_text_control_codes(D_80176440, message);
    text_arg = record;
    clear_byte_and_advance(expand_text_control_codes(D_80176455, append_entity_display_text(text_arg, cursor)));
    display_text_with_fullwidth_adjustment(message);
}
