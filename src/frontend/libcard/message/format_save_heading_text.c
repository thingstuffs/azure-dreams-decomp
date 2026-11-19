#include "common.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/save_heading.h"
#include "main/data.h"

/* Decodes the save heading from D_800282CC into the text buffer at offset 0x7C in mode 1. */
void format_save_heading_text(CardSaveHeadingDisplayPrefix *heading) {
    decode_fullwidth_text(heading->heading_text, &D_800282CC[0], 1);
}
