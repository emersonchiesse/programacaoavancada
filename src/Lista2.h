/*
 * Lista2.h
 *
 *  Created on: 31 de ago de 2015
 *      Author: x
 */

#ifndef LISTA2_H_
#define LISTA2_H_

#include <iostream>

template <typename T>
class List;

template <class TNode>
class Iterator
{
	/* Helper class to provide pointer like facilities around a node */
	friend class List<typename TNode::value_type>;
	TNode* pNode; //The node oriented with this instance of iterator.

	Iterator(TNode* _pNode) : pNode(_pNode) {}
public:
	void operator++(){ pNode = pNode->_next; }
	void operator++(int){ pNode = pNode->_next; }
	bool operator!=(Iterator<TNode> rval){ return !(pNode == rval.pNode); }
	bool operator==(Iterator<TNode> rval){ return (pNode == rval.pNode); }
	typename TNode::value_type operator*(){
		return pNode->_data;
	}
	Iterator<TNode> operator+(int _i)
	{
		Iterator<TNode> iter = *this;
		for (int i = 0; i < _i; ++i)
		{
			if (iter.pNode) //If there's something to move onto...
				++iter;
			else
				break;
		}
		return iter; //Return regardless of whether its valid...
	}
};

template <typename T>
class Node
{
	friend class List<T>;
	friend class Iterator<Node<T> >;
	Node () : _next(0) {}
	Node (T data) : _data(data), _next(0) {}
	Node (T data, Node<T>* next) : _data(data), _next(next){}
	Node (Node<T>* next) : _next(next) {}
	~Node() {};

	T _data;
	Node<T>* _next;
public:
	typedef T value_type;
};

template <typename T>
class List
{
	Node<T>* first;
	int tamanho;

public:
	typedef Iterator<Node<T> > iterator;
	typedef T 		  value_type;

	List () : first(0) { tamanho = 0; }
	~List()
	{
		if (first)
		{
			Node<T> *iter = first;
			while (iter != 0)
			{
				Node<T>* tmp = iter;
				iter = iter->_next;
				if (tmp)
					delete tmp;
			}
		}
	}

	void insere(T data)
	{
		if (first)
		{
			Node<T> *iter = first;
			for (; iter->_next != 0; iter = iter->_next); //Iterate until we reach the end of our linked list.
			iter->_next = new Node<T>(data);
		}
		else
			first = new Node<T>(data);

		tamanho++;
	};

	void push_front(T data)
	{
		if (first)
		{
			Node<T> * tmp = new Node<T>(data);
			tmp->_next = first;
			first = tmp;
		}
		else
			first = new Node<T>(data);

		tamanho++;
	}

	iterator begin(){ return iterator(first); }
	iterator end(){ return iterator(0); }

	Node<T>* procura ()
	{

	}

	bool apaga(iterator& _iNode) //True for success, vice versa
	{
		/* This is rather inneffecient. Maybe a better way to do this? */
		/* Even then, it's *still* more effecient than a contiguous container */
		if (_iNode.pNode == first)
		{
			first = first->_next;
			delete _iNode.pNode;
			tamanho--;
			return true;
		}
		else
		{
			for (Node<T>* iter = first; iter->_next; iter = iter->_next)
			{
				if (iter->_next == _iNode.pNode) //Find our node.
				{
					iter->_next = _iNode.pNode->_next;
					delete _iNode.pNode;
					tamanho--;
					return true;
				}
			}
		}

		return false;
	}

	int getTamanho ()
	{ return tamanho; }
};



#endif /* LISTA2_H_ */
