#include "common.h"

typedef s32 M2C_UNK;

M2C_UNK func_8002522C();
void *func_8003FD64();
M2C_UNK func_8004491C();

extern M2C_UNK D_800247AC[3];
extern M2C_UNK D_80024A68[3];

/* Creates an object, copies three source fields to its child, and applies sixteen setup steps. */
void *func_80024804(s32 type_code, void *source, s32 unused, s32 object_value)
{
    register u32 stored_value;
    s32 type_id;
    s32 step;
    void *child;
    void *object;

    stored_value = object_value;
    type_id = type_code - 0x20;
    object = func_8003FD64(2, type_id);
    if (object != 0) {
        *(M2C_UNK **)((u8 *)object + 0x10) = D_800247AC;
        func_8004491C(object, D_80024A68);

        child = *(void **)((u8 *)object + 8);
        *(u16 *)((u8 *)child + 2) = *(u16 *)((u8 *)source + 2);
        step = 0;
        *(u16 *)((u8 *)child + 6) = *(u16 *)((u8 *)source + 6);
        *(u16 *)((u8 *)child + 0xA) = *(u16 *)((u8 *)source + 0xA);
        source = (void *)type_id;
        *(s32 *)((u8 *)object + 0x20) = stored_value;

        do {
            func_8002522C(child, (s16)(step << 8), 0x40, -0x100, source);
            step += 1;
        } while (step < 0x10);
    }
    return object;
}

/* MECHANISM: The 0x38 frame holds s3=source, s5=object_value, s4=type_code-0x20,
   s2=result, s1=child, and s0=loop index; the fifth call arg uses sp+0x10.
   ASM_KEEP(s5) at its true last use changes sched2 prologue entry order only,
   placing the s5 save/copy between the s3 and s4 packets byte-exactly. */
