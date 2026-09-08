#include "common.h"

typedef struct DungeonObject {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 flags_14;
    u8 pad_18[0xf8];
    s32 unk_110;
} DungeonObject;

extern DungeonObject *D_800E3D7C[];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u16 D_80083460[];
extern u8 D_800E15BB[];
extern u8 D_800E15E5[];

extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern s32 func_800A48F0(void *, s32, s32);
extern s32 func_800A5720(s32);
extern s32 func_800A5F38(void *, s32);
extern s32 func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);

/* Processes an object action, dispatching the player case and reporting failure. */
s32 func_800C24A8(DungeonObject *object, s32 action, s16 action_type) {
    s32 message;
    s32 message_end;

    if (object == D_800E3D7C[0]) {
        object->unk_110 = action;
        func_8008D330(object, D_80083780, D_80082E80, object);
        return 0;
    }
    if ((u32) object <= 0x9FFFFFFFU) {
        func_800A63B8(object, action, action_type);
        if (func_800AD6FC(object, (D_800DDE84[object->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(object, action);
            return 1;
        }
    }
    if ((func_800A48F0(object, 9, 0x60) << 16) != 0) {
        if (object->flags_14 & 0x4000) {
            message = func_800990FC();
            message_end = func_80099734(object, message);
            message_end = func_80099194(D_800E15BB, message_end);
        } else {
            message = func_800990FC();
            message_end = message;
            message_end = func_80099194(D_800E15E5, message_end);
        }
        func_80099290(message_end);
        func_800A5720(message);
    }
    func_80098B38(action);
    D_80083460[5] = D_80083460[5] - 1;
    return 1;
}
