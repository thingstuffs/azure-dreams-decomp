#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"
#include "m2c_compat.h"

s32 func_80099194();                  /* extern */
s32 dungeonAppendTypedFormattedValue();                    /* extern */
s32 func_80099734();                        /* extern */
s32 dungeonWriteStatusPrefixBytes();                             /* extern */
extern u8 D_80089000[];
extern M2C_UNK D_800E0A03[];
extern M2C_UNK D_800E0A12[];

/* Builds and displays an item message with the selected phrase and entity name. */
void func_800A63B8(s32 entity, M2C_UNK item, s32 message_kind, s32 buffer_arg) {
    s32 message;

    s32 text_end;

    message = func_800990FC(entity, item, message_kind, buffer_arg);
    if ((s16)message_kind == 0x15) {
        text_end = func_80099194(D_800E0A03, dungeonAppendTypedFormattedValue(item, message));
    } else {
        text_end = func_80099194(D_800E0A12, dungeonAppendTypedFormattedValue(item, message));
    }
    func_80099290(dungeonWriteStatusPrefixBytes(func_80099194(&D_80089000, func_80099734(entity, text_end))));
    func_800A5720(message);
}
