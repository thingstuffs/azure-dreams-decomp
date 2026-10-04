#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
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
M2C_UNK func_800C4AFC();            /* extern */
extern extern M2C_UNK D_80083460[3];
extern M2C_UNK D_800E0E69;


typedef struct S_800BD45C_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD45C_0_pre;   /* the 0x18 bytes before arg0 in func_800BD45C, addressed as arg0[-1] */


typedef struct S_800BD45C_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BD45C_1;   /* counter in func_800BD45C */

/* Applies an item's effect to an entity and consumes the processed item. */
s32 func_800BD45C(void *entity, s32 item, s16 action) {
    u16 *type_flags;
    s32 *item_counts;

    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = item;
        func_8008D330(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        void *call_entity;
        u8 type_id;

        func_800A63B8(entity, item, action);
        call_entity = entity;
        type_id = (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3));
        if (func_800AD6FC(call_entity, (D_800DDE84[type_id] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    func_800C4AFC(((S_800BD45C_0_pre *)entity)[-1].unk_00, 0x802080, entity);
    if ((((EntityRec *)entity)->flags14 & 0x4000) && !(((EntityRec *)entity)->flags1C & 0x40)) {
        void *message_text;
        s32 message_pos;
        s32 message_start;
        s32 message_end;

        message_end = func_800990FC();
        message_text = &D_800E0E69;
        message_pos = message_end;
        message_start = message_pos;
        message_end = func_80099194(message_text, message_pos);
        func_80099290(message_end);
        func_800A5720(message_start);
    }
    func_80042B68(entity, 5);
    func_80098B38(item);
    item_counts = D_80083460;
    ((S_800BD45C_1 *)item_counts)->unk_0A = (u16) (((S_800BD45C_1 *)item_counts)->unk_0A - 1);
    return 1;
}
