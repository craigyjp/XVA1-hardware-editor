//
// Created by André Mathlener on 16/04/2021.
//

#ifndef XVA1USERINTERFACE_SECTIONFACTORY_H
#define XVA1USERINTERFACE_SECTIONFACTORY_H


#include "Section.h"

class SectionFactory {
public:
    Section createDefaultSection();

    Section createEffectsSection();

    Section createOscillatorSection();

    Section createEnvelopeSection();

    Section createLFOSection();

    Section createFilterSection();

    Section createPatchSection();

    Section createExternalControlsSection();

    Section createPerformanceControlsSection();

    Section createSequencerSection();

    Section createMIDIModSection();

    Section createGlobalSection();
};


#endif //XVA1USERINTERFACE_SECTIONFACTORY_H
