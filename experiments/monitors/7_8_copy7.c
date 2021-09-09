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

const uint16_t lut0[256] = {0x309,0x309,0x319,0x309,0x301,0x304,0x311,0x301,
    0x321,0x321,0x334,0x321,0x301,0x301,0x311,0x301,
    0x309,0x309,0x319,0x309,0x304,0x304,0x314,0x304,
    0x321,0x321,0x334,0x321,0x301,0x301,0x311,0x301,
    0x349,0x349,0x359,0x349,0x341,0x344,0x351,0x341,
    0x364,0x364,0x374,0x364,0x341,0x341,0x351,0x341,
    0x309,0x309,0x319,0x309,0x301,0x304,0x311,0x301,
    0x321,0x321,0x334,0x321,0x301,0x301,0x311,0x301,
    0x309,0x30c,0x319,0x309,0x301,0x304,0x311,0x301,
    0x321,0x324,0x334,0x321,0x301,0x304,0x311,0x301,
    0x30c,0x30c,0x31c,0x30c,0x304,0x304,0x314,0x304,
    0x324,0x324,0x334,0x324,0x304,0x304,0x314,0x304,
    0x349,0x34c,0x359,0x349,0x341,0x344,0x351,0x341,
    0x364,0x364,0x374,0x364,0x341,0x344,0x351,0x341,
    0x309,0x30c,0x319,0x309,0x301,0x304,0x311,0x301,
    0x321,0x324,0x334,0x321,0x301,0x304,0x311,0x301,
    0x389,0x389,0x39c,0x389,0x381,0x384,0x394,0x381,
    0x3a1,0x3a1,0x3b4,0x3a1,0x381,0x381,0x394,0x381,
    0x389,0x389,0x39c,0x389,0x384,0x384,0x394,0x384,
    0x3a1,0x3a1,0x3b4,0x3a1,0x381,0x381,0x394,0x381,
    0x3cc,0x3cc,0x3dc,0x3cc,0x3c4,0x3c4,0x3d4,0x3c4,
    0x3e4,0x3e4,0x3f4,0x3e4,0x3c4,0x3c4,0x3d4,0x3c4,
    0x389,0x389,0x39c,0x389,0x381,0x384,0x394,0x381,
    0x3a1,0x3a1,0x3b4,0x3a1,0x381,0x381,0x394,0x381,
    0x309,0x309,0x319,0x309,0x301,0x304,0x311,0x301,
    0x321,0x321,0x334,0x321,0x301,0x301,0x311,0x301,
    0x309,0x309,0x319,0x309,0x304,0x304,0x314,0x304,
    0x321,0x321,0x334,0x321,0x301,0x301,0x311,0x301,
    0x349,0x349,0x359,0x349,0x341,0x344,0x351,0x341,
    0x364,0x364,0x374,0x364,0x341,0x341,0x351,0x341,
    0x309,0x309,0x319,0x309,0x301,0x304,0x311,0x301,
    0x321,0x321,0x334,0x321,0x301,0x301,0x311,0x301};
