#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern void func_80042B68(void *, s32);
extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099368(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800C4D78(s32, s32);

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E1756[];
extern u8 D_800E176F[];
extern u8 D_800E1788[];
extern u8 *D_800E3D7C;

/* Applies a curse-removal item effect and reports changes to equipped items. */
s32 func_800C3440(void *target, s32 item, s16 use_mode, s32 use_context)
{
    u8 *equipment;
    s32 message_buf;
    s32 uncursed;

    if (use_mode == 13) {
        return func_80098864(item, use_context);
    }

    if (target == D_800E3D7C) {
        *(s32 *)((u8 *)target + 0x110) = item;
        func_8008D344(target, D_80083780, D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, item);
        if (func_800AD6FC(target,
                         D_800DDE84[((u8 *)target)[0x13]] & 3,
                         item) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    } else {
        func_800C4D78(0xC0C0C0, 0);
        func_800A56E0(0x702);
        func_80042B68(target, 8);

        uncursed = 0;
        equipment = *(u8 **)(D_800E3D7C + 0x4C);
        if (equipment[1] != 0 && (equipment[3] & 0x40) != 0) {
            equipment[3] &= 0xBF;
            message_buf = func_800990FC();
            func_80099290(func_80099194(D_800E1756,
                                      func_80099368(equipment, message_buf)));
            func_800A5720(message_buf);
            uncursed = 1;
        }

        equipment = *(u8 **)(D_800E3D7C + 0x50);
        if (equipment[1] != 0 && (equipment[3] & 0x40) != 0) {
            equipment[3] &= 0xBF;
            message_buf = func_800990FC();
            func_80099290(func_80099194(D_800E176F,
                                      func_80099368(equipment, message_buf)));
            func_800A5720(message_buf);
            uncursed = 1;
        }

        if (uncursed == 0) {
            message_buf = func_800990FC();
            func_80099290(func_80099194(D_800E1788, message_buf));
            func_800A5720(message_buf);
        }
    }

    D_80083460.fieldA--;
    func_80098B38(item);
    return 1;
}
