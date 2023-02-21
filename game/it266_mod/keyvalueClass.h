#ifndef KeyValueClass
#define KeyValueClass

template <typename Key, typename Value> class keyvalueClass {
	public:
		Key key;
		Value value;
		keyvalueClass()
		{

		}
		keyvalueClass(Key key , Value value)
		{
			this->key = key;
			this->value = value;
		}
	bool operator<(const keyvalueClass& obj)
	{
		if (this->key == obj.key)
			return this->value < obj.value;
		return this->key < obj.key;
	}
	bool operator>(const keyvalueClass& obj)
	{
		if (this->key == obj.key)
			return this->value > obj.value;
		return this->key > obj.key;
	}
	bool operator==(const keyvalueClass& obj)
	{
		return this->key == obj.key && this->value == obj.value;
	}
};

#endif // !KeyValueClass