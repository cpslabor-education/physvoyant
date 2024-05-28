#ifndef DDELEGATE_ACTION
#define DDELEGATE_ACTION

/// <summary>
/// Delegate action, containing the pointer to a function and other information
/// </summary>
/// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template<typename Return, typename... Params>
class DDelegateAction
{
public:
	DDelegateAction() : functionPointer(nullptr), identifier(0), timesCalled(0)
	{

	}
	// DDelegateAction(int ID);
	DDelegateAction(Return(*function)(Params...)) : functionPointer(function), identifier(0), timesCalled(0)
	{

	}
	DDelegateAction(Return(*function)(Params...), int ID) : functionPointer(function), identifier(ID), timesCalled(0)
	{

	}
	~DDelegateAction()
	{

	}

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>The returned value of the function</returns>
	Return Fire(Params... p)
	{
		++timesCalled;
		return (*functionPointer)(p...);
	}

	int ID()
	{
		return identifier;
	}

	unsigned int TimesCalled()
	{
		return timesCalled;
	}

	Return(*functionPointer)(Params...);
private:
	int identifier;
	unsigned int timesCalled;

};


/// <summary>
/// Delegate action, containing the pointer to a function and other information
/// </summary>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template<typename... Params>
class DDelegateAction<void, Params...>
{
public:
	DDelegateAction() : functionPointer(nullptr), identifier(0), timesCalled(0)
	{

	}
	// DDelegateAction(int ID);
	DDelegateAction(void (*function)(Params...)) : functionPointer(function), identifier(0), timesCalled(0)
	{

	}
	DDelegateAction(void (*function)(Params...), int ID) : functionPointer(function), identifier(ID), timesCalled(0)
	{

	}
	~DDelegateAction()
	{

	}

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>The returned value of the function</returns>
	void Fire(Params... p)
	{
		++timesCalled;
		(*functionPointer)(p...);
	}

	int ID()
	{
		return identifier;
	}

	unsigned int TimesCalled()
	{
		return timesCalled;
	}

	void (*functionPointer)(Params...);
private:
	int identifier;
	unsigned int timesCalled;

};


template<typename Return, typename Class, typename... Params>
class DDelegateAction<Return(Class::*)(Params...)>
{
public:
	DDelegateAction() : functionPointer(nullptr), identifier(0), timesCalled(0)
	{

	}
	// DDelegateAction(int ID);
	DDelegateAction(Return(Class::* function)(Params...)) : functionPointer(function), identifier(0), timesCalled(0)
	{

	}
	DDelegateAction(Return(Class::* function)(Params...), int ID) : functionPointer(function), identifier(ID), timesCalled(0)
	{

	}
	~DDelegateAction()
	{

	}

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>The returned value of the function</returns>
	Return Fire(Class* caller, Params... p)
	{
		++timesCalled;
		return (caller->*functionPointer)(p...);
	}

	int ID()
	{
		return identifier;
	}

	unsigned int TimesCalled()
	{
		return timesCalled;
	}

	Return(Class::* functionPointer)(Params...);
private:
	int identifier;
	unsigned int timesCalled;

};


template<typename Class, typename... Params>
class DDelegateAction<void (Class::*)(Params...)>
{
public:
	DDelegateAction() : functionPointer(nullptr), identifier(0), timesCalled(0)
	{

	}
	// DDelegateAction(int ID);
	DDelegateAction(void(Class::* function)(Params...)) : functionPointer(function), identifier(0), timesCalled(0)
	{

	}
	DDelegateAction(void(Class::* function)(Params...), int ID) : functionPointer(function), identifier(ID), timesCalled(0)
	{

	}
	~DDelegateAction()
	{

	}

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>The returned value of the function</returns>
	void Fire(Class* caller, Params... p)
	{
		++timesCalled;
		(caller->*functionPointer)(p...);
	}

	int ID()
	{
		return identifier;
	}

	unsigned int TimesCalled()
	{
		return timesCalled;
	}

	void (Class::* functionPointer)(Params...);
private:
	int identifier;
	unsigned int timesCalled;

};


#endif