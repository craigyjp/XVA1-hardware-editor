//
// Created by André Mathlener on 16/04/2021.
//

#include "SectionFactory.h"
#include "SynthParameter.h"

Section SectionFactory::createDefaultSection() {
    return Section("Default")
            // 1
            .addParameter(SynthParameter("Cutoff 1").number(72))
            // 9
            .addParameter(SynthParameter("Resonance 1").number(77))
            // 2
            .addParameter(SynthParameter("Cutoff 2").number(78))
            //10
            .addParameter(SynthParameter("Resonance 2").number(79))
            //3
            .addParameter(
                    SynthParameter("ARP Mode")
                            .number(450)
                            .max(5)
                            .descriptions({"Off", "Up", "Down", "Up/Down", "As played", "Random"})
            )
            //11
            .addParameter(
                    SynthParameter("ARP Tempo")
                            .number(451)
//                            .min(50) // TODO: Also allow 0 to follow incoming MIDI clock tempo
            )
            //4
            .addParameter(
                    SynthParameter("Multiplier").number(453).min(1)
            )
            //12
            .addParameter(
                    SynthParameter("Octaves").number(454).max(10)
            )
            //5
            .addParameter(
                    SynthParameter("Sequencer")
                            .number(428)
                            .max(1)
                            .descriptions({"OFF", "ON"})
            )
            //13
            .addParameter(SynthParameter("Sequencer Tempo").number(431))
            //6
            .addParameter(
                    SynthParameter("Legato Mode")
                            .number(244)
                            .max(1)
                            .descriptions({" Polyphonic ", "Monophonic/Legato"})
            )
            //14
            .addParameter(SynthParameter("Tuning").number(251))
            //7
                        .addParameter(
                    SynthParameter("Glide")
                            .number(245)
                            .max(2)
                            .descriptions({"Off", "Always", "Only Legato Notes"})
            )
            //15
            .addParameter(SynthParameter("Glide Time").number(246))
            //8
            .addParameter(
                    SynthParameter("Transpose")
                            .type(CENTER_128)
                            .number(241)
            )
            //16
            .addParameter(SynthParameter("Volume").number(509));
}

Section SectionFactory::createOscillatorSection() {
    return Section("Oscillators")
            .virtualSubSectionTitles({"Oscillator 1", "Oscillator 2", "Oscillator 3", "Oscillator 4"})
            //1
            .addParameter(
                    SynthParameter("On or Off")
                            .numbers({1, 2, 3, 4})
                            .max(1)
                            .descriptions({"OFF", "ON"})
            )
            //9
            .addParameter(
                    SynthParameter("Mode")
                            .type(BITWISE)
                            .number(6)
                            .bitNumbers({0, 1, 2, 3})
                            .descriptions({"KeyTrack", "FixedPitch"})
            )
            //2
            .addParameter(
                    SynthParameter("Sync")
                            .type(BITWISE)
                            .number(5)
                            .bitNumbers({0, 1, 2, 3})
                            .descriptions({"Free running", "Restart on Key-ON"})
            )
            //10
            .addParameter(
                    SynthParameter("Waveform")
                            .numbers({11, 12, 13, 14})
                            .max(8)
                            .descriptions({"Saw up", "Saw down", "Square", "Triangle", "Sine",
                                           "Noise", "Sawstack x3 (stereo)",
                                           "Sawstack x7 (mono)", "Sawstack x7 (stereo)"})
            )
            //3
            .addParameter(
                    SynthParameter("Phase")
                            .numbers({7, 8, 9, 10})
                            .max(3)
                            .descriptions({"0 deg", "90 deg", "180 deg", "270 deg"})
            )
            //11
            .addParameter(
                    SynthParameter("Pulse Width")
                            .type(CENTER_128)
                            .numbers({15, 16, 17, 18})
            )
            //4
            .addParameter(
                    SynthParameter("Transpose")
                            .type(CENTER_128)
                            .numbers({19, 20, 21, 22})
            )
            //12
            .addParameter(
                    SynthParameter("Detune")
                            .type(CENTER_128)
                            .numbers({23, 24, 25, 26})
            )
            //5
            .addParameter(SynthParameter("Sawstack Detune").numbers({285, 286, 287, 288}))
            //13
            .addParameter(SynthParameter("Drift").numbers({260, 261, 262, 263}))
            //6
            .addParameter(SynthParameter("Oscillator Level").numbers({27, 28, 29, 30}))
            //14
            .addParameter(SynthParameter("Panning Level L").numbers({31, 33, 35, 37}))
            //7
            .addParameter(SynthParameter("Panning Level R").numbers({32, 34, 36, 38})) 
            //15
            .addParameter(SynthParameter("Velocity sens.").numbers({39, 40, 41, 42})) 
            //8
            .addParameter(SynthParameter("PMS").numbers({63, 64, 65, 66}))
            //16
            .addParameter(SynthParameter("AMS").numbers({67, 66, 67, 68}))   
                         
            // page 2
            //1
            .addParameter(SynthParameter("Key L depth").numbers({47, 48, 49, 50}))
            //9
            .addParameter(SynthParameter("Key L curve").numbers({55, 56, 57, 58}))
            //2
            .addParameter(SynthParameter("Key R depth").numbers({51, 52, 53, 54}))
            //10
            .addParameter(SynthParameter("Key R curve").numbers({59, 60, 61, 62}))
            //3
            .addParameter(SynthParameter("Key breakpoint").numbers({43, 44, 45, 46}))           
            //11
            .addParameter(SynthParameter("Ring Mod").number(271));
}

