#include "common.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard/message.h"
#include "main/data.h"

/* Processes data at base offset 0x7C using D_800282CC and mode 1. */
void format_save_heading_text(s32 base_addr) {
    decode_fullwidth_text(base_addr + 0x7C, &D_800282CC[0], 1);
}