const uint32_t lut1[256] = {0x182,0x2,0x2,0x2,0x182,0x2,0xc02,0x2,
    0x1c2,0x342,0x2,0x343,0x1c2,0x342,0xc02,0x343,
    0x182,0x2,0x2,0x2,0x184,0x4,0xc02,0x4,
    0x1c2,0x342,0x2,0x343,0x1c4,0x344,0xc02,0x345,
    0x9188,0x9008,0x2,0x9008,0x9182,0x9008,0xc02,0x9002,
    0x91c8,0x9348,0x2,0x9349,0x91c2,0x9348,0xc02,0x9343,
    0x9188,0x9008,0x2,0x9008,0x9184,0x900c,0xc02,0x9004,
    0x91c8,0x9348,0x2,0x9349,0x91c4,0x934c,0xc02,0x9345,
    0x30182,0x2,0x30002,0x30002,0x30190,0xa002,0x30c10,0x30010,
    0x301c2,0x342,0x30002,0x30343,0x301d0,0xa342,0x30c10,0x30351,
    0x30182,0x2,0x30002,0x30002,0x30194,0xa004,0x30c10,0x30014,
    0x301c2,0x342,0x30002,0x30343,0x301d4,0xa344,0x30c10,0x30355,
    0x39188,0x9008,0x30002,0x39008,0x39190,0xb008,0x30c10,0x39010,
    0x391c8,0x9348,0x30002,0x39349,0x391d0,0xb348,0x30c10,0x39351,
    0x39188,0x9008,0x30002,0x39008,0x39194,0xb00c,0x30c10,0x39014,
    0x391c8,0x9348,0x30002,0x39349,0x391d4,0xb34c,0x30c10,0x39355,
    0xc0182,0xc0002,0x2,0xc0002,0xc01a0,0xcc002,0xc02,0xc0020,
    0xc01c2,0xc0342,0x2,0xc0343,0xc01e0,0xcc342,0xc02,0xc0361,
    0xc0182,0xc0002,0x2,0xc0002,0xc01a4,0xcc004,0xc02,0xc0024,
    0xc01c2,0xc0342,0x2,0xc0343,0xc01e4,0xcc344,0xc02,0xc0365,
    0xc9188,0xc9008,0x2,0xc9008,0xc91a0,0xcd008,0xc02,0xc9020,
    0xc91c8,0xc9348,0x2,0xc9349,0xc91e0,0xcd348,0xc02,0xc9361,
    0xc9188,0xc9008,0x2,0xc9008,0xc91a4,0xcd00c,0xc02,0xc9024,
    0xc91c8,0xc9348,0x2,0xc9349,0xc91e4,0xcd34c,0xc02,0xc9365,
    0xf0182,0xc0002,0x30002,0xf0002,0xf01b0,0xce002,0x30c10,0xf0030,
    0xf01c2,0xc0342,0x30002,0xf0343,0xf01f0,0xce342,0x30c10,0xf0371,
    0xf0182,0xc0002,0x30002,0xf0002,0xf01b4,0xce004,0x30c10,0xf0034,
    0xf01c2,0xc0342,0x30002,0xf0343,0xf01f4,0xce344,0x30c10,0xf0375,
    0xf9188,0xc9008,0x30002,0xf9008,0xf91b0,0xcf008,0x30c10,0xf9030,
    0xf91c8,0xc9348,0x30002,0xf9349,0xf91f0,0xcf348,0x30c10,0xf9371,
    0xf9188,0xc9008,0x30002,0xf9008,0xf91b4,0xcf00c,0x30c10,0xf9034,
    0xf91c8,0xc9348,0x30002,0xf9349,0xf91f4,0xcf34c,0x30c10,0xf9375};