Section SectionFactory::createFilterSection() {
    return Section("Filters")
                            //1
                            .addParameter(SynthParameter("Cutoff 1").number(72))
                            //9
                            .addParameter(SynthParameter("Resonance 1").number(77))
                            //2
                            .addParameter(SynthParameter("Cutoff 2").number(78))
                            //10
                            .addParameter(SynthParameter("Resonance 2").number(79))
                            //3
                            .addParameter(
                                    SynthParameter("Type")
                                            .number(71)
                                            .max(21)
                                            .descriptions({"Bypass", "LPF 1P", "LPF 2P", "LPF 3P", "LPF 4P", "HPF 1P",
                                                           "HPF 2P", "HPF 3P", "HPF 4P", "BPF 2P", "BPF 4P", "BRF 2P",
                                                           "BRF 4P", "LP -> LP", "LP -> BP", "LP -> HP", "LP // LP",
                                                           "LP // BP", "LP // HP", "BP // BP", "BP // HP", "HP // HP"})
                            )
                            //11
                            .addParameter(
                                    SynthParameter("Velocity")
                                            .type(CENTER_128)
                                            .number(73)
                            )
                            //4
                            .addParameter(
                                    SynthParameter("KBD Track")
                                            .type(CENTER_128)
                                            .number(74)
                            )
                            //12
                            .addParameter(
                                    SynthParameter("EG depth")
                                            .type(CENTER_128)
                                            .number(75)
                            )
                            //5
                            .addParameter(
                                    SynthParameter("EG Velocity")
                                            .type(CENTER_128)
                                            .number(76)
                            )
                            //13
                            .addParameter(
                                    SynthParameter("Velocity RESO")
                                            .type(CENTER_128)
                                            .number(276)
                            )
                            //6
                            .addParameter(
                                    SynthParameter("KBD Track RESO")
                                            .type(CENTER_128)
                                            .number(277)
                            )
                            //14
                            .addParameter(
                                    SynthParameter("Drive")
                                            .number(275)
                                            .max(7)
                            )
                            .addParameter(
                                    SynthParameter("Routing")
                                            .number(278)
                                            .max(1)
                                            .descriptions({"Standard", "LR Mode"})
                            );
}

