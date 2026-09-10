#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p)+(o)))
extern u8 *D_800E3D7C;
extern u8 D_80082E80[],D_80083780[],D_800893D8[],D_800E16E3[],D_800E1713[],D_800E39C8[];
extern s32 D_80083460;
extern s16 func_800B60B8(s32,s32,s16,s32,s32);
extern void func_8008D344(void *, void *, void *, void *);
extern void func_80098B38(void *);
extern void func_80099290(s32);
extern void func_800997FC(void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800C8CD8(void *, s32, s32);
/* Processes an actor's item and updates its object entry, effects, and item count. */
s32 func_800C2F2C(void *actor, u8 *item, s16 action) {
    s16 entry_index;
    s32 message_handle;
    s32 saved_handle, object_addr;
    s32 *counter_base;
    void *entity;
    u8 *object_fields;
    u8 *entries;

    if (actor == D_800E3D7C) {
        F(actor, u8 *, 0x110) = item;
        func_8008D344(actor, D_80083780, D_80082E80, actor);
        return 0;
    }

    entity = F(actor, void **, -0x14);
    object_addr = func_800C7380(F(entity, u8, 0x24), F(entity, u8, 0x25),
                               F(actor, s16, 0x88), -1, *item);
    if (object_addr != 0) {
        func_800A56E0(0x60D);
        entry_index = func_800B60B8(F(entity, u8, 0x24), F(entity, u8, 0x25),
                                   F(actor, s16, 0x88), 5, object_addr);
        object_fields = (u8 *)object_addr + 0x20;
        ASM_KEEP(object_fields);
        entries = D_800E39C8;
        F(object_fields, s16, 0x20) = entry_index;
        F(entries + entry_index * 0x18, s32, 8) = 0;
        message_handle = func_800990FC();
        saved_handle = message_handle;

        if (action == 0xD) {
            func_80099290(func_800999B0(func_80099194(D_800893D8,
                func_80099734(actor, func_80099194(D_800E1713,
                    func_80099368(item, message_handle))))));
    message_handle = 0;
            func_800A5720(saved_handle);
        }

        func_800997FC(D_800E16E3);
        func_800C8CD8(actor, 0x100, 0x10);
        func_8009A21C(F(entity, u8, 0x24), F(entity, u8, 0x25), 0x10);
        func_80098B38(item);
        counter_base = &D_80083460;
        F(counter_base, u16, 0xA)--;
        return 1;
    }
    return 0;
}
