#include "common.h"

typedef struct {
    u8 pad[8];
    s32 value;
} TownRecord;

extern TownRecord D_8001791C[];
extern s32 D_80018054[];
extern u8 *D_8001E950;
extern void func_8001E578(s32);

/* Return the player's table value, calling func_8001E578 if its town record value is zero. */
s32 func_8001B5A0(void) {
    u8 **player_ptr = &D_8001E950;
    u8 *player = *player_ptr;
    u8 player_index = player[4];

    if (D_8001791C[player_index].value == 0) {
        func_8001E578(0x401);
    }

    {
        u8 *updated_player = *player_ptr;
        u8 updated_index = updated_player[4];

        return D_80018054[updated_index];
    }
}
