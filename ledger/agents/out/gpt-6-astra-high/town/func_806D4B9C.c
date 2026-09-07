#include "common.h"

extern s32 func_80016D98(s32);
extern s32 func_800178A8(void *, s32, s32);
extern s32 func_80017904(void *, s32, s32);
extern s32 func_80017960(void *, void *, s32, s32);
extern void func_80018594(s32);
extern s32 func_8001868C(s32);
extern s32 func_80018868(s32, s32);
extern void func_800188E8(s32, s32, s32);

extern u8 D_80018A0C;
extern u8 D_80018B94[16];
extern u8 D_8001B333[];
extern u8 D_8001B3D2[];

/* Selects a response and advances the four-state counter for event 11. */
s32 func_80016B9C(s32 context, s32 unused, s32 event_id)
{
    register s32 saved_context ASM_REG("$19") = context;   /* MATCH pin: load-bearing for the whole function shape */
    register void *data_base ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u32 data_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u32 table_page;
    s32 result;
    s32 state_index;

    if (event_id == 1) {
        return (s32) D_8001B3D2;
    }

    result = func_80016D98(event_id);
    if (result != 0) {
        return result;
    }

    table_page = 0x80020000;
    ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
    data_page = 0x80020000;
    ASM_KEEP(data_page);   /* MATCH pin: keeps a constant in a register as retail does */
    data_base = (void *) (data_page - 0x75F4);
    result = func_80017960(data_base, (void *) (table_page - 0x746C),
                          saved_context, event_id);
    ASM_KEEP(saved_context);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state_index = func_80018868(0x990, 2);

    if (event_id != 0xB) {
        return result;
    }

    func_80018594(0x998);
    if (func_80017904(data_base, saved_context, 0xB) == 0) {
        if (func_8001868C(0x997) == 0) {
            state_index++;
            if (state_index == 4) {
                state_index = 0;
            }
            func_800188E8(0x990, state_index, 2);
        }
    }

    if (func_800178A8(&D_80018A0C, saved_context, event_id) == 0) {
        return result;
    }
    return (s32) D_8001B333;
}

