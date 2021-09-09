#ifndef NO_MONITORING
#include "UVWMonitor.h"
#include <stdbool.h>
/* Declare variables for monitoring */
bool uvwState0 = 0;
bool uvwState1 = 0;
bool uvwState2 = 0;
bool uvwState3 = 0;
bool uvwState4 = 0;
bool uvwState5 = 0;
bool uvwState6 = 0;
bool uvwState7 = 0;
bool uvwState8 = 0;
bool uvwState9 = 0;
bool uvwState10 = 0;
bool uvwState11 = 0;
bool uvwState12 = 0;
bool uvwState13 = 0;
bool uvwState14 = 0;
bool uvwState15 = 0;
bool uvwState16 = 0;
bool uvwState17 = 1;
bool uvwState18 = 0;
bool uvwState19 = 0;
bool uvwState20 = 1;
bool uvwState21 = 1;
struct bufType {
  uint32_t b0p0;
  uint32_t b1p0;
  uint32_t b2p0;
  uint32_t b3p0;
  uint32_t b4p0;
  uint32_t b5p0;
  uint32_t b6p0;
  uint32_t b7p0;
  uint32_t b8p0;
  uint32_t b9p0;
  uint32_t b10p0;
  uint32_t b11p0;
  uint32_t b12p0;
  uint32_t b13p0;
  uint32_t b14p0;
  uint32_t b15p0;
  uint32_t b16p0;
  uint32_t b18p0;
  uint32_t b19p0;
} buf = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint32_t b17p0 = 0;
const uint32_t b20p0 = 0;
const uint32_t b21p0 = 0;

