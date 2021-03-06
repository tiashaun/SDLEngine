#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Headers.h"
#include "Rect.h"
#include "Color.h"
#include "Exception.h"

NS_BEGIN

class Image : public Rect{
	private:
		uint m_Image;
		Rect rect;

		Image();

		void loadSurface(SDL_Surface*);
	public:
		float rotation;
		static Color colorKey;

		~Image();
		static Image *loadImage(String file, Rect rect);
		static Image *loadImage(String file);
		static Image *createImage(Rect, Color);

		void draw();
		
};

NS_END

#endif

