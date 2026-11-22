"""common.append_jsonl (flock append) composed with atomic_io.write_text (rename replace under the same lock)."""
import fcntl, json, os, sys, tempfile, threading, time, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import atomic_io, common


class Compose(unittest.TestCase):
    def test_replace_waits_for_the_append_lock(self):
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "j.jsonl"; p.write_text('{"old":1}\n')
            fd = os.open(p, os.O_RDONLY); fcntl.flock(fd, fcntl.LOCK_EX)
            t = threading.Thread(target=atomic_io.write_text, args=(p, '{"new":1}\n')); t.start()
            time.sleep(0.4)
            self.assertTrue(t.is_alive(), "replace must wait while an appender holds the lock")
            self.assertEqual(p.read_text(), '{"old":1}\n')
            os.close(fd); t.join(10)
            self.assertEqual(p.read_text(), '{"new":1}\n')

    def test_appends_and_replaces_interleaved_stay_parseable(self):
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "j.jsonl"; p.write_text("")
            stop = []
            def appender(tag):
                for i in range(150): common.append_jsonl(p, {"a": tag, "i": i})
            def replacer():
                while not stop: atomic_io.write_text(p, p.read_text()); time.sleep(0.001)
            ts = [threading.Thread(target=appender, args=(k,)) for k in range(3)]; r = threading.Thread(target=replacer)
            r.start(); [t.start() for t in ts]; [t.join() for t in ts]; stop.append(1); r.join()
            rows = [json.loads(l) for l in p.read_text().splitlines()]   # no torn line
            self.assertLessEqual(len(rows), 450)   # a read-modify-write replace may drop rows appended meanwhile (inherent)
            self.assertGreater(len(rows), 0)
            self.assertEqual(list(Path(d).glob(".*.tmp")), [])


if __name__ == "__main__":
    unittest.main()
