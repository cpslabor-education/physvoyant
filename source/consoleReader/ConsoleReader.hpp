#ifndef CONSOLE_READER
#define CONSOLE_READER

class ConsoleReader
{
public:
	ConsoleReader(ConsoleReader& other) = delete;

	void operator=(const ConsoleReader& other) = delete;

	~ConsoleReader();

	static ConsoleReader* GetInstance()
	{
		if (instancePtr == nullptr)
		{
			instancePtr = new ConsoleReader();
		}
		return instancePtr;
	}

	void GetCommand(); // MOSZE keyreader

private:
	ConsoleReader();
	void Initialise();
	static ConsoleReader* instancePtr;

};

ConsoleReader* ConsoleReader::instancePtr = nullptr; // Move this to the .cpp file



#endif
