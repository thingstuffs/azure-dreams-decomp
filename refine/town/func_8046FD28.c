#include "common.h"
#include "m2c_compat.h"

s32 func_8001628C();           /* extern */
s32 func_80017E98(s32, M2C_UNK);                                /* extern */
s32 func_80019A04();         /* extern */
s32 func_80019ABC(); /* extern */
s32 func_8001A510();                         /* extern */
extern M2C_UNK D_8001A97C;
extern M2C_UNK D_8001B1FC;
extern M2C_UNK D_8001B63C;
extern M2C_UNK D_8001CDF2;

/* Select dialogue from the table, state override, or fallback. */
s32 func_80016D28(s32 speaker, M2C_UNK interaction, M2C_UNK dialogue_id) {
    s32 dialogue;

    if (func_80017E98(speaker, interaction) != 0) {
        s32 text_page;

        text_page = (s32) 0x80020000;
        ASM_KEEP(text_page);
        return text_page - 0x49C4;
    }
    dialogue = func_80019ABC(&D_8001A97C, &D_8001B1FC, speaker, dialogue_id);
    if (func_80019A04(&D_8001A97C, speaker, dialogue_id) != 0) {
        if (func_8001A510(0x799) != 0) {
            s32 text_page;

            text_page = (s32) 0x80020000;
            ASM_KEEP(text_page);
            dialogue = text_page - 0x320E;
        } else {
            dialogue = func_8001628C(speaker, interaction, dialogue_id);
        }
    }
    return dialogue;
}
