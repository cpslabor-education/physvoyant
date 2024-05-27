#ifndef REFLECTION_OBJ
#define REFLECTION_OBJ

template <class T>
class ReflectionObject
{
public:

	void operator=(const ReflectionObject& other);
	ReflectionObject(ReflectionObject& other);

	ReflectionObject(T& variable, const char* name) : variable(variable), name(name)
	{

	}

	~ReflectionObject()
	{

	}

	T& GetReference()
	{
		return this->variable;
	}

	const char* GetName()
	{
		return name;
	}

private:
	T& variable;
	const char* name;

};

#endif // !DTYPE_H
