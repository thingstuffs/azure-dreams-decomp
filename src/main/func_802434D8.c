/* Relink of matched main/func_80013494; every changed retail word is a paired relocation. */
#define cardBootShowInsufficientSpaceOverwriteAdvice cardBootShowInsufficientSpaceCardAdvice
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026494_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x40];
    M2C_UNK * unk_44;
} S_80026494_0;   /* arg0 in func_800264D8; pointer addresses record offset 0x10 */


extern void cardBootShowInsufficientSpaceCardAdvice(s32);                         /* extern */
extern M2C_UNK D_800261F0;
extern M2C_UNK D_800265B8;

/* Set record pointers around an update of its base record. */
void func_800264D8(void *record_part) {
    ((S_80026494_0 *)((u8 *)record_part - 0x10))->unk_44 = &D_800265B8;
    cardBootShowInsufficientSpaceCardAdvice(record_part - 0x20);
    ((S_80026494_0 *)((u8 *)record_part - 0x10))->unk_00 = &D_800261F0;
}