Section SectionFactory::createEnvelopeSection() {
    return Section("Envelopes")
            .virtualSubSectionTitles({"AMP", "CUTOFF", "PITCH"})
            //1
            .addParameter(SynthParameter("L0: Start").numbers({82, 81, 80}).type(CENTER_128))            
            //9
            .addParameter(SynthParameter("Delay").numbers({112, 111, 110}))            
            //2
            .addParameter(SynthParameter("L1: Attack").numbers({88, 86, 85}).type(CENTER_128))            
            //10
            .addParameter(SynthParameter("R1: Attack").numbers({117, 116, 115}))
            //3
            .addParameter(SynthParameter("L2: Decay").numbers({92, 91, 90}).type(CENTER_128))            
            //11
            .addParameter(SynthParameter("R2: Decay").numbers({122, 121, 120}))
            //4
            .addParameter(SynthParameter("L3: Sustain").numbers({97, 96, 95}).type(CENTER_128))
            //12
            .addParameter(SynthParameter("R3: Sustain").numbers({127, 126, 125}))
            //5
            .addParameter(SynthParameter("L4: Release 1").numbers({102, 101, 100}).type(CENTER_128))           
            //13
            .addParameter(SynthParameter("R4: Release 1").numbers({132, 131, 130}))
            //6
            .addParameter(SynthParameter("L5: Release 2").numbers({107, 106, 105}).type(CENTER_128))
            //14
            .addParameter(SynthParameter("R5: Release 2").numbers({137, 136, 135}))
            //7
            .addParameter(SynthParameter(""))            
            //15
            .addParameter(SynthParameter(""))
            //8
            .addParameter(SynthParameter(""))
            //16
            .addParameter(SynthParameter(""))
            
            //p2-1
            .addParameter(
                    SynthParameter("EG Loop")
                            .type(BITWISE)
                            .number(145)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"Normal", "Loop"})
            )
            //p2-9
            .addParameter(SynthParameter(""))
            //p2-2
            .addParameter(
                    SynthParameter("EG Loop Segment")
                            .type(BITWISE)
                            .number(146)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"L0: Attack", "L5: Decay"})
            )
            //p2-10
            .addParameter(SynthParameter(""))
            //p2-3
            .addParameter(
                    SynthParameter("EG Restart from")
                            .type(BITWISE)
                            .number(147)
                            .bitNumbers({0, 1, 6})
                            .descriptions({"L5: Decay", "L0: Start"})
            )
            //p2-11
            .addParameter(SynthParameter(""))
            //p2-4
            .addParameter(
                    SynthParameter("Range")
                            .numbers({148, -1, -1})
                            .max(10)
            )
            //p2-12
            .addParameter(SynthParameter(""))
            //p2-5           
            .addParameter(
                    SynthParameter("Velocity")
                            .numbers({149, -1, -1})
                            .max(10)
            );
}

Section SectionFactory::createLFOSection() {
    return Section("LFO")
                            //1
                            .addParameter(
                                    SynthParameter("LFO 1 Wave")
                                            .number(160)
                                            .max(9)
                                            .descriptions({"Triangle", "Square", "Saw Up", "Saw Down", "Sine",
                                                           "Sin( x ) + Sin( 2x )", "Sin( x ) + Sin( 3x )",
                                                           "Sin( x ) ^ 3", "Guitar", "S & H"})
                            )
                            //9
                            .addParameter(SynthParameter("LFO 1 Speed").number(161))
                            //2
                            .addParameter(SynthParameter("LFO 1 Range").number(166))
                            //10
                            .addParameter(
                                    SynthParameter("LFO 1 Sync")
                                            .number(162)
                                            .max(4)
                                            .descriptions({"Single, Free running", "Single, Key sync",
                                                           "Multi, Free running", "Multi, Key sync"})
                            )
                            //3
                            .addParameter(SynthParameter("LFO 1 Fade").number(163))
                            //11
                            .addParameter(SynthParameter(""))
                            //4
                            .addParameter(SynthParameter("LFO 1 Depth Amplitude").number(165))
                            //12
                            .addParameter(SynthParameter("LFO 1 Depth Pitch").number(164))
                            //5
                            .addParameter(
                                    SynthParameter("LFO 2 Wave")
                                            .number(170)
                                            .max(9)
                                            .descriptions({"Triangle", "Square", "Saw Up", "Saw Down", "Sine",
                                                           "Sin( x ) + Sin( 2x )", "Sin( x ) + Sin( 3x )",
                                                           "Sin( x ) ^ 3", "Guitar", "S & H"})
                            )
                            //13
                            .addParameter(SynthParameter("LFO 2 Speed").number(171))
                            //6
                            .addParameter(SynthParameter("LFO 2 Range").number(176))
                            //14
                            .addParameter(
                                    SynthParameter("LFO 2 Sync")
                                            .number(172)
                                            .max(4)
                                            .descriptions({"Single, Free running", "Single, Key sync",
                                                           "Multi, Free running", "Multi, Key sync"})
                            )
                            //7
                            .addParameter(SynthParameter("LFO 2 Fade").number(173))
                            //15
                            .addParameter(SynthParameter(""))
                            //8
                            .addParameter(SynthParameter("LFO 2 Depth PWM").number(174))
                            //16
                            .addParameter(SynthParameter("LFO 2 Depth Filter").number(175))
                            
                            //Page 2
                            //1
                            .addParameter(SynthParameter("Pitch LFO Aftertouch").number(180))
                            //9
                            .addParameter(SynthParameter("Pitch LFO Breath").number(182))
                            //2
                            .addParameter(SynthParameter("Pitch LFO Wheel").number(181))
                            //10
                            .addParameter(SynthParameter("Pitch LFO Foot").number(183))
                            //3
                            .addParameter(SynthParameter("PW LFO Aftertouch").number(184))
                            //11
                            .addParameter(SynthParameter("PW LFO Breath").number(186))
                            //4
                            .addParameter(SynthParameter("PW LFO Wheel").number(183))
                            //12
                            .addParameter(SynthParameter("PW LFO Foot").number(187))
                            //5
                            .addParameter(SynthParameter("Filter LFO Aftertouch").number(188))
                            //9
                            .addParameter(SynthParameter("Filter LFO Breath").number(189))
                            //2
                            .addParameter(SynthParameter("Filter LFO Wheel").number(190))
                            //10
                            .addParameter(SynthParameter("Filter LFO Foot").number(191))
                            //3
                            .addParameter(SynthParameter("AMP LFO Aftertouch").number(192))
                            //11
                            .addParameter(SynthParameter("AMP LFO Breath").number(194))
                            //4
                            .addParameter(SynthParameter("AMP LFO Wheel").number(193))
                            //12
                            .addParameter(SynthParameter("AMP LFO Foot").number(195));
}

