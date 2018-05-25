/*************************************************************************
                           Lecteur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Lecteur> (fichier Lecteur.h) ----------------
#if ! defined ( Lecteur_H )
#define Lecteur_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include "Attribut.h"
#include <vector> 
#include <string.h>
#include <fstream>
#include <unordered_map>
#include <list>
#include "Empreinte.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unordered_map<string,list<Empreinte>> donnees;

//------------------------------------------------------------------------
// Rôle de la classe <Lecteur>
//
//
//------------------------------------------------------------------------

class Lecteur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void chargerMetaDonnee(string lecStr);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void display();
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void chargerDonnes(string lecStr);

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Lecteur ( const Lecteur & unLecteur );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Lecteur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Lecteur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<Attribut> Attributs;
    donnees data;

};

//-------------------------------- Autres définitions dépendantes de <Lecteur>

#endif // Lecteur_H

