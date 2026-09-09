#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

typedef struct S_800A55CC_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A55CC_0_pre;   /* the 0x10 bytes before arg0 in func_800A55CC, addressed as arg0[-1] */



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_800942B0(void *arg0, Rec_D_800E3D7C *arg1, s32 arg2);
extern M2C_UNK D_800903FC[];
extern M2C_UNK D_800970FC[];
extern s32 D_800D0CC0[];

/* Initialize the object and adjust its record value before final setup. */
void func_800A55CC(void *object, Rec_D_800E3D7C *record, s32 init_value) {
    register s32 delta ASM_REG("$6"); /* MATCH: reuse a2 for delta after the explicit pass-through call. */

    ((S_800A55CC_0_pre *)object)[-1].unk_00 = D_800903FC;
    func_800942B0(object, record, init_value);
    {
        register void *call_object ASM_REG("$4") = object;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *setup_data = D_800970FC;
        register s32 record_value ASM_REG("$2"); /* MATCH: keep the arithmetic result in retail's v0. */

        ASM_KEEP(call_object);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        delta = 0x10000;
        record_value = record->unk_08.at00_s32.v;
        record->unk_08.at00_s32.v =
            (record_value + delta) - D_800D0CC0[0];
        func_80033CD8(call_object, setup_data, delta);
    }
}
