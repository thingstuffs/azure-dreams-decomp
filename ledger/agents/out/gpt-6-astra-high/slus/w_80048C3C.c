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

#ifndef NON_MATCHING
#undef ASM_KEEP
#define ASM_KEEP(v) __asm__("" : "=r"(v) : "0"(v))
#endif

M2C_UNK DrawSync();                          /* extern */
M2C_UNK func_8003E4FC();       /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8003F80C(); /* extern */
M2C_UNK func_80046F88();                      /* extern */
M2C_UNK func_80047200();    /* extern */
M2C_UNK func_80048B8C();                      /* extern */
extern u8 D_80071210[];
extern s8 D_80080A89[9];

/* Load and initialize a resource, upload its payload, and return its table slot. */
void *func_80048C3C(s32 resource_id) {
    void *payload;
    register void *entry ASM_REG("$17");
    void *resource;
    s32 load_mode;
    s32 enabled;
    register void *payload_arg ASM_REG("$4");

    entry = (void *)(resource_id * 8);
    load_mode = 6;
    ASM_KEEP(load_mode);
    entry = (u8 *)entry + (u32)D_80071210;
    func_8003E4FC(load_mode, ((S_80048C3C_0 *)entry)->unk_00, 0);
    func_8003F320();
    resource = ((S_80048C3C_0 *)entry)->unk_04;
    payload = resource + ((S_80048C3C_1 *)resource)->unk_1C;
    func_8003F80C(payload, 0x7A00, ((S_80048C3C_1 *)resource)->unk_20, 2);
    DrawSync(0);
    payload_arg = payload;
    enabled = 1;
    ASM_KEEP(enabled);
    func_80047200(payload_arg, enabled, enabled);
    func_8003F80C(payload, 0x7980, ((S_80048C3C_1 *)resource)->unk_20, 2);
    func_80046F88(resource);
    func_80048B8C(resource);
    entry = (u8 *)entry + 4;
    ASM_KEEP(entry);
    D_80080A89[0] = 0;
    return entry;
}