Section SectionFactory::createEffectsSection() {
    return Section("Effects")
            .addSubSection(
                    Section("Main")
                            .addParameter(
                                    SynthParameter("Bandwidth")
                                            .number(340)
                                            .max(7)
                                            .descriptions({"Full", "20 kHz", "18 kHz", "16 kHz",
                                                           "14 kHz", "12 kHz", "10 kHz", "8 kHz"})
                            )
                            .addParameter(
                                    SynthParameter("FX Routing")
                                            .number(508)
                                            .max(2)
                                            .descriptions({"Chor/Phas/AM/Gate/Dly", "Gate/Dly/Chor/Phas/AM",
                                                           "Bypass effects"})
                            )
                            .addParameter(
                                    SynthParameter("Bitcrusher depth").number(380)
                            )
                            .addParameter(
                                    SynthParameter("Decimator depth").number(370)
                            )
                            .addParameter(
                                    SynthParameter("Filter HI").number(320)
                            )
                            .addParameter(
                                    SynthParameter("Filter LO").number(321)
                            )
            )
            .addSubSection(
                    Section("Distortion")
                            .addParameter(
                                    SynthParameter("On or Off")
                                            .number(350)
                                            .max(1)
                                            .descriptions({"OFF", "ON"})
                            )
                            .addParameter(
                                    SynthParameter("Type")
                                            .number(354)
                                            .max(3)
                                            .descriptions(
                                                    {"Hard clip", "Soft clip", "Tube 12AX",
                                                     "Tube DSL"})
                            )
                            .addParameter(SynthParameter("Gain PRE").number(351))
                            .addParameter(SynthParameter("Gain POST").number(352))
                            .addParameter(
                                    SynthParameter("Filter POST")
                                            .number(353)
                                            .max(7)
                                            .descriptions({"Full", "20 kHz", "18 kHz", "16 kHz",
                                                           "14 kHz", "12 kHz", "10 kHz", "8 kHz"})
                            )
            )
            .addSubSection(
                    Section("Chorus/Flanger")
                            .addParameter(SynthParameter("DRY").number(360))
                            .addParameter(SynthParameter("WET").number(351))
                            .addParameter(
                                    SynthParameter("Mode")
                                            .number(362)
                                            .max(3)
                                            .descriptions(
                                                    {"Chorus Long", "Chorus Short", "Flanger Long", "Flanger Short"})
                            )
                            .addParameter(SynthParameter("Speed").number(363))
                            .addParameter(SynthParameter("Depth").number(364))
                            .addParameter(SynthParameter("Feedback").number(365))

                            .addParameter(SynthParameter("LR Phase").number(366).type(CENTER_128))
            )
            .addSubSection(
                    Section("Phaser")
                            .addParameter(SynthParameter("DRY").number(310))
                            .addParameter(SynthParameter("WET").number(311))
                            .addParameter(
                                    SynthParameter("Mode")
                                            .number(312)
                                            .max(2)
                                            .descriptions({"Mono", "Stereo", "Cross"})
                            )
                            .addParameter(SynthParameter("Speed").number(314))
                            .addParameter(SynthParameter("Depth").number(313))
                            .addParameter(SynthParameter("Offset").number(316))
                            .addParameter(
                                    SynthParameter("Stages")
                                            .number(317)
                                            .min(4).max(12)
                            )
                            .addParameter(SynthParameter("Feedback").number(315))
                            .addParameter(SynthParameter("LR Phase").number(318).type(CENTER_128))
            )
            .addSubSection(
                    Section("Delay")
                            .addParameter(SynthParameter("DRY").number(300))
                            .addParameter(SynthParameter("WET").number(301))
                            .addParameter(
                                    SynthParameter("Mode")
                                            .number(302)
                                            .max(2)
                                            .descriptions({"Mono", "Stereo", "Cross"})
                            )
                            .addParameter(SynthParameter("Time").number(303))
                            .addParameter(SynthParameter("Feedback").number(304))
                            .addParameter(SynthParameter("Tempo").number(307))
                            .addParameter(SynthParameter("HI").number(305))
                            .addParameter(SynthParameter("LO").number(306))
                            .addParameter(SynthParameter("Multiplier").number(308).min(1))
                            .addParameter(SynthParameter("Divider").number(309).min(1))
                            .addParameter(SynthParameter("Mod Speed").number(298))
                            .addParameter(SynthParameter("Mod Depth").number(299))
                            .addParameter(
                                    SynthParameter("Smear")
                                            .number(291)
                                            .max(7)
                                            .descriptions(
                                                    {"None", "16-bit", "15-bit", "14-bit", "13-bit", "12-bit", "11-bit",
                                                     "10-bit"})
                            )
                            .addParameter(
                                    SynthParameter("2x")
                                            .number(291)
                                            .max(1)
                                            .descriptions({"Off", "2x Delay"})
                            )
            )
            .addSubSection(
                    Section("Reverb")
                            .addParameter(SynthParameter("DRY").number(390))
                            .addParameter(SynthParameter("WET").number(291))
                            .addParameter(
                                    SynthParameter("Mode")
                                            .number(392)
                                            .max(1)
                                            .descriptions({"Plate", "Hall"})
                            )
                            .addParameter(SynthParameter("Decay").number(393))
                            .addParameter(SynthParameter("Damping").number(394))
                            .addParameter(SynthParameter("HPF").number(397))
                            .addParameter(SynthParameter("Modulation Speed").number(395))
                            .addParameter(SynthParameter("Modulation Depth").number(396))

            )
            .addSubSection(
                    Section("Gate")
                            .addParameter(
                                    SynthParameter("On or Off")
                                            .number(385)
                                            .max(1)
                                            .descriptions({"OFF", "ON"})
                            )
                            .addParameter(
                                    SynthParameter("Curve")
                                            .number(386)
                                            .max(1)
                                            .descriptions({"S-Shape 1", "S-Shape 2"})
                            )
                            .addParameter(SynthParameter("Attack").number(387))
                            .addParameter(SynthParameter("Release").number(388))
            )
            .addSubSection(
                    Section("Early Reflections")
                            .addParameter(SynthParameter("DRY").number(294))
                            .addParameter(SynthParameter("WET").number(295))
                            .addParameter(SynthParameter("Room").number(296).max(31))
                            .addParameter(SynthParameter("Taps").number(293).max(32))
                            .addParameter(SynthParameter("Feedback").number(297))
            );
}

