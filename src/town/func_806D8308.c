typedef unsigned short u16;

extern u16 D_80019114;

/* Advance the counter modulo eight. */
void advance_counter_modulo_eight(void)
{
    D_80019114 = (D_80019114 + 1) & 7;
}
