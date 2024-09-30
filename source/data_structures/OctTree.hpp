#ifndef OCTTREE
#define OCTTREE

template <typename T>
class OctTree;


#include "../defines.hpp"
#include INCL_GLM
#include <list>

template <typename T>
class OctTree
{
	VECTOR3 center;
	uintStandard_t* widthOnLayer;
	uintStandard_t depth;
	ChunkedVector<std::list<T>*> elements;

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
	OctTree() : center(VECTOR3(0)), widthOnLayer(nullptr), depth(0), elements()
	{

	}
	OctTree(VECTOR3& center, uintStandard_t depth, uintStandard_t chunkSize) : center(center), widthOnLayer(nullptr), depth(depth), elements()
	{
		assert(depth <= 9);
		assert(chunkSize % 2 == 0);
		widthOnLayer = new uintStandard_t[this->depth];
		NULL_CHECK(widthOnLayer);
		for (size_t i = 0; i < this->depth; i++)
		{
			widthOnLayer[i] = chunkSize * ((size_t)1 << i);
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

	std::list<T>* GetList(uintStandard_t index)
	{
		return elements[index];
	}

	std::list<T>** GetListHandle(uintStandard_t index)
	{
		return &(elements[index]);
	}

	std::list<T>* CreateList(uintStandard_t index)
	{
		if (elements[index] != nullptr)
		{
			return elements[index];
		}
		std::list<T>* list = new std::list<T>();
		NULL_CHECK(list);
		elements[index] = list;
		return list;
	}

	void MoveItem(uintStandard_t originalIndex, T object, uintStandard_t newIndex)
	{
		if (originalIndex == newIndex)
		{
			return;
		}
		std::list<T>* oldList = elements[originalIndex];
		if (oldList == nullptr)
		{
			return;
		}
		std::list<T>* newList = elements[newIndex];
		auto it = oldList->begin();
		for (size_t i = 0; i < oldList->size(); i++)
		{
			if (*it == object)
			{
				if (newList == nullptr)
				{
					newList = CreateList(newIndex);
				}
				newList->push_back(object);
				oldList->erase(it);
				break;
			}
			++it;
		}
		if (oldList->empty())
		{
			delete oldList;
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
			realIndex = (realIndex << point.length()) | index;  // This is some serious black magic right here...
			index = 0;
		}
		return realIndex;
	}

	uintStandard_t Find(VECTOR3& point, std::list<T>** result)
	{
		uintStandard_t realIndex = Find(point);
		*result = (elements[realIndex]);
		return realIndex;
	}

	uintStandard_t Find(VECTOR3& point, std::list<T>*** result)
	{
		uintStandard_t realIndex = Find(point);
		*result = &(elements[realIndex]);
		return realIndex;
	}

	void Insert(T object, VECTOR3 point)
	{
		uintStandard_t index = Find(point);
		std::list<T>* list = elements[index];
		if (list == nullptr)
		{
			list = CreateList(index);
		}
		list->push_back(object);
	}

	std::vector<std::list<T>*> GetNeighbours(VECTOR3& point)
	{
		std::vector<std::list<T>> result;
		result.reserve((intStandard_t)glm::pow(3, DIMENSIONS));
		intStandard_t offsets[]{ -((intStandard_t)widthOnLayer[0]), 0, (intStandard_t)widthOnLayer[0] };
		VECTOR3 local(0);
		uintStandard_t counter[point.length()];
		for (size_t i = 0; i < point.length(); i++)
		{
			counter[i] = 0;
		}
		for (size_t i = 0; i < glm::pow(3, DIMENSIONS); i++)
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
			uintStandard_t index = Find(local);
			result.push_back(GetList(index));
		}
		return result;
	}

	bool WithinSameSquare(VECTOR3 point1, VECTOR3 point2)
	{
		intStandard_t width = widthOnLayer[0];
		for (size_t i = 0; i < point1.length(); i++)
		{
			point1[i] = ((intStandard_t)point1[i]) / width;
			point2[i] = ((intStandard_t)point2[i]) / width;
		}
		return point1 == point2;
	}

};



#endif