const uint16_t lut2[256] = {0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0xc0,0xc0,0xc0,0xc1,0xe0,0xe0,0xe0,0xe1,
    0x6c8,0x6c8,0x6c8,0x6c9,0x6e8,0x6e8,0x6e8,0x6e9,
    0x0,0x0,0x0,0x1,0x5a0,0x5a0,0x5a0,0x5a1,
    0x600,0x600,0x600,0x601,0x7a0,0x7a0,0x7a0,0x7a1,
    0xb802,0xb802,0xb802,0xb802,0xbda2,0xbda2,0xbda2,0xbda2,
    0xbe02,0xbe02,0xbe02,0xbe02,0xbfa2,0xbfa2,0xbfa2,0xbfa2,
    0xc010,0xc010,0xc010,0xc010,0xc5b0,0xc5b0,0xc5b0,0xc5b0,
    0xc610,0xc610,0xc610,0xc610,0xc7b0,0xc7b0,0xc7b0,0xc7b0,
    0xf812,0xf812,0xf812,0xf812,0xfdb2,0xfdb2,0xfdb2,0xfdb2,
    0xfe12,0xfe12,0xfe12,0xfe12,0xffb2,0xffb2,0xffb2,0xffb2,
    0x1000,0x1000,0x1000,0x1001,0x1000,0x1000,0x1000,0x1001,
    0x1000,0x1000,0x1000,0x1001,0x1000,0x1000,0x1000,0x1001,
    0x1800,0x1800,0x1800,0x1801,0x1800,0x1800,0x1800,0x1801,
    0x1800,0x1800,0x1800,0x1801,0x1800,0x1800,0x1800,0x1801,
    0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,
    0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,0xd010,
    0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,
    0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,0xd810,
    0x0,0x0,0x0,0x1,0x5a4,0x5a4,0x5a4,0x5a5,
    0x608,0x608,0x608,0x609,0x7ac,0x7ac,0x7ac,0x7ad,
    0xb800,0xb800,0xb800,0xb801,0xbda4,0xbda4,0xbda4,0xbda5,
    0xbe08,0xbe08,0xbe08,0xbe09,0xbfac,0xbfac,0xbfac,0xbfad,
    0xc000,0xc000,0xc000,0xc001,0xc5a4,0xc5a4,0xc5a4,0xc5a5,
    0xc608,0xc608,0xc608,0xc609,0xc7ac,0xc7ac,0xc7ac,0xc7ad,
    0xf800,0xf800,0xf800,0xf801,0xfda4,0xfda4,0xfda4,0xfda5,
    0xfe08,0xfe08,0xfe08,0xfe09,0xffac,0xffac,0xffac,0xffad};
const uint16_t lut3[128] = {0xc0,0xc1,0xc0,0xc1,0xe0,0xe1,0xe0,0xe1,
    0x6d0,0x6d1,0x6d0,0x6d1,0x6f0,0x6f1,0x6f0,0x6f1,
    0x0,0x1,0xc008,0xc008,0x5a0,0x5a1,0xc5a8,0xc5a8,
    0x600,0x601,0xc608,0xc608,0x7a0,0x7a1,0xc7a8,0xc7a8,
    0x1000,0x1001,0xd008,0xd008,0x1000,0x1001,0xd008,0xd008,
    0x1000,0x1001,0xd008,0xd008,0x1000,0x1001,0xd008,0xd008,
    0x0,0x1,0xc000,0xc001,0x5a4,0x5a5,0xc5a4,0xc5a5,
    0x610,0x611,0xc610,0xc611,0x7b4,0x7b5,0xc7b4,0xc7b5,
    0xc0,0xc1,0xc0,0xc1,0xe0,0xe1,0xe0,0xe1,
    0x6d0,0x6d1,0x6d0,0x6d1,0x6f0,0x6f1,0x6f0,0x6f1,
    0xb802,0xb802,0xf80a,0xf80a,0xbda2,0xbda2,0xfdaa,0xfdaa,
    0xbe02,0xbe02,0xfe0a,0xfe0a,0xbfa2,0xbfa2,0xffaa,0xffaa,
    0x1800,0x1801,0xd808,0xd808,0x1800,0x1801,0xd808,0xd808,
    0x1800,0x1801,0xd808,0xd808,0x1800,0x1801,0xd808,0xd808,
    0xb800,0xb801,0xf800,0xf801,0xbda4,0xbda5,0xfda4,0xfda5,
    0xbe10,0xbe11,0xfe10,0xfe11,0xbfb4,0xbfb5,0xffb4,0xffb5};
