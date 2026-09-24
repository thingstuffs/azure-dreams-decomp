# D_80080B6C declaration evidence

The private `candidate_small` trial changes the DCEC declaration from
`extern char D_80080B6C[16]` to `[2]`. Its direct comparison shows DCEC
retail-exact at default CDK through genuine ASPSX, and the combined candidate
can emit the target 156 words. That is **code-generation evidence**, not proof
that the original C object had exactly two bytes. This audit makes no source
or candidate edits.

## What the image and named uses establish

`config/slus_006.14.yaml:316` keeps this region in the `0x54240` binary asset.
`build_slus/config/generated/slus_006.14.undefined_syms.txt:563-564` names
both `D_80080B6C = 0x80080B6C` and the next symbol
`D_80080B70 = 0x80080B70`. With asset base `0x80080A40`, B6C is at
asset offset `0x12C`, retail file offset `0x5436C`. Its bytes are
`23 00 00 00`: an ASCII `#`, a NUL, and two zero bytes. B70 begins four bytes
later with `81 40 00 00`, a Shift-JIS two-byte sequence followed by zeros.
The named B70 start bounds the pre-B70 region to four bytes if these are
nonoverlapping objects. The image cannot distinguish `char[2]` followed by
two alignment bytes from `char[4]` initialized as `"#"` or another equivalent
layout. A sixteen-byte B6C object would span the separate B70 label and its
observed data, so the old `[16]` declaration is not an extent witness.

The bounded `src/slus/` and `include/` search found one named B6C use:
`src/slus/w_8004DCEC.c:6,14` declares `[16]` and passes its address to the
handler selected from `D_800714A4`. It neither reads nor writes B6C bytes.
The separate B70 users `src/slus/w_8004E9EC.c` and `w_8004EA70.c` copy its
first three or two bytes. EA70 explicitly says its 16-byte B70 declaration
was inflated to change address generation; that provisional size cannot be
used to infer B6C's size either.

The table bytes at `D_800714A4` (in `build_slus/assets/3E018.bin`, offset `0x6C8C`)
begin with pointers `0x80035208`, `0x80035234`, and `0x80035260`. These are
`func_80035208`, `func_80035234`, and `func_80035260` in the source. Each
takes a 32-bit value, passes it as `script_addr` or `value` to
`func_80035164`, which ultimately calls `func_80034F88`. That function stores
the value into two fields of `Rec_D_80082A38`; these wrappers do not scan for
a NUL. The current DCEC function-pointer typedef says `char *`, while the
three implementations say `s32`, a provisional source-type discrepancy with
the same 32-bit calling slot. The visible callback chain therefore supports
"address of initialized script/text data" and does not establish that a
two-byte C string is the complete object or that later runtime code never
reads or writes beyond the NUL.

## Declaration judgment

`[2]` has a concrete lower-bound rationale: the initialized `#` and NUL are
both present before the distinct B70 label. It is a plausible **trial view**
for DCEC, but the exact storage extent remains unresolved between two content
bytes and the four-byte region before B70. Do not present `[2]` as recovered
historical type or use its successful code generation alone to certify data
ownership. An incomplete `extern char D_80080B6C[]` expresses the unresolved
extent honestly, although its compiler emission would need a separate direct
check. Adding `const` is also premature: the scoped source shows no B6C write,
but the callback stores its address for later runtime use, and the present
handler prototype accepts mutable `char *`. Prefer retaining the byte-array
trial with this explicit uncertainty until a bounded downstream script-reader
audit or independent size provenance resolves it. No larger declaration,
padding, or colocated ownership should be inferred from this data.
