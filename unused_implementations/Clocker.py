import time
import pprint as pp
DEBUG = True
last_call_tag = None
time_log = dict()


def log_step(tag, terminate=False):
    global time_log
    global last_call_tag
    global DEBUG
    if not terminate:
        tag = str(tag)
        time_log[tag] = dict()
        time_log[tag]["tag"] = tag
    if last_call_tag is not None:
        time_log[last_call_tag]["end"] = time.time()
        time_log[last_call_tag]["duration"] = time_log[last_call_tag]["end"] - time_log[last_call_tag]["start"]
        if DEBUG:
            pp.pprint("Step " + last_call_tag + " took " + str(time_log[last_call_tag]["duration"]))
    if not terminate:
        time_log[tag]["start"] = time.time()
        last_call_tag = tag


def log_by_duration():
    global time_log
    log_step("done", True)
    sum_durations = 0
    subroutines = list(time_log.values())
    subroutines.sort(key=lambda x: x["duration"])
    for s in subroutines:
        sum_durations += s["duration"]
    for s in subroutines:
        s["percentage"] = str(round(s["duration"] / sum_durations * 100)) + "%"
    if DEBUG:
        pp.pprint(subroutines)
