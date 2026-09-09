#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C13C8_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x74];
    s16 unk_9C;
    u8 pad_9E[0x86];
    s32 unk_124;
} S_800C13C8_0;   /* arg0 in func_800C13C8; pointer addresses record offset 0x14 */

typedef struct S_800C13C8_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C13C8_1;   /* state in func_800C13C8 */

typedef struct S_800C13C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C13C8_2;   /* temp_v0 in func_800C13C8 */


M2C_UNK func_8008D344(); /* extern */
s32 func_80098864(s32, s32);           /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A6480();            /* extern */
s32 func_800AD6FC();                /* extern */
s32 func_800BBA40(); /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800C135C;
extern u16 D_800DDE84[];
extern M2C_UNK D_800DEAE0;
extern M2C_UNK D_800E1482;
extern void *D_800E3D7C[];

/* Handles an object operation and updates its state or triggers its effect. */
s32 func_800C13C8(void *object, s32 value, s16 operation, M2C_UNK context) {
    S_800C13C8_2 *object_data;
    S_800C13C8_1 *state;
    s32 result;

    if (operation == 0xD) {
        return func_80098864(value, context);
    }
    if (object == D_800E3D7C[0]) {
        ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_124 = value;
        func_8008D344(object, &D_80083780, &D_80082E80, 0);
        return 0;
    }
    if ((u32) object <= 0x9FFFFFFFU) {
        func_800A6480(object, value, operation);
        if (func_800AD6FC(object, D_800DDE84[((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_27] & 3, value) == 0) {
            func_800A5F38(object, value);
            return 1;
        }
        state = &D_80083460;

        state->unk_0A--;
        goto shared;
    }
    object_data = ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_00;
    if (func_800BBA40(object_data->unk_24, object_data->unk_25, ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_9C, &D_800DEAE0, 0x5000, 0x202080, &D_800C135C) != 0) {
        goto success;
    }
    result = 0;
    goto done;
success:
    func_800997FC(&D_800E1482);
shared:
    func_80098B38(value);
    result = 1;
done:
    return result;
}
