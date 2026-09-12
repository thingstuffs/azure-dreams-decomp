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
extern M2C_UNK D_80082E80;
extern extern M2C_UNK D_80083460[3];
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0E69;
extern void *D_800E3D7C[];


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
    M2C_UNK *item_counts;

    if (entity == D_800E3D7C[0]) {
        ((Rec_D_800E3D7C *)entity)->unk_110 = item;
        func_8008D330(entity, &D_80083780, &D_80082E80, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        register void *call_entity ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register u8 *table_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 type_id;

        func_800A63B8(entity, item, action);
        call_entity = entity;
        table_page = (u8 *)0x800E0000;
        ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        type_id = ((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        type_flags = (u16 *)(table_page - 0x217C);
        ASM_KEEP(type_flags);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        if (func_800AD6FC(call_entity, (type_flags[type_id] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    func_800C4AFC(((S_800BD45C_0_pre *)entity)[-1].unk_00, 0x802080, entity);
    if ((((Rec_D_800E3D7C *)entity)->unk_14.as_s32 & 0x4000) && !(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x40)) {
        M2C_UNK *message_text;
        s32 message_pos;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 message_start;
        s32 message_end;

        message_end = func_800990FC();
        message_text = &D_800E0E69;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        message_pos = message_end;
        message_start = message_pos;
        message_end = func_80099194(message_text, message_pos);
        func_80099290(message_end);
        func_800A5720(message_start);
    }
    func_80042B68(entity, 5);
    func_80098B38(item);
    item_counts = D_80083460;
    ASM_KEEP(item_counts);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_800BD45C_1 *)item_counts)->unk_0A = (u16) (((S_800BD45C_1 *)item_counts)->unk_0A - 1);
    return 1;
}
