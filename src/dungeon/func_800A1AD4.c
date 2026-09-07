#include "common.h"

extern u16 D_8008347E[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009A350();
s32 func_800A7338();
s32 func_800A7514();
s32 func_800BCB04();
extern u16 D_800DCE6C[];
extern u16 D_800DCE8C[];

s32 func_800A7234(s32 arg0, s32 arg1, s32 arg2, s16 *arg3, s16 *arg4, s16 *arg5) {
    u16 sp10;
    s32 initial;
    s32 initial_shifted_x;
    s32 initial_x;
    s32 distance;
    register s32 shifted_x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 shifted_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 scan_x1;
    s32 scan_y1;
    s32 scan_y2;
    register s32 scan_x2 ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    s32 count8;
    s32 dir8;
    register s32 count16 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 dir16 ASM_REG("$17");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 call_dir;
    register s32 call_x ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 call_y ASM_REG("$5");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 distance_z ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 empty_arg ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u16 *sp_arg ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 table_index8;
    s32 table_index16;
    register u32 scratch ASM_REG("$8");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 next_dir8;
    register s32 next_dir16 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 dir_seed ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 base_x ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 base_y ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    s32 base_z;
    u16 *dx;
    u16 *dy;
    register s32 raw_arg0 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 raw_arg1 ASM_REG("$17");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 raw_arg2 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 norm_arg1;
    register s32 found_result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 found_x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 found_y ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    raw_arg0 = arg0;
    raw_arg1 = arg1;
    raw_arg2 = arg2;
    ASM_KEEP_NV(raw_arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    initial_x = (s16)(raw_arg0 - 1);
    norm_arg1 = (s16)raw_arg1;
    initial = func_8009A350(initial_x, norm_arg1, 0, &sp10);
    base_x = raw_arg0;
    base_y = raw_arg1;
    base_z = raw_arg2;
    if ((initial << 0x10) != 0) {
        if (!(sp10 & 0x8820)) {
            initial_shifted_x = raw_arg0 << 0x10;
            distance = func_800BCB04((((initial_shifted_x >> 0xA) + 0x20) & 0xFFE0), ((norm_arg1 << 6) + 0x20) & 0xFFE0, (s16)(raw_arg2 - 0x20));
            if ((s16)distance < 0x200) {
                scratch = (u32)arg3;
                ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
                *(s16 *)scratch = (s16)raw_arg0;
                scratch = (u32)arg4;
                ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
                *(s16 *)scratch = (s16)raw_arg1;
                return func_800A7338(distance);
            }
        }
    }

    goto scan_start;
found:
    found_x = *dx;
    ASM_KEEP(found_x);   /* MATCH pin: load-bearing for the whole function shape */
    scratch = (u32)arg3;
    ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    found_x = base_x + found_x;
    *(s16 *)scratch = found_x;
    found_y = *dy;
    ASM_KEEP(found_y);   /* MATCH pin: load-bearing for the whole function shape */
    scratch = (u32)arg4;
    ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    found_y = base_y + found_y;
    *(s16 *)scratch = found_y;
    scratch = (u32)arg5;
    ASM_KEEP(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    found_result = 1;
    ASM_LIVE_SIBCALL_PIN(found_result, 1);   /* MATCH pin: retail keeps a computation the compiler would drop */
    *(s16 *)scratch = distance;
    func_800A7514(distance);
    return found_result;
scan_start:
    shifted_x = base_x << 0x10;
    scan_x1 = shifted_x >> 0x10;
    shifted_y = base_y << 0x10;
    scan_y1 = shifted_y >> 0x10;
    count8 = 0;
    dir_seed = D_8008347E[0];
    dir8 = dir_seed & 7;
loop8:
    call_x = scan_x1;
    call_y = scan_y1;
    call_dir = dir8;
    ASM_KEEP_NV(call_dir);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (((func_8009A350(call_x, call_y, call_dir, &sp10) << 0x10) == 0) || (sp10 & 0x8820)) {
        goto next8;
    }
    table_index8 = call_dir << 1;
    ASM_KEEP_NV(table_index8);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch = (u32)D_8006CCD8;
    dx = (u16 *)(table_index8 + scratch);
    distance_z = (s16)(base_z - 0x20);
    dy = (u16 *)((u8 *)D_8006CCE8 + table_index8);
    distance = func_800BCB04(((((scan_x1 + (s16)*dx) << 6) + 0x20) & 0xFFE0), ((((scan_y1 + (s16)*dy) << 6) + 0x20) & 0xFFE0), distance_z);
    if ((s16)distance < 0x200) {
        goto found;
    }
next8:
    count8 += 1;
    next_dir8 = dir8 + 1;
    dir8 = next_dir8 & 7;
    if (count8 < 8) {
        goto loop8;
    }

    count16 = 0;
    shifted_x = base_x << 0x10;
    scan_y2 = shifted_x >> 0x10;
    ASM_KEEP(scan_y2);   /* MATCH pin: keeps a statement from moving across a call/branch */
    dir_seed = D_8008347E[0];
    shifted_y = base_y << 0x10;
    scan_x2 = shifted_y >> 0x10;
    dir16 = dir_seed & 0xF;
loop16:
    empty_arg = hard_zero;
    table_index16 = dir16 << 1;
    ASM_KEEP_NV(table_index16);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch = (u32)D_800DCE6C;
    dx = (u16 *)(table_index16 + scratch);
    sp_arg = &sp10;
    ASM_KEEP_NV(sp_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch = (u32)D_800DCE8C;
    dy = (u16 *)(table_index16 + scratch);
    call_x = *dx;
    ASM_KEEP_NV(call_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    call_y = *dy;
    ASM_KEEP_NV(call_y);   /* MATCH pin: load-bearing for the whole function shape */
    call_x = (s16)(base_x + call_x - 1);
    call_y = (s16)(base_y + call_y);
    if (((func_8009A350(call_x, call_y, empty_arg, sp_arg) << 0x10) == 0) || (sp10 & 0x8820)) {
        goto next16;
    }
    call_x = (s16)*dx;
    call_y = (s16)*dy;
    call_x = (((scan_y2 + call_x) << 6) + 0x20) & 0xFFE0;
    call_y = (((scan_x2 + call_y) << 6) + 0x20) & 0xFFE0;
    distance = func_800BCB04(call_x, call_y, (s16)(base_z - 0x20));
    if ((s16)distance < 0x200) {
        goto found;
    }
next16:
    count16 += 1;
    next_dir16 = dir16 + 1;
    dir16 = next_dir16 & 0xF;
    if (count16 < 0x10) {
        goto loop16;
    }
    return 0;
}
