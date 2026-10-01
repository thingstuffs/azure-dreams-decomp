#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    s16 x;
    u16 y;
} OffsetPair;

typedef struct {
    OffsetPair entries[8];
} OffsetTable;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;

typedef struct {
    u8 pad0[0x2A];
    u16 unk2A;
    u8 pad2C[0x6A];
    s16 unk96;
    u8 pad98[0x0E];
    u16 unkA6;
    u8 unkA8;
    u8 unkA9;
    u8 unkAA;
    u8 pad_AB[0x49];
    s32 unk_F4;
    u8 pad_F8[0xA];
    u8 unk_102;
} GlobalObj;

typedef struct {
    u16 flags;
} ChildObj;

typedef struct S_func_819C0C18_0 {
    u8 pad_00[4];
    ChildObj *unk_04;
    u8 unk_08;
    u8 pad_09[1];
    union { s16 s; u16 u; } unk_0A;
    u8 pad_0C[0x10];
    union { s16 s; u16 u; } unk_1C;
    u8 pad_1E[6];
    s16 unk_24;
    u8 pad_26[2];
    union { s16 s; u16 u; } unk_28;
    u16 unk_2A;
} S_func_819C0C18_0;

typedef struct S_func_819C0C18_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_func_819C0C18_1;

typedef struct S_func_819C0C18_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_func_819C0C18_3;

extern OffsetTable D_80024028;
extern s16 D_8002992E;
extern u8 D_8006E8A0[];
extern u8 D_8006EE50[];

extern void func_80024BA0(void);
extern void func_80025CE8(s32, s32, s32, s32);
extern void func_8002626C(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_8003F80C(void *, s32, s32, s32);
extern s32 func_80040490(void *, void *);
extern void func_800542BC(void);
extern s32 func_80069EF8(void);
extern void func_800A56E0(s32);
extern void func_800C77D0(void *, void *, s32, s32);

/* Advances a particle effect through its timed color fade and cleanup states. */
void func_819C0C18(S_func_819C0C18_0 *effect)
{
    s32 rect[2];
    OffsetTable offsets = D_80024028;
    GameWork *colors = &gameWork;
    s32 state;
    s32 rect_xy;
    s32 rect_size;
    GlobalObj *owner;
    ChildObj *child;
    u16 next_state;
    s32 reset_timer;

    state = effect->unk_0A.s;
    switch (state) {
    case 0:
        func_800C77D0((u8 *)((GlobalObj *)D_800814A8) - 0x20, ((Position *)&D_80083780), 8, 0x400);
        rect_xy = 0x010003A0;
        rect_size = 0x00400020;
        D_800814A8->unk_102 = 1;
        rect[0] = rect_xy;
        rect[1] = rect_size;
        func_80040490(D_8006E8A0, rect);
        func_8003F80C(D_8006EE50, 0x7AC0, 1, 2);
        func_80024BA0();

        owner = ((GlobalObj *)D_800814A8);
        owner->unk_F4 = 0;
        owner->unk96 = 30;
        next_state = effect->unk_0A.u;
        D_8002992E = 1;
        effect->unk_2A = 0;
        effect->unk_0A.u = next_state + 1;
    case 1:
        child = effect->unk_04;
        if ((child->flags & 0x80) == 0) {
            return;
        }
        func_800A56E0(0x300);
        func_800542BC();
        effect->unk_28.u = 0;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 2:
    {
        u16 timer = effect->unk_28.u;
        GlobalObj *owner;
        EntityRec *position;
        OffsetPair *offset_base;
        u16 next_state;
        u16 direction;
        s16 particle_index;

        effect->unk_28.u = timer + 1;
        if ((s16)timer >= 0x52) {
            owner = ((GlobalObj *)D_800814A8);
            effect->unk_1C.s = 0x21;
            owner->unkA6 = owner->unkA6 - 1;
            owner->unkA8 = effect->unk_08;
            next_state = effect->unk_0A.u;
            direction = ((u16)D_800814A8->facing);
            effect->unk_0A.u = next_state + 1;
            effect->unk_28.u = 0;
            effect->unk_24 = (direction >> 9) & 7;
        }

        particle_index = 0;
        if (effect->unk_28.s == 0x4A) {
            EntityRec *effect_position = &D_80083780;

            func_80025CE8((s16)((u16)effect_position->x.w.i),
                          (s16)((u16)effect_position->y.w.i),
                          (s16)((u16)effect_position->z.w.i),
                          (s16)((u16)D_800814A8->facing));
        }

        effect->unk_24 = (((u16)D_800814A8->facing) >> 9) & 7;
        position = &D_80083780;
        offset_base = offsets.entries;
        do {
            s32 spread_y;
            s32 spread_x;
            s32 spread_z;

            spread_y = (s16)((func_80069EF8() & 0x7F) - 0x40);
            spread_x = (s16)((func_80069EF8() & 0x7F) - 0x40);
            spread_z = (s16)((func_80069EF8() & 0x7F) - 0x40);

            func_8002626C((u8 *)effect - 0x20, effect->unk_24,
                          0x00C0C0C0, 0x28, spread_y, spread_x, spread_z,
                          (s16)(((u16)position->x.w.i) + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offset_base +
                                   effect->unk_24 * 4);
                              offset->x;
                          }) * 128),
                          (s16)(((u16)position->y.w.i) + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offset_base +
                                   effect->unk_24 * 4);
                              (s32)(offset->y << 16) >> 9;
                          })),
                          (s16)(((u16)position->z.w.i) - 0x74));
            particle_index++;
        } while (particle_index < 2);

        if (colors->view.unk_090 < 0x3D) {
            return;
        }
        colors->view.unk_090 -= 2;
        colors->view.unk_091 -= 2;
        colors->view.unk_092 -= 2;
        return;
    }

    case 3:
        effect->unk_28.u = 0;
        effect->unk_0A.u = effect->unk_0A.u + 1;
    case 4:
        if (colors->view.unk_090 >= 0x3D) {
            colors->view.unk_090 -= 2;
            colors->view.unk_091 -= 2;
            colors->view.unk_092 -= 2;
        }
        effect->unk_1C.u = effect->unk_1C.u - 1;
        if (effect->unk_1C.s > 0) {
            return;
        }
        reset_timer = 0x3C;
        effect->unk_1C.s = reset_timer;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 5:
    {
        s8 color = colors->view.unk_090;
        s32 dungeon_mode;

        if ((u8)color < 0x80) {
            colors->view.unk_090 += 10;
            colors->view.unk_091 += 10;
            colors->view.unk_092 += 10;
        }
        if ((D_80082E80.unk_014 & 0x8000) == 0) {
            effect->unk_1C.u = effect->unk_1C.u - 1;
            if (effect->unk_1C.s >= 0) {
                return;
            }
        }
        dungeon_mode = D_8002992E;
        effect->unk_1C.s = 0;
        if (dungeon_mode == 0) {
            effect->unk_28.u = 0;
            effect->unk_0A.u = effect->unk_0A.u + 1;
            return;
        } else {
            D_8002992E = 0;
            return;
        }
    }

    case 6:
    {
        u16 timer = effect->unk_28.u;

        effect->unk_28.u = timer + 1;
        if ((s16)timer < 4) {
            return;
        }
        colors->view.unk_092 = 0x80;
        colors->view.unk_091 = 0x80;
        colors->view.unk_090 = 0x80;
        {

            dungeonStatus.unk_0C = 0;
            dungeonStatus.unk_0A =
                ((u16)dungeonStatus.unk_0A) - 1;
        }
        D_80082E80.unk_006 = 0;
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }

    default:
        return;
    }
}
