#include "Size.h"

NS_BEGIN

Size::Size()
:width(0),height(0){
}

Size::Size(int w, int h)
:width(w), height(h){
}

Size::~Size(){
}

int Size::getWidth(){
	return width;
}

int Size::getHeight(){
	return height;
}

void Size::setWidth(int w){
	width = w;
}

void Size::setHeight(int h){
	height = h;
}

NS_END
