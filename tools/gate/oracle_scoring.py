#!/usr/bin/env python3
"""Compact-oracle scoring core shared by codex_wave and oracle_census.

This module holds the scoring-relevant helpers that translate a dossier/main
config label into the explicit ``match.py`` argv used to evaluate a candidate.
It is deliberately small and free of CLI/routing/worker-dispatch code so that
``oracle_census`` can hash *this* file (not the whole ``codex_wave.py``) into its
content-addressed cache key: churn in codex_wave's provider routing no longer
invalidates every scored record.

``codex_wave`` re-imports the public names from here, so
``codex_wave.main_match_config_args`` keeps working unchanged.
"""

from __future__ import annotations

import re
import shlex


def main_match_config_args(raw_config: str) -> list[str]:
    """Translate dossier/main config labels into explicit match.py argv.

    Reviewed evaluations may carry either the compact overlay-style dialect
    (``2.8.1+-G0 -fno-schedule-insns``) or match.py's full banner
    (``gcc-2.8.1 -O2 aspsx=2.56 -fno-strength-reduce``).  Treating the latter
    banner as one gcc-flags string fed ``aspsx=2.56`` to cc1.  Parse both
    dialects and keep compiler, optimization, assembler version, and flags in
    their typed command-line fields.
    """
    tokens = shlex.split(str(raw_config))
    if not tokens:
        return []
    head, *tail = tokens
    head = re.sub(r"^gcc-", "", head)
    flags: list[str] = []
    if "+" in head:
        head, plus = head.split("+", 1)
        if plus:
            flags.append(plus)
    if head.endswith("-G0"):
        head = head[:-3]
        flags.append("-G0")
    args = ["--gcc", head]
    opt = None
    aspsx = None
    for token in tail:
        if re.fullmatch(r"-O[0-3s]", token):
            opt = token[1:]
        elif token.startswith("aspsx="):
            aspsx = token.split("=", 1)[1]
        elif token:
            flags.append(token)
    if opt:
        args += ["--opt", opt]
    if aspsx:
        args += ["--aspsx", aspsx]
    if flags:
        args += ["--gcc-flags", " ".join(flags)]
    return args
