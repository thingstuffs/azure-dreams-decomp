#include "engine/message.h"
#include "engine/script.h"

/* Opcode 0x12: Wait the number of frames given by the 16-bit operand. */
void script_wait_frames(MessageWindow *window) {
    u32 addr_or_high = (u32)window->cursor;
    u32 read_addr = addr_or_high;
    u32 low_byte = *(u8 *)addr_or_high;

    addr_or_high = *(u8 *)(addr_or_high + 1);
    window->cursor = (u8 *)(read_addr + 2);
    window->message_handler = wait_message_countdown;
    window->countdown = low_byte + (addr_or_high << 8);
}
