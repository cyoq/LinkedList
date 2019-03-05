
#include "functionality.h"

template <typename T>
void removeBack(node<T> * &head) {
	if (head == NULL) { return; }
	if (head->next == NULL) {
		delete head;
		head = nullptr;
	}
	else {
		removeBack(head->next);
	}
}



