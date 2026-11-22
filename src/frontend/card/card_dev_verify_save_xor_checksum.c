#include "frontend/card/save_image.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/checksum_trace_data.h"

/* Computes the game-save XOR checksum and compares it with the stored checksum. */
s32 card_dev_verify_save_xor_checksum(CardDevSaveWork *save)
{
    u32 *word;
    u32 checksum;
    s32 count;
    u32 value;

    checksum = 0;
    word = save->words;
    if (save != 0) {
        count = checksum;
    } else {
        count = checksum;
    }
    do {
        value = *word;
        checksum ^= value;
        word++;
        count++;
    } while (count < 0x1782);

    printf_8007C040(checksum_trace_format, computed_checksum_label, checksum);
    printf_8007C040(checksum_trace_format, saved_checksum_label,
                  save->checksum);
    return save->checksum == checksum;
}
