#include "common.h"
#include "m2c_compat.h"

s32 func_800990FC(s32, M2C_UNK, s32, s32);                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099368();                    /* extern */
s32 func_80099734();                        /* extern */
s32 func_800999B0();                             /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern M2C_UNK D_80089000[];
extern M2C_UNK D_800E0A03[];
extern M2C_UNK D_800E0A12[];

/* Builds and displays an item message with the selected phrase and entity name. */
void func_800A63B8(s32 entity, M2C_UNK item, s32 message_kind, s32 buffer_arg) {
    s32 message;

    s32 text_end;

    message = func_800990FC(entity, item, message_kind, buffer_arg);
    if ((s16)message_kind == 0x15) {
        text_end = func_80099194(D_800E0A03, func_80099368(item, message));
    } else {
        text_end = func_80099194(D_800E0A12, func_80099368(item, message));
    }
    func_80099290(func_800999B0(func_80099194(&D_80089000, func_80099734(entity, text_end))));
    func_800A5720(message);
}
