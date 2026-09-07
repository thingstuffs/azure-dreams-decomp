#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s16 state;
    u16 timer;
    u16 x;
    u16 y;
    u16 z;
    s32 unkC;
} DungeonState __attribute__((packed));

typedef struct {
    u8 bytes[8];
} PositionCopy __attribute__((packed));

typedef struct {
    u8 pad0[4];
    PositionCopy position;
} StatePositionView __attribute__((packed));

typedef struct {
    u8 pad0[0x2C];
    PositionCopy position;
} ObjectPositionView __attribute__((packed));

typedef struct {
    u8 pad0[4];
    s32 unk4;
} DungeonTemplate;

typedef struct {
    DungeonTemplate *unk0;
    u8 unk4;
    u8 unk5;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    s16 unk10;
    u8 pad12[2];
    u16 unk14;
    u8 pad16[6];
    s16 unk1C;
    s16 unk1E;
} DungeonInner;

typedef struct {
    u8 pad0[8];
    DungeonInner *unk8;
    DungeonInner *unkC;
    DungeonInner *unk10;
    u8 pad14[0x18];
    PositionCopy position;
} DungeonObject;

typedef struct {
    u8 pad0[0x18];
    s16 position;
    s32 unk1C;
    u8 pad20[0xA];
    s16 unk2A;
    u8 pad2C[8];
    s32 unk34;
} DungeonObjectTail;

typedef struct {
    u8 pad0[0xA];
    u16 count;
} DungeonCounter;

extern u8 D_80082E80[];
extern u8 D_80083780[12];
extern u8 D_80083460[];
extern u8 D_800814A0[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DEA68[];
extern u8 D_800D7D30[];

extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern DungeonObject *func_8003FD64(s32, void *);
extern void func_8004491C(DungeonObject *, void *);
extern void func_800A56E0(s32);

void func_800D7A78(DungeonState *arg0) {
    u16 sp10[3];

    {
        u8 *table = D_80082E80;
        if (func_8003DE58(*(s32 *)(table + 8), table, sp10, 0) != 0) {
            u8 *base = D_80083780;
            arg0->x = *(u16 *)(base + 2) + sp10[0];
            arg0->y = *(u16 *)(base + 6) + sp10[1];
            arg0->z = *(u16 *)(base + 0xA) + sp10[2] + 0x20;
        }
    }

    if (arg0->state == 1) {
        goto spawn_objects;
    }
    if (arg0->state < 2) {
        if (arg0->state == 0) {
            goto start_objects;
        }
        goto done;
    }
    if (arg0->state == 0xFF) {
        goto expired;
    }
    goto done;

start_objects:
    func_800A56E0(0x600);
    arg0->timer = 0x3C;
    arg0->state += 1;

spawn_objects:
    {
        s32 index = 7;
        u8 *list = D_800D7D30;
        DungeonCounter *counter = (DungeonCounter *)D_80083460;
        DungeonTemplate *template = (DungeonTemplate *)D_800DEA68;

        do {
            DungeonObject *object = func_8003FD64(0x312, D_80083498);
            if (object != NULL) {
                object->unk10 = (DungeonInner *)list;
                counter->count += 1;
                func_8004491C(object, D_80045340);
                {
                    DungeonInner *inner = object->unkC;
                    DungeonObjectTail *tail = (DungeonObjectTail *)((u8 *)object + 0x20);
                    u16 flags;

                    *(s32 *)((u8 *)object->unk8 + 0x14) = 0xFFFC0000;
                    flags = inner->unk14;
                    inner->unk1E = 0x600;
                    inner->unk1C = 0x600;
                    inner->unk10 = 0x20;
                    inner->unk0 = template;
                    inner->unk14 = flags | 0xC;
                    inner->unk8 = template->unk4;
                    inner->unk4 = 0;
                    inner->unk5 = 0;
                    inner->unkC = arg0->unkC;
                    ((ObjectPositionView *)object)->position = ((StatePositionView *)arg0)->position;
                    *(u16 *)((u8 *)object->unk8 + 0xA) = arg0->z;
                    tail->position = (s16)((index << 9) + ((s16)arg0->timer * 0x28));
                    tail->unk1C = 0x180000 - ((0x3C - (s16)arg0->timer) << 0xD);
                    tail->unk2A = 6;
                    tail->unk34 = ((s16)arg0->timer - 0x3C) << 0xC;
                }
            }
            index -= 1;
        } while (index >= 0);
    }

    {
        u16 value = arg0->timer - 1;
        arg0->timer = value;
        if ((s16)value <= 0) {
            arg0->timer = 8;
            arg0->state = 0xFF;
        }
    }
    goto done;

expired:
    {
        u16 value = arg0->timer - 1;
        arg0->timer = value;
        if ((s16)value <= 0) {
            ((DungeonCounter *)D_80083460)->count -= 1;
            *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
            *(u32 *)D_800814A0 |= 0x8000;
        }
    }

done:
    return;
}
