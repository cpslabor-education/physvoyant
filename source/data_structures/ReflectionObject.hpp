#ifndef REFLECTION_OBJ
#define REFLECTION_OBJ

template <class T>
class ReflectionObject
{
public:

	void operator=(const ReflectionObject& other);
	ReflectionObject(ReflectionObject& other);

	ReflectionObject(T& referencedValue, const char* name) : referencedValue(referencedValue), name(name)
	{

	}

	~ReflectionObject()
	{

	}

	T& GetReference()
	{
		return this->referencedValue;
	}

	const char* GetName()
	{
		return name;
	}

private:
	T& referencedValue;
	const char* name;

};

template <typename Return, typename... Params>
class ReflectionObject<Return(*)(Params...)>

{
public:

	void operator=(const ReflectionObject& other);
	ReflectionObject(ReflectionObject& other);

	ReflectionObject(Return(*referencedValue)(Params...), const char* name) : referencedValue(referencedValue), name(name)
	{

	}

	~ReflectionObject()
	{

	}

	Return(*GetReference())(Params...)
	{
		return this->referencedValue;
	}

	const char* GetName()
	{
		return name;
	}

private:
	Return(*referencedValue)(Params...);
	const char* name;

};

template <typename Return, typename Class, typename... Params>
class ReflectionObject<Return(Class::*)(Params...)>

{
public:

	void operator=(const ReflectionObject& other);
	ReflectionObject(ReflectionObject& other);

	ReflectionObject(Return(Class::* referencedValue)(Params...), const char* name) : referencedValue(referencedValue), name(name)
	{

	}

	~ReflectionObject()
	{

	}

	Return(Class::* GetReference())(Params...)
	{
		return this->referencedValue;
	}

	const char* GetName()
	{
		return name;
	}

private:
	Return(Class::* referencedValue)(Params...);
	const char* name;

};


#endif // !DTYPE_H
