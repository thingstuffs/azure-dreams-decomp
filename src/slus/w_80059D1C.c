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

/* For each of the D_800869B4[0] active entries in D_80085FA8, set field_2C to 1
 * and clear field_00 (offset 0) of the entry. */
void func_80059D1C(void) {
    int one;
    unsigned int i;
    unsigned int count;

    if (D_800869B4[0] != 0) {
        i = 0;
        one = 1;
        count = D_800869B4[0];
        do {
            D_80085FA8[i].field_2C = one;
            D_80085FA8[i].field_00 = 0;
            i++;
        } while (i < count);
    }
}
