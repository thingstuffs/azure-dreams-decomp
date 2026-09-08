#include "common.h"

typedef struct S_8005A4E8 {
    s32 type;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} S_8005A4E8;

extern void func_8005EDA0(S_8005A4E8 *s);

/* Selects a tagged value type from two flags and passes its byte payload to func_8005EDA0. */
void func_8005A4E8(u8 type_group, u8 type_variant, u8 value) {
    S_8005A4E8 tagged_value;
    if (type_group == 0) {
        if (type_variant == 0) {
            tagged_value.type = 0x200;
            tagged_value.unk18 = value;
        } else {
            tagged_value.type = 0x100;
            tagged_value.unk14 = value;
        }
    } else {
        if (type_variant == 0) {
            tagged_value.type = 0x2000;
            tagged_value.unk24 = value;
        } else {
            tagged_value.type = 0x1000;
            tagged_value.unk20 = value;
        }
    }
    func_8005EDA0(&tagged_value);
}
