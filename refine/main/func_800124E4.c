#include "common.h"

typedef struct S_800254E4_0_pre {
    u8 * unk_00;
    u8 pad_04[0xC];
} S_800254E4_0_pre;   /* the 0x10 bytes before base in func_800254E4, addressed as base[-1] */

typedef struct S_800254E4_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x8];
    u8 * unk_34;
} S_800254E4_0;   /* base in func_800254E4 */



typedef struct TableEntry {
    s32 value;
    u8 pad[0x7C];
} TableEntry;

extern s32 func_80022138(void *arg0);
extern void func_80022FDC(void *arg0);
extern void func_8002311C(void *arg0);
extern void func_80025494(void *arg0);

extern u8 D_80024FAC[];
extern u8 D_80024FFC[];
extern TableEntry D_80083E98[];

/* Selects a record update based on its table entry and status and assigns data pointers. */
void func_800254E4(void *context)
{
    u8 *record;
    s32 table_index;
    s32 status;

    record = context;
    table_index = ((S_800254E4_0 *)record)->unk_28;
    context = record - 0x20;

    if (D_80083E98[table_index].value == 0) {
        status = func_80022138(context);
        context = 0;
        context = record - 0x20;
        if (status < 3) {
            ((S_800254E4_0 *)record)->unk_34 = D_80024FFC;
            func_80022FDC(context);
        } else {
            func_80025494(record);
            return;
        }
    } else {
        ((S_800254E4_0 *)record)->unk_34 = D_80024FFC;
        func_8002311C(context);
    }

    ((S_800254E4_0_pre *)record)[-1].unk_00 = D_80024FAC;
}
