//
// Created by André Mathlener on 07/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHESIZER_H
#define XVA1USERINTERFACE_SYNTHESIZER_H

#include <string>
#include <Arduino.h>
#include "Envelope.h"

using namespace std;

class Synthesizer {
private:
    int currentPatchNumber = 1;
    string currentPatchName = "";
    byte currentPatchData[512] = {};

public:
    void begin();

    void selectPatch(int number);

    void changePatch(int number);

    void loadPatchData();

    void savePatchData(int number);

    int getPatchNumber() const;

    const string &getPatchName() const;

    byte getParameter(int number) const;

    void setParameter(int number, int value);

    void setCurrentPatchName();

    Envelope getEnvelopeValues(Envelope &envelope);
};


#endif //XVA1USERINTERFACE_SYNTHESIZER_H
