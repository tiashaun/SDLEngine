#include "Image.h"

NS_BEGIN

Color Image::colorKey(0,255,0);

Image::Image()
:rotation(0.0f){
	Rect();
}

Image::~Image(){
	std::cout << "Oi\n";
	glDeleteTextures(1, &m_Image);
}

Image *Image::loadImage(String file){
	Image *ret = new Image();
	SDL_Surface *s;

	s = IMG_Load(file.c_str());
	if( s == NULL )
		throw Exception("IMG Error: %s", IMG_GetError());

	if( SDL_SetColorKey(s, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(s->format, colorKey.r, colorKey.g, colorKey.b)) == -1 )
		throw Exception("SDL Error: %s", SDL_GetError());

	ret->loadSurface(s);
	return ret;
}

Image *Image::loadImage(String file, Rect rect){
	Image *ret = new Image();
	SDL_Surface *s, *r;
	SDL_Rect src, dest;

	src.x = rect.x;
	src.y = rect.y;
	src.w = rect.w;
	src.h = rect.h;

	dest.x = 0;
	dest.y = 0;
	dest.w = 0;
	dest.h = 0;

	s = IMG_Load(file.c_str());
	if( s == NULL )
		throw Exception("IMG Error: %s", IMG_GetError());

	r = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	if( r == NULL )
		throw Exception("SDL Error: %s", SDL_GetError());

	SDL_FillRect(r, NULL, SDL_MapRGB(r->format,0,0,0));

	if( SDL_BlitSurface(s, &src, r, &dest) != 0 )
		throw Exception("SDL Error: %s", SDL_GetError());

	if( SDL_SetColorKey(r, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(r->format, colorKey.r, colorKey.g, colorKey.b)) == -1 )
		throw Exception("SDL Error: %s", SDL_GetError());

	ret->loadSurface(r);
	SDL_FreeSurface(s);
	return ret;
}

Image *Image::createImage(Rect rect, Color color){
	Image *ret = new Image();
	SDL_Surface *s;

	s = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	if( s == NULL )
		throw Exception("SDL Error: %s", SDL_GetError());

	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, color.r, color.b, color.g));
	
	ret->loadSurface(s);
	ret->x = rect.x;
	ret->y = rect.y;

	return ret;
}

void Image::loadSurface(SDL_Surface *s){
	GLenum format = GL_NONE;
	GLint bpp;
	SDL_Surface *t = SDL_DisplayFormatAlpha(s);
	if( t == NULL )
		throw Exception("SDL Error: %s", SDL_GetError());

	SDL_FreeSurface(s);
	s = t;

	w = s->w;
	h = s->h;
	bpp = s->format->BytesPerPixel;

	if( bpp == 4 ){
		if( s->format->Rmask == 0x000000ff )
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}
	else if( bpp == 3 ){
		if( s->format->Rmask == 0x000000ff )
			format = GL_RGB;
		else
			format = GL_BGR;
	}

	glGenTextures(1, &m_Image);
	glBindTexture(GL_TEXTURE_2D, m_Image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, bpp, w, h, 0, format, GL_UNSIGNED_BYTE, s->pixels);

	SDL_FreeSurface(s);
}

void Image::draw(){
	glBindTexture(GL_TEXTURE_2D, m_Image);
	glLoadIdentity();

	glTranslatef(x, y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(w, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(w, h);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(0.0f, h);
	glEnd();
}

NS_END

