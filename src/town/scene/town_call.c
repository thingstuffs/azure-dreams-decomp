#include "common.h"
#include "m2c_compat.h"
void func_8003AFE0(s32 table_index, s32 flags);            /* extern */
void file_load_com(void *packed_data);                   /* extern */
extern s8 D_80080A88;
extern M2C_UNK D_80080E28;

/* town_movie3_call: Clear the shared flag and invoke the movie setup routines. */
void town_movie3_call(void) {
    D_80080A88 = 0;
    func_8003AFE0(0x14, 0x304);
    file_load_com(&D_80080E28);
}