Section SectionFactory::createPatchSection() {
    return Section("Patch")
            .addParameter(SynthParameter("Name 1").asciiCharacterType(480))
            .addParameter(SynthParameter("Name 9").asciiCharacterType(488))
            .addParameter(SynthParameter("Name 2").asciiCharacterType(481))
            .addParameter(SynthParameter("Name 10").asciiCharacterType(489))
            .addParameter(SynthParameter("Name 3").asciiCharacterType(482))
            .addParameter(SynthParameter("Name 11").asciiCharacterType(490))            
            .addParameter(SynthParameter("Name 4").asciiCharacterType(483))
            .addParameter(SynthParameter("Name 12").asciiCharacterType(491))
            .addParameter(SynthParameter("Name 5").asciiCharacterType(484))
            .addParameter(SynthParameter("Name 13").asciiCharacterType(492))
            .addParameter(SynthParameter("Name 6").asciiCharacterType(485))
            .addParameter(SynthParameter("Name 14").asciiCharacterType(493))
            .addParameter(SynthParameter("Name 7").asciiCharacterType(486))
            .addParameter(SynthParameter("Name 15").asciiCharacterType(494))
            .addParameter(SynthParameter("Name 8").asciiCharacterType(487))
            .addParameter(SynthParameter("Name 16").asciiCharacterType(495))
            .addParameter(SynthParameter("Name 17").asciiCharacterType(496))
            .addParameter(SynthParameter("Name 25").asciiCharacterType(504))
            .addParameter(SynthParameter("Name 18").asciiCharacterType(497))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Name 19").asciiCharacterType(498))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Name 20").asciiCharacterType(499))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Name 21").asciiCharacterType(500))
            .addParameter(SynthParameter(""))           
            .addParameter(SynthParameter("Name 22").asciiCharacterType(501)) 
            .addParameter(SynthParameter(""))          
            .addParameter(SynthParameter("Name 23").asciiCharacterType(502))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Name 24").asciiCharacterType(503));            
} 

