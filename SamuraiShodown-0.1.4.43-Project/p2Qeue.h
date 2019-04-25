// ----------------------------------------------------
// FIFO implementation with single linked list  -------
// ----------------------------------------------------

#ifndef __p2Qeue_H__
#define __p2Qeue_H__

/**
* Contains items from double linked list
*/
template<class tdata>
struct p2Qeue_item
{
	tdata                 data;
	p2Qeue_item<tdata>*   next;

	inline p2Qeue_item(const tdata& _data) : data(_data), next(NULL)
	{}
};

/**
* Manages a double linked list
*/
template<class tdata>
class p2Qeue
{

public:

	p2Qeue_item<tdata>*   start;

public:

	/**
	* Constructor
	*/
	inline p2Qeue() : start(NULL)
	{}

	/**
	* Destructor
	*/
	~p2Qeue()
	{
		Clear();
	}

	/**
	* Get Size
	*/
	unsigned int Count() const
	{
		unsigned int result = 0;
		p2Qeue_item<tdata>* tmp;

		for (tmp = start; tmp != NULL; tmp = tmp->next)
			++result;

		return result;
	}

	/**
	* Get last item
	*/
	p2Qeue_item<tdata>* GetLast()
	{
		p2Qeue_item<tdata>* tmp = start;

		while (tmp != NULL && tmp->next != NULL)
			tmp = tmp->next;

		return tmp;
	}

	/**
	* push new item
	*/
	void Push(const tdata& item)
	{
		p2Qeue_item<tdata>*   p_data_item;
		p_data_item = new p2Qeue_item < tdata >(item);

		p2Qeue_item<tdata>* last = GetLast();

		if (last == NULL)
		{
			start = p_data_item;
		}
		else
		{
			last->next = p_data_item;
		}
	}

	/**
	* Deletes an item from the list
	*/
	bool Pop(tdata& item)
	{
		bool result = false;

		p2Qeue_item<tdata>* last = GetLast();

		if (last != NULL)
		{
			p2Qeue_item<tdata>* tmp = start;

			if (tmp == last)
			{
				// Only one item left in the qeue
				item = start->data;
				delete start;
				start = NULL;
			}
			else
			{
				while (tmp->next != last)
					tmp = tmp->next;

				item = tmp->next->data;
				delete tmp->next;
				tmp->next = NULL;
			}

			result = true;
		}

		return result;
	}

	/**
	* Reads one of the values
	*/
	const tdata* Peek(unsigned int index) const
	{
		unsigned int i = 0;
		p2Qeue_item<tdata>* tmp;

		for (tmp = start; tmp != NULL && i < index; tmp = tmp->next)
			++i;

		if (tmp != NULL)
			return &(tmp->data);

		return NULL;
	}

	/**
	* Destroy and free all mem
	*/
	void Clear()
	{
		p2Qeue_item<tdata>*   p_data;
		p2Qeue_item<tdata>*   p_next;
		p_data = start;

		while (p_data != NULL)
		{
			p_next = p_data->next;
			delete p_data;
			p_data = p_next;
		}

		start = NULL;
	}

};
#endif /*__p2Qeue_H__*/