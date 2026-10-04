#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


typedef s32 M2C_UNK;

typedef struct S_81988800_0 {
    void * unk_00;
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 u; s16 s; } unk_50;   /* accessed as both */
    union { s16 s; u16 u; } unk_52;   /* accessed as both */
} S_81988800_0;   /* state in func_8002401C */


typedef struct S_81988800_2 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81988800_2;   /* out in func_8002401C */

typedef struct S_81988800_3 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    union { void * p32; u16 u16; } unk_08;   /* accessed as both */
    void * unk_0C;
    struct {
        s16 unk_00;
        s16 unk_02;
        s16 unk_04;
    } entries[8];
    s16 unk_40;
} S_81988800_3;   /* work in func_8002401C */

typedef struct S_81988800_4 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_81988800_4;   /* global in func_8002401C */

typedef struct S_81988800_5 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
    void * unk_20;
} S_81988800_5;   /* object in func_8002401C */

typedef struct S_81988800_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} S_81988800_6;   /* spawn_fields in func_8002401C */

typedef struct S_81988800_8 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_81988800_8;   /* base in func_8002401C */

typedef struct S_81988800_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_81988800_9;   /* tail in func_8002401C */

typedef struct S_81988800_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81988800_10;   /* ((S_81988800_3 *)work)->unk_08.p32 in func_8002401C */

typedef struct S_81988800_11 {
    u16 unk_00;
} S_81988800_11;   /* ((S_81988800_0 *)state)->unk_04 in func_8002401C */

typedef struct S_81988800_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81988800_12;   /* ((S_81988800_3 *)work)->unk_0C in func_8002401C */


extern M2C_UNK D_8002441C;
extern M2C_UNK D_80024648;
extern M2C_UNK D_80024B20;
extern M2C_UNK D_80024D58;

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_80053EF0();
extern void func_8009CE1C();
extern void *func_800A3F28();
extern void func_800A56E0();

void func_8002401C(void *state_data, void *position_data);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The phase table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const module_entry)(void *, void *) __asm__("func_80024000") = func_8002401C;

