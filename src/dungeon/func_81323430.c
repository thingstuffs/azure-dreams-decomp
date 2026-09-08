#include "common.h"


typedef struct {
    u8 bytes[12];
} Packed12;

typedef struct {
    u8 pad[0xA];
    u16 count;
} DungeonState;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80044BB0[];
extern Packed12 D_80077818;
extern DungeonState D_80083460;
extern u8 D_8016A9FC[];


typedef struct S_8016AC30_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016AC30_0;   /* position in func_8016AC30 */

typedef struct S_8016AC30_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016AC30_1;   /* primitive in func_8016AC30 */

/* Allocate and initialize a dungeon object, then increment the object count. */
void func_8016AC30(void) {
    void *object;
    S_8016AC30_0 *position;
    S_8016AC30_1 *primitive;

    object = func_8003FC64(0x12);
    if (object != 0) {
        (*(void * *)((u8 *)object + 0x10)) = D_8016A9FC;
        func_8004491C(object, D_80044BB0);

        do { position = (*(void * *)((u8 *)object + 8)); } while (0);
        position->unk_0A = 0;
        position->unk_06 = 0;
        position->unk_02 = 0;

        primitive = (*(void * *)((u8 *)object + 0xC));
        primitive->unk_1E = 0;
        primitive->unk_1C = 0;
        primitive->unk_0E = 0;
        primitive->unk_0D = 0;
        primitive->unk_0C = 0;

        (*(Packed12 *)((u8 *)object + 0x4C)) = D_80077818;
        primitive->unk_08 = (u8 *)object + 0x4C;
        D_80083460.count++;
    }
}
