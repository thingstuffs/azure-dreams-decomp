typedef int s32;

s32 section_probe_left __attribute__((section(".sdata.section_probe_left"))) = 3;
s32 section_probe_right __attribute__((section(".sdata.section_probe_right"))) = 5;

s32 section_probe_read(void)
{
    return section_probe_left + section_probe_right;
}

void section_probe_write(s32 left, s32 right)
{
    section_probe_left = left;
    section_probe_right = right;
}

s32 *section_probe_left_address(void)
{
    return &section_probe_left;
}

s32 *section_probe_right_address(void)
{
    return &section_probe_right;
}
