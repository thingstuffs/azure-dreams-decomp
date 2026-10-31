#include "common.h"
#include "engine/text.h"
#include "engine/util.h"
#include "town/shop.h"

/* Builds and processes a short encoded sequence in the output buffer. */
void *build_encoded_display_sequence(s32 source, u8 *outputBuffer) {
    u8 *payload;

    payload = outputBuffer + 1;
    outputBuffer[0] = 0x20;
    func_8004E5A0(source, 2, payload);
    outputBuffer[3] = 0xA;
    outputBuffer[4] = 0x6F;
    outputBuffer[5] = 0;
    remap_flagged_string_bytes(payload);
    return outputBuffer;
}
