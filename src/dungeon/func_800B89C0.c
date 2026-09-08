#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
s32 func_800990FC(void);
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099368();
s32 func_80099734();
M2C_UNK func_80099844();
M2C_UNK func_800A5720();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
M2C_UNK func_800D5460();

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern M2C_UNK D_80082E80;
extern D_80083460_t D_80083460;
extern M2C_UNK D_80083780;
extern u8 D_8008935C[];
extern u16 D_800DDE84[];
extern u8 D_800E0FF4[];
extern u8 D_800E100F[];
extern s32 D_800E3D7C[];


typedef struct S_800BE120_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x30];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_48;   /* overlapping accesses */
    u8 pad_4C[0x8];
    u32 unk_54;
    u8 pad_58[0xB8];
    s32 unk_110;
} S_800BE120_0;   /* arg0 in func_800BE120 */

typedef struct S_800BE120_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800BE120_1;   /* arg1 in func_800BE120 */

/* Applies data to an entity and handles the resulting update or fallback. */
s32 func_800BE120(void *entity, S_800BE120_1 *data, s16 mode) {
    s32 stored;
    s32 stored_test;
    void *call_entity;
    register s32 context_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 zero_result ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 new_context;
    s32 context;

    stored = 0;
#ifdef NON_MATCHING
    zero_result = 0;
#endif
    if (entity == D_800E3D7C[0]) {
        ((S_800BE120_0 *)entity)->unk_110 = (s32)data;
        func_8008D330(entity, &D_80083780, &D_80082E80, entity);
        return zero_result;
    }

    if ((u32)entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, data, mode);
        if (((S_800BE120_0 *)entity)->unk_13 >= 2) {
            if (!(((S_800BE120_0 *)entity)->unk_54 & 0x800000)) {
                if (((S_800BE120_0 *)entity)->unk_48.at01.v == 0) {
                    if (func_800AD6FC(entity,
                            (D_800DDE84[((S_800BE120_0 *)entity)->unk_13] >> 6) & 3,
                            0) == 0) {
                        goto finalize;
                    }
                    ((S_800BE120_0 *)entity)->unk_48.at00.v = *(s32 *)data;
                    ((S_800BE120_0 *)entity)->unk_48.at00u.v = data->unk_00;
                    ((S_800BE120_0 *)entity)->unk_48.at01.v = data->unk_01;
                    ((S_800BE120_0 *)entity)->unk_48.at02.v = data->unk_02;
                    ((S_800BE120_0 *)entity)->unk_48.at03.v = data->unk_03;
                    ((S_800BE120_0 *)entity)->unk_54 |= 0x800000;
                    func_800D5460((s8 *)entity - 0x20, 0x20A0A0, 0x702);
                    stored = 1;
                    if (((S_800BE120_0 *)entity)->unk_14 & 0x4000) {
                        func_80099844(entity, D_800E0FF4);
                    }
                }
            }
        }
    }

    stored_test = stored;
    ASM_KEEP(stored_test);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (stored_test != 0) {
        goto consume_data;
    }
    if ((((S_800BE120_0 *)entity)->unk_13 < 2) ||
        (((S_800BE120_0 *)entity)->unk_54 & 0x800000) ||
        (((S_800BE120_0 *)entity)->unk_48.at01.v != 0)) {
        new_context = func_800990FC();
        call_entity = entity;
        ASM_KEEP(call_entity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        context_arg = new_context;
        ASM_KEEP(context_arg);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        context = context_arg;
        func_80099290(func_80099194(D_8008935C,
            func_80099368(data, func_80099194(D_800E100F,
                func_80099734((s32)call_entity, context_arg)))));
        func_800A5720(context);
        goto finalize;
    }
    goto consume_data;

finalize:
    func_800A5F38(entity, data);
    return 1;

consume_data:
    func_80098B38(data);
    D_80083460.fieldA = (u16)(D_80083460.fieldA - 1);
    return 1;
}
