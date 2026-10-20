#include "common.h"
void func_8003D548(s32);                     /* extern */
void func_80400EF8(void);                            /* extern */
extern s32 D_80010208;
extern s16 D_80011F48;
extern s8 D_8008CA34;

typedef struct S_8001EC4C_0 {
    u8 pad_00[0x44];
    s32 unk_44;
} S_8001EC4C_0;   /* arg0 in card_dev_start_next_screen */

/* Set the state from the object and select an action from the global flag. */
void card_dev_start_next_screen(S_8001EC4C_0 *object) {
    s32 actionId;
    s16 state;

    D_8008CA34 = 2;
    func_80400EF8();
    state = 1;
    if (object->unk_44 == 0) {
        state = 3;
    }
    D_80011F48 = state;
    actionId = 4;
    if (D_80010208 != 0) {
        actionId = 5;
    }
    func_8003D548(actionId);
}
