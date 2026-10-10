#include "modules/dungeon_native_abi.h"
#include "modules/dungeon_ovl_1894800.h"
#include "common.h"

typedef s32 M2C_UNK;

extern const u8 D_80024004[48];
extern const u8 D_80024034[4];
extern M2C_UNK D_800E1C8A;

extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_80099734(void *record, u8 *out);
extern void func_80099844(void *, void *);
extern s32 func_8009D218(void *, s32);
extern s32 func_800A48F0(void *, s32, s32);
extern void func_800A5720(s8 *text);
extern s32 func_800A6870(s16 input_value);

/* Applies a directional effect and reports the result for flagged entities. */
void func_80024098(void *entity, s32 direction, void *unused)
{
    s32 message_start;
    s32 message_end;

    if (func_8009D218(entity, 2) == 0) {
        if (func_800A48F0(
                entity, 0x13,
                ((func_800A6870(direction & 0xFF) + 4) << 24) >> 24) << 16) {
            if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
                func_80099844(entity, &D_800E1C8A);
                return;
            }
        } else if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
            message_end = func_800990FC();
            message_start = message_end;
            message_end = func_80099194(&D_80024004, message_end);
            message_end = func_80099734(entity, message_end);
            message_end = func_80099194(&D_80024034, message_end);
            func_80099290(message_end);
            func_800A5720(message_start);
        }
    }
}
