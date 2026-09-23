#!/usr/bin/env python3
"""Shared classifier: was a lane cut off by a PROVIDER quota/capacity error, rather than genuinely
finishing with no win?

Round 76 bug: RESOURCE_EXHAUSTED/429 (agy/Gemini) and "at capacity"/"usage limit"/"rate limit" (codex)
errors were recorded as normal finishes.  Two consequences: (a) tools/lanes/ab_report.py counted them
status "ok" and folded them into the rates; (b) tools/lanes/served.py's tier guard (`serve_records`'s
`launched` flag) treated their served rows as served, so a pack builder never retried them after the
provider's reset.

Evidence (2026-09-23): agy.log for a quota-cut lane is a short, error-only file, e.g.
    error: Individual quota reached. ... Resets in 4h14m1s.
    AGY_ERROR: {"short_error":"RESOURCE_EXHAUSTED (code 429): ...","status":"RESOURCE_EXHAUSTED",...}
codex.log is a full transcript (model prose, diffs) that ends, on a capacity cut, with a bare line:
    ERROR: Selected model is at capacity. Please try a different model.
so the codex pattern is anchored to a line that STARTS with "ERROR:" (re.M) to keep prose mentioning
"capacity" or "rate limit" elsewhere in the transcript from ever matching.

This used to be approximated by tools/lanes/gemini_feed.sh's `mark_limit_cut`, a shell grep over
last_message.txt+agy.log that ONLY ran right after a batch that script itself launched, and SKIPPED any
lane that had even one file under out/ (a non-exact candidate) -- so it missed lanes launched outside
the feed loop and lanes that got as far as writing a candidate before the quota hit (r76_agy_b37_1,
r76_gemf_w_12: 2 out files each, RESOURCE_EXHAUSTED in agy.log, never marked).  Reading the logs
directly, here, means every caller sees the same answer regardless of which launcher ran the lane.

    from lane_limit import lane_hit_limit, agy_hit_limit, codex_hit_limit
"""
import re
from pathlib import Path

AGY_LIMIT_RE = re.compile(r"resource_exhausted|code 429|\bquota\b", re.IGNORECASE)
CODEX_LIMIT_RE = re.compile(r"^ERROR:.*(at capacity|usage limit|rate limit)", re.IGNORECASE | re.MULTILINE)
ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")   # codex >= 0.154 bolds/dims header and error lines
TAIL_BYTES = 65536


def agy_hit_limit(text):
    """True if an agy.log's text carries Gemini's quota/429 error."""
    return bool(text) and AGY_LIMIT_RE.search(text) is not None


def codex_hit_limit(text):
    """True if a codex.log's text carries a codex capacity/usage-limit/rate-limit ERROR line (ANSI
    codes stripped first, so a `\\x1b[2m` dim/bold wrapper before "ERROR:" doesn't hide the line start)."""
    return bool(text) and CODEX_LIMIT_RE.search(ANSI_RE.sub("", text)) is not None


def _tail(path, n=TAIL_BYTES):
    try:
        with path.open("rb") as fh:
            size = fh.seek(0, 2)
            fh.seek(max(0, size - n))
            return fh.read().decode("utf-8", "replace")
    except OSError:
        return ""


def lane_hit_limit(lane_dir):
    """True if lane_dir's agy.log or codex.log (tail-read, not searched) carries a provider quota or
    capacity error.  Independent of any limit_cut.txt a launcher script may or may not have written."""
    d = Path(lane_dir)
    if agy_hit_limit(_tail(d / "agy.log")):
        return True
    if codex_hit_limit(_tail(d / "codex.log")):
        return True
    return False
