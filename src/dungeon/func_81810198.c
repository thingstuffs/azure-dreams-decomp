#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK func_800250B4();
extern void *func_80025350();
extern M2C_UNK func_800253C0();
extern s32 func_80026168();
extern s32 func_80026A64();
extern s32 func_8002845C();
extern void *func_8003FC64();
extern s32 func_8004A330();
extern M2C_UNK func_800DBF38();
extern s32 D_80029498;
extern s32 D_800814A0;
extern u8 D_80082E6A;


typedef struct S_80025198_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025198_0;   /* temp_v0 in func_80025198 */

typedef struct S_80025198_1_pre {
    u16 unk_00;
} S_80025198_1_pre;   /* the 0x2 bytes before temp_s2 in func_80025198, addressed as temp_s2[-1] */

typedef struct S_80025198_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} S_80025198_1;   /* temp_s2 in func_80025198 */

typedef struct S_80025198_2 {
    u8 unk_00;
    u8 unk_01;
} S_80025198_2;   /* temp_a1 in func_80025198 */

typedef struct S_80025198_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80025198_3;   /* temp_s0 in func_80025198 */

typedef struct S_80025198_4 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025198_4;   /* var_v1 in func_80025198 */

typedef struct S_80025198_5 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80025198_5;   /* temp_s5 in func_80025198 */

/* Allocate and initialize an object, cleaning up if any required resource is missing. */
void *func_80025198(s32 value_00, s32 value_10, s32 value_18, void *descriptor, s32 setup_arg) {
    s32 *display_ids;
    register s32 display_flags ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 resource_index;
    void *descriptor_data;
    void *state;
    s32 *globals_base;
    void *object;
    void *resource_cursor;

    object = func_8003FC64(0);
    if (object != NULL) {
        descriptor_data = descriptor;
        state = object + 0x20;
        ((S_80025198_0 *)object)->unk_20 = value_00;
        ((S_80025198_1 *)state)->unk_10 = value_10;
        ((S_80025198_1 *)state)->unk_14 = (s32) ((S_80025198_2 *)descriptor_data)->unk_01;
        ((S_80025198_1 *)state)->unk_18 = value_18;
        ((S_80025198_1 *)state)->unk_1C = (s32) ((S_80025198_2 *)descriptor_data)->unk_00;
        func_800250B4(state, descriptor_data, setup_arg);
        (*(s32 *)((u8 *)object + (0x10))) = 0;
        display_flags = 8;
        if (D_80082E6A != 1) {
            func_800DBF38();
            display_flags = 8;
        }
        display_ids = &D_80029498;
        ((S_80025198_1 *)state)->unk_2C = func_8004A330(display_flags, 0xEC, 0x64, 0xEC, 0x64, 0x50, 1, D_80029498);
        ((S_80025198_1 *)state)->unk_30 = func_8004A330(4, 0xEC, 0x64, 0xEC, 0x74, 0x50, 1, ((S_80025198_3 *)display_ids)->unk_04);
        ((S_80025198_1 *)state)->unk_34 = func_8004A330(0x10, 0xEC, 0x64, 0xEC, 0x84, 0x50, 1, ((S_80025198_3 *)display_ids)->unk_08);
        ((S_80025198_1 *)state)->unk_20 = func_80026168(object, ((S_80025198_1 *)state)->unk_14, ((S_80025198_1 *)state)->unk_04);
        ((S_80025198_1 *)state)->unk_24 = func_8002845C(object, ((S_80025198_1 *)state)->unk_14);
        ((S_80025198_1 *)state)->unk_28 = func_80026A64(object, ((S_80025198_1 *)state)->unk_14, ((S_80025198_1 *)state)->unk_04);
        globals_base = (s32 *) 0x80080000;
        resource_index = 0;
        resource_cursor = state;
check_resource:
        resource_index += 1;
        if (((S_80025198_4 *)resource_cursor)->unk_20 != 0) {
            goto next_resource;
        }
        func_800253C0(state);
        ((S_80025198_1_pre *)state)[-1].unk_00 = (u16) (((S_80025198_1_pre *)state)[-1].unk_00 | 0x8000);
        object = NULL;
        ((S_80025198_5 *)globals_base)->unk_14A0 |= 0x8000;
        goto done;
next_resource:
        resource_cursor += 4;
        if (resource_index < 3) {
            goto check_resource;
        }
    }
done:
    return object;
}
