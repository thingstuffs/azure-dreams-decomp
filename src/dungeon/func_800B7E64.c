#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

M2C_UNK func_80042B68();             /* extern */
void func_8008D330(); /* extern */
void func_80098B38();                         /* extern */
s32 func_800990FC(void);                          /* extern */
s32 func_80099194();                  /* extern */
void *func_80099290();                         /* extern */
s32 func_800A5720();                         /* extern */
void func_800A5F38();                 /* extern */
void func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800C4AFC();            /* extern */
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;
extern M2C_UNK D_800E0E82;


typedef struct S_800BD5C4_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD5C4_0_pre;   /* the 0x18 bytes before arg0 in func_800BD5C4, addressed as arg0[-1] */


/* Applies an entity update and handles its follow-up effects and state count. */
s32 func_800BD5C4(void *entity, s32 update_value, s16 mode) {
    u16 *type_flags;
    void *call_arg;
    s32 context_arg;
    s32 saved_context;
    s32 type_index;
    s32 effect_result;

    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = update_value;
        func_8008D330(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, update_value, mode);
        call_arg = entity;
        type_index = (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3));
        type_flags = (u16 *)&D_800DDE84;
        if (func_800AD6FC(call_arg, (type_flags[type_index] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, update_value);
            return 1;
        }
    }
    func_800C4AFC(((S_800BD5C4_0_pre *)entity)[-1].unk_00, 0xC02020, entity);
    if ((((EntityRec *)entity)->flags14 & 0x4000) && !(((EntityRec *)entity)->flags1C & 0x400)) {
        effect_result = func_800990FC();
        call_arg = &D_800E0E82;
        context_arg = effect_result;
        saved_context = context_arg;
        effect_result = func_80099194(call_arg, context_arg);
        func_80099290(effect_result);
        func_800A5720(saved_context);
    }
    func_80042B68(entity, 2);
    func_80098B38(update_value);
    dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    return 1;
}
