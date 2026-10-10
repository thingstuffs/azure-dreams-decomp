#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

typedef struct S_func_819A6800_1 {
    void *unk_00;
    void *unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;
    u8 pad_0C[0x44];
    union { s16 s; u16 u; } unk_50;
    union { s16 s; u16 u; } unk_52;
} S_func_819A6800_1;

typedef struct S_func_819A6800_2 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x0C];
    void *unk_20;
    u8 unk_24;
    u8 unk_25;
} S_func_819A6800_2;

typedef struct S_func_819A6800_3 {
    u8 pad_00[0x60];
    union { void *p; u32 u; } unk_60;
    u8 pad_64[0x0E];
    u8 unk_72;
    u8 unk_73;
} S_func_819A6800_3;

typedef struct S_func_819A6800_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x7A];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    u32 unk_F4;
    u8 pad_F8[0x0A];
    u8 unk_102;
} S_func_819A6800_4;

typedef struct S_func_819A6800_5 {
    union {
        u32 u;
        s32 s;
        struct { u8 pad_00[2]; u16 unk_02; } h;
    } unk_00;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_04[2]; u16 unk_06; } h;
    } unk_04;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_08[2]; u16 unk_0A; } h;
    } unk_08;
} S_func_819A6800_5;

typedef struct S_func_819A6800_6 {
    u16 unk_00;
} S_func_819A6800_6;

typedef struct S_func_819A6800_7 {
    u8 pad_00[0x0C];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x1E];
    u16 unk_30;
    u16 unk_32;
    u32 unk_34;
    u32 unk_38;
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
    u16 unk_42;
    u8 pad_44[8];
    u16 unk_4C;
} S_func_819A6800_7;

typedef struct S_func_819A6800_8 {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    u32 unk_08;
    u32 unk_0C;
    u16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} S_func_819A6800_8;

typedef struct S_func_819A6800_9 {
    u8 pad_00[4];
    u32 unk_04;
} S_func_819A6800_9;

typedef struct S_func_819A6800_10 {
    u8 pad_00[0x0A];
    u16 unk_0A;
    u32 unk_0C;
} S_func_819A6800_10;

extern u8 D_800814A8[16];
struct S_800244BC_2;
void func_800244BC(void *, struct S_800244BC_2 *, s32);
void func_80024810(void *);
s32 func_80024B20(void *);
extern u8 D_800DEE38[];
extern u32 D_800814A0[];

#define GLOBAL_OBJECT (*(void **)D_800814A8)

extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_80053EF0(s32);
extern u16 func_80066460(s32, s32, s32, s32);
extern u16 func_8006649C(s32, s32);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);

void func_80024020(void *sequence, void *out_position);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */

void (*const dungeon_19c6800_entry)(void *, void *) = func_80024020;

#define SELF ((S_func_819A6800_1 *)sequence)

