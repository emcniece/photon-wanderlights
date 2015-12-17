#include <FastLED.h>
#include <LightString.h>
#include <LightStringEffects.h>

#include "utilities.h"
#include "NodeTest.h"
#include "BrushStrokes.h"
#include "Wander.h"
#include "Bands.h"
#include "Edges.h"
#include "Bars.h"

#include "GradientRoll.h"
#include "GradientNodes.h"
#include "Particles.h"

#include "Wave.h"
#include "Overlay.h"

const uint8_t kDataPin = 7;
const EOrder kColorOrder = GRB;

const uint32_t kProgramLength = 15000;
const uint16_t kTotalLEDs = 410;

void programEvent(ILightProgram &lightProgram, EPlayState state);

RGBBuffer ledBuffer(kTotalLEDs);
TPixelBuffer<RGBA> backBuffer1(kTotalLEDs);
TPixelBuffer<RGBA> backBuffer2(kTotalLEDs);
TPixelBuffer<RGBA> backBuffer3(kTotalLEDs);

ProgramManager<RGBA, 3, 10, 6> programManager;

// #define B_LIGHT_GREEN_GRADIENT 			CRGBPalette(CRGB(0, 255, 0), CRGB::White, CRGB(0, 255, 0))

TPalette<RGBA> B_LIGHT_GREEN_GRADIENT(CRGB(32, 255, 96), CRGB::Black, CRGB(32, 255, 96));

// Bands bands;

Wander wander0;
BrushStrokes brushStrokes0;
GradientRoll gradientRoll0, gradientRoll1;
Particles particles0;
GradientNodes gradientNodes0;

TTwinkle<RGBA> twinkle1(130);
Wave wave1;
Overlay overlay1;

void setupColors() {
	Serial.print(F("Setting up colors..."));

	//Swatches.add(RGBA(255, 255, 255, 255));
	//Swatches.add(RGBA(255, 0, 96, 255));
	Swatches.add(RGBA(230, 80, 0, 255));
	Swatches.add(RGBA(230, 70, 0, 255));
	Swatches.add(RGBA(255, 160, 0, 255));
	Swatches.add(RGBA(255, 92, 0, 255));
	// Swatches.add(RGBA(0, 240, 128, 255));
	// Swatches.add(RGBA(0, 255, 128, 255));

	Swatches.shuffle();

	// Palettes.add(RAINBOW_GRADIENT);
	Palettes.add(RED_ORGANGE_GRADIENT);

	Palettes.add(YELLOW_GRADIENT);
	// Palettes.add(WHITE_GRADIENT);
	Palettes.add(BLUE_WHITE_GRADIENT);
	Palettes.add(GREEN_YELLOW_GRADIENT);
	// Palettes.add(CYAN_PINK_GRADIENT);

	// Palettes.add(BLUE_WHITE_GRADIENT);
	Palettes.add(BLUE_YELLOW_BLACK_GRADIENT);
	// Palettes.add(RED_WHITE_BLACK_GRADIENT);
	
	Palettes.shuffle();

	// Palettes.add(GREEN_GRADIENT);
	// Palettes.add(YELLOW_GRADIENT);
	// Palettes.add(BLUE_GREEN_GRADIENT);

	//Palettes.add(B_LIGHT_GREEN_GRADIENT);

	Serial.println(F("done"));
}

void setup() {
	Serial.begin(9600);	
	delay(1000);
	Serial.println(("\n - Wanderlights Lights Startup - \n"));
	
	randomSeed(analogRead(0));

	FastLED.addLeds<WS2812B, kDataPin, kColorOrder>(ledBuffer.pixels, kTotalLEDs);
	blink();
	FastLED.setCorrection(TypicalSMD5050);
	// FastLED.setTemperature(Candle);

	setupColors();

	programManager.setMaxFPS(30);

	programManager.addLightSection(ledBuffer);
	programManager.addBufferToLightSection(0, backBuffer1);
	programManager.addBufferToLightSection(0, backBuffer2);
	programManager.addBufferToLightSection(0, backBuffer3);

	programManager.setProgramEventHandler(programEvent);
	programManager.setMaxProgramLength(kProgramLength);

	programManager.setPlayMode(PLAY_MODE_ONCE, 1);

	//
	// programManager.addLightProgram(*(new Edges()));

	// programManager.addLightProgram(wander0, 0);
	// programManager.addLightProgram(brushStrokes0);
	// programManager.addLightProgram(gradientRoll0, 0);
	// programManager.addLightProgram(gradientRoll1, 1);
	programManager.addLightProgram(particles0, 0);
	// programManager.addLightProgram(gradientNodes0, 0);

	// programManager.addLightProgram(wave1, 1);
	// programManager.addLightProgram(twinkle1, 1);
	programManager.addLightProgram(overlay1, 1);

//	programManager.shufflePrograms();

	blink(CRGB::Green, 8, 40);

	programManager.startRandomProgram(0);
	// programManager.startRandomProgram(1);
}

void programEvent(ILightProgram &lightProgram, EPlayState state) {
	if (state == PROGRAM_FINISHED) {
		Palettes.next();
	}
}

void loop() {
	programManager.loop();
	FastLED.show();
}
