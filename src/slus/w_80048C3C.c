#include "common.h"
#include "m2c_compat.h"

typedef struct S_80048C3C_0 {
    s32 unk_00;
    void * unk_04;
} S_80048C3C_0;   /* temp_s1 in func_80048C3C */

typedef struct S_80048C3C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_80048C3C_1;   /* temp_s2 in func_80048C3C */

M2C_UNK DrawSync();                          /* extern */
M2C_UNK Control_CD();       /* extern */
M2C_UNK func_8003F320();                            /* extern */
void func_8003F80C(); /* extern */
s32 func_80046F88();                      /* extern */
void func_80047200();    /* extern */
void func_80048B8C();                      /* extern */
extern u8 D_80071210[];
extern s8 D_80080A89;

/* Loads and initializes a resource, registers its payload in two VRAM cache slots, and returns its table slot. */
void *func_80048C3C(s32 resource_id) {
    void *payload;
    void *entry;
    void *entry2;
    void *entry3;
    void *resource;
    s32 load_mode;

    entry = (void *)(resource_id * 8);
    load_mode = 6;
    entry2 = (u8 *)entry + (u32)D_80071210;
    Control_CD(load_mode, ((S_80048C3C_0 *)entry2)->unk_00, 0);
    func_8003F320();
    resource = ((S_80048C3C_0 *)entry2)->unk_04;
    payload = resource + ((S_80048C3C_1 *)resource)->unk_1C;
    func_8003F80C(payload, 0x7A00, ((S_80048C3C_1 *)resource)->unk_20, 2);
    DrawSync(0);
    func_80047200(payload, 1, 1);
    func_8003F80C(payload, 0x7980, ((S_80048C3C_1 *)resource)->unk_20, 2);
    func_80046F88(resource);
    entry3 = (u8 *)entry2 + 4;
    func_80048B8C(resource);
    D_80080A89 = 0;
    return entry3;
}
