//
//  main.cpp
//  Projet de programmation
//
//  Created by Elio Skiadas Deltell on 27.03.2018
//  Copyright © 2018 Elio Skiadas Deltell. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

//La fonction FindPuck permet de trouver les coordonnées des deux pucks par le biais de boucles for et if imbriquées. Celles-ci vont chercher des pixels ayant la même couleur que les pucks (0 et 1 respectivement), en s'assurant que ces pixels forment bien une "pattern" de 5x5 pixels d'une même couleur. Pour cela, on se déplace sur le tableau (hauteur h (axe y) et longueur l (axe x)) en incrémentant les deux variables et en comparant la valeur de chaque pixel à celle de la couleur de chacun des deux pucks. Les coordonnées sont ainsi stockées dans des vecteurs passés en paramètres.

void FindPuck(int l, int h, int couleur, vector<vector<int>> Pix, vector<int>& coordonnees, int nbcolorbad){
    for (int y(0);y<h;y++) {
        for (int x(0);x<l;x++) {
            int nbcolorbad(0);
            if (Pix[y][x]==couleur) {
                for (int yy(y);yy<y+5;yy++)
                    for (int xx(x);xx<x+5;xx++)
                        if (Pix[yy][xx]!=couleur) nbcolorbad++;
                
                unsigned int a(x+2);//dans le référentiel MathLab, l'abscisse reste la même
                unsigned int b(h-1-(y+2));//Le repère MathLab est en bas à gauche, donc l'ordonnée change par rapport au repère cpp
                if (nbcolorbad==0) {
                    coordonnees.push_back(a); coordonnees.push_back(b);
                }
            }
        }
    }
    if (coordonnees.size()==0){
        coordonnees.push_back(-1); coordonnees.push_back(-1);
    }
}

//La fonction CouleurPuck compare les couleurs lues à 0 et 1 et correspond à un warning. Ce programme gère uniquement les couleurs 0 et 1 et retourne une erreur si l'une des couleurs de puck a une autre valeur
void CouleurPuck(int couleur){
    if (couleur!=0 && couleur!=1){
        cout<<"Warning: La couleur d'un ou deux pucks n'est pas valable (différente de 0 et 1)"<<endl;
        exit(EXIT_FAILURE);
    }
}
//La fonction NombrePucks permet de s'assurer qu'il n'y a pas plus d'un puck d'une certaine couleur
void NombrePucks(vector<int> coordonnees){
    if (coordonnees.size()>2){ //2 car le vecteur coordonnées contient la position de chaque puck (x,y)
        cerr<<"Arrêt: Il y a plus d'un puck de couleur 0 ou 1."<<endl;
        exit(EXIT_FAILURE);
    }
}


