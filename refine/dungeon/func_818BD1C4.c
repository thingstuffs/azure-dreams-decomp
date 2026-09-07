#include "common.h"
#include "m2c_compat.h"

typedef struct S_818BD1C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BD1C4_0;   /* temp_v0 in func_818BD1C4 */

typedef struct S_818BD1C4_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_818BD1C4_1;   /* temp_v0_2 in func_818BD1C4 */

typedef struct S_818BD1C4_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818BD1C4_2;   /* temp_s0 in func_818BD1C4 */


typedef struct Copy24 {
    s32 words[6];
} Copy24;

extern void func_80024ABC(void) __attribute__((noreturn));
extern void func_80024AC0() __attribute__((noreturn));
extern void func_80024AC8() __attribute__((noreturn));
extern void func_80024B8C(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(s32);                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_80069EF8();                                /* extern */
extern M2C_UNK D_800248C0;
extern M2C_UNK D_80025E04;
extern M2C_UNK D_80045340;

/* Creates a colored object, copies its transform, and applies a vertical offset. */
s32 func_818BD1C4(s32 *owner_id, void *transform, s16 color_index, s32 y_offset) {
    s16 color_channel;
    u16 pos_y;
    s32 phase_value;
    s32 phase_rounded;
    register void *data_ptr ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    register u32 code_page ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    register s32 object_result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *unused_ptr;
    S_818BD1C4_2 *visual;
    void *object;
    S_818BD1C4_1 *state;
    register s32 saved_y_offset ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    saved_y_offset = y_offset;
    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((S_818BD1C4_0 *)object)->unk_10 = &D_800248C0;
        ((S_818BD1C4_0 *)object)->unk_20 = (s32) *owner_id;
        state = object + 0x20;
        state->unk_06 = 0;
        state->unk_08 = 0;
        visual = ((S_818BD1C4_0 *)object)->unk_0C;
        color_channel = color_index % 3;
        if (color_channel == 1) {
            goto case_1;
        }
        if (color_channel >= 2) {
            goto check_2;
        }
        if (color_channel == 0) {
            goto case_0;
        }
        data_ptr = visual;
        code_page = 0x80020000;
        ASM_KEEP(data_ptr);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_PAGEBASE_PIN(code_page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024AC8();

check_2:
        if (color_channel == 2) {
            goto case_2;
        }
        data_ptr = visual;
        code_page = 0x80020000;
        ASM_PAGEBASE_PIN(code_page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024AC8();

case_0:
        visual->unk_0C = 0x80;
        visual->unk_0E = 0;
        visual->unk_0D = 0;
        func_80024AC0();

case_1:
        visual->unk_0D = 0x80;
        visual->unk_0E = 0;
        func_80024ABC();

case_2:
        data_ptr = visual;
        ASM_KEEP(data_ptr);   /* MATCH pin: retail basic-block layout depends on it */
        visual->unk_0E = 0x80;
        visual->unk_0D = 0;
        visual->unk_0C = 0;
        ASM_CLOBBER("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
        data_ptr = visual;
        visual->unk_12 = 0x7DCF;
        visual->unk_14 = (u16) (visual->unk_14 | 0xC);
        visual->unk_10 = (u16) (visual->unk_10 | 0x60);
        visual->unk_14 = (u16) (visual->unk_14 | 0x100);
        func_8003DB94(data_ptr, &D_80025E04, 0);
        phase_rounded = func_80069EF8();
        phase_value = phase_rounded;
        if (phase_value < 0) {
            phase_rounded = phase_value + 0xFFF;
        }
        visual->unk_1A = (s16) (phase_value - ((phase_rounded >> 0xC) << 0xC));
        visual->unk_1E = 0x2000;
        visual->unk_1C = 0x2000;
        func_8004491C(object, &D_80045340);
        data_ptr = ((S_818BD1C4_0 *)object)->unk_08;
        (*(Copy24 *)((u8 *)data_ptr + 0)) =
            (*(Copy24 *)((u8 *)transform + 0));
        pos_y = (*(u16 *)((u8 *)data_ptr + 0xA));
        object_result = (s32) object;
        pos_y -= saved_y_offset;
        ASM_KEEP(object_result);   /* MATCH pin: load-bearing for the whole function shape */
        (*(u16 *)((u8 *)data_ptr + 0xA)) = pos_y;
        func_80024B8C();
    }
    return 0;
}
