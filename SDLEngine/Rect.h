#ifndef __RECT_H__
#define __RECT_H__

#include "Headers.h"

NS_BEGIN

class Rect {
	public:
		float x, y, w, h;

		Rect();
		Rect(float, float, float, float);
		virtual ~Rect();

		Rect operator = (Rect);
};

NS_END

#endif
