#include "common.h"

typedef struct S_80016B0C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    u8 * unk_40;
} S_80016B0C_0;   /* state in func_80016B0C */

typedef struct S_80016B0C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    u8 * unk_40;
} S_80016B0C_1;   /* *(void **)D_80016000 in func_80016B0C */

typedef struct S_80016B0C_2 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016B0C_2;   /* (u8 *)((S_80016B0C_1 *)(*(void **)D_80016000))->unk_40
                + ((S_80016B0C_1 *)(*(void **)D_80016000))->unk_08 * 8 in func_80016B0C */



extern s8 D_80016000[];
extern s32 D_80019AFC;
extern void *D_80019B90;

extern s32 func_80018504(void);
extern void func_80018934(void);
extern void func_80018D54(void *, u8 *);
extern void func_80019458(s32);
extern s32 func_800194D8(s32);
extern void func_80019638(void);

/* Process the current cell value and clear it when the handler returns nonzero. */
s32 func_80016B0C(void) {
    u8 fallback_args[2];
    S_80016B0C_0 *state;
    s32 result;
    s32 cell_index;
    u8 *cells;

    do {
    } while (0);
    state = *(void **)D_80016000;
    do {
        fallback_args[0] = 2;
    } while (0);
    fallback_args[1] = 0xFF;
    cell_index = state->unk_08;
    cells = state->unk_40;
    D_80019AFC = cells[cell_index * 8 + 4];
    result = func_80018504();

    if (result != 0) {
        if (func_800194D8(0x632) == 0) {
            func_80019458(0x62C);
            func_80019458(0x62D);
        }

        ((S_80016B0C_2 *)((u8 *)((S_80016B0C_1 *)(*(void **)D_80016000))->unk_40
                + ((S_80016B0C_1 *)(*(void **)D_80016000))->unk_08 * 8))->unk_04 = 0;
        D_80019AFC = 0;
        func_80018934();
    } else {
        func_80018D54(D_80019B90, fallback_args);
        func_80019638();
    }

    return result;
}
