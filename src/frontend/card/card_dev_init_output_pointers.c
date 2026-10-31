#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

typedef struct S_8002089C_0 {
    u8 pad_00[0xF0];
    s32 ** unk_F0;
    s32 ** unk_F4;
    void ** unk_F8;
    void ** unk_FC;
} S_8002089C_0;   /* arg0 in card_dev_init_output_pointers */

/* Populate the indirect output pointers with shared data and embedded records. */
void card_dev_init_output_pointers(void *record_arg) {
    S_8002089C_0 *record = record_arg;

    *record->unk_F0 = &D_80083060;
    *record->unk_F4 = &D_8008306C;
    *record->unk_F8 = record_arg + 4;
    *record->unk_FC = record_arg + 0x7C;
}