const uint16_t lut4[128] = {0x40,0x60,0x350,0x370,0x0,0x20,0x300,0x320,
    0x800,0x820,0x800,0x820,0x0,0x20,0x310,0x330,
    0x40,0x60,0x350,0x370,0x5c01,0x5c01,0x5f01,0x5f01,
    0xc00,0xc20,0xc00,0xc20,0x5c00,0x5c20,0x5f10,0x5f30,
    0x40,0x60,0x350,0x370,0x6002,0x6002,0x6302,0x6302,
    0x6802,0x6802,0x6802,0x6802,0x6000,0x6020,0x6310,0x6330,
    0x40,0x60,0x350,0x370,0x7c03,0x7c03,0x7f03,0x7f03,
    0x6c02,0x6c02,0x6c02,0x6c02,0x7c00,0x7c20,0x7f10,0x7f30,
    0x44,0x64,0x354,0x374,0x2c4,0x2e4,0x3c4,0x3e4,
    0x800,0x820,0x800,0x820,0x2cc,0x2ec,0x3dc,0x3fc,
    0x44,0x64,0x354,0x374,0x5ec5,0x5ec5,0x5fc5,0x5fc5,
    0xc00,0xc20,0xc00,0xc20,0x5ecc,0x5eec,0x5fdc,0x5ffc,
    0x44,0x64,0x354,0x374,0x62c6,0x62c6,0x63c6,0x63c6,
    0x6802,0x6802,0x6802,0x6802,0x62cc,0x62ec,0x63dc,0x63fc,
    0x44,0x64,0x354,0x374,0x7ec7,0x7ec7,0x7fc7,0x7fc7,
    0x6c02,0x6c02,0x6c02,0x6c02,0x7ecc,0x7eec,0x7fdc,0x7ffc};
const uint8_t lut5[256] = {0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x20,0x20,0x28,0x20,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x20,0x9d,0x2c,0xbc,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x20,0xc2,0xca,0xe0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x20,0xdf,0xce,0xfc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc};
const uint8_t lut6[256] = {0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x0,0x0,0x0,0x0,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xc,0x0,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0x2,0xa,0x2,0xa,0x2,0xa,0x2,0xa,
    0x2,0xa,0x2,0xa,0x2,0xa,0x2,0xa,
    0x2,0xa,0x2,0xa,0x2,0xa,0x2,0xa,
    0x2,0xa,0x2,0xa,0x2,0xa,0x2,0xa,
    0x0,0x8,0x0,0xa,0x2,0xa,0x2,0xa,
    0x2,0xa,0x2,0xa,0x2,0xa,0x2,0xa,
    0x2,0xa,0x2,0xa,0x2,0xa,0x2,0xa,
    0x2,0xa,0x2,0xa,0x2,0xa,0x2,0xa,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xc,0x0,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf,
    0xf,0xe,0x2,0xf,0xf,0xe,0x2,0xf};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = (apValues & 255);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 256)>0?4:0) | (uvwState1>0?8:0) | (uvwState18>0?16:0) | (uvwState19>0?32:0) | (uvwState20>0?64:0) | (uvwState21>0?128:0) | (apValues & 3);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = (uvwState7>0?4:0) | (uvwState8>0?8:0) | (uvwState15>0?16:0) | (uvwState16>0?32:0) | (lut0output & 1) | (lut1output & 2) | (apValues & 192);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13>0?64:0) | (lut2output & 1) | (apValues & 48);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState4>0?2:0) | (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState3>0?64:0) | (lut3output & 1) | (apValues & 12);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState9>0?64:0) | (uvwState10>0?128:0) | (apValues & 3) | (lut2output & 12) | (lut3output & 16) | (lut4output & 32);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState2>0?64:0) | (uvwState1>0?128:0) | (apValues & 3) | (lut3output & 4) | (lut4output & 24) | (lut5output & 32);
  uint32_t lut6output = lut6[lut6input];
  if ((lut0output & 2)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 1)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 8)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 16)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 16)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 1)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 1)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 2)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 8)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 16)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 4)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 4)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 8)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 16)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 32)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut1output & 64)) {
  } else if ((lut1output & 128)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 512)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut6output & 4)) {
  }
  if ((lut4output & 4)) {
  } else if ((lut0output & 8)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 128)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut4output & 256)) {
  }
  if ((lut3output & 32)) {
  } else if ((lut3output & 64)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 256)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut3output & 512)) {
  }
  if ((lut2output & 32)) {
  } else if ((lut2output & 64)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 256)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut2output & 512)) {
  }
  if ((lut5output & 4)) {
  } else if ((lut0output & 16)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 16)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut5output & 64)) {
  }
  if ((lut4output & 1024)) {
  } else if ((lut0output & 32)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 4096)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut4output & 8192)) {
  }
  if ((lut3output & 2048)) {
  } else if ((lut0output & 64)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 8192)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut3output & 16384)) {
  }
  if ((lut2output & 2048)) {
  } else if ((lut0output & 128)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 8192)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut2output & 16384)) {
  }
  if ((lut0output & 256)) {
  }
  if ((lut1output & 1024)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 4096)) {
  } else if ((lut1output & 8192)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut1output & 16384)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut1output & 65536)) {
  }
  if ((lut1output & 262144)) {
  }
  uvwState0 = (lut6output & 2);
  uvwState1 = (lut1output & 256);
  uvwState2 = (lut6output & 8);
  uvwState3 = (lut4output & 64);
  uvwState4 = (lut4output & 512);
  uvwState5 = (lut3output & 128);
  uvwState6 = (lut3output & 1024);
  uvwState7 = (lut2output & 128);
  uvwState8 = (lut2output & 1024);
  uvwState9 = (lut5output & 8);
  uvwState10 = (lut5output & 128);
  uvwState11 = (lut4output & 2048);
  uvwState12 = (lut4output & 16384);
  uvwState13 = (lut3output & 4096);
  uvwState14 = (lut3output & 32768);
  uvwState15 = (lut2output & 4096);
  uvwState16 = (lut2output & 32768);
  uvwState17 = (lut0output & 512);
  uvwState18 = (lut1output & 2048);
  uvwState19 = (lut1output & 32768);
  uvwState20 = (lut1output & 131072);
  uvwState21 = (lut1output & 524288);
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

