#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80042B68();             /* extern */
M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
s32 func_800990FC(void);                          /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
M2C_UNK func_800A5720();                         /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
M2C_UNK func_800C4AFC();            /* extern */
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;
extern M2C_UNK D_80082E80;
extern D_80083460_t D_80083460;
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0E82;
extern void *D_800E3D7C[];


typedef struct S_800BD5C4_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD5C4_0_pre;   /* the 0x18 bytes before arg0 in func_800BD5C4, addressed as arg0[-1] */


/* Applies an entity update and handles its follow-up effects and state count. */
s32 func_800BD5C4(void *entity, s32 update_value, s16 mode) {
    u16 *type_flags;
    void *call_arg;
    register s32 context_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 saved_context ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    D_80083460_t *state;
    s32 type_index;
    s32 effect_context;
    s32 effect_result;

    if (entity == D_800E3D7C[0]) {
        ((Rec_D_800E3D7C *)entity)->unk_110 = update_value;
        func_8008D330(entity, &D_80083780, &D_80082E80, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, update_value, mode);
        call_arg = entity;
        type_index = ((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v;
        type_flags = (u16 *)&D_800DDE84;
        if (func_800AD6FC(call_arg, (type_flags[type_index] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, update_value);
            return 1;
        }
    }
    func_800C4AFC(((S_800BD5C4_0_pre *)entity)[-1].unk_00, 0xC02020, entity);
    if ((((Rec_D_800E3D7C *)entity)->unk_14.as_s32 & 0x4000) && !(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x400)) {
        effect_context = func_800990FC();
        call_arg = &D_800E0E82;
        ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        context_arg = effect_context;
        saved_context = context_arg;
        effect_result = func_80099194(call_arg, context_arg);
        func_80099290(effect_result);
        func_800A5720(saved_context);
    }
    func_80042B68(entity, 2);
    func_80098B38(update_value);
    state = &D_80083460;
    state->fieldA = (u16) (state->fieldA - 1);
    return 1;
}
