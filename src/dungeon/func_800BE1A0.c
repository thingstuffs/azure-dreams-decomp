#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern u8 D_800DDE84[];
extern M2C_UNK D_800E17C6;
extern M2C_UNK D_800E17EF;
extern M2C_UNK D_800E180E;
extern s32 D_800E3D7C;


typedef struct S_800C3900_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C3900_1;   /* var_v1 in func_800C3900 */

typedef struct S_800C3900_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C3900_2;   /* counter_base in func_800C3900 */

/* Processes an entity action, preserves its state flag, and updates the shared counter. */
s32 func_800C3900(Rec_D_800E3D7C *entity, s32 action, s16 action_param) {
    register M2C_UNK *counter_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    M2C_UNK *counter_base;
    s32 saved_flag;
    s32 flag_test;
    u32 flags;

    if (entity == D_800E3D7C) {
        entity->unk_110 = action;
        func_8008D330(entity, &D_80083780, &D_80082E80, entity);
        return 0;
    }
    if (((u32) (entity->unk_10.at03_u8.v - 1) < 0x2EU) && ((u32) entity <= 0x9FFFFFFFU)) {
        func_800A63B8(entity, action, action_param);
        saved_flag = ((u32) entity->unk_1C.as_u32 >> 3) & 1;
        if (func_800AD6FC(entity, (((u16 *) D_800DDE84)[entity->unk_10.at03_u8.v] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, action);
            return 1;
        }
        flag_test = saved_flag;
        if (flag_test != 0) {
            entity->unk_1C.as_u32 = (u32) (entity->unk_1C.as_u32 | 8);
        }
        flags = entity->unk_1C.as_u32;
        entity->unk_24.at00_s16.v = 0;
        if (!(flags & 8)) {
            flag_test = flags & 0x80000;
            counter_page = (M2C_UNK *)0x80080000;
            if (flag_test != 0) {
                func_80094E34();
                counter_page = (M2C_UNK *)0x80080000;
            }
            counter_page = (M2C_UNK *)((u8 *)counter_page + 0x3460);
            ((S_800C3900_1 *)counter_page)->unk_0A = (u16) (((S_800C3900_1 *)counter_page)->unk_0A + 1);
        }
        func_800A56E0(0x51E);
        if (entity->unk_14.as_s32 & 0x4000) {
            func_80099844(entity, &D_800E17C6);
        }
        func_80098B38(action);
        goto decrement_counter;
    }
    if (entity->unk_10.at03_u8.v == 0) {
        func_800997FC(&D_800E17EF);
        func_800A56E0(0x506);
        goto decrement_counter;
    }
    func_80098B38(action);
    func_800997FC(&D_800E180E);
decrement_counter:
    counter_base = &D_80083460;
    ((S_800C3900_2 *)counter_base)->unk_0A = (u16) (((S_800C3900_2 *)counter_base)->unk_0A - 1);
    return 1;
}
