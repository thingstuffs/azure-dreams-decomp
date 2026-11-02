#include "common.h"
#include "frontend/card/server_imports.h"

/* The devkit server's slot word references: 3 text, 4 detail and 10 icon words (the retail card UI keeps the
 * same three tables 0x34 bytes further in, see draw_cylindrical). */
typedef struct CardDevSlotWords {
    u8 unk_000[0xB18];
    s32 *text_words[3];
    s32 *detail_words[4];
    s32 *icon_words[10];
} CardDevSlotWords;

/* Releases and clears the three text words, then clears the detail and icon words. */
void card_dev_clear_slot_words(CardDevSlotWords *object)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        func_80051FBC(*object->text_words[i]);
        *object->text_words[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        *object->detail_words[i] = 0;
    }
    for (i = 0; i < 10; i++) {
        *object->icon_words[i] = 0;
    }
}
