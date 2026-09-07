#include "common.h"

extern void func_800A4C10(void);
extern void func_800A4C00(void);

typedef struct {
    s32 *unk00;
    s32 *unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    void (*unk28)(void);
} UnkStruct_800A7434;

void func_800A4B94(UnkStruct_800A7434 *arg0) {
    s32 *v1;
    s32 *v1_2;
    s32 v0;

    v1 = arg0->unk00;
    if (v1 != arg0->unk04) {
        arg0->unk20 = 9;
        arg0->unk28 = func_800A4C10;
        arg0->unk14 = 0;
        arg0->unk18 = 0;
        arg0->unk1C = 0;
        arg0->unk04 = v1;
        func_800A4C10();
        return;
    }
    __asm__ __volatile__("" ::: "memory");
    v1_2 = arg0->unk00;
    arg0->unk08 = v1[0];
    v0 = v1_2[1];
    arg0->unk0C = v0;
    v0 = v1_2[2];
    arg0->unk10 = v0;
}
