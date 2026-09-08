#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D9E4_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_8009D9E4_0;   /* arg0 in func_8009D9E4 */

typedef struct S_8009D9E4_1 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_8009D9E4_1;   /* arg1 in func_8009D9E4 */

/* Builds four corner vertices from a rectangle with position offsets. */
void func_8009D9E4(S_8009D9E4_0 *rectangle, S_8009D9E4_1 *vertices) {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;

    left = rectangle->unk_00 + rectangle->unk_04;
    vertices->unk_08 = left;
    vertices->unk_00 = left;
    right = rectangle->unk_08 + (rectangle->unk_00 + rectangle->unk_04);
    vertices->unk_0C = right;
    vertices->unk_04 = right;
    top = rectangle->unk_02 + rectangle->unk_06;
    vertices->unk_06 = top;
    vertices->unk_02 = top;
    bottom = rectangle->unk_0A + (rectangle->unk_02 + rectangle->unk_06);
    vertices->unk_0E = bottom;
    vertices->unk_0A = bottom;
}
