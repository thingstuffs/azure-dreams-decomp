#include "modules/ovmovie_libpress.h"


/* Apply option flags to a command word and dispatch its update. */
void configure_decoder_command_flags(s32 *command, s32 flags)
{
    if (flags & 1) {
        *command &= ~0x08000000;
    } else {
        *command |= 0x08000000;
    }

    if (flags & 2) {
        *command |= 0x02000000;
    } else {
        *command &= ~0x02000000;
    }

    start_decoder_input_dma(command, *(u16 *)command);
}
