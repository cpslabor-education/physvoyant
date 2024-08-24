#ifndef CHUNKED_VECTOR
#define CHUNKED_VECTOR

#include <vector>
#include <iostream>

#define CHUNK_SIZE 1024
#define MAX_CHUNKS 1024

template<typename T>
class ChunkedVector
{
public:
	ChunkedVector()
	{
		chunks.reserve(MAX_CHUNKS);
	}

	bool push_back(const T& value)
	{
		if (chunks.size() > MAX_CHUNKS)
		{
			return false;
		}
		if ((chunks.size() == 0 || chunks.back().size() >= CHUNK_SIZE))
		{
			chunks.push_back(std::vector<T>());
			chunks.back().reserve(CHUNK_SIZE);
		}
		chunks.back().push_back(value);
		return true;
	}

	bool push_back(T&& value)
	{
		if (chunks.size() > MAX_CHUNKS)
		{
			return false;
		}
		if (chunks.size() == 0 || chunks.back().size() >= CHUNK_SIZE)
		{
			chunks.push_back(std::vector<T>());
			chunks.back().reserve(CHUNK_SIZE);
		}
		chunks.back().push_back(std::move(value)); // RValue, std::move is necessary
		return true;
	}

	T& operator[](size_t index)
	{
		size_t chunkIndex = index / CHUNK_SIZE;
		size_t indexInChunk = index % CHUNK_SIZE;
		return (chunks[chunkIndex])[indexInChunk];
	}

	const T& operator[](size_t index) const
	{
		size_t chunkIndex = index / CHUNK_SIZE;
		size_t indexInChunk = index % CHUNK_SIZE;
		return (chunks[chunkIndex])[indexInChunk];
	}

	size_t size() const
	{
		if (chunks.empty())
		{
			return 0;
		}
		size_t fullChunksCount = (chunks.size() - 1) * CHUNK_SIZE;
		size_t lastChunkSize = chunks.back().size();
		return fullChunksCount + lastChunkSize;
	}

private:
	std::vector<std::vector<T>> chunks;
};

#endif