int main()
{
    int nbcolorbad(0);
    vector<int> coordonnees1; //vecteur contenant les coordonnées du premier puck
    vector<int> coordonnees2; //vecteur contenant les coordonnées du deuxième puck
    ifstream f_in;
    f_in.open("pixmap.bin", ios::binary);
    if (f_in.fail() && !f_in.eof())
    {
        cerr << "Arrêt: Erreur lors de l'ouverture du fichier."<< endl;
        return -1;
    }
    
    else
    {
        unsigned int tmp;
        
        
        int Largeur = -1; // On assigne la valeur -1 à la largeur
        int Hauteur = -1; // On assigne la valeur -1 à la hauteur
        int Couleur1 = -1; // On assigne la valeur -1 à la couleur du premier puck
        int Couleur2 = -1; // On assigne la valeur -1 à la couleur du deuxième puck
        
        
        f_in.read(reinterpret_cast<char *>(&Largeur), sizeof(Largeur));
        if (f_in.fail() )    { cerr<<"err read largeur"<<endl; return -2; }
        
        f_in.read(reinterpret_cast<char *>(&Hauteur), sizeof(Hauteur));
        if (f_in.fail() )    { cerr<<"err read hauteur"<<endl; return -2; }
        
        f_in.read(reinterpret_cast<char *>(&Couleur1), sizeof(Couleur1));
        if (f_in.fail() )    { cerr<<"err read Couleur1"<<endl; return -2; }
        
        f_in.read(reinterpret_cast<char *>(&Couleur2), sizeof(Couleur2));
        if (f_in.fail() )    { cerr<<"err read Couleur2"<<endl; return -2; }
        
        
        //GESTION D'ERREURS POUR LES DIMENSIONS (HAUTEUR ET LARGEUR) ET COULEURS
        
        // On vérifie que la largeur est bien dans l'intervalle donné
        if (Largeur<10 || Largeur>1000)
        {
            cerr<<"Arrêt: La valeur de la largeur n'est pas comprise dans les bornes données"<<endl;
            exit(EXIT_FAILURE);
        }
        
        // On vérifie que la hauteur est bien dans l'intervalle donné
        if (Hauteur<10 || Hauteur>1000)
        {
            cerr<<"Arrêt: La valeur de la hauteur n'est pas comprise dans les bornes données"<<endl;
            exit(EXIT_FAILURE);
        }
        
        //On vérifie que les deux pucks soient différents
        if (Couleur1==Couleur2){
            cerr<<"Arrêt: Les deux pucks ont la même couleur"<<endl;
            exit(EXIT_FAILURE);
        }
        
        //Appel de la fonction CouleurPuck
        CouleurPuck(Couleur1);
        CouleurPuck(Couleur2);
        
        vector<vector<int>> Pix; //tableau dynamique
        vector<int> data; //vecteur contenant tous les pixels
        int NombrePixels = Largeur*Hauteur;
        
        while(!f_in.eof()){
            f_in.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            if(f_in.eof())
                break;
            if (f_in.fail() && !f_in.eof()){
                cerr<<"Arrêt: Erreur lors de la lecture du fichier pixmap.bin. Vérifier qu'il contient le bon type de données."<<endl;
                exit(EXIT_FAILURE);
            }
            data.push_back(tmp);
        }
        
        //Création du tableau Pix
        for (int y(0);y<Hauteur;y++) {
            vector<int> ligne; //création du vecteur ligne
            for (int x(0);x<Largeur;x++) {
                uint tmp = data[y*Largeur+x]; //l'élément de coordonnées x,y de l'image est le (y*Largeur+x)ème élément du vecteur data
                ligne.push_back(tmp); //on stocke chaque ligne dans ce vecteur
                
            }
            Pix.push_back(ligne); //Comme dans une matrice, le premier indice de chaque composante du tableau est la ligne (y) et le deuxième est la colonne(c): Pix[L][C]
        }
        
        //GESTION D'ERREURS (SUITE)
        
        //On vérifie que le nombre de pixels soit le bon
        
        long dif= data.size()-NombrePixels;//on définit la différence entre le nombre de pixels contenus dans pixmap et le nombre de pixels attendus
        long diff= abs(dif);
        
        if(data.size()<NombrePixels){
            cerr << "Arrêt: Le fichier pixmap.bin ne contient pas le bon nombre de pixels (Nombre de pixels manquants: "<< diff <<")"<< endl; //Cette gestion d'erreur affiche donc le nombre de pixels manquants
            exit(EXIT_FAILURE);
        }
        if(data.size()>NombrePixels){
            cout << "Warning: Le fichier pixmap.bin ne contient pas le bon nombre de pixels (Nombre de pixels de trop: "<< diff <<"). Les pixels excédentaires à la fin du fichier vont être ignorés"<< endl;
            //Délétion des valeurs excédentaires en fin du vector data si le fichier contient plus de valeurs que nécessaire
            for (int i(NombrePixels+1);i<data.size();i++)
                data.pop_back();
            
        }
        
        //On vérifie que la valeur des pixels soit bien définie entre 0 et 255
        int i(0);
        for (i=0;i<data.size();i++){
            if (data[i]<0 || data[i]>255){ //On compare la ième composante du vecteur data aux bornes de valeurs
                cerr<<"Arrêt: la valeur des pixels doit être comprise entre 0 et 255"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        
        FindPuck(Largeur, Hauteur, Couleur1, Pix, coordonnees1, nbcolorbad);//appel de la fonction pour le premier puck
        FindPuck(Largeur, Hauteur, Couleur2, Pix, coordonnees2, nbcolorbad);//appel de la fonction pour le deuxième puck
        
        //Appel de la fonction NombrePucks pour chacun des vecteurs (gestion d'erreur)
        NombrePucks(coordonnees1);
        NombrePucks(coordonnees2);
        
        //On vérifie que les deux pucks ne se touchent pas
        int c=coordonnees1[0]-coordonnees2[0];//distance entre les centres des pucks selon l'axe x
        int d=coordonnees1[1]-coordonnees2[1];//distance entre les centres des pucks selon l'axe y
        if (abs(c)<6 && abs(d)<6){
            cerr<<"Arrêt: Les pucks se touchent"<<endl;
            exit(EXIT_FAILURE);
        }
        ofstream f_out("Pos.txt", ios::out);//Placé ici pour que le document ne se crée pas automatiquement même en cas d'erreur
        if(f_out){
            
            f_out <<"0,"<<coordonnees1[0]<<","<<coordonnees1[1]<<endl;//affichage des coordonnées du premier puck dans le fichier pos.txt
            f_out <<"1,"<<coordonnees2[0]<<","<<coordonnees2[1]<<endl;//affichage des coordonnées du deuxième puck dans le fichier pos.txt
            
            
            f_out.close();
        }
        else {
            cerr << "Impossible d'ouvrir ou de créer le fichier Pos.txt"<< endl;
            
            return 0;
        }
        f_in.close();
        f_out.close();
    }
    
    return 0;
    
}

