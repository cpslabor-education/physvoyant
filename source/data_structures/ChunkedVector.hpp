#ifndef CHUNKED_VECTOR
#define CHUNKED_VECTOR

#include <vector>
#include <iostream>

template<typename T>
class ChunkedVector
{
	size_t chunkSize;
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

	void erase(size_t index)
	{
		if (index >= size())
		{
			throw std::out_of_range("Index out of range");
		}

		chunks[index / chunkSize].erase(chunks[index / chunkSize].begin() + index % chunkSize);

		// Remove empty chunks
		while (!chunks.empty() && chunks.back().empty())
		{
			chunks.pop_back();
		}
	}

	void erase(size_t first, size_t last)
	{
		if (first >= last || last > size())
		{
			throw std::out_of_range("Invalid range");
		}

		//for (size_t i = first; i < last; i++)
		//{
		//	erase(i);
		//}
		//return;

		size_t firstChunkIndex = first / chunkSize;
		size_t firstElemIndex = first % chunkSize;
		size_t lastChunkIndex = last / chunkSize;
		size_t lastElemIndex = last % chunkSize;

		if (firstChunkIndex == lastChunkIndex)
		{
			erase(firstChunkIndex);
			return;
		}
		else
		{
			if (firstChunkIndex == lastChunkIndex)
			{
				chunks[firstChunkIndex].erase(chunks[firstChunkIndex].begin() + firstElemIndex, chunks[firstChunkIndex].begin() + lastElemIndex);
			}
			else
			{
				chunks[firstChunkIndex].erase(chunks[firstChunkIndex].begin() + firstElemIndex, chunks[firstChunkIndex].end());
				for (size_t i = 1; i < lastChunkIndex - firstChunkIndex - 1; i++)
				{
					std::vector<T>& current = chunks[i];
					chunks[i].clear();
				}
				chunks[lastChunkIndex].erase(chunks[lastChunkIndex].begin(), chunks[lastChunkIndex].begin() + lastElemIndex);
			}
		}

		// Remove empty chunks
		while (!chunks.empty() && chunks.back().empty())
		{
			chunks.pop_back();
		}
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
