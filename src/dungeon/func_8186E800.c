#include "modules/dungeon_ovl_188e800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"



extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_80099734(void *record, u8 *out);
extern void func_80099844(void *, void *);
extern s32 func_8009D218(void *, s32);
extern s32 func_800A48F0(void *, s32, s8);
extern void func_800A5720(s8 *text);
extern s32 func_800A6870(s16 input_value);

extern const u8 D_80024004[48];
extern const u8 D_80024034[4];
extern s32 D_800E1C64;



/* Applies effect 0x12 to an eligible entity and handles messages for flagged entities. */
void func_8002407C(S_func_8186E800_0 *entity, s32 effect_param, void *context)
{
    s32 message_end;
    s32 message_start;

    if (func_8009D218(entity, 1) == 0) {
        if ((func_800A48F0(entity, 0x12,
                           (s8)(func_800A6870(effect_param & 0xFF) + 2)) << 16) != 0) {
            if (entity->unk_14 & 0x4000) {
                func_80099844(entity, &D_800E1C64);
                return;
            }
        } else if (entity->unk_14 & 0x4000) {
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
