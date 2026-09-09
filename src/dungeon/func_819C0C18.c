#include "common.h"

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
extern void *D_80024048[];
extern s16 D_8002992E;
extern u8 D_8006E8A0[];
extern u8 D_8006EE50[];
extern s32 D_800814A0;
extern GlobalObj *D_800814A8[3];
extern u16 D_80082E86;
extern u16 D_80082E94;
extern u8 D_80083160[];
extern u8 D_80083460[];
extern Position D_80083780;

extern void func_80024BA0(void);
extern void func_80025CE8(s32, s32, s32, s32);
extern void func_8002626C(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80026898(void) __attribute__((noreturn));
extern void func_800268A0(void) __attribute__((noreturn));
extern void func_80026924(void) __attribute__((noreturn));
extern void func_8003F80C(void *, s32, s32, s32);
extern s32 func_80040490(void *, void *);
extern void func_800542BC(void);
extern s32 func_80069EF8(void);
extern void func_800A56E0(s32);
extern void func_800C77D0(void *, void *, s32, s32);

/* Advances a particle effect through its timed color fade and cleanup states. */
void func_819C0C18(S_func_819C0C18_0 *effect)
{
    static void *const keep_cases[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&done, &&done
    };
    s32 rect[2];
    OffsetTable offsets = D_80024028;
    S_func_819C0C18_3 *colors = (S_func_819C0C18_3 *)D_80083160;
    s32 state;

    state = effect->unk_0A.s;
    if ((u32)state >= 7) {
        goto done;
    }
    goto *D_80024048[state];

case_0:
    {
        s32 rect_xy;
        s32 rect_size;
        GlobalObj *owner;
        ChildObj *child;
        u16 state;

        func_800C77D0((u8 *)D_800814A8[0] - 0x20, &D_80083780, 8, 0x400);
        rect_xy = 0x010003A0;
        rect_size = 0x00400020;
        D_800814A8[0]->unk_102 = 1;
        rect[0] = rect_xy;
        rect[1] = rect_size;
        func_80040490(D_8006E8A0, rect);
        func_8003F80C(D_8006EE50, 0x7AC0, 1, 2);
        func_80024BA0();

        owner = D_800814A8[0];
        owner->unk_F4 = 0;
        owner->unk96 = 30;
        state = effect->unk_0A.u;
        D_8002992E = 1;
        effect->unk_2A = 0;
        effect->unk_0A.u = state + 1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        child = effect->unk_04;
        if ((child->flags & 0x80) == 0) {
            return;
        }
        func_800A56E0(0x300);
        func_800542BC();
        func_80026898();
        return;
    }

case_1:
    {
        u16 timer = effect->unk_28.u;
        register GlobalObj *owner ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        Position *position;
        OffsetPair *offset_base;
        u16 next_state;
        u16 direction;
        s16 particle_index;

        effect->unk_28.u = timer + 1;
        if ((s16)timer >= 0x52) {
            owner = D_800814A8[0];
            effect->unk_1C.s = 0x21;
            owner->unkA6 = owner->unkA6 - 1;
            owner->unkA8 = effect->unk_08;
            owner = D_800814A8[0];
            next_state = effect->unk_0A.u;
            direction = owner->unk2A;
            effect->unk_0A.u = next_state + 1;
            effect->unk_28.u = 0;
            effect->unk_24 = (direction >> 9) & 7;
        }

        particle_index = 0;
        if (effect->unk_28.s == 0x4A) {
            Position *effect_position = &D_80083780;

            func_80025CE8((s16)effect_position->x,
                          (s16)effect_position->y,
                          (s16)effect_position->z,
                          (s16)D_800814A8[0]->unk2A);
        }

        effect->unk_24 = (D_800814A8[0]->unk2A >> 9) & 7;
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
                          (s16)(position->x + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offset_base +
                                  effect->unk_24 * 4);
                              offset->x;
                          }) * 128),
                          (s16)(position->y + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offset_base +
                                  effect->unk_24 * 4);
                              (s32)(offset->y << 16) >> 9;
                          })),
                          (s16)(position->z - 0x74));
            particle_index++;
        } while (particle_index < 2);

        if (colors->unk_A8 < 0x3D) {
            return;
        }
        colors->unk_A8 -= 2;
        colors->unk_A9 -= 2;
        colors->unk_AA -= 2;
        func_80026924();
        return;
    }

case_2:
    {
        s32 reset_timer;
        u16 current_state;

        effect->unk_28.u = 0;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        if (colors->unk_A8 >= 0x3D) {
            colors->unk_A8 -= 2;
            colors->unk_A9 -= 2;
            colors->unk_AA -= 2;
        }
        effect->unk_1C.u = effect->unk_1C.u - 1;
        if (effect->unk_1C.s > 0) {
            return;
        }
        reset_timer = 0x3C;
        current_state = effect->unk_0A.u;
        ASM_KEEP(current_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        effect->unk_1C.s = reset_timer;
        func_800268A0();
        return;
    }

case_3:
    {
        s8 color = colors->unk_A8;
        s32 dungeon_mode;

        if ((u8)color < 0x80) {
            colors->unk_A8 += 10;
            colors->unk_A9 += 10;
            colors->unk_AA += 10;
        }
        if ((D_80082E94 & 0x8000) == 0) {
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
            func_80026924();
            return;
        } else {
            D_8002992E = 0;
            func_80026924();
            return;
        }
    }

case_4:
    {
        u16 timer = effect->unk_28.u;

        effect->unk_28.u = timer + 1;
        if ((s16)timer < 4) {
            return;
        }
        colors->unk_AA = 0x80;
        colors->unk_A9 = 0x80;
        colors->unk_A8 = 0x80;
        {
            S_func_819C0C18_1 *dungeon_state = (S_func_819C0C18_1 *)D_80083460;

            dungeon_state->unk_0C = 0;
            dungeon_state->unk_0A =
                dungeon_state->unk_0A - 1;
        }
        D_80082E86 = 0;
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }

done:
    return;
}
