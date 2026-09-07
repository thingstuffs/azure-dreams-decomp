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

/* Applies an item effect, selects its amount, and displays the result. */
s32 func_800BD1C4(DungeonObject *obj, u8 *payload, s16 effect_arg) {
    s16 effect_state;
    s32 amount;
    s16 remaining;
    u8 counter;
    s32 message_handle;
    s32 message_arg;
    const void *message;
    volatile u16 *kind_flags;

    effect_state = 0;
    if (obj == (DungeonObject *)D_800E3D7C[0]) {
        obj->payload = payload;
        func_8008D330(obj, D_80083780, D_80082E80, obj);
        return 0;
    }
    if ((u32)obj <= 0x9FFFFFFFU) {
        func_800A63B8(obj, payload, effect_arg);
        kind_flags = D_800DDE84;
        if (func_800AD6FC(obj, ((u32)kind_flags[obj->kind] >> 6) & 3, 0) == 0) {
            func_800A5F38(obj, payload);
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
        effect_state = -1;
        if (*payload == 0xF) {
            counter = obj->counter;
            if (counter < 0xFFU) {
                obj->counter = counter + 1;
                func_80041E70(obj);
            }
            obj->amount = 1;
            effect_state = 1;
            goto after_amount;
        }
    } else {
        remaining = obj->limit - obj->current;
        if (remaining < amount) {
            amount = remaining;
        }
        obj->amount = amount;
    }

after_amount:
    if (func_800AD568(obj) != 0) {
        s32 display_mode;

        display_mode = 0x10;
        if ((effect_state << 16) > 0) {
            display_mode = 0x8010;
        }
        func_800B4C7C(display_mode, obj, obj->amount, 1);
    }
    if (obj->flags & 0x4000) {
        message_handle = func_800990FC();
        if (effect_state > 0) {
            func_80099290(func_80099194(&D_80089354[0], func_8003AD08(obj->amount, func_80099194(&D_800E0E14[0], func_80099734(obj, message_handle)))));
        } else if (effect_state == 0) {
            func_80099290(func_80099194(&D_80089354[0], func_8003AD08(obj->amount, func_80099194(&D_800E0E34[0], func_80099734(obj, message_handle)))));
        } else {
            func_80099290(func_80099194(&D_800E0E50[0], message_handle));
        }
        func_800A5720(message_handle);
    }
    func_80098B38(payload);
    {
        volatile u16 *counter_base;

        counter_base = D_80083460;
        counter_base[5] = counter_base[5] - 1;
    }
    return 1;
}
