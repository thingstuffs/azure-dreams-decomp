#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80024390_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80024390_5;   /* assetSlot in func_80024390 */

typedef struct S_80024390_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x1A];
    s32 unk_24;
    s32 unk_28;
    u32 unk_2C;
    u8 pad_30[0x4];
    s32 unk_34;
} S_80024390_6;   /* ((((S_80024390_0 *)record)->unk_7C << 7) + recordBase) in func_80024390 */

typedef struct S_80024390_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80024390_7;   /* ((S_80024390_5 *)assetSlot)->unk_04 in func_80024390 */


typedef struct S_80024390_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    u8 pad_80[0xACC];
    void * unk_B4C;
    void * unk_B50;
    void * unk_B54;
    void * unk_B58;
    void * unk_B5C;
    void * unk_B60;
    void * unk_B64;
} S_80024390_0;   /* record in func_80024390 */

typedef struct S_80024390_1 {
    union { void * s; s32 u; } unk_00;   /* accessed as both */
} S_80024390_1;   /* assetSlot in func_80024390 */

typedef struct S_80024390_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    M2C_UNK * unk_0C;
} S_80024390_2;   /* table_base in func_80024390 */

typedef struct S_80024390_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x10];
    s32 unk_30;
} S_80024390_3;   /* recordData in func_80024390 */

typedef struct S_80024390_4 {
    u8 pad_00[0xB68];
    void * unk_B68;
} S_80024390_4;   /* recordCursor in func_80024390 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

u8 *func_8003AD08(); /* extern */
void *func_8004DA74(); /* extern */
void *func_8004E298(); /* extern */
char *func_8004E5A0(); /* extern */
char *func_8004E5E8(); /* extern */
u8 *func_8004E69C(); /* extern */
M2C_UNK func_80069E38();
M2C_UNK func_80069E78();
extern u8 D_800200A4[0x100];
extern s32 D_80027FD4[0x40];
extern u8 D_800282D8[0x100];
extern u8 D_800282E8[0x100];
extern u8 D_800283A8[0x100];
extern u8 D_80083EA4[0x4000];

