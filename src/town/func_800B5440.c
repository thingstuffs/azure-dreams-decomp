#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033D44();                     /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_800A48A4();                     /* extern */
M2C_UNK func_800B2394();             /* extern */
s32 func_800B29D0();                          /* extern */
M2C_UNK func_800B2B60();                      /* extern */
M2C_UNK func_800B2C6C();                      /* extern */
s32 func_800B3924();                          /* extern */
s32 func_800B4588();                          /* extern */
s32 func_800B4F60();                          /* extern */
extern M2C_UNK D_800B260C;


typedef struct S_800B2BA0_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800B2BA0_0_pre;   /* the 0x10 bytes before temp_s0 in func_800B2BA0, addressed as temp_s0[-1] */

typedef struct S_800B2BA0_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x3C];
    s32 unk_48;
} S_800B2BA0_0;   /* temp_s0 in func_800B2BA0 */

typedef struct S_800B2BA0_1 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B2BA0_1;   /* temp_v0 in func_800B2BA0 */

/* Initializes the task and resources for open_twin_souko. */
s32 func_800B2BA0(s32 option) {
    s32 resource_08;
    s32 resource_00;
    s32 resource_04;
    void *state;
    void *task;

    task = func_8003FC64(0);
    state = task + 0x20;
    if (task == NULL) {
        goto tail;
    }
    func_800B2B60(state);
    if (func_800B29D0(state) == 0) {
        goto fail;
    }
    func_800B2394(state, 0);
    resource_08 = func_800B4588(task);
    ((S_800B2BA0_0 *)state)->unk_08 = resource_08;
    if (resource_08 == 0) {
        goto fail;
    }
    resource_00 = func_800B3924(task);
    ((S_800B2BA0_1 *)task)->unk_20 = resource_00;
    if (resource_00 == 0) {
        goto fail;
    }
    resource_04 = func_800B4F60(task);
    ((S_800B2BA0_0 *)state)->unk_04 = resource_04;
    if (resource_04 == 0) {
        goto fail;
    }
    func_800A48A4(5);
    func_80033D44(1);
    ((S_800B2BA0_0 *)state)->unk_48 = option;
    ((S_800B2BA0_0_pre *)state)[-1].unk_00 = &D_800B260C;
tail:
    return (s32)task;
fail:
    func_800B2C6C(state);
    return 0;
}
