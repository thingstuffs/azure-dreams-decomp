#include "common.h"
#include "frontend/card.h"

/* Three template words for the selected-row packet, in the server's data. */
extern s32 D_80408CDC[3];

/* Build the selected-row packet and the boundary command after it; return the next free byte. */
void *card_background_init_selected_prims(u8 *record)
{
    s32 word_04;
    s32 word_0C;

    record[1] = 0xB0;
    /* BYTES: a typed two-record view lets gcc move the boundary-command stores ahead of the template word stores; the byte buffer with its 24-byte advance keeps the retail order */
    *(s32 *)(record + 8) = D_80408CDC[0];
    word_04 = D_80408CDC[2];
    word_0C = D_80408CDC[1];
    record[1] |= 2;
    record[0] |= 0x41;
    /* BYTES: as above, a word store into the byte buffer */
    *(s32 *)(record + 4) = word_04;
    /* BYTES: as above, a word store into the byte buffer */
    *(s32 *)(record + 0xC) = word_0C;
    record += 24;
    record[1] = 0x81;
    /* BYTES: as above, halfword stores into the boundary command of the byte buffer */
    *(s16 *)(record + 4) = 32;
    /* BYTES: as above, a halfword store into the byte buffer */
    *(s16 *)(record + 6) = 0;
    record[0] |= 0x80;
    return record + 0xC;
}
