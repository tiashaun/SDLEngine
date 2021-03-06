#ifndef __EVENTLIST_H__
#define __EVENTLIST_H__

#include "Headers.h"
#include "EventListener.h"
#include "List.h"

NS_BEGIN

class EventList {
	private:
		vector<int> m_Events;
		int m_Id;
		EventListener *m_Listener;

	public:
		EventList(int[], int, EventListener *);
		EventList(int, int, EventListener *);
		virtual ~EventList();

		bool verify(vector<SDL_Event>, Uint8 *);
};

NS_END

#endif
