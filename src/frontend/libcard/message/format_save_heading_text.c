#include "common.h"

extern void decode_note_text(s32 base_addr, void *data, s32 mode);
extern u8 D_800282CC[];

/* Processes data at base offset 0x7C using D_800282CC and mode 1. */
void format_save_heading_text(s32 base_addr) {
    decode_note_text(base_addr + 0x7C, &D_800282CC[0], 1);
}