/* Advance a timed effect sequence, spawning objects and applying the effect to targets. */
void func_8002401C(void *state_data, void *position_data)
{
    s16 offset[3];
    void *object;
    u8 *work;
    void *source;
    void *list_head;
    void *actor;
    u8 *unused_fields;
    s32 timer;

    timer = ((S_81988800_0 *)state_data)->unk_50.u;
    source = ((S_81988800_0 *)state_data)->unk_00;
    timer--;
    ((S_81988800_0 *)state_data)->unk_50.u = timer;
    work = (u8 *)source - 0x20;

    switch (((S_81988800_0 *)state_data)->unk_0A.s) {
    case 0:
        D_800814A8->unk_102 = 1;
        D_800814A8->unk_F4 = 0;
        ((S_81988800_2 *)position_data)->unk_00 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00;
        ((S_81988800_2 *)position_data)->unk_04 = ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04;
        ((S_81988800_2 *)position_data)->unk_08.at00.v =
            ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08;
        ((S_81988800_0 *)state_data)->unk_0A.u++;
    case 1:
    {
        u8 *spawn_data;
        if (((S_81988800_11 *)(((S_81988800_0 *)state_data)->unk_04))->unk_00 & 0x80) {
            actor = D_800814A8;
            ((S_81988800_0 *)state_data)->unk_50.u = 10;
            ((S_81988800_4 *)actor)->unk_A6--;
            ((S_81988800_4 *)actor)->unk_A8 = ((S_81988800_0 *)state_data)->unk_08;

            object = func_8003FD64(0x302, ((u8 *)(&D_80083498)));
            if (object != 0) {
                if (func_8003DE58(((S_81988800_12 *)(((S_81988800_3 *)work)->unk_0C))->unk_08,
                                  ((S_81988800_3 *)work)->unk_0C, offset, 0) == 0) {
                    offset[2] = 0;
                    offset[1] = 0;
                    offset[0] = 0;
                }
                ((S_81988800_5 *)object)->unk_10 = &D_80024648;
                func_8004491C(object, &D_8002441C);
                ((S_81988800_5 *)object)->unk_20 = state_data;
                spawn_data = (u8 *)object + 0x20;

                ((S_81988800_2 *)position_data)->unk_00 =
                    ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_00 +
                                      ((s32)offset[0] << 16);
                ((S_81988800_6 *)spawn_data)->unk_1C = ((S_81988800_2 *)position_data)->unk_00;
                ((S_81988800_2 *)position_data)->unk_04 =
                    ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_04 +
                                      ((s32)offset[1] << 16);
                ((S_81988800_6 *)spawn_data)->unk_20 = ((S_81988800_2 *)position_data)->unk_04;
                ((S_81988800_2 *)position_data)->unk_08.at00.v =
                    ((S_81988800_10 *)(((S_81988800_3 *)work)->unk_08.p32))->unk_08 +
                                      ((s32)offset[2] << 16);
                ((S_81988800_6 *)spawn_data)->unk_24 = ((S_81988800_2 *)position_data)->unk_08.at00.v;
            }
            ((S_81988800_0 *)state_data)->unk_0A.u++;
        }
        break;
    }

    case 2:
    {
        s32 effect_id;
        s32 variant;
        if (((S_81988800_0 *)state_data)->unk_50.s <= 0) {
            variant = func_80053EF0(4);
            effect_id = 0x4300;
            if (variant != 2) {
                effect_id = 0x300;
            }
            func_800A56E0(effect_id);
            ((S_81988800_0 *)state_data)->unk_50.u = 13;
            ((S_81988800_0 *)state_data)->unk_0A.u++;
        }
        break;
    }

    case 3:
    {
        s32 entry_index;
        if (((S_81988800_0 *)state_data)->unk_50.s <= 0) {
            object = func_8003FD64(0x302, ((u8 *)(&D_80083498)));
            if (object != 0) {
                ((S_81988800_5 *)object)->unk_10 = &D_80024B20;
                func_8004491C(object, &D_80024D58);
                actor = (void *)((u8 *)(&D_80082E80));
                offset[0] = (((u16)D_800814A8->facing) >> 9) & 7;
                work = (u8 *)object + 0x20;
                ((S_81988800_3 *)work)->unk_04 = (((u8 *)actor)[0x24] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_06 = (((u8 *)actor)[0x25] << 6) + 0x20;
                ((S_81988800_3 *)work)->unk_08.u16 = ((S_81988800_2 *)position_data)->unk_08.at02.v;
                for (entry_index = 7; entry_index >= 0; entry_index--) {
                    ((S_81988800_3 *)work)->entries[entry_index].unk_02 = 0;
                    ((S_81988800_3 *)work)->entries[entry_index].unk_00 = 0;
                }
                ((S_81988800_3 *)work)->unk_00 = state_data;
                ((S_81988800_3 *)work)->unk_40 = 0;
            }
            ((S_81988800_0 *)state_data)->unk_50.u = 0x3D;
            ((S_81988800_0 *)state_data)->unk_0A.u++;
        }
        break;
    }

    case 4:
    {
        if (((S_81988800_0 *)state_data)->unk_50.s == 8) {
            object = D_800814A8;
            if (object != 0) {

                list_head = object;
                work = (u8 *)((u8 *)(&D_80082E80));
loop:
                object = func_800A3F28(work[0x24], work[0x25], list_head, object);
                if (object != 0) {
                    if (!(((S_81988800_5 *)object)->unk_1C & 0x2000)) {
                        func_8009CE1C(object, 0x10, ((S_81988800_0 *)state_data)->unk_09, 10,
                                      ((S_81988800_8 *)source)->unk_2A, source, 2);
                    }
                    goto loop;
                }
            }
        }

        if ((D_80082E80.unk_014 & 0x8000) || ((S_81988800_0 *)state_data)->unk_50.s < 0) {
            if (((S_81988800_0 *)state_data)->unk_52.s & 0x8000) {
                ((S_81988800_0 *)state_data)->unk_52.u &= 0x7FFF;
            } else {
                dungeonStatus.unk_0C = 0;
                dungeonStatus.unk_0A--;
                (*(u16 *)((u8 *)state_data + -2)) |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
            }
        }
        break;
    }
    }
}
