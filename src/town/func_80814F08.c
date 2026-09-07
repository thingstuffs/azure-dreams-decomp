#include "common.h"


typedef void (*Callback)(void);

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern s32 func_80071494(void);
extern void func_8028E170(void);
extern void func_8052FC8C(void);
extern u8 D_8003C558[];


typedef struct S_80814F08_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80814F08_0;   /* temp_s2 in func_80814F08 */

typedef struct S_80814F08_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
} S_80814F08_1;   /* arg0 in func_80814F08 */

void func_80814F08(S_80814F08_1 *arg0) {
    void *temp_s0;
    S_80814F08_0 *temp_s2;
    void *temp_v0;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != 0) {
        (*(Callback *)((u8 *)temp_v0 + 0x10)) = func_8052FC8C;
        func_8003BC18(temp_v0, D_8003C558);
        temp_s2 = (*(void * *)((u8 *)temp_v0 + 8));
        temp_s0 = (*(void * *)((u8 *)temp_v0 + 0xC));
        temp_s2->unk_02 =
            (arg0->unk_02 + (func_80071494() % 40)) - 0x14;
        temp_s2->unk_06 =
            (arg0->unk_06 + (func_80071494() % 40)) - 0x14;
        temp_s2->unk_0A =
            (arg0->unk_0A + (func_80071494() % 40)) - 0x14;
        temp_s2->unk_0C = arg0->unk_0C;
        temp_s2->unk_14 =
            ((func_80071494() & 0x1FF) - 0x100) * 0x400;
        (*(s16 *)((u8 *)temp_v0 + 0x2E)) = 3;
        (*(s16 *)((u8 *)temp_s0 + 0x1E)) = 0x1000;
        (*(s16 *)((u8 *)temp_s0 + 0x1C)) = 0x1000;
        (*(Callback *)((u8 *)temp_s0 + 8)) = func_8028E170;
        (*(s8 *)((u8 *)temp_s0 + 4)) = 0;
        (*(s8 *)((u8 *)temp_s0 + 5)) = 0;
        (*(s32 *)((u8 *)temp_s0 + 0xC)) = 0x808080;
        (*(u16 *)((u8 *)temp_s0 + 0x14)) |= 0xC;
    }
}
