#include "EventList.h"

NS_BEGIN

EventList::EventList(int e, int id, EventListener *l)
:m_Id(id)
,m_Listener(l){
	m_Events.push_back(e);
}

EventList::EventList(int e[], int id, EventListener *l)
:m_Id(id)
,m_Listener(l){
	for( int i = 0; e[i] > SDLK_FIRST && e[i] < SDLK_END; i++ ){
		m_Events.push_back(e[i]);
	}
}

EventList::~EventList(){
}

bool EventList::verify(vector<SDL_Event> events, Uint8 *k){
	vector<SDL_Event>::iterator it;
	vector<int>::iterator i;
	int n = 0;
	int x, y;
	for( it = events.begin(); it != events.end(); it++ ){
		SDL_Event e = (*it);
		x = e.motion.x;
		y = e.motion.y;
		for( i = m_Events.begin(); i != m_Events.end(); i++ ){
			if( e.type == SDL_QUIT && (*i) == SDL_QUIT )
				n++;
			else if( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == (*i) ){
				n++;
			}
			else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == (*i) )
				n++;
		}

	}
	if( n >= m_Events.size() ){
		Event e;
		e.id = m_Id;
		e.mouseX = x;
		e.mouseY = y;
		m_Listener->treat(e);
		return true;
	}
	return false;
}

NS_END
