#include "common.h"

typedef struct DungeonObject {
    u8 pad00[5];
    u8 counter;
    u8 pad06[13];
    u8 kind;
    s32 flags;
    u8 pad18[0x10];
    u8 current;
    u8 limit;
    u8 pad2a[0x3a];
    s16 amount;
    u8 pad66[0xaa];
    u8 *payload;
} DungeonObject;

extern u8 *D_800E3D7C[];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u16 D_80083460[];
extern u8 D_80089354[];
extern u8 D_800E0E14[];
extern u8 D_800E0E34[];
extern u8 D_800E0E50[];

extern s32 func_8003AD08(s16, s32);
extern void func_80041E70(DungeonObject *);
extern void func_8008D330(DungeonObject *, u8 *, u8 *, DungeonObject *);
extern void func_80098B38(u8 *);
extern s32 func_800990FC(void);
extern s32 func_80099194(const void *, s32);
extern void func_80099290(u32);
extern s32 func_80099734(DungeonObject *, s32);
extern void func_800A5720(s32);
extern void func_800A5F38(DungeonObject *, u8 *);
extern void func_800A63B8(DungeonObject *, u8 *, s16);
extern s32 func_800A6D30(void);
extern s32 func_800AD568(DungeonObject *);
extern s32 func_800AD6FC(DungeonObject *, u32, s32);
extern void func_800B4C7C(s32, DungeonObject *, s16, s32);
extern void func_800C4AFC(s32, s32, DungeonObject *);

s32 func_800BD1C4(DungeonObject *obj, u8 *arg1, s16 arg2) {
    s16 state;
    s32 amount;
    s16 delta;
    u8 value;
    s32 timer;
    s32 message_arg;
    const void *message;
    volatile u16 *lookup;

    state = 0;
    if (obj == (DungeonObject *)D_800E3D7C[0]) {
        obj->payload = arg1;
        func_8008D330(obj, D_80083780, D_80082E80, obj);
        return 0;
    }
    if ((u32)obj <= 0x9FFFFFFFU) {
        func_800A63B8(obj, arg1, arg2);
        lookup = D_800DDE84;
        if (func_800AD6FC(obj, ((u32)lookup[obj->kind] >> 6) & 3, 0) == 0) {
            func_800A5F38(obj, arg1);
            return 1;
        }
    }
    func_800C4AFC(*(s32 *)((u8 *)obj - 0x18), 0x20E020, obj);
    amount = (func_800A6D30() & 7) + 0x20;
    if (amount >= 0x100) {
        amount = 0xFF;
    }
    obj->amount = amount;
    if (obj->current == obj->limit) {
        state = -1;
        if (*arg1 == 0xF) {
            value = obj->counter;
            if (value < 0xFFU) {
                obj->counter = value + 1;
                func_80041E70(obj);
            }
            obj->amount = 1;
            state = 1;
            goto after_amount;
        }
    } else {
        delta = obj->limit - obj->current;
        if (delta < amount) {
            amount = delta;
        }
        obj->amount = amount;
    }

after_amount:
    if (func_800AD568(obj) != 0) {
        s32 mode;

        mode = 0x10;
        if ((state << 16) > 0) {
            mode = 0x8010;
        }
        func_800B4C7C(mode, obj, obj->amount, 1);
    }
    if (obj->flags & 0x4000) {
        timer = func_800990FC();
        if (state > 0) {
            func_80099290(func_80099194(&D_80089354[0], func_8003AD08(obj->amount, func_80099194(&D_800E0E14[0], func_80099734(obj, timer)))));
        } else if (state == 0) {
            func_80099290(func_80099194(&D_80089354[0], func_8003AD08(obj->amount, func_80099194(&D_800E0E34[0], func_80099734(obj, timer)))));
        } else {
            func_80099290(func_80099194(&D_800E0E50[0], timer));
        }
        func_800A5720(timer);
    }
    func_80098B38(arg1);
    {
        volatile u16 *counter_base;

        counter_base = D_80083460;
        counter_base[5] = counter_base[5] - 1;
    }
    return 1;
}
