#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;


extern void *func_7003CF18();
extern void func_7010D230();
extern s32 D_80086AD8;
extern u16 D_80094422;
extern u8 D_800E0F20[16];
extern M2C_UNK D_8010CEE0;
extern Packed12 D_8010D40C;


typedef struct S_7FFEB1CC_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
} S_7FFEB1CC_0;   /* arg0 in func_7FFEB1CC */

typedef struct S_7FFEB1CC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_7FFEB1CC_1;   /* primitive in func_7FFEB1CC */

typedef struct S_7FFEB1CC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFEB1CC_2;   /* part in func_7FFEB1CC */

typedef struct S_7FFEB1CC_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFEB1CC_3;   /* ((S_7FFEB1CC_0 *)arg0)->unk_00 in func_7FFEB1CC */

void func_7FFEB1CC(void *arg0, s32 arg1, s32 arg2) {
    s16 timer;
    u16 life;
    void *obj;
    void *part;
    void *primitive;

    timer = ((S_7FFEB1CC_0 *)arg0)->unk_16 + 1;
    ((S_7FFEB1CC_0 *)arg0)->unk_16 = timer;
    if ((timer < 0x17) && (timer & 1)) {
        obj = func_7003CF18(0x212);
        if (obj != NULL) {
            func_7010D230(obj, arg0, arg1, arg2);
            (*(s16 *)((u8 *)obj + 0x3E)) = 0x1E;
            (*(s16 *)((u8 *)obj + 0x40)) = 0x1E;
            (*(M2C_UNK * *)((u8 *)obj + 0x10)) = &D_8010CEE0;

            primitive = (*(void * *)((u8 *)obj + 8));
            ((S_7FFEB1CC_1 *)primitive)->unk_0A =
                ((S_7FFEB1CC_1 *)primitive)->unk_0A -
                (D_800E0F20[(u8)((S_7FFEB1CC_3 *)(((S_7FFEB1CC_0 *)arg0)->unk_00))->unk_13] >> 1);

            part = (*(void * *)((u8 *)obj + 0xC));
            (*(Packed12 *)((u8 *)obj + 0x62)) = D_8010D40C;
            ((S_7FFEB1CC_2 *)part)->unk_08 = (u8 *)obj + 0x62;
            ((S_7FFEB1CC_2 *)part)->unk_10 = 0x40;
            ((S_7FFEB1CC_2 *)part)->unk_1E = 0x32C8;
            ((S_7FFEB1CC_2 *)part)->unk_1C = 0x32C8;
            ((S_7FFEB1CC_2 *)part)->unk_06 = 0x64;
            ((S_7FFEB1CC_2 *)part)->unk_0C = 0;
        }
    }

    life = ((S_7FFEB1CC_0 *)arg0)->unk_1E - 1;
    ((S_7FFEB1CC_0 *)arg0)->unk_1E = life;
    if ((life << 0x10) <= 0) {
        u16 *counter = &D_80094422;
        u16 next_counter;

        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        next_counter = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = next_counter;
    }
}