void func_80024390(void *record) {
    u8 textBuffer[256];
    u8 numberBuffer[16];
    s32 coordinate;
    s32 *tableCursor;
    s32 totalMinutes;
    s32 hours;
    s32 elapsedSeconds;
    s32 value;
    u32 displayValue;
    u32 boundedValue;
    u32 one;
    s32 width;
    s32 scaledTime;
    void *recordBase;
    void *assetDataBase;
    void *loop_base;
    void *asset0;
    void *asset1;
    void *asset2;
    void *asset3;
    void *asset4;
    void *asset5;
    void *asset6;
    S_80024390_2 *table_base;
    S_80024390_1 *assetSlot;
    void *recordData;
    void *recordCursor;
    s32 *global_table;

    assetSlot = ((S_80024390_0 *)record)->unk_B4C;
    func_8003AD08(((S_80024390_0 *)record)->unk_7C + 1, &textBuffer);
    func_80069E38(&textBuffer, D_800282D8);
    assetDataBase = D_80083EA4;
    func_80069E38(&textBuffer, (((S_80024390_0 *)record)->unk_7C << 7) + assetDataBase);
    asset0 = record + 0x84;
    func_8004DA74(asset0, &textBuffer, 1);
    assetSlot->unk_00.s = asset0;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = 0xA8;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = 0x110;
    assetSlot = ((S_80024390_0 *)record)->unk_B50;
    func_80069E78(&textBuffer, D_800282E8);
    asset1 = record + 0x204;
    func_8004DA74(asset1, &textBuffer, 1);
    assetSlot->unk_00.s = asset1;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = 0xA0;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = 0x110;
    recordBase = assetDataBase - 0xC;
    if (((S_80024390_6 *)(((((S_80024390_0 *)record)->unk_7C << 7) + recordBase)))->unk_08 != 0) {
        table_base = D_800283A8;
        assetSlot = ((S_80024390_0 *)record)->unk_B54;
        func_80069E78(&textBuffer, table_base->unk_08);
        func_8003AD08(((S_80024390_6 *)(((((S_80024390_0 *)record)->unk_7C << 7) + recordBase)))->unk_34, &numberBuffer);
        func_80069E38(&textBuffer, &numberBuffer);
        func_80069E38(&textBuffer, table_base->unk_0C);
        asset2 = record + 0x384;
        func_8004DA74(asset2, &textBuffer, 1);
        assetSlot->unk_00.s = asset2;
        ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = 0xB8;
        ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = 0x140;
    }
    assetSlot = ((S_80024390_0 *)record)->unk_B58;
    func_8004E5A0(((S_80024390_6 *)(((((S_80024390_0 *)record)->unk_7C << 7) + recordBase)))->unk_24, 0xA, &textBuffer);
    func_8004E69C(&textBuffer);
    asset3 = record + 0x504;
    func_8004E298(asset3, &textBuffer, 1);
    assetSlot->unk_00.s = asset3;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = 0x148;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = 0x110;
    recordData = (((S_80024390_0 *)record)->unk_7C << 7) + recordBase;
    scaledTime = ((S_80024390_3 *)recordData)->unk_1C / 60;
    elapsedSeconds = scaledTime;
    assetSlot = ((S_80024390_0 *)record)->unk_B5C;
    hours = elapsedSeconds / 3600;
    value = 0x3E7;
    if (hours < 0x3E8) {
        value = hours;
    }
    func_8004E5A0(value, 3, &textBuffer);
    func_80069E38(&textBuffer, D_800200A4);
    totalMinutes = elapsedSeconds / 60;
    func_8004E5E8(totalMinutes - (hours * 0x3C), 2, &numberBuffer);
    func_80069E38(&textBuffer, &numberBuffer);
    func_80069E38(&textBuffer, D_800200A4);
    func_8004E5E8(elapsedSeconds - (totalMinutes * 0x3C), 2, &numberBuffer);
    func_80069E38(&textBuffer, &numberBuffer);
    func_8004E69C(&textBuffer);
    asset4 = record + 0x684;
    func_8004E298(asset4, &textBuffer, 1);
    assetSlot->unk_00.s = asset4;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = 0x150;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = 0x120;
    displayValue = ((S_80024390_6 *)(((((S_80024390_0 *)record)->unk_7C << 7) + recordBase)))->unk_2C;
    assetSlot = ((S_80024390_0 *)record)->unk_B60;
    boundedValue = 0x3E7;
    if (displayValue < 0x3E8U) {
        boundedValue = displayValue;
    }
    func_8004E5A0((s32) boundedValue, 3, &textBuffer);
    func_8004E69C(&textBuffer);
    asset5 = record + 0x804;
    func_8004E298(asset5, &textBuffer, 1);
    assetSlot->unk_00.s = asset5;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = 0x100;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = 0x120;
    assetSlot = ((S_80024390_0 *)record)->unk_B64;
    func_8004E5A0(((S_80024390_6 *)(((((S_80024390_0 *)record)->unk_7C << 7) + recordBase)))->unk_28, 2, &textBuffer);
    func_8004E69C(&textBuffer);
    asset6 = record + 0x984;
    func_8004E298(asset6, &textBuffer, 1);
    value = 0;
    loop_base = recordBase;
    global_table = D_80027FD4;
    one = 1;
    width = 0xB0;
    coordinate = 0x34;
    tableCursor = global_table;
    recordCursor = record;
    assetSlot->unk_00.s = asset6;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = 0x188;
    ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = 0x130;
    do {
        assetSlot = ((S_80024390_4 *)recordCursor)->unk_B68;
        recordData = (void *)(((S_80024390_0 *)record)->unk_7C << 7);
        recordData = (void *)((u32)recordData + (u32)loop_base);
        if (((S_80024390_3 *)recordData)->unk_30 & (one << value)) {
            displayValue = *tableCursor;
        } else {
            displayValue = global_table[8];
        }
        tableCursor += 1;
        recordCursor += 4;
        value += 1;
        assetSlot->unk_00.u = (s32) displayValue;
        ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_08 = coordinate;
        ((S_80024390_7 *)(((S_80024390_5 *)assetSlot)->unk_04))->unk_0A = width;
        coordinate += 0x10;
    } while (value < 8);
}
