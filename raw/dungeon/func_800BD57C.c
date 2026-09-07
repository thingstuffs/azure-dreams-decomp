#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_8008D344(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80098B38(void *arg0);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *arg0, s32 arg1);
extern void func_80099290(s32 arg0);
extern s32 func_8009929C(s32 arg0, s32 arg1);
extern s32 func_80099368(void *arg0, s32 arg1);
extern s32 func_80099734(void *arg0, s32 arg1);
extern s32 func_800999B0(s32 arg0);
extern void func_8009A21C(u8 arg0, u8 arg1, s32 arg2);
extern void func_8009A3D0(u8 arg0, u8 arg1, s32 arg2);
extern void func_800A56E0(s32 arg0);
extern void func_800A5720(s32 arg0);
extern s16 func_800B60B8(u8 arg0, u8 arg1, s16 arg2, s32 arg3, s32 arg4);
extern s32 func_800C2F04(void);
extern s32 func_800C7380(u8 arg0, u8 arg1, s16 arg2, s32 arg3, s32 arg4);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern u8 D_800893D4[];
extern u8 D_800E1684[];
extern u8 D_800E169A[];
extern u8 D_800E39C8[];
extern u8 D_800E3D7C[];

s32 func_800C2CDC(void *arg0, u8 *arg1, s16 arg2) {
    void *entity;
    register s32 object_fields ASM_REG("$3");
    u8 *entries;
    s32 *counter_base;
    s32 object;
    s32 handle;
    s16 index;

    if (arg0 == *(u8 **)D_800E3D7C) {
        FIELD(arg0, u8 *, 0x110) = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        func_800C2F04();
        return 0;
    }

    entity = FIELD(arg0, void *, -0x14);
    object = func_800C7380(FIELD(entity, u8, 0x24),
                           FIELD(entity, u8, 0x25),
                           FIELD(arg0, s16, 0x88), 7, *arg1);
    if (object == 0) {
        return 0;
    }

    func_800A56E0(0x816);
    index = func_800B60B8(FIELD(entity, u8, 0x24),
                          FIELD(entity, u8, 0x25),
                          FIELD(arg0, s16, 0x88), 6, object);
    object_fields = object + 0x20;
    ASM_KEEP(object_fields);
    entries = D_800E39C8;
    FIELD(object_fields, s16, 0x20) = index;
    FIELD(entries + (index * 24), s32, 8) = 0;

    handle = func_800990FC();
    object = func_8009929C(8, handle);

    if (arg2 == 13) {
        object = func_800999B0(func_80099194(D_800893D4,
                    func_80099734(arg0, func_80099194(D_800E1684,
                        func_80099368(arg1, object)))));

        if (!(FIELD(arg0, s32, 0x1C) & 0x2000) &&
                FIELD(arg0, u8, 0x13) < 0x31) {
            func_8009A3D0(FIELD(entity, u8, 0x24),
                          FIELD(entity, u8, 0x25), 0x3000);
            FIELD(arg0, s32, 0x1C) |= 0x2000;
            func_8009A21C(FIELD(entity, u8, 0x24),
                          FIELD(entity, u8, 0x25), 0x300);
        }

        func_80099290(object);
        func_800A5720(handle);
    }

    handle = func_800990FC();
    func_80099290(func_80099194(D_800E169A, handle));
    func_800A5720(handle);

    if ((s16)func_80042900(arg0, 2) != 0) {
        func_80042B68(arg0, 2);
    }

    func_8009A21C(FIELD(entity, u8, 0x24), FIELD(entity, u8, 0x25), 2);
    func_80098B38(arg1);
    counter_base = &D_80083460;
    FIELD(counter_base, u16, 0xA)--;
    return 1;
}