void monitorUpdate(uint32_t apValues) {
  bool a1 = apValues & (1 << 0);
  (void)(a1); // Avoid symbol ununsed warning.
  bool a2 = apValues & (1 << 1);
  (void)(a2); // Avoid symbol ununsed warning.
  bool b1 = apValues & (1 << 2);
  (void)(b1); // Avoid symbol ununsed warning.
  bool b2 = apValues & (1 << 3);
  (void)(b2); // Avoid symbol ununsed warning.
  bool c1 = apValues & (1 << 4);
  (void)(c1); // Avoid symbol ununsed warning.
  bool c2 = apValues & (1 << 5);
  (void)(c2); // Avoid symbol ununsed warning.
  bool d1 = apValues & (1 << 6);
  (void)(d1); // Avoid symbol ununsed warning.
  bool d2 = apValues & (1 << 7);
  (void)(d2); // Avoid symbol ununsed warning.
  bool m = apValues & (1 << 8);
  (void)(m); // Avoid symbol ununsed warning.
  bool nextUVW0 = 0;
  if (uvwState0 && (1)) {
    nextUVW0 = 1;
  }
  else if (uvwState1 && ((a1 && a2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState2 && ((!a1||a2) && (a1||!a2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState3 && ((b1 && b2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState4 && ((!b1||b2) && (b1||!b2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState5 && ((c1 && c2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState6 && ((!c1||c2) && (c1||!c2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState7 && ((d1 && d2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState8 && ((!d1||d2) && (d1||!d2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState9 && ((a1 && !a2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState10 && ((!a1||!a2) && (a1||a2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState11 && ((b1 && !b2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState12 && ((!b1||!b2) && (b1||b2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState13 && ((c1 && !c2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState14 && ((!c1||!c2) && (c1||c2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState15 && ((d1 && !d2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState16 && ((!d1||!d2) && (d1||d2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState17 && ((c1 && !c2 && d1 && !d2) || (!c1 && c2 && !d1 && d2) || (b1 && !b2 && c1 && !c2) || (!b1 && b2 && !c1 && c2) || (a1 && !a2 && d1 && !d2) || (a1 && !a2 && b1 && !b2) || (!a1 && a2 && !d1 && d2) || (!a1 && a2 && !b1 && b2))) {
    nextUVW0 = 1;
    buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState18 && ((m) && (a1||!a2))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState19 && ((!a2||!m) && (a1||!a2) && (a1||!m))) {
    nextUVW0 = 1;
    buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState20 && ((m) && (!a1||a2))) {
    nextUVW0 = 1;
    buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  else if (uvwState21 && ((m) && (!a1||a2) && (a1||!a2))) {
    nextUVW0 = 1;
    buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  bool nextUVW1 = 0;
  if (uvwState1 && ((a1||!a2))) {
    nextUVW1 = 1;
  }
  else if (uvwState17 && ((!a1 && !a2))) {
    nextUVW1 = 1;
    buf.b1p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW2 = 0;
  if (uvwState2 && ((a1||!a2))) {
    nextUVW2 = 1;
  }
  else if (uvwState1 && ((a1))) {
    nextUVW2 = 1;
    buf.b2p0 = buf.b1p0 | (apValues << 9);
  }
  bool nextUVW3 = 0;
  if (uvwState3 && ((b1||!b2))) {
    nextUVW3 = 1;
  }
  else if (uvwState17 && ((!b1 && !b2))) {
    nextUVW3 = 1;
    buf.b3p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW4 = 0;
  if (uvwState4 && ((b1||!b2))) {
    nextUVW4 = 1;
  }
  else if (uvwState3 && ((b1))) {
    nextUVW4 = 1;
    buf.b4p0 = buf.b3p0 | (apValues << 9);
  }
  bool nextUVW5 = 0;
  if (uvwState5 && ((c1||!c2))) {
    nextUVW5 = 1;
  }
  else if (uvwState17 && ((!c1 && !c2))) {
    nextUVW5 = 1;
    buf.b5p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW6 = 0;
  if (uvwState6 && ((c1||!c2))) {
    nextUVW6 = 1;
  }
  else if (uvwState5 && ((c1))) {
    nextUVW6 = 1;
    buf.b6p0 = buf.b5p0 | (apValues << 9);
  }
  bool nextUVW7 = 0;
  if (uvwState7 && ((d1||!d2))) {
    nextUVW7 = 1;
  }
  else if (uvwState17 && ((!d1 && !d2))) {
    nextUVW7 = 1;
    buf.b7p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW8 = 0;
  if (uvwState8 && ((d1||!d2))) {
    nextUVW8 = 1;
  }
  else if (uvwState7 && ((d1))) {
    nextUVW8 = 1;
    buf.b8p0 = buf.b7p0 | (apValues << 9);
  }
  bool nextUVW9 = 0;
  if (uvwState9 && ((a1||a2))) {
    nextUVW9 = 1;
  }
  else if (uvwState17 && ((!a1 && a2))) {
    nextUVW9 = 1;
    buf.b9p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW10 = 0;
  if (uvwState10 && ((a1||a2))) {
    nextUVW10 = 1;
  }
  else if (uvwState9 && ((a1))) {
    nextUVW10 = 1;
    buf.b10p0 = buf.b9p0 | (apValues << 9);
  }
  bool nextUVW11 = 0;
  if (uvwState11 && ((b1||b2))) {
    nextUVW11 = 1;
  }
  else if (uvwState17 && ((!b1 && b2))) {
    nextUVW11 = 1;
    buf.b11p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW12 = 0;
  if (uvwState12 && ((b1||b2))) {
    nextUVW12 = 1;
  }
  else if (uvwState11 && ((b1))) {
    nextUVW12 = 1;
    buf.b12p0 = buf.b11p0 | (apValues << 9);
  }
  bool nextUVW13 = 0;
  if (uvwState13 && ((c1||c2))) {
    nextUVW13 = 1;
  }
  else if (uvwState17 && ((!c1 && c2))) {
    nextUVW13 = 1;
    buf.b13p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW14 = 0;
  if (uvwState14 && ((c1||c2))) {
    nextUVW14 = 1;
  }
  else if (uvwState13 && ((c1))) {
    nextUVW14 = 1;
    buf.b14p0 = buf.b13p0 | (apValues << 9);
  }
  bool nextUVW15 = 0;
  if (uvwState15 && ((d1||d2))) {
    nextUVW15 = 1;
  }
  else if (uvwState17 && ((!d1 && d2))) {
    nextUVW15 = 1;
    buf.b15p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW16 = 0;
  if (uvwState16 && ((d1||d2))) {
    nextUVW16 = 1;
  }
  else if (uvwState15 && ((d1))) {
    nextUVW16 = 1;
    buf.b16p0 = buf.b15p0 | (apValues << 9);
  }
  bool nextUVW17 = 0;
  if (uvwState17 && (1)) {
    nextUVW17 = 1;
  }
  bool nextUVW18 = 0;
  if (uvwState18 && (1)) {
    nextUVW18 = 1;
  }
  else if (uvwState17 && ((!a1 && a2 && m))) {
    nextUVW18 = 1;
    buf.b18p0 = b17p0 | (apValues << 0);
  }
  bool nextUVW19 = 0;
  if (uvwState19 && ((a1||!a2))) {
    nextUVW19 = 1;
  }
  else if (uvwState20 && ((a1 && !a2 && m))) {
    nextUVW19 = 1;
    buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  }
  else if (uvwState21 && ((a1 && !a2 && m))) {
    nextUVW19 = 1;
    buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  bool nextUVW20 = 0;
  if (uvwState20 && ((!a1||a2))) {
    nextUVW20 = 1;
  }
  bool nextUVW21 = 0;
  if (uvwState21 && ((a1||!a2))) {
    nextUVW21 = 1;
  }
  uvwState0 = nextUVW0;
  uvwState1 = nextUVW1;
  uvwState2 = nextUVW2;
  uvwState3 = nextUVW3;
  uvwState4 = nextUVW4;
  uvwState5 = nextUVW5;
  uvwState6 = nextUVW6;
  uvwState7 = nextUVW7;
  uvwState8 = nextUVW8;
  uvwState9 = nextUVW9;
  uvwState10 = nextUVW10;
  uvwState11 = nextUVW11;
  uvwState12 = nextUVW12;
  uvwState13 = nextUVW13;
  uvwState14 = nextUVW14;
  uvwState15 = nextUVW15;
  uvwState16 = nextUVW16;
  uvwState17 = nextUVW17;
  uvwState18 = nextUVW18;
  uvwState19 = nextUVW19;
  uvwState20 = nextUVW20;
  uvwState21 = nextUVW21;
}

#endif
/* Decoding information for the buffers:
   -------------------------------------

 - UVW state 0 with LTL subformula (Polish notation):
    Bits 0 to 17: previous buffer
    Bits 18 to 26: propositions
    Bits 27 to 31: incoming transition
       -> Value 0 for transition from UVW state 1
       -> Value 1 for transition from UVW state 2
       -> Value 2 for transition from UVW state 3
       -> Value 3 for transition from UVW state 4
       -> Value 4 for transition from UVW state 5
       -> Value 5 for transition from UVW state 6
       -> Value 6 for transition from UVW state 7
       -> Value 7 for transition from UVW state 8
       -> Value 8 for transition from UVW state 9
       -> Value 9 for transition from UVW state 10
       -> Value 10 for transition from UVW state 11
       -> Value 11 for transition from UVW state 12
       -> Value 12 for transition from UVW state 13
       -> Value 13 for transition from UVW state 14
       -> Value 14 for transition from UVW state 15
       -> Value 15 for transition from UVW state 16
       -> Value 16 for transition from UVW state 17
       -> Value 17 for transition from UVW state 18
       -> Value 18 for transition from UVW state 19
       -> Value 19 for transition from UVW state 20
       -> Value 20 for transition from UVW state 21
 - UVW state 1 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 2 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 3 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 4 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 5 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 6 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 7 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 8 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 9 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 10 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 11 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 12 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 13 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 14 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 15 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 16 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 17 with LTL subformula (Polish notation):
    Initial state only
 - UVW state 18 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 19 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
    Bits 9 to 9: incoming transition
       -> Value 0 for transition from UVW state 20
       -> Value 1 for transition from UVW state 21
 - UVW state 20 with LTL subformula (Polish notation):
    Initial state only
 - UVW state 21 with LTL subformula (Polish notation):
    Initial state only


UVW on which the monitor is based:
 UVW with 22 states and initial states [17, 20, 21]:
 - State No. 0 with name reject (rej.):
   - t.t.s. 0 for TRUE
 - State No. 1 with name || reject R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 1 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, FALSE)
   - t.t.s. 2 for a1
 - State No. 2 with name || reject || reject || reject || reject R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 2 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, (~ a2))
 - State No. 3 with name || reject R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 3 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, FALSE)
   - t.t.s. 4 for b1
 - State No. 4 with name || reject || reject || reject || reject R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 4 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, (~ b2))
 - State No. 5 with name || reject R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 5 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, FALSE)
   - t.t.s. 6 for c1
 - State No. 6 with name || reject || reject || reject || reject R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 6 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, (~ c2))
 - State No. 7 with name || reject R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 7 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, FALSE)
   - t.t.s. 8 for d1
 - State No. 8 with name || reject || reject || reject || reject R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 8 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, (~ d2))
 - State No. 9 with name || reject R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 9 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, TRUE))
   - t.t.s. 10 for a1
 - State No. 10 with name || reject || reject || reject || reject R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 10 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, (~ a2)))
 - State No. 11 with name || reject R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 11 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, TRUE))
   - t.t.s. 12 for b1
 - State No. 12 with name || reject || reject || reject || reject R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 12 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, (~ b2)))
 - State No. 13 with name || reject R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 13 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, TRUE))
   - t.t.s. 14 for c1
 - State No. 14 with name || reject || reject || reject || reject R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 14 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, (~ c2)))
 - State No. 15 with name || reject R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 15 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, TRUE))
   - t.t.s. 16 for d1
 - State No. 16 with name || reject || reject || reject || reject R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 16 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, (~ d2)))
 - State No. 17 with name & & & & & & & & & & & & & & & & & & G | | d1 ! d2 R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2 & G | | c1 ! c2 R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2 & G | | b1 ! b2 R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2 & G | | a1 ! a2 R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2 & G | | d1 d2 R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2 & G | | c1 c2 R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2 & G | | b1 b2 R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2 G | | a1 a2 R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2 G | | a1 ! a2 | b1 ! b2 G | | a1 ! a2 | d1 ! d2 G | | b1 ! b2 | a1 ! a2 G | | b1 ! b2 | c1 ! c2 G | | c1 ! c2 | b1 ! b2 G | | c1 ! c2 | d1 ! d2 G | | d1 ! d2 | a1 ! a2 G | | d1 ! d2 | c1 ! c2 G | | ! a1 a2 | ! b1 b2 G | | ! a1 a2 | ! d1 d2 G | | ! b1 b2 | ! a1 a2 G | | ! b1 b2 | ! c1 c2 G | | ! c1 c2 | ! b1 b2 G | | ! c1 c2 | ! d1 d2 G | | ! d1 d2 | ! a1 a2 G | | ! d1 d2 | ! c1 c2 G | | | a1 ! a2 ! m X | ! m & ! a1 a2:
   - t.t.s. 15 for (~ ite(d1, TRUE, (~ d2)))
   - t.t.s. 17 for TRUE
   - t.t.s. 13 for (~ ite(c1, TRUE, (~ c2)))
   - t.t.s. 11 for (~ ite(b1, TRUE, (~ b2)))
   - t.t.s. 9 for (~ ite(a1, TRUE, (~ a2)))
   - t.t.s. 7 for (~ ite(d1, TRUE, d2))
   - t.t.s. 5 for (~ ite(c1, TRUE, c2))
   - t.t.s. 3 for (~ ite(b1, TRUE, b2))
   - t.t.s. 1 for (~ ite(a1, TRUE, a2))
   - t.t.s. 0 for (~ ite(a1, ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))), ite(b1, ite(b2, ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE))), FALSE), ite(b2, ite(c1, ite(d1, d2, TRUE), (~ ite(c2, TRUE, (~ ite(d1, d2, TRUE))))), ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE)))))), ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))), ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), FALSE), ite(d1, TRUE, (~ d2)))), (~ ite(b2, TRUE, (~ ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))))))), ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))))))
   - t.t.s. 18 for (~ ite(a1, TRUE, (~ ite(a2, m, FALSE))))
 - State No. 18 with name || reject | ! m & ! a1 a2:
   - t.t.s. 0 for ite(a1, m, (~ ite(a2, TRUE, (~ m))))
 - State No. 19 with name || reject R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0:
   - t.t.s. 19 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for (~ ite(a1, ite(a2, m, FALSE), ite(a2, TRUE, m)))
 - State No. 20 with name & R & a1 ! a2 | | | ! a1 a2 ! m X R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0 R & a1 ! a2 | & | a1 ! m | ! a2 ! m X 0:
   - t.t.s. 20 for ite(a1, a2, TRUE)
   - t.t.s. 19 for (~ ite(a1, ite(a2, TRUE, (~ m)), TRUE))
   - t.t.s. 0 for ite(a1, ite(a2, m, FALSE), m)
 - State No. 21 with name & R & ! a1 a2 | | | ! a1 a2 ! m X R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0 R & ! a1 a2 | & | | a1 a2 ! m | | ! a1 ! a2 ! m X 0:
   - t.t.s. 21 for ite(a1, TRUE, (~ a2))
   - t.t.s. 19 for (~ ite(a1, ite(a2, TRUE, (~ m)), TRUE))
   - t.t.s. 0 for ite(a1, ite(a2, m, FALSE), (~ ite(a2, TRUE, (~ m))))

*/
