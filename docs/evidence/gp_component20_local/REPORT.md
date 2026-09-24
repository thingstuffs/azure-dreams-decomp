# Local `AD0` / `AD4` / `ADC` audit within historical `gp_01`

The historical 20-row component contains a bounded four-row **use cluster** for three GP-relative state locations. Retail directly accesses `D_80080AD0` as one byte, `D_80080AD4` as one halfword, and `D_80080ADC` as one word. The known source uses are confined to `w_8003E34C`, `w_8003E4FC`, `w_8003E758`, and `w_8003F5AC`; the [case-insensitive source scan](source_hits.txt) found no other direct named or numeric references in `src/slus` or `include/slus`. This is enough to scope a smaller ownership investigation. It does **not** identify one original C translation unit or prove separate object extents.

[receipt.json](receipt.json) records source, ledger, inventory, asset, ELF, and image hashes, exact recipe rows, registry `defs`, the access list, and initial bytes. The current built SLUS image and split asset matched retail when measured. `work/native_lane/gp_component20_local_audit/receipt.py` validates the four complete retail maps and regenerates that receipt without compiling anything.

| Retail function map | Words | Current split recipe | Lexical source body | Registry `defs` |
| --- | ---: | --- | --- | --- |
| [3E34C](retail_3e34c_20.dis), through `0x8003E398` | 20 | CDK 2.7.2, empty flags | `func_8003E34C` | 1: same symbol |
| [3E4FC](retail_3e4fc_132.dis), through `0x8003E708` | 132 | CDK 2.7.2, empty flags | `Control_CD` (one body; linked function is `func_8003E4FC`) | 2: `func_8003E39C`, `func_8003E4FC` |
| [3E758](retail_3e758_698.dis), through `0x8003F23C` | 698 | CDK 2.7.2 `-G32 -fno-expensive-optimizations` | `func_8003E758` (one body) | 5: `func_8003E70C`, `func_8003E758`, `func_8003F240`, `func_8003F5EC`, `func_8003F624` |
| [3F5AC](retail_3f5ac_10.dis), through `0x8003F5D0` | 10 | CDK 2.7.2, empty flags | `func_8003F5AC` | 1: same symbol |

The row registry's multi-symbol `defs` for `3E4FC` and `3E758` are **not lexical source function counts**. The neighboring named retail functions are distinct slices, and the source files each show only one top-level body. Likewise, the historical component's large `slus/code` and `slus/code2` files have lexical lower bounds of 156 and 24 bodies versus registry `defs` counts of 221 and 32. These registry entries cannot be summed into a proposed combined TU.

| Symbol and GP displacement | Direct retail sites | Observed width and action |
| --- | --- | --- |
| `AD0`, `316($gp)` | `0x8003E384` `sb $zero`; `0x8003EEE0` `lbu $v0` | 1-byte reset in `3E34C`; unsigned-byte check in `3E758` after `CdReadSync` |
| `AD4`, `320($gp)` | `0x8003E38C` `sh $zero`; `0x8003E66C` `sh $zero`; `0x8003F154` `sh $v0`; `0x8003F5B0` `lhu $v1` | 2-byte resets in `3E34C` and `Control_CD`, write of 1 in `3E758`, unsigned flag read in `3F5AC` |
| `ADC`, `328($gp)` | `0x8003E388` `sw $zero`; `0x8003E64C` `sw $v0`; `0x8003E6A4` `sw $s0` | 4-byte reset in `3E34C`; pointer-valued stores in `Control_CD` |

The three initial retail values are zero: `AD0` at SLUS file offset `0x542D0` is `00`, `AD4` at `0x542D4` is `00 00`, and `ADC` at `0x542DC` is `00 00 00 00`. All are inside the unchanged `54240_000074_0000C0.bin` split asset (`0x80080AB4`–`0x80080AFF`). ELF absolute labels also mark `AD2` and `AD8` between these addresses; `3E758` directly reads/writes the `AD2` halfword and writes the `AD8` word. The next named label after `ADC` is `AF0`. Labels and intervening zero bytes do not determine actual object sizes. The current source declarations are `s8/u8` for AD0, `s16/u16` for AD4, and `s32/void *` for ADC, matching the observed access widths but varying by consumer.

The four rows are not an isolated C group. `3E758` currently uses a different registered compiler flag recipe, and `3E34C`/`3E758` also use `D_800814D0`, which links onward to `code2`, `w_8003F2A4`, and `w_8003F368` in the historical map. The four functions are separated in retail order by other named functions. A **small data-state ownership candidate** for the directly observed AD0/AD4/ADC cells is therefore supportable as the next bounded question without grouping all 20 C rows. Any physical data owner must account for adjacent `AD2`/`AD8`, exact bytes, linker order, and genuine assembler behavior; this audit does not prove one owner, full image equality after extraction, or an original TU boundary. The scan excludes indirect pointer access and code outside these four retail slices, so it cannot establish exclusive runtime use.
