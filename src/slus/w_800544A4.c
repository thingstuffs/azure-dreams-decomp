#include "common.h"

#include "common.h"

typedef struct S_800847D0 {
    /* 0x00 */ u32 flags1;
    /* 0x04 */ u32 flags2;
    /* 0x08 */ u32 field8;
    /* 0x0C */ u32 fieldC;
    /* 0x10 */ u32 field10;
    /* 0x14 */ u32 field14;
    /* 0x18 */ u32 field18;
    /* 0x1C */ s16 field1C;
    /* 0x1E */ s16 field1E;
    /* 0x20 */ s16 field20;
    /* 0x22 */ s16 field22;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 field26;
    /* 0x28 */ u8 field28;
    /* 0x29 */ u8 pad29[7];
    /* 0x30 */ s8 field30;
    /* 0x31 */ s8 field31;
    /* 0x32 */ s8 field32;
    /* 0x33 */ s8 field33;
} S_800847D0;

typedef struct S_80084858 {
    /* 0x00 */ void (*field0)(void);
    /* 0x04 */ s32 field4;
    /* 0x08 */ s16 field8;
    /* 0x0A */ s16 fieldA;
    /* 0x0C */ s32 fieldC;
    /* 0x10 */ s16 field10;
    /* 0x12 */ s16 field12;
    /* 0x14 */ s16 field14;
    /* 0x16 */ s16 field16;
    /* 0x18 */ s16 field18;
} S_80084858;

extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;

extern void func_80054538(S_80084858 *arg0);
extern void func_800546B0(void);
extern void func_80054704(void);
extern void func_80054E00(s32 arg0);

/* Dispatch flag-selected updates and handle task state 3. */
void func_800544A4(void) {
    if (D_800847D0.flags2 & 0x200) {
        func_80054704();
    }

    if (D_800847D0.flags1 & 0x400) {
        if (D_800847D0.flags1 & 0x4000) {
            S_80084858 *task = &D_80084858;

            func_80054538(task);
            if (task->fieldC == 3) {
                func_80054E00(0x74);
            }
        } else {
            func_800546B0();
        }
    }
}
