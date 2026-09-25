#include "slus/message_mode_81550.h"

typedef void (*FuncPtr_8004DCEC)(char *);
extern char D_80080B6C[2];

/* Calls the selected mode handler with the shared work buffer. */
void func_8004DCEC(void)
{
    FuncPtr_8004DCEC handler;
    handler = D_800714A4[D_80081550];
    do { } while (0);
    handler(D_80080B6C);
}
