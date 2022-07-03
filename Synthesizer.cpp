//
// Created by André Mathlener on 07/04/2021.
//

#include "Synthesizer.h"
int read_status;

#define HWSERIAL Serial5 

void Synthesizer::selectPatch(int number) {
    int synthPatchNumber = number - 1;

    Serial.print("Selecting patch #");
    Serial.print(synthPatchNumber);
    Serial.print(" on Synth...");

    HWSERIAL.write('r'); // 'r' = Read program
    HWSERIAL.write(synthPatchNumber);



    int bytesRead = 0;
    int retry = 0;
    while (bytesRead == 0 && retry != 100) {
        if (HWSERIAL.available()) {
            read_status = HWSERIAL.read();
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(1);
        }
    }

    Serial.print("Status=");
    Serial.println(read_status, DEC);

    loadPatchData();
    currentPatchNumber = number;
}

void Synthesizer::changePatch(int number) {
    currentPatchNumber = number;
}

void Synthesizer::loadPatchData() {
    HWSERIAL.write('d'); // 'd' = Display program

    Serial.println("Reading patch data from Synth...");

    byte rxBuffer[512];
    int bytesRead = 0;
    int retry = 0;
    while (bytesRead != 512 && retry != 100) {
        if (HWSERIAL.available()) {
            byte b = HWSERIAL.read();
            rxBuffer[bytesRead] = b;
            bytesRead++;
            retry = 0;
        } else {
            retry++;
            delay(1);
        }
    }
    HWSERIAL.flush();
    memcpy(currentPatchData, rxBuffer, 512);
    setCurrentPatchName();
}

void Synthesizer::savePatchData(int number) {
    int synthPatchNumber = number - 1;

    Serial.println("Writing patch data from Synth...");
    Serial.println(number);
    HWSERIAL.write('w'); // 'w' = Write program
    HWSERIAL.write(synthPatchNumber);
}

void Synthesizer::setCurrentPatchName() {
    string patchName = "";

    for (int i = 480; i <= 504; i++) {
        patchName += (char) currentPatchData[i];
    }
    currentPatchName = patchName;

    Serial.print("Patch name: ");
    Serial.println(patchName.c_str());
}

int Synthesizer::getPatchNumber() const {
    return currentPatchNumber;
}

const string &Synthesizer::getPatchName() const {
    return currentPatchName;
}

byte Synthesizer::getParameter(int number) const {
    return currentPatchData[number];
}

void Synthesizer::setParameter(int number, int value) {
    HWSERIAL.write('s'); // 's' = Set Parameter

    if (number > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        HWSERIAL.write(255);
        HWSERIAL.write(number - 256);
        HWSERIAL.write(value);
    } else {
        HWSERIAL.write(number);
        HWSERIAL.write(value);
    }

    currentPatchData[number] = value;

    if (number >= 480 && number <= 504) {
        setCurrentPatchName();
    }
}

void Synthesizer::begin() {
    HWSERIAL.begin(500000, SERIAL_8N1); // XVA1 Serial

}

Envelope Synthesizer::getEnvelopeValues(Envelope &envelope) {
    Envelope returnEnvelope = Envelope();

    for (int i = 0; i < 6; ++i) {
        returnEnvelope.level[i] = getParameter(envelope.level[i]);
        returnEnvelope.rate[i] = getParameter(envelope.rate[i]);
    }

    return returnEnvelope;
}
