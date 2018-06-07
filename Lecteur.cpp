/*************************************************************************
                           Lecteur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Lecteur> (fichier Lecteur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Lecteur.h"
#include <stdlib.h>
#include <sstream>
#include <cmath>

//------------------------------------------------------------- Constantes
const char POINTVIRGULE = ';';
const char SAUTDELIGNE = '\r';

const double MAX_DISTANCE = 1000000000;
//----------------------------------------------------------------- PUBLIC
static Type StringToType(string s); 

//----------------------------------------------------- Méthodes publiques

void Lecteur::displayEmpreinte(){
    int size = emp_aAnalyser.size();
    for(int i = 0; i < size; ++i)
        cout << emp_aAnalyser[i];
}

int Lecteur::chargerMetaDonnee(string lectStr)
{
    ifstream fichier;
    fichier.open(lectStr);
    string key = "";
    string value = "";
    if(fichier){
        getline(fichier,key,POINTVIRGULE);
        getline(fichier,value);
        while(!fichier.eof()){
			getline(fichier,key,POINTVIRGULE);
			getline(fichier,value,SAUTDELIGNE);
			Type t = StringToType(value);
			Attribut attribut = Attribut(key,t);
			attributs.push_back(attribut);
			getline(fichier,value);
        }
        cout << "Fichier chargé" << endl;
        return 0;
    } else{
        cout << "Aucun fichier" << endl;
        return -1;
    }
}

//lit le fichier de donn�e :
int Lecteur::chargerDonnees(string lectStr, bool aAnalyser)
{
    ifstream fichierA;
    fichierA.open(lectStr);
    try {
        if(fichierA){
            string line = "";
            string value = "";
            string maladie="";
            string tmp ="";
            if(aAnalyser == false){
                string firstLine = "";
                getline(fichierA,firstLine);
                //Code pour lire les empreintes :
                while(!fichierA.eof())
                {
                    int j = 0;
                    getline(fichierA,line);
                    istringstream iss2(line);
                    Empreinte e;
                    while(!iss2.eof() && j < (attributs.size()))
                    {
                        getline(iss2,value,POINTVIRGULE);
                        Attribut a = Attribut(attributs[j].getNom(),attributs[j].getType(),value);
                        j++;
                        e.addValeur(a);
                    }
                    getline(iss2,maladie,SAUTDELIGNE);
                    e.setMaladie(maladie);
                    
                    //-------- code ajouté
                    for (const Attribut & a : e.getValeur())
                    {
                        if (a.getType() == STRING)
                        {
                            if (maladieStrings[maladie][a.getNom()].find(a.getValeur()) == maladieStrings[maladie][a.getNom()].end())
                            {
                                maladieStrings[maladie][a.getNom()][a.getValeur()] = 0;
                            }
                            else
                            {
                                maladieStrings[maladie][a.getNom()][a.getValeur()] += 1;
                            }
                        }
                    }
                    //-------------------
                    
                    getline(iss2,tmp);
                    if(data.find(e.getMaladie()) == data.end())
                    {
                        vector<Empreinte> vectorE;
                        vectorE.push_back(e);
                        data.insert(pair<string,vector<Empreinte>>(e.getMaladie(),vectorE));
                    } else
                    {
                        data.find(e.getMaladie())->second.push_back(e);
                    }
                }
            calculMoyenne();           
        } else if (aAnalyser == true){
            while(!fichierA.eof())
            {
                int j = 0;
                getline(fichierA,line);
                istringstream iss2(line);
                Empreinte e;
                while(!iss2.eof() && j < (attributs.size()-1))
                {
                    getline(iss2,value,POINTVIRGULE);
                    Attribut a = Attribut(attributs[j].getNom(),attributs[j].getType(),value);
                    j++;
                    e.addValeur(a);
                }
                getline(iss2,value,SAUTDELIGNE);
                Attribut a = Attribut(attributs[j].getNom(),attributs[j].getType(),value);
                j++;
                e.addValeur(a);
                emp_aAnalyser.push_back(e);
                //displayEmpreinte();
            }
            cout << "Fichier de données chargé" << endl;
            return 0;
            //return donnee;
        }
    } else {
        cout << " Aucun fichier " << endl;
        return -1;
    }
    } catch (exception e) {
        cout << "Erreur lors de la lecture" << endl;
        return -1;
    }
    return 0;
}

void Lecteur::calculMoyenne(){
    donnees::iterator itD;
    vector<Empreinte>::iterator itE;
    vector<Attribut>::iterator itA;
    
    //calcul de la moyenne (somme des valeurs des attributs)
    for(itD = data.begin(); itD != data.end(); itD++){
        int nb = 0;
        vector<Attribut> vectAt(attributs.size()-1);
        int tmp = 0;
        vector<Attribut> vectorA = itD->second.begin()->getValeur();
        copy(vectorA.begin()+1,vectorA.end(),vectAt.begin());
        
        size_t taille = vectorA.size();
        for (int i = 0; i < taille; ++i)
        {
            if (vectAt[i].getType() == STRING)
            {
                string meilleurString;
                int maxOccur = 0;
                for (const auto & stringEtOccurence : maladieStrings[itD->first][vectAt[i].getNom()])
                {
                    if (maxOccur < stringEtOccurence.second)
                    {
                        maxOccur = stringEtOccurence.second;
                        meilleurString = stringEtOccurence.first;
                    }
                }
                vectAt[i].setValeur(meilleurString);
            }
        }
        
        for (itE = ++(itD->second.begin()); itE != itD->second.end(); itE++)
        {
            int i = 0;
            vectorA = itE->getValeur();
            for(itA = ++(vectorA.begin()); itA != vectorA.end(); itA++){
                Attribut a = *itA;
                if(a.getType() == DOUBLE){
                        vectAt[i].setValeur(to_string( stod(vectAt[i].getValeur())  + stod(a.getValeur()) ));
                        vectAt[i].setType(DOUBLE);
                        vectAt[i++].setNom(a.getNom());
                } else
                {
                    vectAt[i].setNom(a.getNom());
                    i++;
                }
            }
            nb++;
        }
        
        //calcul de la moyenne (division)
        int size = vectAt.size();
        Empreinte e;
        for(int i = 0; i < size; ++i)
        {
            switch(vectAt[i].getType()){
                case DOUBLE:
                    vectAt[i].setValeur(to_string(stod(vectAt[i].getValeur())/nb));
                    e.addValeur(vectAt[i]);
                    break;
                default :
                    e.addValeur(vectAt[i]);
                    break;
            }
        }
        e.setMaladie(itD->first);
        moyenne.push_back(e);
    }
    
     // affichage de la moyenne
    for(int i = 0; i < moyenne.size(); i++){
        cout << "moyenne : " << moyenne[i] << " ";
        }
}

// type Lecteur::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

int Lecteur::displayAttributs() const
{
    if(attributs.size() == 0) {
        cout << "MetaDonnee abscente" << endl;
        return 5;
    }
    for(int i =0;i<attributs.size();i++)
    {
        cout << attributs[i] << endl;
    }
    return 0;
}

int Lecteur::displayData() 
{
    if(data.begin() == data.end()) {
        cout << "Donnee abscente" << endl;
        return 5;
    }
    donnees::iterator it;
    for(it = data.begin(); it != data.end(); it++)
    {
        cout << it->first << " et " << endl;
        displayVector(it->second);
        cout << endl;

    }
    return 0;
}

void Lecteur::displayVector(vector<Empreinte> l) const{
    vector<Empreinte> tmp = l;
    vector<Empreinte>::iterator it;
    for(it = tmp.begin(); it != tmp.end(); it++)
    {
        cout << "valeur empreinte : " << *it << endl;
    }
}


vector<pair<Empreinte,Resultat>> Lecteur::diagnostic(string nomFichierEmpreinte){
    vector<pair<Empreinte,Resultat>> res;
    chargerDonnees(nomFichierEmpreinte,true);
    int size = emp_aAnalyser.size();
    for(int i = 0; i < size; ++i){
        Resultat r = chercherMaladie(emp_aAnalyser[i]);
        pair<Empreinte,Resultat> pairAajouter(emp_aAnalyser[i],r);
        res.push_back(pairAajouter);
    }
    return res;
}

Resultat Lecteur::chercherMaladie(Empreinte e){
    string maladie = "";
    double distanceActuelle = MAX_DISTANCE;
    double distancetotale = 0;
    int size = moyenne.size();
    for (int i = 0; i < size; ++i)
    {
        cout << size << endl;
        if(moyenne[i].getMaladie() !=""){
            Empreinte temoin = moyenne[i];
            double tmp = testMaladie(temoin,e);
            distancetotale += tmp;
            if(tmp < distanceActuelle){
                distanceActuelle = tmp;
                maladie = temoin.getMaladie();
             }
          }
    }
    double probabilite = 100*(1-distanceActuelle/distancetotale);
    Resultat r(maladie,probabilite);
    return r;
}


double Lecteur::testMaladie(Empreinte temoin,Empreinte e){
    vector<Attribut> tmp = e.getValeur();
    std::vector<Attribut> vectEmpreinte(++(tmp.begin()), tmp.end());
    int size = vectEmpreinte.size();
    double distance = 0;
    cout << " lol " << size << endl;
    for(int i = 0; i < size; ++i)
    {
        cout << "[" << temoin.getValeur().at(i) << "] - ";
        if(temoin.getValeur().at(i).getType() == DOUBLE){
            cout << temoin.getValeur().at(i).getValeur() << endl;
            double moyenne = stod(temoin.getValeur().at(i).getValeur());
            cout << "--> " << vectEmpreinte.at(i) << endl;
            distance += abs(stod(vectEmpreinte.at(i).getValeur())-moyenne)*abs(stod(vectEmpreinte.at(i).getValeur())-moyenne);
        } else {
            cout << "c'est un string" << endl;
        }
    }
    double proba = 0;
    return sqrt(distance);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Lecteur::Lecteur ( const Lecteur & unLecteur )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Lecteur>" << endl;
#endif
} //----- Fin de Lecteur (constructeur de copie)


Lecteur::Lecteur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Lecteur>" << endl;
#endif
} //----- Fin de Lecteur


Lecteur::~Lecteur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Lecteur>" << endl;
#endif
} //----- Fin de ~Lecteur


//------------------------------------------------------------------ PRIVE

static Type StringToType(string s){
    Type t;
    if(s=="NoId"){
        return t = LONG;
    }
    if(s=="string"){
        return t = STRING;
    } else if(s=="double"){
        return t = DOUBLE;
    } else {
        return t = INT;
    }
}

//----------------------------------------------------- Méthodes protégées
