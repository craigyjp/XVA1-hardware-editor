//
// Created by André Mathlener on 30/04/2021.
//

#ifndef XVA1USERINTERFACE_ALLSYNTHPARAMETERS_H
#define XVA1USERINTERFACE_ALLSYNTHPARAMETERS_H

#include "SectionFactory.h"

Envelope envelopes[] = {
        Envelope ({{82, 87, 92, 97, 102, 107}, {112, 117, 122, 127, 132, 137}}),
        Envelope ({{81, 86, 91, 96, 101, 106}, {111, 116, 121, 126, 131, 136}}),
        Envelope ({{80, 85, 90, 95, 100, 105}, {110, 115, 120, 125, 130, 135}})
};

Section sections[] = {
        SectionFactory().createDefaultSection(),     // 0
        SectionFactory().createOscillatorSection(),  // 1
        SectionFactory().createFilterSection(),      // 2
        SectionFactory().createEnvelopeSection(),    // 3
        SectionFactory().createLFOSection(),         // 4
        SectionFactory().createEffectsSection(),     // 5
        SectionFactory().createPatchSection(),       // 6
        SectionFactory().createSequencerSection(),   // 7
        SectionFactory().createExternalControlsSection(), //8
        SectionFactory().createPerformanceControlsSection(), //9
        SectionFactory().createMIDIModSection(), // 10
        SectionFactory().createGlobalSection(), //11 
};

#endif //XVA1USERINTERFACE_ALLSYNTHPARAMETERS_H
