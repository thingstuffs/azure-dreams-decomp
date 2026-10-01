#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8195AB84_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195AB84_2;   /* header in func_8195AB84 */

typedef struct S_8195AB84_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_8195AB84_3;   /* node in func_8195AB84 */

typedef struct S_8195AB84_4 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
    s16 unk_36;
} S_8195AB84_4;   /* tail in func_8195AB84 */


extern void func_80025B5C();
extern s32 func_8003FA44(s32);
extern void *func_8003FD64(s32, void *);

extern s32 D_80025C80;
extern u8 D_80028268[];
extern int D_800814A0;

/* Create 18 linked objects at the given position and angle, marking them for cleanup on failure. */
void *func_8195AB84(s16 x, s16 y, s16 z, s16 angle)
{
    void *objects[18];
    s32 i;
    S_8195AB84_2 *position;
    S_8195AB84_3 *node;
    S_8195AB84_4 *object_state;
    ObjectNodeHeader *obj;

    if (func_8003FA44(18) == 0) {
        return NULL;
    }
    for (i = 0; i < 18; i++) {
        objects[i] = func_8003FD64(18, (i != 0) ? objects[0] : (void *)&D_80083498);
        if (objects[i] != NULL) {
            ((ObjectNodeHeader *)objects[i])->unk_10 = &D_80025C80;
            position = ((ObjectNodeHeader *)objects[i])->unk_08;
            position->unk_02 = x;
            position->unk_06 = y;
            position->unk_0A = z;
            node = ((ObjectNodeHeader *)objects[i])->unk_0C;
            node->unk_16 = 0x400;
            node->unk_1A = angle + 0x400;
            node->unk_20 = 0x1000;
            node->unk_1E = 0x1000;
            node->unk_1C = 0x1000;
            node->unk_08 = &D_80028268[i * 16];
            node->unk_10 = 0x20;
            node->unk_14 |= 0xC;
            object_state = (S_8195AB84_4 *)((u8 *)objects[i] + 0x20);
            if (i != 0) {
                object_state->unk_20 = objects[0];
            }
            object_state->unk_30 = 0x10;
            object_state->unk_34 = angle;
            object_state->unk_36 = 7;
        } else {
            for (i--; i >= 0; i--) {
                obj = objects[i];
                D_800814A0 |= 0x8000;
                obj->flags |= 0x8000;
            }
            return NULL;
        }
    }
    func_80025B5C(objects[0], angle);
    return objects[0];
}
