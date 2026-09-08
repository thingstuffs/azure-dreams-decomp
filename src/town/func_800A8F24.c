#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 padC;
    s32 pad10;
} StackRecord;

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern void func_8003DB94(void *, void *, s8);
extern void func_800478B8(void *);
extern s32 func_80096FF4(void *);
extern void func_800970AC(s32, void *);
extern void func_800A6758(void);
extern void func_800A6888(void);
extern void func_800A6A94(StackRecord *);
extern void func_800A6B70(StackRecord *);
extern s32 func_800C2E1C(s16, s16);
extern s32 func_800C2F14(s16, s16);


typedef struct S_800A6684_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_800A6684_0;   /* arg2 in func_800A6684 */


void func_800A6684(void *arg0, Rec_D_800E3D7C *arg1, S_800A6684_0 *arg2)
{
    StackRecord rec;
    s32 index;
    s32 above;
    s32 value;
    void *call_a0;
    u32 tail_value;

    (*(EntityCallback *)((u8 *)arg0 + 0x50))(arg0, arg0, arg1, arg2);
    if (!((*(u16 *)((u8 *)arg0 + -2)) & 0x8000)) {
        func_800970AC(func_80096FF4(arg1), arg0);

        index = func_800C2E1C((*(s16 *)((u8 *)arg0 + 0x72)), (*(s16 *)((u8 *)arg0 + 0x64)));
        if ((*(s16 *)((u8 *)arg0 + 0x74)) != index) {
            func_8003DB94(arg2, (*(void ** *)((u8 *)arg0 + 0x78))[index], arg2->unk_04);
            (*(s16 *)((u8 *)arg0 + 0x74)) = index;
        }

        if ((func_800C2F14((*(s16 *)((u8 *)arg0 + 0x72)), (*(s16 *)((u8 *)arg0 + 0x64))) << 0x10) != 0) {
            tail_value = arg2->unk_14 | 1;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_800A6758();
            return;
        }

        arg2->unk_14 &= 0xFFFE;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        call_a0 = arg2;
        func_800478B8(call_a0);

        above = arg1->unk_04.at00_s32.v > 0x06500000;
        if (!above && (*(s32 *)((u8 *)arg0 + 0xA0)) > 0x06500000) {
            arg2->unk_0C = arg2->unk_0D = arg2->unk_0E = 0xFF;
            rec.unk0 = arg1->unk_00.at00_s32.v;
            rec.unk4 = 0x06400000;
            rec.unk8 = arg1->unk_08.at00_s32.v - 0x00280000;
            func_800A6A94(&rec);
            func_800A6888();
            return;
        }

        if (above && (*(s32 *)((u8 *)arg0 + 0xA0)) <= 0x06500000 &&
            (*(s32 *)((u8 *)arg0 + 0xA4)) <= 0x06500000) {
            arg2->unk_0C = arg2->unk_0D = arg2->unk_0E = 0xFF;
            rec.unk0 = arg1->unk_00.at00_s32.v;
            rec.unk4 = 0x06600000;
            rec.unk8 = arg1->unk_08.at00_s32.v - 0x00280000;
            func_800A6B70(&rec);
            func_800A6888();
            return;
        }

        value = arg2->unk_0C - 8;
        arg2->unk_0C = value;
        if ((u32)(value & 0xFF) < 0x80U) {
            arg2->unk_0C = 0x80;
        }
        value = arg2->unk_0D - 0x10;
        arg2->unk_0D = value;
        if ((u32)(value & 0xFF) < 0x80U) {
            arg2->unk_0D = 0x80;
        }
        arg2->unk_0E = arg2->unk_0D;
        (*(s32 *)((u8 *)arg0 + 0xA4)) = (*(s32 *)((u8 *)arg0 + 0xA0));
        (*(s32 *)((u8 *)arg0 + 0xA0)) = arg1->unk_04.at00_s32.v;
    }
}
