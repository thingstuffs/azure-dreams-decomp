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

void func_800243E4(void *arg0) {
    S_800243E4_2 *temp_a0;
    Part *temp_a3;
    void *temp_v0;
    S_800243E4_0 *temp_v1;
    S_800243E4_3 *temp_v1_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_2A = 0x9;
        temp_v1->unk_60 = arg0;
        (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = &D_80024104;
        func_8004491C(temp_v0, D_80045340);
        temp_a3 = (*(Part **)((u8 *)temp_v0 + 0xC));
        temp_a3->field10 = 0x20;
        temp_a3->field6 = 0;
        temp_a3->flags14 = (u16) (temp_a3->flags14 | 0xC);
        temp_v1_2 = ((S_800243E4_1_pre *)arg0)[-1].unk_00;
        temp_a0 = (*(void **)((u8 *)temp_v0 + 8));
        temp_a0->unk_00 = (s32) temp_v1_2->unk_00;
        temp_a0->unk_04 = (s32) temp_v1_2->unk_04;
        temp_a0->unk_08 = (s32) temp_v1_2->unk_08;
        temp_a3 = (*(Part **)((u8 *)temp_v0 + 0xC));
        temp_a3->field1E = 0;
        temp_a3->field1C = 0;
        temp_a3->byteE = 0;
        temp_a3->byteD = 0;
        temp_a3->byteC = 0;
        (*(Copy12 *)((u8 *)temp_v0 + 0x92)) = *(Copy12 *)D_8002533C;
        temp_a3->ptr8 = (void *) (temp_v0 + 0x92);
    }
}
