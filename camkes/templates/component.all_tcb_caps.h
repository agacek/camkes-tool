#pragma once

#define ALL_TCB_CAPS_MIN /*? hex(min(cap_space.all_tcb_caps_slots)) ?*/
#define ALL_TCB_CAPS_MAX /*? hex(max(cap_space.all_tcb_caps_slots)) ?*/
#define ALL_TCB_CAPS_NUM (ALL_TCB_CAPS_MAX - ALL_TCB_CAPS_MIN + 1)

static char *cap_names[] = {
/*- for (idx, cap) in cap_space.cnode.slots.items() -*/
/*- if cap -*/
  [/*? hex(idx) ?*/] = "/*? cap.referent.name ?*/",
/*- endif -*/
/*- endfor -*/
};
