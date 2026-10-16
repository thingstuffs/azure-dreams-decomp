#include "common.h"
#include "m2c_compat.h"

s32 townSelectStatusCodeFromCallback();                            /* extern */
void townClearScriptFlagBit();                     /* extern */
s32 townGetScriptFlagMask();                         /* extern */
extern M2C_UNK D_8001B314;
extern M2C_UNK *D_8001C370;
extern s8 D_8001ED72;
extern s8 D_8001F092;

/* Initializes the active data pointer and refreshes two status flags. */
void townInitializeActiveEventData(void) {
    D_8001C370 = &D_8001B314;
    townClearScriptFlagBit(0xD52);
    townClearScriptFlagBit(0xD76);
    townClearScriptFlagBit(0xD77);
    if (townGetScriptFlagMask(0xD32) == 0) {
        townSelectStatusCodeFromCallback();
    }
    D_8001ED72 = townGetScriptFlagMask(0x1463) == 0;
    D_8001F092 = townGetScriptFlagMask(0x9B) != 0;
}
