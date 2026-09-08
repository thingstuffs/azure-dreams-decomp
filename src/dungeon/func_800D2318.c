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

/* Updates the effect position, spawns eight objects per tick, and expires after a delay. */
void func_800D7A78(DungeonState *effect) {
    u16 position_offset[3];

    {
        u8 *position_table = D_80082E80;
        if (func_8003DE58(*(s32 *)(position_table + 8), position_table, position_offset, 0) != 0) {
            u8 *position_base = D_80083780;
            effect->x = *(u16 *)(position_base + 2) + position_offset[0];
            effect->y = *(u16 *)(position_base + 6) + position_offset[1];
            effect->z = *(u16 *)(position_base + 0xA) + position_offset[2] + 0x20;
        }
    }

    if (effect->state == 1) {
        goto spawn_objects;
    }
    if (effect->state < 2) {
        if (effect->state == 0) {
            goto start_objects;
        }
        goto done;
    }
    if (effect->state == 0xFF) {
        goto expired;
    }
    goto done;

start_objects:
    func_800A56E0(0x600);
    effect->timer = 0x3C;
    effect->state += 1;

spawn_objects:
    {
        s32 spawn_index = 7;
        u8 *object_data = D_800D7D30;
        DungeonCounter *object_counter = (DungeonCounter *)D_80083460;
        DungeonTemplate *object_template = (DungeonTemplate *)D_800DEA68;

        do {
            DungeonObject *object = func_8003FD64(0x312, D_80083498);
            if (object != NULL) {
                object->unk10 = (DungeonInner *)object_data;
                object_counter->count += 1;
                func_8004491C(object, D_80045340);
                {
                    DungeonInner *object_inner = object->unkC;
                    DungeonObjectTail *object_tail = (DungeonObjectTail *)((u8 *)object + 0x20);
                    u16 saved_flags;

                    *(s32 *)((u8 *)object->unk8 + 0x14) = 0xFFFC0000;
                    saved_flags = object_inner->unk14;
                    object_inner->unk1E = 0x600;
                    object_inner->unk1C = 0x600;
                    object_inner->unk10 = 0x20;
                    object_inner->unk0 = object_template;
                    object_inner->unk14 = saved_flags | 0xC;
                    object_inner->unk8 = object_template->unk4;
                    object_inner->unk4 = 0;
                    object_inner->unk5 = 0;
                    object_inner->unkC = effect->unkC;
                    ((ObjectPositionView *)object)->position = ((StatePositionView *)effect)->position;
                    *(u16 *)((u8 *)object->unk8 + 0xA) = effect->z;
                    object_tail->position = (s16)((spawn_index << 9) + ((s16)effect->timer * 0x28));
                    object_tail->unk1C = 0x180000 - ((0x3C - (s16)effect->timer) << 0xD);
                    object_tail->unk2A = 6;
                    object_tail->unk34 = ((s16)effect->timer - 0x3C) << 0xC;
                }
            }
            spawn_index -= 1;
        } while (spawn_index >= 0);
    }

    {
        u16 ticks_left = effect->timer - 1;
        effect->timer = ticks_left;
        if ((s16)ticks_left <= 0) {
            effect->timer = 8;
            effect->state = 0xFF;
        }
    }
    goto done;

expired:
    {
        u16 ticks_left = effect->timer - 1;
        effect->timer = ticks_left;
        if ((s16)ticks_left <= 0) {
            ((DungeonCounter *)D_80083460)->count -= 1;
            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            *(u32 *)D_800814A0 |= 0x8000;
        }
    }

done:
    return;
}
