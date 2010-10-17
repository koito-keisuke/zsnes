#ifndef SOUND_H
#define SOUND_H

#include "../types.h"

extern void SBHandler(void);

extern u1 PICMaskP;
extern u1 SBDMA;
extern u1 SBDMAPage;
extern u1 SBHDMA;
extern u1 SBHDMAPage;
extern u1 SBIrq;
extern u1 SBswitch;
extern u1 vibracard;
extern u2 SBPort;
extern u2 oldhandSBs;
extern u2 sbselec;
extern u4 sbpmofs;

#endif
