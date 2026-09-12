#include "common.h"

typedef s32 M2C_UNK;


M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099734();
s32 func_800A48F0();
M2C_UNK func_800A5720();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
M2C_UNK func_800D5460();

typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u8 D_80089358[];
extern u16 D_800DDE84[];
extern u8 D_800E0FA4[];
extern u8 D_800E0FB9[];
extern u8 D_800E0FD7[];
extern u8 *D_800E3D7C;


typedef struct S_800BDEB8_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800BDEB8_0_pre;   /* the 0x14 bytes before var_s2 in func_800BDEB8, addressed as var_s2[-1] */

typedef struct S_800BDEB8_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0x84];
    s32 unk_A4;
    u8 pad_A8[0x2];
    s16 unk_AA;
    u8 pad_AC[0x64];
    s32 unk_110;
} S_800BDEB8_0;   /* var_s2 in func_800BDEB8 */

typedef struct S_800BDEB8_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800BDEB8_1;   /* ((S_800BDEB8_0_pre *)var_s2)[-1].unk_00 in func_800BDEB8 */

/* Applies an interaction to an entity and displays the outcome. */
s32 func_800BDEB8(void *target, s32 action, s16 mode) {
    void *current_entity = D_800E3D7C;
    void *entity = target;
    s32 action_id = action;
    register s32 special_case ASM_REG("$19") = 0;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 original_id;
    register s32 message_handle ASM_REG("$17"); /* MATCH: Keep the shared-tail value in s1 after merging the two call paths. */
    register s32 saved_id ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *return_address ASM_REG("$31");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u32 entity_id;
    s32 result;
    u32 flag_mask;

    ASM_KEEP4_NV(entity, action_id, special_case, return_address);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP4_NV(entity, action_id, special_case, original_id);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (entity == current_entity) {
        ((S_800BDEB8_0 *)entity)->unk_110 = action_id;
        func_8008D330(target, D_80083780, D_80082E80, target);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, action_id, mode);
        if (func_800AD6FC(entity, (D_800DDE84[((S_800BDEB8_0 *)entity)->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, action_id);
            return 1;
        }
    }

    entity_id = ((S_800BDEB8_0 *)entity)->unk_13;
    if (entity_id >= 0x2E) {
        goto set_special;
    }
    if (entity_id == 0x1E) {
        if ((((S_800BDEB8_0 *)entity)->unk_A4 != 0) || (((S_800BDEB8_0 *)entity)->unk_AA != 0)) {
            special_case = 1;
        }
        result = special_case;
    } else {
        result = special_case;
    }
    if (result != 0) {
        goto show_special;
    }

    flag_mask = 0x80000;
    original_id = ((S_800BDEB8_0 *)entity)->unk_13;
    if (((S_800BDEB8_0 *)entity)->unk_1C & flag_mask) {
        ((S_800BDEB8_1 *)(((S_800BDEB8_0_pre *)entity)[-1].unk_00))->unk_06 = 0;
    }
    {
        u8 *message; /* MATCH: Keep the merged message address in retail's argument register. */
        result = func_800A48F0(entity, 10, 0x20);
        if ((s16)result >= 0) {
            saved_id = ((S_800BDEB8_0 *)entity)->unk_13;
            message_handle = func_800990FC();
            ((S_800BDEB8_0 *)entity)->unk_13 = original_id;
            result = func_80099734(entity, message_handle);
            ((S_800BDEB8_0 *)entity)->unk_13 = saved_id;
            message = D_800E0FA4;
            result = func_80099194(message, result);
        } else {
            message_handle = func_800990FC();
            message = D_800E0FB9;
            result = func_80099194(message, message_handle);
        }
    }
    func_80099290(result);
    func_800A5720(message_handle);
    func_800D5460((u8 *)entity - 0x20, 0x20A0A0, 0x613);
    result = special_case;
    goto check_special;

set_special:
    special_case = 1;
    ASM_KEEP(special_case);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    result = special_case;
check_special:
    if (result == 0) {
        goto finish;
    }
show_special:
    result = func_800990FC();
    {
        register u8 *message ASM_REG("$4") = D_800E0FD7;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register s32 message_arg ASM_REG("$5") = result;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(message_arg);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        saved_id = message_arg;
        result = func_80099194(message, message_arg);
    }
    result = func_80099734(entity, result);
    result = func_80099194(D_80089358, result);
    func_80099290(result);
    func_800A5720(saved_id);

finish:
    func_80098B38(action_id);
    D_80083460.field_A--;
    return 1;
}
