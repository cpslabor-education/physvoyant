#ifndef OCTTREE
#define OCTTREE

template <typename T>
class OctTree;


#include "../defines.hpp"
#include INCL_GLM
#include "ChunkedVector.hpp"


template <typename T>
class OctTree
{
	VECTOR3 center;
	uintStandard_t* widthOnLayer;
	uintStandard_t depth;
	ChunkedVector<ChunkedVector<T>*> elements;

	// 1st octet:
	//  positive, positive, positive
	// 2nd:
	//  positive, positive, negative
	// 3rd:
	//  positive, negative, positive
	// 4th:
	//  positive, negative, negative
	// 5th:
	//  negative, positive, positive
	// 6th:
	//  negative, positive, negative
	// 7th:
	//  negative, negative, positive
	// 8th:
	//  negative, negative, negative

public:
	OctTree(VECTOR3& center, uintStandard_t depth, uintStandard_t chunkSize) : center(center), widthOnLayer(nullptr), depth(depth), elements()
	{
		assert(depth <= 9);
		assert(chunkSize % 2 == 0);
		widthOnLayer = new uintStandard_t[this->depth];
		NULL_CHECK(widthOnLayer);
		for (size_t i = 0; i < this->depth; i++)
		{
			widthOnLayer[i] = chunkSize * (1 << i);
		}
		uintStandard_t totalLeafs = glm::pow(8, depth);
		for (size_t i = 0; i < totalLeafs; i++)
		{
			elements.push_back(nullptr);
		}
	}
	~OctTree()
	{
		for (size_t i = 0; i < elements.size(); i++)
		{
			delete elements[i];
		}
		delete[] widthOnLayer;
	}

	ChunkedVector<T>* CreateVector(uintStandard_t index)
	{
		ChunkedVector<T>* vector = new ChunkedVector<T>();
		elements[index] = vector;
		NULL_CHECK(vector);
		return vector;
	}

	void MoveItem(uintStandard_t originalIndex, T object, uintStandard_t newIndex)
	{
		ChunkedVector<T>* oldVec = elements[originalIndex];
		if (oldVec == nullptr)
		{
			return;
		}
		ChunkedVector<T>* newVec = elements[newIndex];
		if (newVec == nullptr)
		{
			newVec = CreateVector(newIndex);
		}
		bool empty = true;
		for (size_t i = 0; i < oldVec->size(); i++)
		{
			if ((*oldVec)[i] == object)
			{
				newVec->push_back(object);
				(*oldVec)[i] = nullptr;
			}
			else if ((*oldVec)[i] != nullptr)
			{
				empty = false;
			}
		}
		if (empty)
		{
			delete oldVec;
			elements[originalIndex] = nullptr;
		}
	}

	uintStandard_t Find(VECTOR3& point)
	{
		uintStandard_t realIndex = 0;
		VECTOR3 localCenter = center;
		VECTOR3 newCenter = center;
		unsigned char index = 0;
		for (intStandard_t i = depth - 1; i >= 0; i--)
		{
			for (size_t j = 0; j < point.length(); j++)
			{
				newCenter[j] += widthOnLayer[i] >> 1;
				if (point[j] - localCenter[j] < 0)
				{
					newCenter[j] -= widthOnLayer[i];
					index |= (1 << point.length() - 1 - j);
				}
			}
			localCenter = newCenter;
			realIndex = (realIndex << point.length()) + index;  // This is some serious black magic right here...
			index = 0;
		}
		return realIndex;
	}

	uintStandard_t Find(VECTOR3& point, ChunkedVector<T>** result)
	{
		uintStandard_t realIndex = 0;
		VECTOR3 localCenter = center;
		VECTOR3 newCenter = center;
		unsigned char index = 0;
		for (intStandard_t i = depth - 1; i >= 0; i--)
		{
			for (size_t j = 0; j < point.length(); j++)
			{
				newCenter[j] += widthOnLayer[i] >> 1;
				if (point[j] - localCenter[j] < 0)
				{
					newCenter[j] -= widthOnLayer[i];
					index |= (1 << point.length() - 1 - j);
				}
			}
			localCenter = newCenter;
			realIndex = (realIndex << point.length()) + index;  // This is some serious black magic right here...
			index = 0;
		}
		if (elements[realIndex] == nullptr)
		{
			result = nullptr;
		}
		else
		{
			*result = (elements[realIndex]);
		}
		return realIndex;
	}

	void Insert(T object, VECTOR3 point)
	{
		ChunkedVector<T>* vect = nullptr;
		uintStandard_t index = Find(point, &vect);
		if (vect == nullptr)
		{
			vect = CreateVector(index);
		}
		for (size_t i = 0; i < vect->size(); i++)
		{
			if ((*vect)[i] == nullptr)
			{
				(*vect)[i] = object;
				return;
			}
		}
		vect->push_back(object);
	}

	ChunkedVector<T>** GetNeighbours(VECTOR3& point)
	{
		ChunkedVector<T>** result = (ChunkedVector<T>**)calloc(glm::pow(3, point.length()), sizeof(ChunkedVector<T>*));
		NULL_CHECK(result);
		intStandard_t offsets[]{ -((intStandard_t)widthOnLayer[0]), 0, (intStandard_t)widthOnLayer[0] };
		VECTOR3 local(0);
		uintStandard_t counter[point.length()];
		for (size_t i = 0; i < point.length(); i++)
		{
			counter[i] = 0;
		}
		for (size_t i = 0; i < glm::pow(3, point.length()); i++)
		{
			for (size_t j = 0; j < point.length(); j++)
			{
				local[j] = point[j] + offsets[counter[j]];
			}
			++(counter[point.length() - 1]);
			for (int j = point.length() - 1; j >= 0; j--)
			{
				if (counter[j] % 3 == 0 && counter[j] != 0)
				{
					counter[j] = 0;
					++(counter[j - 1]);
				}
			}
			Find(local, &result[i]);
		}
		return result;
	}

};



#endif
