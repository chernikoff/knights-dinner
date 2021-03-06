#ifndef _PriorityDinner_H_
#define _PriorityDinner_H_

#include "Dinner.h"
#include "Knight/Knight.h"

namespace knights
{

/*!
	Алгоритм обеда:
		формируем очередь HungerQuery, по которой выдаем разрешение
*/

class PriorityDinner :
	public Dinner
{
	public:
		PriorityDinner( const int& num = 5 );
		PriorityDinner( const Dinner& dinner );
		virtual ~PriorityDinner();
		virtual void step(); // шаг обеда
		virtual void start(); // начать обед
		virtual const std::string getName() { return "PriorityDinner"; }
		
		class HungerQuery
		{
			public:
				bool operator()( Knight*& left, Knight*& right) const { return left->getHunger() > right->getHunger(); } // Сначала идут более голодные рыцари
		};
		
	protected:
		typedef std::list<Knight*> HungryKnights;
		HungryKnights hungryKnights; // список рыцарей отсортированный по голоду
		
	private:
		unsigned int max_permitions_;
};

}
#endif //_PriorityDinner_H_