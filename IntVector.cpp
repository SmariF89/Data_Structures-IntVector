#include <cmath>
#include "IntVector.h"

#include <vector>

using namespace std;

// Constructors

IntVector::IntVector()
{
    capacity = INITIAL_CAPACITY;
    array = new int[capacity];
    count = 0;
}

IntVector::IntVector(int size, int value)
{
    if(size < 0)
    {
        capacity = INITIAL_CAPACITY;
        count = 0;

        array = new int[capacity];

        return;
    }
    else
    {
        capacity = size;
        count = size;

        array = new int[capacity];

        for(int i = 0; i < size; i++)
        {
            array[i] = value;
        }
    }
}

IntVector::IntVector(const IntVector& vec) : capacity(vec.capacity), count(vec.count)
{
    array = new int[capacity];

    for(int i = 0; i < count; i++)
    {
        array[i] = vec.array[i];
    }
}


IntVector::~IntVector()
{
    if(array != NULL)
	{
		delete [] array;
	}
}

// Public member functions

void IntVector::push_back(int elem)
{

    if(count == capacity)
    {
        resizeArray();
    }

    array[count] = elem;
    count++;
}

void IntVector::insert(int index, int elem)
{

    if(index < 0 || index > count)
    {
        throw IndexOutOfRangeException();
    }

    if(count == capacity)
    {
        resizeArray();
    }

    for(int i = count - 1; i >= index; i--)
    {
        array[i + 1] = array[i];
    }

    array[index] = elem;

    count++;
}

int IntVector::at(int index) const
{
    if(index < 0 || index >= count)
    {
        throw IndexOutOfRangeException();
    }
    else if(empty())
    {
        throw EmptyException();
    }

    return array[index];
}

void IntVector::set_value_at(int index, int elem)
{

    if(index < 0 || index >= count || empty())
    {
        throw IndexOutOfRangeException();
    }

    array[index] = elem;
}

int IntVector::size() const
{
    return count;
}

bool IntVector::empty() const
{
    return count == 0;
}

void IntVector::remove_at(int index)
{
    if(index < 0 || index >= count || empty())
    {
        throw IndexOutOfRangeException();
    }

    for(int i = index; i < count; i++)
    {
        if(index == count)
        {
            break;
        }

        array[index] = array[index + 1];
        index++;
    }

    count--;
}

int IntVector::pop_back()
{
    if(empty())
    {
        throw EmptyException();
    }

    int returnValue = array[count - 1];

    count--;

    return returnValue;
}

void IntVector::clear()
{
    count = 0;
}

// Private functions

void IntVector::resizeArray()
{
   	capacity *= 2;
	int *tmpArray = new int[capacity];

	for(int i = 0; i < count; i++)
	{
		tmpArray[i] = array[i];
	}

	delete[] array;

	array = tmpArray;
}

// Overloaded operators

void IntVector::operator=(const IntVector& vec)
{
    if(capacity < vec.capacity)
    {
        delete [] array;
        array = new int[vec.capacity];
    }

    capacity = vec.capacity;
    count = vec.count;

    for(int i = 0; i != count; i++)
    {
        array[i] = vec.array[i];
    }
}

int& IntVector::operator[] (int index)
{
    if(index < 0 || index >= count)
    {
        throw IndexOutOfRangeException();
    }

    return array[index];
}

ostream& operator << (ostream& out, const IntVector& rhs)
{
    for(int i = 0; i < rhs.size(); i++)
    {
		if(i > 0)
		{
			out << " ";
		}
        out << rhs.at(i);
    }
    return out;
}
