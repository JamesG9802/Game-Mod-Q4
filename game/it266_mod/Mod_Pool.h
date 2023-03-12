#ifndef MOD_POOL_H
#define MOD_POOL_H
#include "vectorClass.h"

template <typename T> class Mod_Pool
{
private:
	vectorClass<T> freeItems;
	vectorClass<T> usedItems;
public:

	Mod_Pool() {};
	~Mod_Pool() {};
	T getItem()
	{
		T item = freeItems.size() == 0 ? T() : freeItems.pop();
		usedItems.push(item);
		return item;
	}
	void deleteItem(T item)
	{
		usedItems.removeAt(usedItems.indexOf(item));
		freeItems.push(item);
	}
};
#endif