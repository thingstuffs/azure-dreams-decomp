#include "common.h"

typedef struct S_800254C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800254C4_0;   /* node in func_800254C4 */

typedef struct S_800254C4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800254C4_1;   /* payload in func_800254C4 */

typedef struct S_800254C4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800254C4_2;   /* source in func_800254C4 */

typedef struct S_800254C4_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x8];
    s16 unk_26;
} S_800254C4_3;   /* fields in func_800254C4 */

typedef struct S_800254C4_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
} S_800254C4_4;   /* ((S_800254C4_0 *)node)->unk_0C in func_800254C4 */

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_800250E8[3];
extern s32 D_800252E0[3];

/* Allocates a node, copies or jitters its source values, and initializes its fields. */
s32 func_800254C4(void *source_data, s16 initial_1a, s16 initial_1c, s16 spawn_mode) {
    register void *source = source_data;
    register s16 field_1a = initial_1a;
    register s16 field_1c = initial_1c;
    register s16 mode = spawn_mode;
    register void *node;

    node = func_8003FC64(0x202);
    if (node != 0) {
        s32 mode_test;

        ((S_800254C4_0 *)node)->unk_10 = D_800250E8;
        func_8004491C(node, D_800252E0);
        mode_test = mode << 0x10;
        {
            S_800254C4_1 *payload = ((S_800254C4_0 *)node)->unk_08;

            s32 value_0a;

            if (mode_test == 0) {
                payload->unk_02 =
                    (u16)((((S_800254C4_2 *)source)->unk_02 + (rand() & 0x1F)) - 0x10);
                payload->unk_06 =
                    (u16)((((S_800254C4_2 *)source)->unk_06 + (rand() & 0x1F)) - 0x10);
                value_0a = ((S_800254C4_2 *)source)->unk_0A - 0x50;
            } else {
                payload->unk_02 = ((S_800254C4_2 *)source)->unk_02;
                payload->unk_06 = ((S_800254C4_2 *)source)->unk_06;
                value_0a = ((S_800254C4_2 *)source)->unk_0A;
            }
            payload->unk_0A = value_0a;
        }
        ((S_800254C4_4 *)(((S_800254C4_0 *)node)->unk_0C))->unk_0C = 0xF0;
        {
            S_800254C4_3 *fields = node + 0x20;

            fields->unk_1A = field_1a;
            fields->unk_1C = field_1c;
            fields->unk_26 = mode;
        }
    }
}

