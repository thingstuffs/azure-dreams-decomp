#include "common.h"
#include "frontend/card/server_imports.h"

/* The devkit server's four referenced fade values (card_dev's fade_four_entries reads them at +0x68C). */
typedef struct CardDevFadeRefs {
    u8 unk_000[0x1F0];
    s32 *values[4];
} CardDevFadeRefs;

/* Passes each of the four referenced values to the devkit release call. */
void card_dev_fade_four_values(CardDevFadeRefs *object)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80051FBC(*object->values[i]);
    }
}