/* Lookup-Table contents:
- LUT 0 has:
  -> Inputs a1 a2 b1 b2 c1 c2 d1 d2
  -> Outputs new_n77 uvwState0incoming0 uvwState0incoming17 uvwState3incoming1 uvwState9incoming1 uvwState11incoming1 uvwState13incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 m uvwState1 uvwState18 uvwState19 uvwState20 uvwState21
  -> Outputs uvwState0incoming1 new_n89 uvwState0incoming18 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState1incoming0 uvwState1incoming1 uvwState1Next uvwState2incoming0 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 2 has:
  -> Inputs new_n77 new_n89 uvwState7 uvwState8 uvwState15 uvwState16 d1 d2
  -> Outputs new_n92 uvwState0incoming15 uvwState0incoming7 uvwState0incoming8 uvwState0incoming16 uvwState7incoming0 uvwState7incoming1 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 3 has:
  -> Inputs new_n92 uvwState14 uvwState5 uvwState6 c1 c2 uvwState13
  -> Outputs new_n94 uvwState0incoming13 uvwState0incoming5 uvwState0incoming14 uvwState0incoming6 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 4 has:
  -> Inputs new_n94 uvwState4 b1 b2 uvwState11 uvwState12 uvwState3
  -> Outputs uvwState0incoming11 uvwState0incoming12 uvwState3incoming0 uvwState0incoming3 uvwState0incoming4 new_n96 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 5 has:
  -> Inputs a1 a2 uvwState0incoming7 uvwState0incoming8 uvwState0incoming6 new_n96 uvwState9 uvwState10
  -> Outputs uvwState0incoming9 uvwState0incoming10 uvwState9incoming0 uvwState9Next uvwState10incoming0 new_n101 uvwState10incoming1 uvwState10Next
- LUT 6 has:
  -> Inputs a1 a2 uvwState0incoming5 uvwState0incoming3 uvwState0incoming4 new_n101 uvwState2 uvwState1
  -> Outputs uvwState0incoming2 uvwState0Next uvwState2incoming1 uvwState2Next
*/
