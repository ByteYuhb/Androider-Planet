#include "Subject.h"
void Subject::_addObserve(Observer& obs) {
	_list.push_back(&obs);
}
void Subject::addObserve(Observer* obs) {
	_list.push_back(obs);
}
void Subject::notify(void* pArg) {
	for (Observer* obs:_list) {
		obs->update(pArg);
	}
}