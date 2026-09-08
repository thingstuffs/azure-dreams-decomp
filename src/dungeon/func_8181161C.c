#include "common.h"

typedef struct {
    s8 pad_00[0x10];
    s32 index;
    s32 field_14;
    u8 pad_18[0x58];
    s32 field_70;
} Func8181161CData;

extern u8 D_800294F8[9];

extern void memset(s32, s32, s32);
extern void strcpy(s32, s32);
extern void func_800263C0(s32, s32);

// Clears the object's text buffer, copies the source string, and passes it to func_800263C0.
void func_8002661C(s8 *object, s32 sourceString) {
    Func8181161CData *textData = (Func8181161CData *)(object + 0x20);

    memset(textData->field_14, 0, (D_800294F8[textData->index] << 1) | 1);
    strcpy(textData->field_14, sourceString);
    func_800263C0(textData->field_70, textData->field_14);
}
