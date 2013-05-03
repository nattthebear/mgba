#ifndef VIDEO_SOFTWARE_H
#define VIDEO_SOFTWARE_H

#include "gba-video.h"

#include <pthread.h>

struct GBAVideoSoftwareBackground {
	int index;
	int enabled;
	int priority;
	uint32_t charBase;
	int mosaic;
	int multipalette;
	uint32_t screenBase;
	int overflow;
	int size;
	int target1;
	int target2;
	uint16_t x;
	uint16_t y;
	uint32_t refx;
	uint32_t refy;
	uint16_t dx;
	uint16_t dmx;
	uint16_t dy;
	uint16_t dmy;
	uint32_t sx;
	uint32_t sy;
};

enum BlendEffect {
	BLEND_NONE = 0,
	BLEND_ALPHA = 1,
	BLEND_BRIGHTEN = 2,
	BLEND_DARKEN = 3
};

enum {
	GBA_COLOR_WHITE = 0x00F8F8F8,
	OFFSET_PRIORITY = 29
};

enum PixelFlags {
	FLAG_FINALIZED = 0x80000000,
	FLAG_PRIORITY = 0x60000000,
	FLAG_IS_BACKGROUND = 0x10000000,
	FLAG_UNWRITTEN = 0x08000000,
	FLAG_TARGET_1 = 0x04000000,
	FLAG_TARGET_2 = 0x02000000
};

struct GBAVideoSoftwareRenderer {
	struct GBAVideoRenderer d;

	uint32_t* outputBuffer;
	unsigned outputBufferStride;

	union GBARegisterDISPCNT dispcnt;

	// BLDCNT
	unsigned target1Obj;
	unsigned target1Bd;
	unsigned target2Obj;
	unsigned target2Bd;
	enum BlendEffect blendEffect;
	uint32_t normalPalette[512];
	uint32_t variantPalette[512];

	uint16_t blda;
	uint16_t bldb;
	uint16_t bldy;

	struct GBAVideoSoftwareBackground bg[4];

	uint32_t* row;
	int start;
	int end;

	pthread_mutex_t mutex;
	pthread_cond_t upCond;
	pthread_cond_t downCond;
};

void GBAVideoSoftwareRendererCreate(struct GBAVideoSoftwareRenderer* renderer);

#endif
