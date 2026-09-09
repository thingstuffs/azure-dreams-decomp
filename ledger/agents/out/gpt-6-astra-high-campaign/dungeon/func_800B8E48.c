#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(s32);
extern void func_800997FC(void *);
extern void func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s32, s32);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800D5460(void *, s32, s32);

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E104E[];
extern u8 D_800E107C[];
extern void *D_800E3D7C;

/* Applies an item effect to the target and handles item consumption. */
s32 func_800BE5A8(void *target, s32 item, s16 message_kind)
{
    if (target == D_800E3D7C) {
        *(s32 *)((u8 *)target + 0x110) = item;
        func_8008D330(target, D_80083780, D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A63B8(target, item, message_kind);
        if (func_800AD6FC(
                target, (D_800DDE84[*((u8 *)target + 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }

        if (func_800A48F0(target, 0x20, 0x10) << 16) {
            if (*(s32 *)((u8 *)target + 0x14) & 0x4000) {
                func_80099844(target, D_800E104E);
            }
        }
        func_800D5460((u8 *)target - 0x20, 0xE0E0E0, 0x702);
    } else {
        func_800997FC(D_800E107C);
    }
    func_80098B38(item);
    D_80083460.fieldA--;
    return 1;
}
