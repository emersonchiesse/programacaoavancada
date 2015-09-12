#ifndef LISTA_H
#define LISTA_H

#include "Elemento.h"
#include "stdlib.h"

template<class TIPO>
class Lista {
private:
	Elemento<TIPO>* pPrimeiro;
	Elemento<TIPO>* pAtual;
public:
	//typedef Iterator<Elemento<TIPO> > iterator;
	typedef TIPO 		  value_type;

	Lista ( );
	~Lista ( );
	void inicializa ( );
	void limpar();
	bool insereElemento ( Elemento<TIPO>* pElemento );
	bool incluaInfo (TIPO* pInfo );

	Elemento<TIPO>* getpPrimeiro();
	Elemento<TIPO>* getpAtual();

//	iterator begin(){ return iterator(pPrimeiro); }
//	iterator end(){ return iterator(0); }
};


template<class TIPO>
Lista<TIPO>::Lista ( )
{
	inicializa ( );
}

template<class TIPO>
Lista<TIPO>::~Lista ( )
{
	limpar();
}

template<class TIPO>
void Lista<TIPO>::inicializa ( )
{
	pPrimeiro = 0;
	pAtual = 0;
}


template<class TIPO>
Elemento<TIPO>* Lista<TIPO>::getpPrimeiro()
{
	return pPrimeiro;
}
template<class TIPO>
Elemento<TIPO>* Lista<TIPO>::getpAtual()
{
	return pAtual;
}

template<class TIPO>
void Lista<TIPO>::limpar ( )
{
	Elemento<TIPO>* paux1;
	Elemento<TIPO>* paux2;
	paux1 = pPrimeiro;
	paux2 = paux1;
	while (paux1 != 0)
	{
		paux2 = paux1->getProximo();
		delete (paux1);
		paux1 = paux2;
	}
	pPrimeiro = 0;
	pAtual = 0;
}

template<class TIPO>
bool Lista<TIPO>::incluaInfo (TIPO *pInfo )
{
	if (NULL != pInfo)
	{
		Elemento<TIPO>* pElemento = NULL;
		pElemento = new Elemento<TIPO>();
		pElemento->setInfo (pInfo);
		insereElemento (pElemento);
		return true;
	}
	else
		return false;
}

template<class TIPO>
bool Lista<TIPO>::insereElemento (
		Elemento<TIPO>* pElemento )
		{
	if (NULL != pElemento)
	{
		if (NULL == pPrimeiro)
		{
			pPrimeiro = pElemento;
			pPrimeiro->setAnterior ( NULL );
			pPrimeiro->setProximo ( NULL );
			pAtual = pPrimeiro;
		}
		else
		{
			pElemento->setAnterior ( pAtual );
			pElemento->setProximo ( NULL );
			pAtual->setProximo ( pElemento );
			pAtual = pAtual->getProximo ( );
		}
		return true;
	}
	else
		return false;
}

#endif /* LISTA_H_ */

