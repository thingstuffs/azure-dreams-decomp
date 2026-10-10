#include "modules/dungeon_native_abi.h"

typedef struct S_func_8187A800_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_func_8187A800_0;

extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_80099734(void *record, u8 *out);
extern void func_80099844(void *, void *);
extern s32 func_8009D218(void *, s32);
extern s32 func_800A48F0(void *, s32, s8);
extern void func_800A5720(s8 *text);
extern s32 func_800A6870(s16 input_value);

void func_80025C5C(void *, void *, void *);
void (*const dungeon_189a800_entry)(void *, void *, void *) = func_80025C5C;
const u8 D_80024004[48] = {0x82,0x73,0x82,0x88,0x82,0x85,0x82,0x92,0x82,0x85,0x81,0x40,0x82,0x97,0x82,0x81,0x82,0x93,0x81,0x40,0x82,0x8e,0x82,0x8f,0x81,0x40,0x82,0x85,0x82,0x86,0x82,0x86,0x82,0x85,0x82,0x83,0x82,0x94,0x81,0x40,0x82,0x8f,0x82,0x8e,0x81,0x40,0x0,0x0};
const u8 D_80024034[4] = {0x81,0x44,0x0,0x0};
extern s32 D_800E1CB0;

void func_800240B8(S_func_8187A800_0 *target, s32 effect_arg, void *unused);

/* Attempts to apply an effect and reports the outcome for flagged targets. */
void func_800240B8(S_func_8187A800_0 *target, s32 effect_arg, void *unused)
{
    s32 message;
    s32 message_start;

    if (func_8009D218(target, 4) == 0) {
        if ((func_800A48F0(target, 0x14,
                           (s8)(func_800A6870(effect_arg & 0xFF) + 2)) << 16) != 0) {
            if (target->unk_14 & 0x4000) {
                func_80099844(target, &D_800E1CB0);
                return;
            }
        } else if (target->unk_14 & 0x4000) {
            message = func_800990FC();
            message_start = message;
            message = func_80099194(&D_80024004, message);
            message = func_80099734(target, message);
            message = func_80099194(&D_80024034, message);
            func_80099290(message);
            func_800A5720(message_start);
        }
    }
}