Section SectionFactory::createSequencerSection() {
    return Section("Sequencer")
            .addSubSection(
                    Section("Main")
                            .addParameter(
                                    SynthParameter("On or Off")
                                            .number(428)
                                            .max(1)
                                            .descriptions({"OFF", "ON"})
                            )
                            .addParameter(SynthParameter("Steps").number(430).max(16))
                            .addParameter(SynthParameter("Tempo").number(431))
                            .addParameter(SynthParameter("Multiplier").number(432).min(1))
                            .addParameter(SynthParameter("Velocity").number(429))
                            .addParameter(SynthParameter("Transpose").number(433))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            .addParameter(SynthParameter(""))
                            
                            .addParameter(SynthParameter("Step 1").number(434).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 5").number(438).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 2").number(435).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 6").number(439).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 3").number(436).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 7").number(440).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 4").number(437).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 8").number(441).type(MIDI_NOTE))

                            .addParameter(SynthParameter("Step 9").number(442).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 13").number(446).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 10").number(443).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 14").number(447).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 11").number(444).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 15").number(448).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 12").number(445).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 16").number(449).type(MIDI_NOTE))

            )
            .addSubSection(
                    Section("Steps")
                            .addParameter(SynthParameter("Step 1").number(434).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 5").number(438).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 2").number(435).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 6").number(439).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 3").number(436).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 7").number(440).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 4").number(437).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 8").number(441).type(MIDI_NOTE))

                            .addParameter(SynthParameter("Step 9").number(442).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 13").number(446).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 10").number(443).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 14").number(447).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 11").number(444).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 15").number(448).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 12").number(445).type(MIDI_NOTE))
                            .addParameter(SynthParameter("Step 16").number(449).type(MIDI_NOTE))

            );
}

