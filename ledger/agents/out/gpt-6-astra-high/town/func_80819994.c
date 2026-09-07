#include "common.h"

typedef struct S_80023994_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80023994_0;   /* button_base in func_80023994 */

typedef struct S_80023994_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_80023994_1;   /* record_base in func_80023994 */

typedef struct S_80023994_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80023994_2;   /* arg1 in func_80023994 */


typedef struct {
    u16 field_0;
    u16 field_2;
    u8 pad_4[8];
    s32 field_C;
} Unk83780;

extern s32 func_800C2AE8(void *);
extern void func_80093CEC(void *);

extern u16 D_80026F24[];
extern s16 D_800272C8;
extern s16 D_800272CA;
extern u16 D_80082E94;
extern u8 D_80083160[];
extern Unk83780 D_80083780;
extern s32 D_8008378C;
extern u8 D_800D00C0[];
extern u8 D_800D0128[];


/* Updates the three-choice selection and the object's vertical motion. */
void func_80023994(void *unused, S_80023994_2 *object)
{
    u8 *button_base;
    s32 height_limit;

    button_base = D_80083160;
    height_limit = (s16)func_800C2AE8(object);
    if (D_800272CA > 0) {
        D_800272CA--;
        D_80083780.field_C -= D_80083780.field_C >> 1;
        goto update_height;
    }

    {
        s16 choice_index;
        u16 choice_id;
        s32 buttons;
        u8 *record_base;

        record_base = (u8 *)&D_80083780;
        choice_index = D_800272C8;
        choice_id = D_80026F24[choice_index];
        buttons = ((S_80023994_0 *)button_base)->unk_10;

        ((S_80023994_1 *)record_base)->unk_0C = 0;
        ((S_80023994_1 *)record_base)->unk_02 = choice_id;
        if ((buttons & 0x8000) && choice_index != 0) {
            D_800272C8--;
            ((S_80023994_1 *)record_base)->unk_0C = (s32)0xFFD00000;
            D_800272CA = 3;
            func_80093CEC(D_800D00C0);
            goto update_height;
        }
    }
    if ((((S_80023994_0 *)button_base)->unk_10 & 0x2000) && D_800272C8 < 2) {
        D_800272C8++;
        D_8008378C = 0x300000;
        D_800272CA = 3;
        func_80093CEC(D_800D00C0);
        goto update_height;
    }
    if (D_80082E94 & 0x6000) {
        func_80093CEC(D_800D0128);
    }

update_height:
    object->unk_14 += 0x1D000;
    if (height_limit < object->unk_0A) {
        object->unk_0A = height_limit;
        object->unk_14 = 0;
    }
}
