#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801743EC_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 pad_0A[0x42];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_801743EC_0;   /* arg0 in func_801743EC */


typedef struct S_801743EC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801743EC_2;   /* arg1 in func_801743EC */



typedef struct {
    u8 bytes[8];
} Unaligned8;

typedef struct {
    void *field0;
    void *field4;
    Unaligned8 field8;
    Unaligned8 field10;
    s16 field18;
    s16 field1A;
    u32 unused1C;
} CallRecord;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} OutputVector;

extern void func_800478B8(void *);
extern void func_800DBA90(void *);
extern u32 D_800814A0;

/* Update the effect trajectory and sprite, then flag completion when its animation ends. */
void func_801743EC(void *effect, void *position, void *sprite)
{
    CallRecord transform;
    OutputVector transformed_position;
    s16 state;
    s32 quarter_angle;
    u16 angle;

    state = ((S_801743EC_0 *)effect)->unk_4C.s;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_800478B8(sprite);
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        ((Rec_D_80082E80 *)sprite)->unk_04.as_s8 = 0;
        ((Rec_D_80082E80 *)sprite)->unk_05.as_s8 = 0;
    }
    ((Rec_D_80082E80 *)sprite)->unk_0C.at00_s32.v += 0xFFE7E7E8;
    if ((u8)((Rec_D_80082E80 *)sprite)->unk_0C.at00_s32.v < 0x30U) {
        ((S_801743EC_0 *)effect)->unk_4C.u++;
    }

    angle = ((S_801743EC_0 *)effect)->unk_08 + 10;
    quarter_angle = (s32)(angle << 16) >> 18;
    ((S_801743EC_0 *)effect)->unk_08 = angle;
    ((S_801743EC_0 *)effect)->unk_04 = (u16)(-(quarter_angle * quarter_angle) >> 4);

    transform.field0 = (u8 *)effect + 4;
    transform.field4 = &transformed_position;
    transform.field8 = *(Unaligned8 *)((u8 *)effect + 0x14);
    transform.field10 = *(Unaligned8 *)((u8 *)effect + 0xC);
    transform.field18 = 1;
    transform.field1A = 1;
    func_800DBA90(&transform);
    ((S_801743EC_2 *)position)->unk_02 = transformed_position.x;
    ((S_801743EC_2 *)position)->unk_06 = transformed_position.y;
    ((S_801743EC_2 *)position)->unk_0A = transformed_position.z;
    goto done;

state_one:
    (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
