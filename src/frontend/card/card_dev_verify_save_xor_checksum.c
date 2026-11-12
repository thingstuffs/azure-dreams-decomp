#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/checksum_trace_data.h"

/* Computes the game-save XOR checksum and compares it with the stored checksum. */
s32 card_dev_verify_save_xor_checksum(void *gsw)
{
    s32 *word;
    s32 checksum;
    s32 count;
    s32 value;

    checksum = 0;
    word = (s32 *)((u8 *)gsw + 0x208);
    if (gsw != 0) {
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

    func_8007C040(checksum_trace_format, computed_checksum_label, checksum);
    func_8007C040(checksum_trace_format, saved_checksum_label,
                  *(s32 *)((u8 *)gsw + 0x204));
    return *(s32 *)((u8 *)gsw + 0x204) == checksum;
}
