#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80024320(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern u8 D_80024230[];
extern u8 D_80045340[];
extern u8 D_800DEAE0[];

#ifndef NON_MATCHING
register u32 match_v0 ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
#endif

typedef struct S_818A4A64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818A4A64_0;   /* temp_v0 in func_818A4A64 */

typedef struct S_818A4A64_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818A4A64_1;   /* temp_s0 in func_818A4A64 */

typedef struct S_818A4A64_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4A64_2;   /* arg1 in func_818A4A64 */

typedef struct S_818A4A64_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4A64_3;   /* temp_v1 in func_818A4A64 */

/* Creates an object, initializes its rendering state, and copies its position. */
void *func_818A4A64(s32 context_value, S_818A4A64_2 *initial_position) {
    S_818A4A64_1 *render_state;
    S_818A4A64_0 *object;
    S_818A4A64_3 *position;
    u8 *call_data;
#ifdef NON_MATCHING
    u32 match_v0;
#endif

    object = func_8003FC64(0x212);
#ifndef NON_MATCHING
    call_data = (u8 *) 0x800E0000;
#else
    call_data = D_800DEAE0;
#endif
    if (object == NULL) {
        match_v0 = 0;
        func_80024320();
    }
#ifndef NON_MATCHING
    ASM_KEEP(call_data);   /* MATCH pin: retail immediate-load split depends on it */
    call_data -= 0x1520;
    match_v0 = 0x80020000;
    ASM_KEEP(match_v0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    match_v0 += 0x4230;
#else
    match_v0 = (u32) D_80024230;
#endif
    render_state = object->unk_0C;
    object->unk_10 = (M2C_UNK *) match_v0;
    object->unk_20 = context_value;
    render_state->unk_0E = 0;
    render_state->unk_0D = 0;
    render_state->unk_0C = 0;
    func_8003DB94(render_state, call_data, 0);
    match_v0 = render_state->unk_14;
    render_state->unk_1E = 0x1000;
    render_state->unk_1C = 0x1000;
    match_v0 |= 0xC;
    render_state->unk_14 = (u16) match_v0;
    func_8004491C(object, D_80045340);
    position = object->unk_08;
#ifndef NON_MATCHING
    __asm__ __volatile__("" : : "r"(initial_position));
#endif
    match_v0 = initial_position->unk_02;
    position->unk_02 = (u16) match_v0;
    match_v0 = initial_position->unk_06;
    position->unk_06 = (u16) match_v0;
    position->unk_0A = (u16) initial_position->unk_0A;
    return object;
}
