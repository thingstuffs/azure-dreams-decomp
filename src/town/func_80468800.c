#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct S_func_80019800_0 {
    u8 pad_00[1];
    u8 unk_01;
    u8 pad_02[3];
    u8 unk_05;
} S_func_80019800_0;

typedef struct S_func_80019800_1 {
    s16 unk_00;
    s16 unk_02;
} S_func_80019800_1;

typedef struct S_func_80019800_2 {
    u8 pad_00[0x20];
    void *unk_20;
} S_func_80019800_2;

typedef struct S_func_80019800_3 {
    u8 pad_00[0x2F8];
    M2C_UNK (*unk_2F8)(M2C_UNK, M2C_UNK);
} S_func_80019800_3;

extern void *func_80019AFC();
extern void *D_80016000[];
extern void *D_8001E950[];

/* Checks the active event and dispatches the 0x27/0x200 handler when matched. */
s32 func_80019800(void) {
    S_func_80019800_1 *event;

    if ((u8) ((S_func_80019800_0 *)D_8001E950[0])->unk_01 < 2U) {
        event = func_80019AFC(((S_func_80019800_0 *)D_8001E950[0])->unk_01,
                              ((S_func_80019800_0 *)D_8001E950[0])->unk_05);
        if (event->unk_00 == 0x27) {
            if (event->unk_02 == 0x200) {
                ((S_func_80019800_3 *)((S_func_80019800_2 *)D_80016000[0])->unk_20)->unk_2F8(0x27, 0x200);
            }
        }
        return 1;
    }
    return 0;
}