/* Runs a timed object creation sequence with visual effects and final cleanup. */
void func_80024020(void *sequence, void *out_position)
{
    S_func_819A6800_3 *owner = SELF->unk_00;
    S_func_819A6800_2 *record = ((S_func_819A6800_2 *)((u8 *)owner - 0x20))->unk_0C;
    S_func_819A6800_2 *owner_object = (S_func_819A6800_2 *)((u8 *)owner - 0x20);
    u16 timer;
    s32 state;
    S_func_819A6800_2 *new_object;
    S_func_819A6800_4 *counter_object;
    s16 position_offset[3];
    S_func_819A6800_7 *effect_data;
    S_func_819A6800_8 *sprite;
    u8 *global_slot;
    S_func_819A6800_4 *global_object;
    S_func_819A6800_4 *reloaded_object;

    timer = SELF->unk_50.u - 1;
    state = SELF->unk_0A.s;
    SELF->unk_50.u = timer;
    switch (state) {
    case 0:
        global_slot = (u8 *)&D_800814A0[2];
        global_object = *(void **)global_slot;
        global_object->unk_102 = 1;
        reloaded_object = *(void * *)global_slot;
        reloaded_object->unk_F4 = 0;

        ((S_func_819A6800_5 *)(out_position))->unk_00.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.u;
        ((S_func_819A6800_5 *)(out_position))->unk_04.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.u;
        ((S_func_819A6800_5 *)(out_position))->unk_08.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.u;

        new_object = func_800A05A4(reloaded_object,
                                   D_80082E80.tileX,
                                   D_80082E80.tileY,
                                   reloaded_object->unk_2A,
                                   7);
        owner->unk_60.p = new_object;
        if (new_object == 0) {
            owner->unk_72 = record->unk_24;
            owner->unk_73 = record->unk_25;
        } else {
            sprite = ((S_func_819A6800_2 *)((u8 *)new_object - 0x20))->unk_0C;
            owner->unk_72 = ((S_func_819A6800_2 *)sprite)->unk_24;
            owner->unk_73 = ((S_func_819A6800_2 *)sprite)->unk_25;
        }

        SELF->unk_0A.u++;
    case 1:
        if ((((S_func_819A6800_6 *)(SELF->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }

        counter_object = GLOBAL_OBJECT;
        SELF->unk_50.u = 10;
        counter_object->unk_A6--;
        counter_object->unk_A8 = SELF->unk_08;
        new_object = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
        record = new_object;
        if (record != 0) {
            if (func_8003DE58(((S_func_819A6800_2 *)(owner_object->unk_0C))->unk_08,
                              owner_object->unk_0C, position_offset, 0) == 0) {
                position_offset[2] = 0;
                position_offset[1] = 0;
                position_offset[0] = 0;
            }
            record->unk_10 = func_800244BC;
            func_8004491C(record, func_80045340);
            sprite = record->unk_0C;

            ((S_func_819A6800_5 *)(record->unk_08))->unk_00.s =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.s + ((s32)position_offset[0] << 16);
            ((S_func_819A6800_5 *)(record->unk_08))->unk_04.s =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.s + ((s32)position_offset[1] << 16);
            ((S_func_819A6800_5 *)(record->unk_08))->unk_08.s =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.s + ((s32)position_offset[2] << 16);

            effect_data = (S_func_819A6800_7 *)((u8 *)record + 0x20);
            effect_data->unk_0C = ((S_func_819A6800_5 *)(record->unk_08))->unk_00.h.unk_02;
            effect_data->unk_0E = ((S_func_819A6800_5 *)(record->unk_08))->unk_04.h.unk_06;
            effect_data->unk_10 = ((S_func_819A6800_5 *)(record->unk_08))->unk_08.h.unk_0A;

            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            sprite->unk_10 = 0x20;
            sprite->unk_14 |= 0x0C;
            sprite->unk_00 = D_800DEE38;
            sprite->unk_08 = ((S_func_819A6800_9 *)(D_800DEE38))->unk_04;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->unk_0C = 0x00606060;
            record->unk_20 = SELF;
            effect_data->unk_4C = 0;
        }
        SELF->unk_0A.u++;
        return;

    case 2:
        if ((s16)SELF->unk_50.u > 0) {
            return;
        }
        {
            s32 mode = func_80053EF0(4);
            if (mode != 2) {
                mode = 0x300;
            } else {
                mode = 0x4300;
            }
            func_800A56E0(mode);
        }
        {
            u16 next_state = SELF->unk_0A.u;
            u16 timer;
            timer = 10;
            SELF->unk_50.u = timer;
            SELF->unk_0A.u = next_state + 1;
        }
        return;

    case 3:
    {
        s16 timer_left = SELF->unk_50.s;
        if (timer_left == 7) {
            if (owner->unk_60.p != 0) {
                record = func_8003FD64(0x302, ((u8 *)(&D_80083498)));
                if (record != 0) {
                    S_func_819A6800_7 *effect_data = (S_func_819A6800_7 *)((u8 *)record + 0x20);
                    u32 target_object;
                    record->unk_10 = func_80024810;
                    func_8004491C(record, func_80024B20);
                    target_object = owner->unk_60.u;
                    effect_data->unk_3C = 0;
                    effect_data->unk_3E = 0;
                    effect_data->unk_32 = 0x1F;
                    effect_data->unk_30 = 0x1F;
                    effect_data->unk_34 = target_object;
                    effect_data->unk_40 = func_80066460(0, 1, 0x2C0, 0x100);
                    effect_data->unk_42 = func_8006649C(0x60, 0x1F8);
                    effect_data->unk_38 = 0x00404040;
                    record->unk_20 = SELF;
                }
            }
        }
    }
        if (SELF->unk_50.s == 4) {
            func_8009CE1C(owner->unk_60.p,
                          10,
                          SELF->unk_09,
                          12,
                          ((S_func_819A6800_4 *)(GLOBAL_OBJECT))->unk_2A,
                          owner,
                          2);
        }
        if ((D_80082E80.unk_014 & 0x8000) == 0 &&
            SELF->unk_50.s >= 0) {
            return;
        }
        {
            u16 next_state5 = SELF->unk_0A.u;
            u16 cleanup_delay;
            cleanup_delay = 20;
            SELF->unk_50.u = cleanup_delay;
            SELF->unk_0A.u = next_state5 + 1;
        }
        return;

    case 4:
        if ((s16)SELF->unk_50.u > 0) {
            return;
        }
        SELF->unk_0A.u++;
        return;

    case 5:
    {
        s16 signed_flags = SELF->unk_52.s;
        u16 flags = SELF->unk_52.u;
        if ((signed_flags & 0x8000) != 0) {
            SELF->unk_52.u = flags & 0x7FFF;
            return;
        }
    }
        {
            dungeonStatus.unk_0C = 0;
            dungeonStatus.unk_0A--;
        }
        ((S_func_819A6800_6 *)((u8 *)SELF - 2))->unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;

        return;
    }
}