Section SectionFactory::createExternalControlsSection() {
    return Section("External Ctrls")
            .addSubSection(
                    Section("External Ctrls")
                            //1
                            .addParameter(
                                    SynthParameter("Pitch Temperature")
                                            .number(220)
                                            .type(CENTER_128)
                            )
                            //9
                            .addParameter(
                                    SynthParameter("PWM Temperature")
                                            .number(223)
                                            .type(CENTER_128)
                            )
                            //2
                            .addParameter(
                                    SynthParameter("Pitch CV-1")
                                            .number(221)
                                            .type(CENTER_128)

                            )
                            //10
                            .addParameter(
                                    SynthParameter("PWM CV-1")
                                            .number(224)
                                            .type(CENTER_128)
                            )
                            //3
                            .addParameter(
                                    SynthParameter("Pitch CV-2")
                                            .number(222)
                                            .type(CENTER_128)

                            )
                            //11
                            .addParameter(
                                    SynthParameter("PWM CV-2")
                                            .number(225)
                                            .type(CENTER_128)
                            )
                            //4
                            .addParameter(SynthParameter("Pitch Random").number(203))
                            //12
                            .addParameter(SynthParameter(""))
                            //5
                            .addParameter(
                                    SynthParameter("Filter Temperature")
                                            .number(226)
                                            .type(CENTER_128)
                            )
                            //13
                            .addParameter(SynthParameter("Volume Temperature").number(228))
                            //6
                            .addParameter(
                                    SynthParameter("Filter CV-1")
                                            .number(227)
                                            .type(CENTER_128)
                            )
                            //14
                            .addParameter(SynthParameter("Volume CV-1").number(230))
                            //7
                            .addParameter(
                                    SynthParameter("Filter CV-2")
                                            .number(228)
                                            .type(CENTER_128)
                            )
                            //15
                            .addParameter(SynthParameter("Volume CV-2").number(231))                          
            )
            .addSubSection(
                    Section("LFOs Modulation")
                            //1
                            .addParameter(SynthParameter("Pitch LFO Aftertouch").number(180))
                            //9
                            .addParameter(SynthParameter("Pitch LFO Breath").number(182))
                            //2
                            .addParameter(SynthParameter("Pitch LFO Wheel").number(181))
                            //10
                            .addParameter(SynthParameter("Pitch LFO Foot").number(183))
                            //3
                            .addParameter(SynthParameter("PW LFO Aftertouch").number(184))
                            //11
                            .addParameter(SynthParameter("PW LFO Breath").number(186))
                            //4
                            .addParameter(SynthParameter("PW LFO Wheel").number(183))
                            //12
                            .addParameter(SynthParameter("PW LFO Foot").number(187))
                            //5
                            .addParameter(SynthParameter("Filter LFO Aftertouch").number(188))
                            //9
                            .addParameter(SynthParameter("Filter LFO Breath").number(189))
                            //2
                            .addParameter(SynthParameter("Filter LFO Wheel").number(190))
                            //10
                            .addParameter(SynthParameter("Filter LFO Foot").number(191))
                            //3
                            .addParameter(SynthParameter("AMP LFO Aftertouch").number(192))
                            //11
                            .addParameter(SynthParameter("AMP LFO Breath").number(194))
                            //4
                            .addParameter(SynthParameter("AMP LFO Wheel").number(193))
                            //12
                            .addParameter(SynthParameter("AMP LFO Foot").number(195))
            );
}

Section SectionFactory::createPerformanceControlsSection() {
    return Section("Performance Ctrls")
            .addParameter(SynthParameter("Midi CC 70").performanceControlType(400, 401))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Midi CC 71").performanceControlType(402, 403))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Midi CC 72").performanceControlType(404, 405))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Midi CC 73").performanceControlType(406, 407))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Midi CC 74").performanceControlType(408, 409))
            .addParameter(SynthParameter(""))
            .addParameter(SynthParameter("Midi CC 75").performanceControlType(410, 411))
            .addParameter(SynthParameter(""))            
            .addParameter(SynthParameter("Midi CC 76").performanceControlType(412, 413))
            .addParameter(SynthParameter(""))           
            .addParameter(SynthParameter("Midi CC 77").performanceControlType(414, 415));
}

