#include "common.h"
#include "m2c_compat.h"

s32 func_8007BFE0(void *, s32);
s32 func_8007C040(void *, void *, s32);
s32 func_8007C958(void);
s32 func_8007CB08(s32);
s32 func_80400A10(void);
void libcard_init(s32 slot);
void libcard_start(void);
extern M2C_UNK D_8009DDD8;
extern s32 D_8009E390;
extern s32 D_8009E394;
extern s32 D_8013BB6C;
extern s32 D_80400038;
extern s32 D_80400044;

/* Initializes memory card support when card_first_flg is clear and resets card server state. */
void card_dev_init(void) {
    func_8007C040(&D_80400038, &D_80400044, D_8013BB6C);
    if (D_8013BB6C == 0) {
        D_8013BB6C = 1;
        libcard_init(1);
        libcard_start();
        func_8007C958();
        func_8007CB08(0);
        D_8009E390 = 0;
        D_8009E394 = 0;
        func_8007BFE0(&D_8009DDD8, 0x280);
    }
    func_80400A10();
    *(s32 *)0x804094F0 = 0;
    *(s32 *)0x804094F4 = 0;
    *(s32 *)0x804094F8 = 0;
    *(s32 *)0x804094FC = 0;
    *(s32 *)0x804094E8 = 0;
}
