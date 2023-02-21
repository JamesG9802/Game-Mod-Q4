#ifndef SmartPointer_h
#define SmartPointer_h

template <typename obj> class SmartPointer {
	public:
		obj* pointer;

		explicit SmartPointer(obj* pointer = NULL)
		{
			this->pointer = pointer;
		}
		~SmartPointer()
		{
			delete pointer;
		}
		obj& operator*()
		{
			return pointer;
		}
};
#endif // !SmartPointer_h
