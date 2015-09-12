/*
 * Elemento.h
 *
 *  Created on: 23 de ago de 2015
 *      Author: x
 */

#ifndef ELEMENTO_H_
#define ELEMENTO_H_

//template <typename TIPO>
//class Lista;
//
//template <class TNode>
//class Iterator
//{
//	/* Helper class to provide pointer like facilities around a node */
//	friend class Lista<typename TNode>;
//	TNode* pNode; //The node oriented with this instance of iterator.
//
//
//public:
//	Iterator(TNode* _pNode) : pNode(_pNode) {}
//	void operator++(){ pNode = pNode->pProximo; }
//	void operator++(int){ pNode = pNode->pProximo; }
//	bool operator!=(Iterator<TNode> rval){ return !(pNode == rval.pNode); }
//	bool operator==(Iterator<TNode> rval){ return (pNode == rval.pNode); }
//	//typename TNode operator*(){	return pNode->pInfo; }
//	Iterator<TNode> operator+(int _i)
//	{
//		Iterator<TNode> iter = *this;
//		for (int i = 0; i < _i; ++i)
//		{
//			if (iter.pNode) //If there's something to move onto...
//				++iter;
//			else
//				break;
//		}
//		return iter; //Return regardless of whether its valid...
//	}
//};

template<typename TIPO>
class Elemento {
//	friend class Lista<TIPO>;
//	friend class Iterator<Elemento<TIPO> >;
private:
	Elemento<TIPO>* pProximo;
	Elemento<TIPO>* pAnterior;
	TIPO* pInfo;

public:
	Elemento();
	virtual ~Elemento();

	void setProximo(Elemento<TIPO> *p);
	Elemento<TIPO>* getProximo();

	void setAnterior(Elemento<TIPO> *p);
	Elemento<TIPO>* getAnterior();

	void setInfo (TIPO *p);
	TIPO* getInfo();

	//typedef TIPO value_type;
};

template<class TIPO>
Elemento<TIPO>::Elemento ( )
{
	pProximo = 0;
	pAnterior = 0;
	pInfo = 0;
}

template<class TIPO>
Elemento<TIPO>::~Elemento ( )
{
	pProximo = 0;
	pAnterior = 0;
	pInfo = 0;
}

template<class TIPO>
void Elemento<TIPO>::setProximo (
		Elemento<TIPO>* pP )
		{
	pProximo = pP;
		}

template<class TIPO>
Elemento<TIPO>* Elemento<TIPO>::getProximo ( )
{
	return pProximo;
}

template<class TIPO>
void Elemento<TIPO>::setAnterior (
		Elemento<TIPO>* pA )
		{
	pAnterior = pA;
		}

template<class TIPO>
Elemento<TIPO>* Elemento<TIPO>::getAnterior ( )
{
	return pProximo;
}

template<class TIPO>
void Elemento<TIPO>::setInfo (TIPO* pI )
{
	pInfo = pI;
}

template<class TIPO>
TIPO* Elemento<TIPO>::getInfo()
{
	return pInfo;
}

#endif /* ELEMENTO_H_ */
