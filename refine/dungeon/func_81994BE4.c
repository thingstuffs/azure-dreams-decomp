#include "common.h"
#include "m2c_compat.h"

typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;
typedef struct {
    u8 pad0[6];
    s16 field6;
    void *ptr8;
    u8 byteC;
    u8 byteD;
    u8 byteE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Part;

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
void *func_8003FC64(s32);                       /* extern */
void func_8004491C(void *, void *);                /* extern */
extern M2C_UNK D_80024104;
extern u8 D_8002533C[12];


typedef struct S_800243E4_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
} S_800243E4_0;   /* temp_v1 in func_800243E4 */

typedef struct S_800243E4_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800243E4_1_pre;   /* the 0x18 bytes before arg0 in func_800243E4, addressed as arg0[-1] */

typedef struct S_800243E4_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800243E4_2;   /* temp_a0 in func_800243E4 */

typedef struct S_800243E4_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800243E4_3;   /* temp_v1_2 in func_800243E4 */

/* Create an object linked to its parent and initialize its position and part data. */
void func_800243E4(void *parent) {
    S_800243E4_2 *position;
    Part *part;
    void *object;
    S_800243E4_0 *state;
    S_800243E4_3 *parent_position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_2A = 0x9;
        state->unk_60 = parent;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &D_80024104;
        func_8004491C(object, D_80045340);
        part = (*(Part **)((u8 *)object + 0xC));
        part->field10 = 0x20;
        part->field6 = 0;
        part->flags14 = (u16) (part->flags14 | 0xC);
        parent_position = ((S_800243E4_1_pre *)parent)[-1].unk_00;
        position = (*(void **)((u8 *)object + 8));
        position->unk_00 = (s32) parent_position->unk_00;
        position->unk_04 = (s32) parent_position->unk_04;
        position->unk_08 = (s32) parent_position->unk_08;
        part = (*(Part **)((u8 *)object + 0xC));
        part->field1E = 0;
        part->field1C = 0;
        part->byteE = 0;
        part->byteD = 0;
        part->byteC = 0;
        (*(Copy12 *)((u8 *)object + 0x92)) = *(Copy12 *)D_8002533C;
        part->ptr8 = (void *) (object + 0x92);
    }
}
