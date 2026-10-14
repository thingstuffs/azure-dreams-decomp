#ifndef SLUS_SPADSTK_H
#define SLUS_SPADSTK_H

/* Scratchpad stack switch: Sony's SetSpadStack / ResetSpadStack sample macros (PsyQ Run-time Library 4.4, July 1997,
 * psx/sample/graphics/TEXADDR/WAVE/SPADSTK.H, SPAD_STACK_ADDR 0x1f8003fc), in the game's adapted form: the stack drops by
 * 4 bytes instead of the sample's 24, and the reset ends with an explicit nop after the reload. The asm volatile
 * statements are genuine source (owner ruling 2026-10-14, as the OT-link macro): they are what kept the scheduler from
 * moving the prologue save past the switch, which the earlier register-global text imitated with -fno-schedule-insns2
 * (r118_sonnet_open4; slus/w_8004CAA0). The port build has no scratchpad stack to switch to, so the macros are empty. */
#define SPAD_STACK_ADDR 0x1f8003fc

#ifndef NON_MATCHING
#define SetSpadStack(addr) { \
    __asm__ volatile ("move $8,%0"     ::"r"(addr):"$8","memory"); \
    __asm__ volatile ("sw $29,0($8)"   ::         :"$8","memory"); \
    __asm__ volatile ("addiu $8,$8,-4" ::         :"$8","memory"); \
    __asm__ volatile ("move $29,$8"    ::         :"$8","memory"); \
}

#define ResetSpadStack() { \
    __asm__ volatile ("addiu $29,$29,4" :::"$29","memory"); \
    __asm__ volatile ("lw $29,0($29)"   :::"$29","memory"); \
    __asm__ volatile ("nop"); \
}
#else
#define SetSpadStack(addr) { (void)(addr); }
#define ResetSpadStack() { }
#endif

#endif
