#include "slus/message_mode_81550.h"
#include "slus.h"

extern u32 message_embedded_control_words[0x24];
extern char message_conversion_buffer[0x100];

/* Builds and dispatches a message with control codes and two embedded addresses. */
void runtime_dispatch_control_coded_message(char *message)
{
    char *cursor;
    u32 address;
    char *buffer;

    cursor = message_conversion_buffer;
    *cursor++ = 8;
    strcpy(cursor, message);

    buffer = message_conversion_buffer;
    cursor = strrchr(buffer, 0);
    *cursor++ = 0x19;
    *cursor++ = 2;
    *cursor++ = 0x1A;

    address = (u32)message_embedded_control_words;
    cursor[1] = address >> 8;
    cursor[2] = address >> 16;
    cursor[0] = address;
    cursor[3] = address >> 24;
    cursor += 4;

    address += 4;
    cursor[1] = address >> 8;
    cursor[0] = address;
    cursor[2] = address >> 16;
    cursor[3] = address >> 24;

    message_mode_handlers[message_handler_mode](buffer);
    message_embedded_control_words[0] = 0x2300030C;
    message_embedded_control_words[1] = 0x2300040C;
}
