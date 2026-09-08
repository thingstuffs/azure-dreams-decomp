#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A48F0();    /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
M2C_UNK func_800D4FC8();    /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E206A;
extern void *D_800E3D7C[];



typedef struct S_800C003C_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C003C_1;   /* global_base in func_800C003C */

/* Update entity state and counters, with special handling for the primary entity. */
s32 func_800C003C(void *entity, s32 event_id, s16 event_param) {
    u8 update_count;
    s8 *global_base;

    if (entity == D_800E3D7C[0]) {
        ((Rec_D_800E3D7C *)entity)->unk_110 = event_id;
        func_8008D330(entity, &D_80083780, &D_80082E80, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, event_id, event_param);
        if (func_800AD6FC(entity, (D_800DDE84[((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, event_id);
            return 1;
        }
    }
    update_count = ((Rec_D_800E3D7C *)entity)->unk_00.at02_u8.v;
    if (update_count < 0xFFU) {
        ((Rec_D_800E3D7C *)entity)->unk_00.at02_u8.v = (u8) (update_count + 1);
    }
    func_800A48F0(entity, 7, 8);
    if (((Rec_D_800E3D7C *)entity)->unk_14.as_s32 & 0x4000) {
        func_80099844(entity, &D_800E206A);
    }
    func_800D4FC8(entity - 0x20, 0xF02020, 0x616);
    func_80098B38(event_id);
    global_base = (s8 *) &D_80083460;
    ((S_800C003C_1 *)global_base)->unk_0A = (u16) (((S_800C003C_1 *)global_base)->unk_0A - 1);
    return 1;
}

