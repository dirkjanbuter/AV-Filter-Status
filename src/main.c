#include <math.h>
#include <stdarg.h>

#include "imgbuffer.h"
#include "bitfont.h"

static int _w = 0;
static int _h = 0;
static int _framecount = 0;
static int _fps = 0;

static int _s = 0;
static int _sizebytes = 0;

static IMGBUFFER _backbuffer;
static BITFONT bitfont;

BOOL video(char *text)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int i, j;
	unsigned char statusinfo[2048];
	int statusinfolen = 0;
	float duration = (float)_framecount/(float)_fps;
	int msec = (int)(duration*1000)%1000;
	int sec = (int)duration%60;
	int min = (int)(duration/60)%60;
	int hour = (int)(duration/3600)%60;

	statusinfolen = snprintf((char*)statusinfo, sizeof(statusinfo), " %s | Date: %02d-%02d-%d | Time: %02d:%02d:%02d | FPS: %03i | Frame: %06i | Elapsed: %03i:%02i:%02i:%03i ", text, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, _fps, _framecount, hour, min, sec, msec);
	for(j = _h - 14; j < _h; j++)
	for(i = _w - statusinfolen * 8 - 3; i < _w; i++)
	    imgbuffer_setpixelblend(&_backbuffer, i, j, 0xff, 0xff, 0xff, 0xcc);
	bitfont_text(&bitfont, &_backbuffer, _w - statusinfolen * 8, _h - 12, statusinfo, statusinfolen);

	return TRUE;
}

int filtercreate(int fps)
{
    _fps = fps;

    bitfont_create(&bitfont, "../resources/bitfont.png");

    return 1;
}

void filterdestroy()
{
    bitfont_destroy(&bitfont);
}


int filtervideo(unsigned char *buffer, int w, int h, unsigned int color, char *text, int64_t framecount)
{
    _w = w;
    _h = h;
    _framecount = framecount;

    _s = _w * _h;
    _sizebytes = _s * 4;

    _backbuffer.data = buffer;
    _backbuffer.w = _w;
    _backbuffer.h = _h;
    _backbuffer.s = _sizebytes;

    srand(_framecount);

    return video(text);
}

int filteraudio(float *frame, int64_t framecount, float elapsed)
{

	return TRUE;
}

