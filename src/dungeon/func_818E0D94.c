#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818E0D94_0_pre {
    u16 unk_00;
} S_818E0D94_0_pre;   /* the 0x2 bytes before arg0 in func_818E0D94, addressed as arg0[-1] */

typedef struct S_818E0D94_0 {
    void * unk_00;
    u8 pad_04[0x14];
    u16 unk_18;
    u8 pad_1A[0x2E];
    union { u16 u16; s16 s16; u8 u8; } unk_48;   /* accessed as both */
} S_818E0D94_0;   /* arg0 in func_818E0D94 */

typedef struct S_818E0D94_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_818E0D94_1;   /* inner in func_818E0D94 */


typedef struct S_818E0D94_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818E0D94_3;   /* arg1 in func_818E0D94 */



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
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern void func_800DBA90(void *);
extern u32 D_800814A0;

void func_818E0D94(void *arg0, S_818E0D94_3 *arg1, Rec_D_80082E80 *arg2)
{
    CallRecord record;
    OutputVector output;
    S_818E0D94_1 *inner;
    u16 temp;
    s8 value;

    inner = ((S_818E0D94_0 *)arg0)->unk_00;
    inner->unk_52 |= 0x8000;
    ((S_818E0D94_0 *)arg0)->unk_48.u16++;

    temp = arg2->unk_1C.at02_u16.v - 0x50;
    arg2->unk_1C.at02_u16.v = temp;
    arg2->unk_1C.at00_u16.v = temp;

    {
        register s32 call_arg ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        s32 random;
        s32 height;

        random = rand() & 0x3F;
        call_arg = ((S_818E0D94_0 *)arg0)->unk_48.s16 * 0x32;
        ASM_KEEP(call_arg);   /* MATCH pin: keeps a statement from moving across a call/branch */
        height = ((S_818E0D94_0 *)arg0)->unk_18;
        call_arg += 0xC8;
        height += 0x200;
        height += random;
        ((S_818E0D94_0 *)arg0)->unk_18 = height;
        output.x = func_800644B8(call_arg) / 80;
    }
    output.y = 0;
    {
        s32 random;
        s32 negative;

        random = rand() & 3;
        negative = 0 - ((S_818E0D94_0 *)arg0)->unk_48.s16;
        output.z = (negative * 4) + random - 1;
    }

    value = ((u8)output.x + 0x28) - ((S_818E0D94_0 *)arg0)->unk_48.u8;
    arg2->unk_0C.at01_s8.v = value;
    arg2->unk_0C.at00_s8.v = value;
    arg2->unk_0C.at02_s8.v = ((u8)output.x + 0x60) - ((S_818E0D94_0 *)arg0)->unk_48.u8;

    record.field0 = &output;
    record.field4 = &output;
    record.field8 = *(Unaligned8 *)((u8 *)arg0 + 0x14);
    record.field10 = *(Unaligned8 *)((u8 *)arg0 + 0x0C);
    record.field18 = 1;
    record.field1A = 0;
    func_800DBA90(&record);

    arg1->unk_02 = output.x;
    arg1->unk_06 = output.y;
    arg1->unk_0A = output.z;
    func_800478B8(arg2);

    if (arg2->unk_14.at00_u16.v & 0x6000) {
        arg2->unk_04.as_s8 = 0;
        arg2->unk_05.as_s8 = 0;
    }

    if (((S_818E0D94_0 *)arg0)->unk_48.s16 >= 0x20) {
        u32 *page;

        ((S_818E0D94_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        page = (u32 *)0x80080000;
        ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        page[0x528] |= 0x8000;
    }
}
