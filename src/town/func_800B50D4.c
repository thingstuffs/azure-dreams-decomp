#include "common.h"

typedef struct {
    u8 bytes[4];
} FourBytes;

extern FourBytes D_8008925C;

/* get_player_homerank: Return the index of the player home value or the first zero in the four-byte table. */
s32 get_player_homerank(void) {
    FourBytes home_values;
    s32 home_rank;
    s32 home_value;

    home_values = D_8008925C;
    home_value = *(u8 *)0x800133BA;
    home_rank = 0;
    while (home_values.bytes[home_rank] != 0) {
        if (home_values.bytes[home_rank] == home_value) {
            break;
        }
        home_rank++;
    }
    return home_rank;
}
