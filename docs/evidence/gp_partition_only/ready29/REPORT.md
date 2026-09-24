# Private ready29 collector rehearsal

`python3 work/native_lane/gp_ready29_collectors/probe.py` completed with `MATCH`.
The retained `stage/` is a detached clone of the frozen ready26 SLUS build. No
production source, manifest, partition plan, tool, or object changed.

The private manifest has 33 modules and 860 active physical C objects while
projecting the same 884 logical rows. It preserves the prior 31 modules and
their partition parts. Two new destinations opt in with `partition_only: true`
and `members: []`:

| Destination | Canonical parent functions | Original recipe | Storage |
| --- | --- | --- | --- |
| `accessors_814c8` | `code.c` F5D4/F5E0 | 2.7.2 | Ordinary `int D_800814C8 = 0` at asset `54240` offset `0xA88`, VMA `0x800814C8`, four bytes |
| `table_counters_b1b_b1c` | `code2.c` 48DA0 | 2.8.1 | `u8 D_80080B1B` / `D_80080B1C` at offsets `0xDB` / `0xDC`, named `.sdata` pieces aligned to one byte |

The new aggregators contain only those definitions/declarations and includes
of generated parts. The rendered function text matches the current canonical
parent bodies and the bounded direct-probe sources. The original parent recipe
and raw-source provenance remain in the partition plan. The copied F624 member
has one comment corrected to describe the observed `D_800814D3[2]` address
view; its C expressions and compiled tokens are unchanged. The frozen ready26
stage and combined8 candidate were not edited.

All 860 active C objects were invalidated and rebuilt with the pinned guarded
generic assembler. Normal generated Ninja linking did not rebuild any object.
The full image and generated SHA1 gate match retail; image SHA-256 is
`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.
Of 856 physical objects outside the two changed parent objects and two new
owners, none changed function tokens, allocated data, or canonical relocations.
There were 266 raw ELF hash differences with no semantic difference under
those comparisons. The `code.c` remainder has 149 unchanged functions/1218
words, and `code2.c` has 21 unchanged functions/213 words. Complete connected
emitted-function coverage is 198 functions with no duplicate physical owner.

Fresh generic-versus-built, generic-versus-genuine ASPSX 2.79, and retail
comparisons pass for all 29 selected functions and 1949 words with zero masks:
18 ready18 functions/891 words, eight CD functions/1041 words, and the three
new collector functions/17 words. Linked data checks pass for all 70 records:
56 ready18, 11 CD, and the new three. Each new symbol resolves once at the
recorded non-ABS VMA, has the exact asset and image bytes, and is absent from
the private filtered ABS assignment script. The two byte counters own only
their two named one-byte pieces; the surrounding table and gap bytes remain
outside those records.

The reproducible script, `input_pins.json`, `receipt.json`, logs, and retained
`stage/` are all under this private directory. The pins cover the frozen
ready26 stage graph and objects, the three frozen partition-only build tools,
candidate C sources, assembler, proof helpers, and production code/config/build
bytes and objects. Final validation rechecks every pin. This is a private
generated full-SLUS link and ownership rehearsal, not a production activation
or whole-program generic assembler claim.
