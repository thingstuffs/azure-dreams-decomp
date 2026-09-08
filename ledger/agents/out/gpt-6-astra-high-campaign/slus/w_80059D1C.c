#include "common.h"

/* --- gcc 2.8.x translation unit (see src/code2.c sibling func_8005C818, same
   D_80085FA8 array-of-structs / D_800869B4 count idiom) --- */

extern int D_800869B4[3];

typedef struct {
    int field_00;
    char pad_04[0x2C - 0x04];
    int field_2C;
    char pad_30[0x50 - 0x30];
} Struct_80059D1C_80085FA8;

extern Struct_80059D1C_80085FA8 D_80085FA8[];

/* Sets field_2C to 1 and clears field_00 for each active entry. */
void func_80059D1C(void) {
    int one;
    unsigned int entry_index;
    unsigned int entry_count;

    if (D_800869B4[0] != 0) {
        entry_index = 0;
        one = 1;
        entry_count = D_800869B4[0];
        do {
            D_80085FA8[entry_index].field_2C = one;
            D_80085FA8[entry_index].field_00 = 0;
            entry_index++;
        } while (entry_index < entry_count);
    }
}
