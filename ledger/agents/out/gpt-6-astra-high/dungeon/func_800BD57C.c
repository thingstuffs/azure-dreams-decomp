#include "common.h"


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
extern s32 func_800C7380(u8 arg0, u8 arg1, s16 arg2, s32 arg3, s32 arg4);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern u8 D_800893D4[];
extern u8 D_800E1684[];
extern u8 D_800E169A[];
extern u8 D_800E39C8[];
extern u8 D_800E3D7C[];


typedef struct S_800C2CDC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800C2CDC_0_pre;   /* the 0x14 bytes before arg0 in func_800C2CDC, addressed as arg0[-1] */

typedef struct S_800C2CDC_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x86];
    u8 * unk_110;
} S_800C2CDC_0;   /* arg0 in func_800C2CDC */

typedef struct S_800C2CDC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C2CDC_1;   /* entity in func_800C2CDC */

typedef struct S_800C2CDC_2 {
    u8 pad_00[0x20];
    s16 unk_20;
} S_800C2CDC_2;   /* object_fields in func_800C2CDC */

typedef struct S_800C2CDC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800C2CDC_3;   /* entries + (index * 24) in func_800C2CDC */

typedef struct S_800C2CDC_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C2CDC_4;   /* counter_base in func_800C2CDC */

/* Creates an object at the entity position, updates its state, and decrements the global count. */
s32 func_800C2CDC(void *actor, u8 *object_data, s16 action_type) {
    S_800C2CDC_1 *entity;
    s32 object_fields;
    u8 *entries;
    s32 *counter_base;
    s32 object;
    s32 handle;
    s16 entry_index;

    if (actor == *(u8 **)D_800E3D7C) {
        ((S_800C2CDC_0 *)actor)->unk_110 = object_data;
        func_8008D344(actor, D_80083780, D_80082E80, actor);
        return 0;
    }

    entity = ((S_800C2CDC_0_pre *)actor)[-1].unk_00;
    object = func_800C7380(entity->unk_24,
                           entity->unk_25,
                           ((S_800C2CDC_0 *)actor)->unk_88, 7, *object_data);
    if (object == 0) {
        return 0;
    }

    func_800A56E0(0x816);
    entry_index = func_800B60B8(entity->unk_24,
                          entity->unk_25,
                          ((S_800C2CDC_0 *)actor)->unk_88, 6, object);
    object_fields = object + 0x20;
    ASM_KEEP(object_fields);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    entries = D_800E39C8;
    ((S_800C2CDC_2 *)object_fields)->unk_20 = entry_index;
    ((S_800C2CDC_3 *)(entries + (entry_index * 24)))->unk_08 = 0;

    handle = func_800990FC();
    object = func_8009929C(8, handle);

    if (action_type == 13) {
        object = func_800999B0(func_80099194(D_800893D4,
                    func_80099734(actor, func_80099194(D_800E1684,
                        func_80099368(object_data, object)))));

        if (!(((S_800C2CDC_0 *)actor)->unk_1C & 0x2000) &&
                ((S_800C2CDC_0 *)actor)->unk_13 < 0x31) {
            func_8009A3D0(entity->unk_24,
                          entity->unk_25, 0x3000);
            ((S_800C2CDC_0 *)actor)->unk_1C |= 0x2000;
            func_8009A21C(entity->unk_24,
                          entity->unk_25, 0x300);
        }

        func_80099290(object);
        func_800A5720(handle);
    }

    handle = func_800990FC();
    func_80099290(func_80099194(D_800E169A, handle));
    func_800A5720(handle);

    if ((s16)func_80042900(actor, 2) != 0) {
        func_80042B68(actor, 2);
    }

    func_8009A21C(entity->unk_24, entity->unk_25, 2);
    func_80098B38(object_data);
    counter_base = &D_80083460;
    ((S_800C2CDC_4 *)counter_base)->unk_0A--;
    return 1;
}
