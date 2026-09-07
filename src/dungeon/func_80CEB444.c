#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80174C44_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174C44_0;   /* arg0 in func_80174C44 */




typedef struct S_80174C44_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80174C44_4;   /* global in func_80174C44 */



extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801724BC[];
extern u8 D_80175E3C[];
extern u8 D_80175E44[];
extern u8 D_80175E4C[];

extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

void func_80174C44(S_80174C44_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s32 initial_state;
    s32 kind;
    s16 timer;
    u16 count;
    s32 origin;
    s32 value;
    S_80174C44_4 *global;

    initial_state = arg0->unk_9B;
    if (initial_state == 1) {
        goto state_1;
    }
    if (initial_state < 2) {
        if (initial_state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (initial_state == 2) {
        goto state_2;
    }
    if (initial_state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(arg3);
    arg0->unk_96.s = 6;
    arg0->unk_9B = arg0->unk_9B + 1;
    if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
        goto state_0_active;
    }

    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    kind = ((Rec_D_800E3D7C *)arg3)->unk_48.at00_u8.v;
    if (kind == 14) {
        goto kind_14;
    }
    if (kind < 15) {
        goto kind_less_15;
    }
    if (kind != 15) {
        goto done;
    }
    goto kind_15_from_state_0;

state_0_active:
    if ((arg2->unk_14.at00_u16.v & 0x8000) == 0) {
        goto done;
    }
    arg0->unk_96.s = 0;
    arg0->unk_9B = 3;
    goto done;

state_1:
    timer = (u16)arg0->unk_96.u - 1;
    arg0->unk_96.s = timer;
    if (timer <= 0) {
        goto state_1_nonpositive;
    }

    arg1->unk_0C.as_s32 =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    arg1->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    goto done;

state_1_nonpositive:
    if (timer != 0) {
        goto done;
    }
    arg1->unk_0C.as_s32 =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    arg1->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
    arg0->unk_96.s = 12;
    arg0->unk_9B = arg0->unk_9B + 1;
    goto done;

state_2:
    if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
        goto state_2_active;
    }

    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    kind = ((Rec_D_800E3D7C *)arg3)->unk_48.at00_u8.v;
    if (kind == 14) {
        goto kind_14;
    }
    if (kind >= 15) {
        goto kind_at_least_15;
    }

kind_less_15:
    if (kind == 13) {
        goto kind_13;
    }
    goto done;

kind_at_least_15:
    if (kind == 15) {
        goto kind_15;
    }
    goto done;

kind_13:
    func_800AAA54(arg0, arg1, arg2, D_80175E3C);
    goto done;

kind_14:
    func_800AAA54(arg0, arg1, arg2, D_80175E44);
    goto done;

kind_15:
    func_800AAA54(arg0, arg1, arg2, D_80175E4C);
    goto done;

kind_15_from_state_0:
    func_800AAA54(arg0, arg1, arg2, D_80175E4C);
    goto done;

state_2_active:
    timer = arg0->unk_96.s;
    if (timer != 0) {
        value = arg2->unk_24;
        origin = arg1->unk_00.at02_s16.v;
        value <<= 6;
        origin -= 0x20;
        value -= origin;
        value = (value << 16) / timer;
        origin = arg1->unk_04.at02_s16.v;
        arg1->unk_0C.as_s32 = value;
        origin -= 0x20;
        value = (arg2->unk_25 << 6) - origin;
        value = (value << 16) / arg0->unk_96.s;
        arg1->unk_10.at00_s32.v = value;
    }

    count = arg0->unk_96.u;
    arg0->unk_96.s = count - 1;
    if ((s32)(count << 16) > 0) {
        goto done;
    }
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    arg0->unk_9B = arg0->unk_9B + 1;
    goto done;

state_3:
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    global = &D_80083460;
    if (global->unk_10 == (s32)arg3 - 0x20) {
        global->unk_10 &= 0x7FFFFFFF;
    }
    arg0->unk_8C = D_801724BC;

done:
    return;
}
