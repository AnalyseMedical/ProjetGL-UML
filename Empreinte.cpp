/*************************************************************************
Empreinte  -  description
-------------------
debut                : $DATE$
copyright            : (C) $YEAR$ par $AUTHOR$
e-mail               : $EMAIL$
*************************************************************************/

//---------- Realisation de la classe <Empreinte> (fichier Empreinte.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Empreinte.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
vector<Attribut> Empreinte::getValeur() const {
	return valeur;
}

void Empreinte::addValeur(Attribut a){
    valeur.push_back(a);
}

string Empreinte::getMaladie() const{
	return maladie;
}

void Empreinte::setMaladie(string uneMaladie){
	maladie = uneMaladie;
}

void Empreinte::setValeur(vector<Attribut> unVector) {
	valeur = unVector;
} 
// type Empreinte::Methode ( liste des parametres )
// Algorithme :
//
//{
//} //----- Fin de Methode


//------------------------------------------------- Surcharge d'operateurs


//-------------------------------------------- Constructeurs - destructeur
Empreinte::Empreinte(const Empreinte & unEmpreinte)
// Algorithme :
//
{
	valeur = unEmpreinte.getValeur();
	maladie = unEmpreinte.getMaladie();
#ifdef MAP
	cout << "Appel au constructeur de copie de <Empreinte>" << endl;
#endif
} //----- Fin de Empreinte (constructeur de copie)

Empreinte::Empreinte(){};


Empreinte::Empreinte(vector<Attribut> val, string UneMaladie)
// Algorithme :
//
{
	valeur = val;
	maladie = UneMaladie;

#ifdef MAP
	cout << "Appel au constructeur de <Empreinte>" << endl;
#endif
} //----- Fin de Empreinte


Empreinte::~Empreinte()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Empreinte>" << endl;
#endif
} //----- Fin de ~Empreinte


  //------------------------------------------------------------------ PRIVE

  //----------------------------------------------------- Methodes protegees

