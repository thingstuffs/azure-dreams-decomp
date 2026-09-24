# Registered-recipe CD baseline

Freshly compiled stock objects for all seven unchanged whole sources match both the active pinned objects and their complete retail function extents, with no relocation masks. The private generic assembler and genuine ASPSX 2.79 `-q` emit identical function tokens on every row. Both differ from stock and retail; this is a direct assembly baseline, not an ownership or C-source verdict.

| Row | Registered compiler flags | Stock/retail words | Generic/genuine words | Stock GP-extern relocations | Canonical aligned subs/indels |
| --- | --- | ---: | ---: | ---: | ---: |
| `w_8003E34C` | CDK, empty | 20 | 24 | 4 | 4/4 |
| `w_8003E4FC` | CDK, empty | 132 | 134 | 3 | 13/2 |
| `w_8003E758` | CDK, `-G32 -fno-expensive-optimizations` | 698 | 730 | 32 | 90/32 |
| `w_8003F2A4` | 2.6.3, `-fno-schedule-insns` | 31 | 32 | 3 | 6/1 |
| `w_8003F368` | 2.7.2, empty | 113 | 122 | 9 | 13/9 |
| `w_8003F5AC` | CDK, empty | 10 | 11 | 1 | 1/1 |
| `w_8003F624` | 2.7.2, empty | 25 | 26 | 1 | 1/1 |

Every stock-to-generic comparison contains extern-GP regions. The receipt retains other aligned region classes without assigning a source-level cause. Genuine assembly had no errors or unresolved masks. Length changes are scored with the exact canonical `aligned_word_stats` helper extracted from `tools/gate/match.py`, which `tools/gate/aligned_score.py` calls; the receipt records hashes of both tools and the selected AST. Raw assembly, objects, LNK outputs, and resolved/retail word binaries are in `raw/<stem>/`. Production input hashes match before and after the probe.
