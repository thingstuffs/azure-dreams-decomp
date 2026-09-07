#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036434_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_80036434_1;   /* arg0 in func_80036434 */

typedef struct S_80036434_2 {
    u8 pad_00[0x27];
    u8 unk_27;
} S_80036434_2;   /* ((S_80036434_1 *)arg0)->unk_74 in func_80036434 */


typedef struct S_80036434_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x16];
    s16 unk_64;
    u8 pad_66[0x2];
    M2C_UNK * unk_68;
} S_80036434_0;   /* arg0 in func_80036434 */


M2C_UNK func_80053DA8();                     /* extern */
extern M2C_UNK func_80036484;

/* Saves the object's flags and enters state 0x11 with a new handler and flag 0x80 set. */
void func_80036434(S_80036434_0 *object) {
    ((S_80036434_2 *)(((S_80036434_1 *)object)->unk_74))->unk_27 = (u8) object->unk_4D;
    object->unk_64 = 0x11;
    object->unk_68 = &func_80036484;
    object->unk_4D = (u8) (object->unk_4D | 0x80);
    func_80053DA8(0x503);
}
