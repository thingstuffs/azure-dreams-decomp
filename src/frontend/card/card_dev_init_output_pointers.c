#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80083060;
extern M2C_UNK D_8008306C;

typedef struct S_8002089C_0 {
    u8 pad_00[0xF0];
    s32 ** unk_F0;
    s32 ** unk_F4;
    void ** unk_F8;
    void ** unk_FC;
} S_8002089C_0;   /* arg0 in card_dev_init_output_pointers */

/* Populate the indirect output pointers with shared data and embedded records. */
void card_dev_init_output_pointers(void *record) {
    *((S_8002089C_0 *)record)->unk_F0 = &D_80083060;
    *((S_8002089C_0 *)record)->unk_F4 = &D_8008306C;
    *((S_8002089C_0 *)record)->unk_F8 = record + 4;
    *((S_8002089C_0 *)record)->unk_FC = record + 0x7C;
}
