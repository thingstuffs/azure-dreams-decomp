#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x38];
    s32 field_38;
    u8 pad_3C[0xC];
    s32 entries[15];
} State80082A38;

extern State80082A38 D_80082A38;
extern void *D_80082A70[];
extern u8 D_8006B230[];

extern s32 func_800352FC(void);
extern void func_80035378(void *arg0);
extern void func_80035208(void *arg0);

/* Processes input data, clearing the last five entries when D_8006B230 needs initialization. */
s32 func_800353F4(void *input_data) {
    s32 entry_index;

    if (func_800352FC() == 0 || D_80082A70[0] != D_8006B230) {
        for (entry_index = 10; entry_index < 15; entry_index++) {
            D_80082A38.entries[entry_index] = 0;
        }
        func_80035378(input_data);
        func_80035208(D_8006B230);
    } else {
        func_80035378(input_data);
    }
    return 1;
}
