# Aligned five-byte constant copy, r121 continuation 2

Measured at fixed GCC 2.6.3-G0, MAIN true func_804053A0, complete 328 B.
Retail copies five bytes with an aligned lw and signed lb, followed by sw/sb.
A u8[5] extern gives alignment one and generates lwl/lwr + swl/swr: 336 B,
regional 6 substitutions / 2 indels (capped compare, not a complete match).
A bounded struct { s32 word; s8 byte; } extern retains real four-byte alignment
and covers the five-byte source; ordinary memcpy(..., &object, 5) emits
328/328 exact bytes. The next constant starts eight bytes after this one.
No attribute, alias, asm, pin or unbounded literal page is involved.
Only this declaration changed between the two bounded candidates.
Full ELF symbol size and MAIN production window were independently checked.
This is not a compiler-family attribution or a general memcpy claim.
