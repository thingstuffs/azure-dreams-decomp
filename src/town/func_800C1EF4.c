#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BF654_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800BF654_0;   /* obj in func_800BF654 */

typedef struct S_800BF654_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800BF654_1;   /* part in func_800BF654 */

typedef struct S_800BF654_2 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800BF654_2;   /* setup in func_800BF654 */



extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_8008F074(void *arg0, void *arg1, void *arg2);

extern u8 D_80046398[];
extern u8 D_800BF4CC[];
extern u8 D_800D2348[];
extern s32 D_800D2360;
extern s32 D_800814A0;

void func_800BF654(void *arg0)
{
    void *obj;
    void *part;
    void *setup;
    s32 *packet;

    obj = func_8003FC64(0x136);
    if (obj != NULL) {
        func_8004491C(obj, D_80046398);
        ((S_800BF654_0 *)obj)->unk_10 = D_800BF4CC;
        part = ((S_800BF654_0 *)obj)->unk_0C;
        ((S_800BF654_1 *)part)->unk_1C = 0x1000;
        ((S_800BF654_1 *)part)->unk_1E = 0x1000;
        ((S_800BF654_1 *)part)->unk_20 = 0x1000;
        ((S_800BF654_1 *)part)->unk_0C = 0x808080;
        setup = (u8 *)obj + 0x20;
        ((S_800BF654_1 *)part)->unk_1A = 0;
        ((S_800BF654_1 *)part)->unk_08 = 0x60;
        packet = ((S_800BF654_0 *)obj)->unk_08;
        packet[0] = 0x05400000;
        packet[1] = 0x02300000;
        packet[2] = 0;
        ((S_800BF654_2 *)setup)->unk_48 = D_800D2360;
        func_8008F074(setup, packet, D_800D2348);
    }
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}
