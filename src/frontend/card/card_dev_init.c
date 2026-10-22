#include "common.h"
#include "frontend/card/decimal_format_word.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "main/data.h"

s32 func_8007BFE0(void *, s32);
s32 func_8007C040(void *, void *, s32);
s32 func_8007C958(void);
s32 func_8007CB08(s32);
s32 func_80400A10(void);
extern u8 card_slot_header_cache[0x280];
extern s32 D_8009E390;


/* Initializes memory card support when card_first_flg is clear and resets card server state. */
void card_dev_init(void) {
    func_8007C040(&card_decimal_format, &card_first_flg_label, card_first_flg);
    if (card_first_flg == 0) {
        card_first_flg = 1;
        libcard_init(1);
        libcard_start();
        func_8007C958();
        func_8007CB08(0);
        D_8009E390 = 0;
        D_8009E394 = 0;
        func_8007BFE0(card_slot_header_cache, 0x280);
    }
    func_80400A10();
    *(s32 *)0x804094F0 = 0;
    *(s32 *)0x804094F4 = 0;
    *(s32 *)0x804094F8 = 0;
    *(s32 *)0x804094FC = 0;
    *(s32 *)0x804094E8 = 0;
}
