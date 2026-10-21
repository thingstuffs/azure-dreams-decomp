#include "slus/message_mode_81550.h"

typedef void (*FuncPtr)(char *);

extern char *strcat(char *dst, char *src);
extern char message_conversion_buffer[0x100];
extern char message_appended_suffix[];
extern s32 message_primary_output_control_word;
extern s32 message_output_control_word;

/* Builds and dispatches a control-coded string, then resets its referenced words. */
void runtime_dispatch_and_reset_control_string(char *text)
{
    char *buffer;
    char *cursor;
    char *text_start;
    u32 word_addr;
    s32 *word_ptr;
    FuncPtr handler;

    cursor = message_conversion_buffer;
    *cursor++ = 8;
    strcpy(cursor, text);
    text_start = cursor;
    strcat(text_start, message_appended_suffix);
    buffer = message_conversion_buffer;
    cursor = strrchr(buffer, 0);
    *cursor = 0x19;
    cursor = cursor + 1;
    *cursor = 2;
    cursor = cursor - (-1);
    *cursor = 0x1A;
    cursor = cursor + 1;
    word_ptr = &message_primary_output_control_word;
    word_addr = (u32)word_ptr;
    cursor[1] = (char)(word_addr >> 8);
    cursor[2] = (char)(word_addr >> 16);
    cursor[0] = (char)word_addr;
    cursor[3] = (char)(word_addr >> 24);
    cursor = cursor + 4;
    word_ptr = &message_output_control_word;
    word_addr = (u32)word_ptr;
    cursor[1] = (char)(word_addr >> 8);
    cursor[2] = (char)(word_addr >> 16);
    cursor[0] = (char)word_addr;
    cursor[3] = (char)(word_addr >> 24);
    handler = message_mode_handlers[message_handler_mode];
    handler(buffer);
    word_ptr[-1] = 0x2300030C;
    message_output_control_word = 0x2300040C;
}
