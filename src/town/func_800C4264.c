#include "common.h"
#include "m2c_compat.h"

void appendTownMovieListNode();        /* extern */
M2C_UNK SD_Call();                     /* extern */
M2C_UNK func_800542BC();                            /* extern */
extern M2C_UNK D_800717E8;
extern s8 D_80080A88;
extern M2C_UNK D_800D42B4;

/* Pass the town data pair to appendTownMovieListNode, set the shared flag, and invoke the follow-up routines. */
void func_800C19C4(void) {
    appendTownMovieListNode(&D_800717E8, &D_800D42B4);
    D_80080A88 = 1;
    SD_Call(0xBF);
    func_800542BC();
}
