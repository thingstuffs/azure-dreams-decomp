# CDK named small-data section capability

All three self-contained C variants compiled with stock GCC 2.7.2-cdk at its default flags and assembled successfully with stock maspsx, the private generic maspsx, and genuine ASPSX 2.79 `-q`. Each object contains the four intended load/store/address functions. No production file changed.

| C storage spelling | Object storage | Stock text relocations | Private generic and genuine text relocations |
| --- | --- | --- | --- |
| Two initialized `s32` globals | One `.sdata` section, 8 bytes | 6 `GPREL16` | 4 `GPREL16`, 2 `HI16`, 2 `LO16` |
| Two initialized globals with distinct `section(".sdata.<symbol>")` attributes | Two separate named sections, 4 bytes each | 6 `GPREL16` | 6 `HI16`, 6 `LO16`; no `GPREL16` |
| Two tentative common globals | Stock/generic materialize `.sbss`, 8 zero bytes; genuine retains two 4-byte common symbols | 6 `GPREL16` | 4 `GPREL16`, 2 `HI16`, 2 `LO16` |

The named-section compiler directives are `.section .sdata.section_probe_left,"aw",@progbits` and the analogous right section. Both lines survive unchanged in the stock/private generic processed stream and in the **actual bytes supplied to genuine ASPSX** (`raw/named_sections/genuine_input_bytes.s`). All three assemblers accept them and emit distinct data sections. The different text relocation choices show that section spelling affects GP-relative code generation. This probe establishes assembler and object-format capability; it does not test linker placement or a discontiguous-storage design.

The full [receipt](receipt.json) records directives from every stream, sections, symbols, relocations, accepted stages, hashes, and production snapshots. Raw C compiler output, processed assembly, genuine input, objects, and logs are under `raw/<variant>/`.
