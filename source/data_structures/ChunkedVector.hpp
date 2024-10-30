#ifndef CHUNKED_VECTOR
#define CHUNKED_VECTOR

#include <vector>
#include <iostream>

template<typename T>
class ChunkedVector
{
	const size_t chunkSize;
	std::vector<std::vector<T>> chunks;
public:
	ChunkedVector(size_t chunkSize = 1024) : chunkSize(chunkSize)
	{
		chunks.reserve(this->chunkSize);
	}

	void push_back(const T& value)
	{
		if ((chunks.size() == 0 || chunks.back().size() >= chunkSize))
		{
			chunks.push_back(std::vector<T>());
			chunks.back().reserve(chunkSize);
		}
		chunks.back().push_back(value);
	}

	void push_back(T&& value)
	{
		if (chunks.size() == 0 || chunks.back().size() >= chunkSize)
		{
			chunks.push_back(std::vector<T>());
			chunks.back().reserve(chunkSize);
		}
		chunks.back().push_back(std::move(value)); // RValue, std::move is necessary
	}

	T& operator[](size_t index)
	{
		return (chunks[index / chunkSize])[index % chunkSize];
	}

	const T& operator[](size_t index) const
	{
		return (chunks[index / chunkSize])[index % chunkSize];
	}

	size_t size() const
	{
		if (chunks.empty())
		{
			return 0;
		}
		size_t fullChunksCount = (chunks.size() - 1) * chunkSize;
		size_t lastChunkSize = chunks.back().size();
		return fullChunksCount + lastChunkSize;
	}
};

#endif