Section SectionFactory::createMIDIModSection() {
    return Section("MIDI Mod")
            .addSubSection(
                    Section("Midi Modulation")
                            //1
                            .addParameter(
                                    SynthParameter("Pitch Aftertouch")
                                            .number(200)
                                            .type(CENTER_128)
                            )
                            //9
                            .addParameter(
                                    SynthParameter("PWM Aftertouch")
                                            .number(204)
                                            .type(CENTER_128)
                            )
                            //2
                            .addParameter(
                                    SynthParameter("Pitch Breath")
                                            .number(201)
                                            .type(CENTER_128)
                            )
                            //10
                            .addParameter(
                                    SynthParameter("PWM Breath")
                                            .number(206)
                                            .type(CENTER_128)
                            )
                            //3
                            .addParameter(
                                    SynthParameter("Pitch Foot")
                                            .number(202)
                                            .type(CENTER_128)
                            )
                            //11
                            .addParameter(
                                    SynthParameter("PWM Foot")
                                            .number(207)
                                            .type(CENTER_128)
                            )
                            //4
                            .addParameter(SynthParameter(""))
                            //12
                            .addParameter(
                                    SynthParameter("PWM Wheel")
                                            .number(205)
                                            .type(CENTER_128)
                            )
                            //5
                            .addParameter(
                                    SynthParameter("Filter Aftertouch")
                                            .number(208)
                                            .type(CENTER_128)
                            )
                            //13
                            .addParameter(SynthParameter("Volume Aftertouch").number(212))
                            //6
                            .addParameter(
                                    SynthParameter("Filter Breath")
                                            .number(210)
                                            .type(CENTER_128)
                            )
                            //14
                            .addParameter(SynthParameter("Breath").number(214))
                            //7
                            .addParameter(
                                    SynthParameter("Foot")
                                            .number(211)
                                            .type(CENTER_128)
                            )
                            //15
                            .addParameter(SynthParameter("Foot").number(215)) 
                            //8                           
                            .addParameter(
                                    SynthParameter("Wheel")
                                            .number(209)
                                            .type(CENTER_128)
                            )
                            //16
                            .addParameter(SynthParameter("Wheel").number(213))        
            )
            .addSubSection(
                    Section("LFOs Modulation")
                            //1
                            .addParameter(SynthParameter("Pitch LFO Aftertouch").number(180))
                            //9
                            .addParameter(SynthParameter("Pitch LFO Breath").number(182))
                            //2
                            .addParameter(SynthParameter("Pitch LFO Wheel").number(181))
                            //10
                            .addParameter(SynthParameter("Pitch LFO Foot").number(183))
                            //3
                            .addParameter(SynthParameter("PW LFO Aftertouch").number(184))
                            //11
                            .addParameter(SynthParameter("PW LFO Breath").number(186))
                            //4
                            .addParameter(SynthParameter("PW LFO Wheel").number(183))
                            //12
                            .addParameter(SynthParameter("PW LFO Foot").number(187))
                            //5
                            .addParameter(SynthParameter("Filter LFO Aftertouch").number(188))
                            //9
                            .addParameter(SynthParameter("Filter LFO Breath").number(189))
                            //2
                            .addParameter(SynthParameter("Filter LFO Wheel").number(190))
                            //10
                            .addParameter(SynthParameter("Filter LFO Foot").number(191))
                            //3
                            .addParameter(SynthParameter("AMP LFO Aftertouch").number(192))
                            //11
                            .addParameter(SynthParameter("AMP LFO Breath").number(194))
                            //4
                            .addParameter(SynthParameter("AMP LFO Wheel").number(193))
                            //12
                            .addParameter(SynthParameter("AMP LFO Foot").number(195))
            );
}

Section SectionFactory::createGlobalSection() {
    return Section("Global")
            .addParameter(
                    SynthParameter("Transpose")
                            .type(CENTER_128)
                            .number(241)
            )
            .addParameter(SynthParameter("Ring Mod").number(271))
            .addParameter(SynthParameter("Bend Up").number(242))
            .addParameter(SynthParameter("Bend Down").number(243))
            .addParameter(
                    SynthParameter("Legato Mode")
                            .number(244)
                            .max(1)
                            .descriptions({" Polyphonic ", "Monophonic/Legato"})
            )
            .addParameter(SynthParameter(""))
            .addParameter(
                    SynthParameter("Glide")
                            .number(245)
                            .max(2)
                            .descriptions({"Off", "Always", "Only Legato Notes"})
            )
            .addParameter(SynthParameter("Glide Time").number(246))
            .addParameter(SynthParameter("Velocity offset").number(249))
            .addParameter(SynthParameter("Tuning").number(251))
            .addParameter(SynthParameter("Temperature offset").number(239))
            .addParameter(SynthParameter("Volume").number(509))
                            .addParameter(SynthParameter("Panning").number(247).type(CENTER_128))
                            .addParameter(
                                    SynthParameter("Gain Pre-FX")
                                            .number(510)
                                            .max(3)
                                            .descriptions({"0 dB", "+6 dB", "+12 dB", "+18 dB"})
                            )
                            .addParameter(
                                    SynthParameter("Gain Post-FX")
                                            .number(511)
                                            .max(3)
                                            .descriptions({"0 dB", "+6 dB", "+12 dB", "+18 dB"})
                            );
            
}
