#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"

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



extern s32 func_800C2AE8(void *);
extern void func_80093CEC(void *);

extern u16 D_80026F24[];
extern s16 D_800272C8;
extern s16 D_800272CA;
extern u8 D_800D00C0[];
extern u8 D_800D0128[];


/* Updates the three-choice selection and the object's vertical motion. */
void func_80023994(void *unused, EntityRec *object)
{
    GameWork *button_base;
    s32 height_limit;

    button_base = &gameWork;
    height_limit = (s16)func_800C2AE8(object);
    if (D_800272CA > 0) {
        D_800272CA--;
        D_80083780.unk_0C -= D_80083780.unk_0C >> 1;
        goto update_height;
    }

    {
        s16 choice_index;
        u16 choice_id;
        s32 buttons;
        EntityRec *record_base;

        record_base = &D_80083780;
        choice_index = D_800272C8;
        choice_id = D_80026F24[choice_index];
        buttons = ((s32)button_base->unk_010);

        record_base->unk_0C = 0;
        record_base->x.w.i = choice_id;
        if ((buttons & 0x8000) && choice_index != 0) {
            D_800272C8--;
            record_base->unk_0C = (s32)0xFFD00000;
            D_800272CA = 3;
            func_80093CEC(D_800D00C0);
            goto update_height;
        }
    }
    if ((((s32)button_base->unk_010) & 0x2000) && D_800272C8 < 2) {
        D_800272C8++;
        D_80083780.unk_0C = 0x300000;
        D_800272CA = 3;
        func_80093CEC(D_800D00C0);
        goto update_height;
    }
    if (D_80082E80.unk_014 & 0x6000) {
        func_80093CEC(D_800D0128);
    }

update_height:
    object->flags14 += 0x1D000;
    if (height_limit < object->z.w.i) {
        object->z.w.i = height_limit;
        object->flags14 = 0;
    }
}
