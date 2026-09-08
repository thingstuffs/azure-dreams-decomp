#include "common.h"

typedef struct {
    u8 bytes[4];
} FourBytes;

extern u8 D_800133BA;
extern FourBytes D_8008925C;

/* get_player_homerank: Return the index of the player home value or the first zero in the four-byte table. */
s32 func_800B2834(void) {
    FourBytes home_values;
    register u8 *table_source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 table_page;
    s32 home_rank;
    s32 home_value;

    table_page = (s32)0x80090000;
    ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    table_source = (u8 *)(table_page - 0x6DA4);
    ASM_KEEP(table_source);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    __builtin_memcpy(&home_values, table_source, 4);
    ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    home_value = D_800133BA;
    home_rank = 0;
    while (home_values.bytes[home_rank] != 0) {
        if (home_values.bytes[home_rank] == home_value) {
            break;
        }
        home_rank++;
    }
    return home_rank;
}
