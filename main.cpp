#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;
//Pour avoir toute les intersection ou sont passer chaque voitures
void intersec_passed(vector<string> street,map<string, int> start,map<string, int> end,vector<int> *tab);
//Verifier si l'intersection est deja dans le tableau
bool is_inVector(vector<int> tab,int n);

int main(){

    ifstream file("input.txt");
    ofstream output("output.txt");
    string line("");
    vector<string> street_pass;
    vector<int> intersec_pass;
    map<string, int> street_duration;
    map<string, int> start;
    map<string, int> end;
    
    int duration,nbrIntersec,nbrStreet,nbrCars,bonus;
    if(file.is_open()){
       cout << "file is open \n";
       getline(file,line);
       stringstream ssline(line);
       ssline >> duration;
       ssline >> nbrIntersec;
       ssline >> nbrStreet;
       ssline >> nbrCars;
       ssline >> bonus;
       /*On enregistre pour toute les rues leurs intersection de depart et de fin 
       ainsi que la durer de parcours de la rue dans une map avec key le nom de la rue*/
       for (int  i = 0; i < nbrStreet; i++)
       {
            getline(file,line);
            int n,m,d;
            stringstream ssline(line);
            ssline >> n>> m;
            string street;
            ssline >> street >> d; 
            street_duration.insert(pair<string, int>(street,d));
            end.insert(pair<string,int>(street,m));
       }
       /*Pour toute les voitures on mets leurs rue de passer dans street_pass 
       en fonctions de ca in determine les intersection passé*/
       for (int i = 0; i < nbrCars; i++){
           getline(file,line);
           stringstream ssline(line);
           int k;
           ssline >> k;
           for (int i = 0; i < k; i++)
           {
               string street;
               ssline >> street;
               street_pass.push_back(street);
               intersec_passed(street_pass,start,end,&intersec_pass);
           }
          /* for(int h(0); h<street_pass.size(); h++){
               cout << street_pass[h] <<"\n";
           }*/
           street_pass.clear();
       }
       for(int h(0); h<intersec_pass.size(); h++){
            cout << intersec_pass[h] <<"\n";
       } 
       output << intersec_pass.size() << "\n";
        /*Recuperer à partie des intersections les rue d'entrer*/  
        for(int h(0); h<intersec_pass.size(); h++){
            vector<string> str;
            map<string,int>::iterator itr=end.begin();
            while(itr!=end.end()){
                if(itr->second==intersec_pass[h])
                    str.push_back(itr->first);
                itr++;
            }
            cout << str.size()<< " is\n";
            //Inserer l'intersection le nombre de rue qui lui est entrant
            output << intersec_pass[h] << "\n" << str.size() << "\n";
            for(int j(0); j<str.size(); j++){
                cout << str[j]<<"\n";
                //Inserer les rues entrantes
                output << str[j] <<"\n";
                
            }
        }
    }
    return 0;
}


void intersec_passed(vector<string> street,map<string, int> start,map<string, int> end,vector<int> *tab){
    for(int i(0); i<street.size()-1; i++){
        
        if(!is_inVector(*tab,end[street[i]]))
            tab->push_back(end[street[i]]);
    }
}


bool is_inVector(vector<int> tab,int n){
    for(int i(0); i<tab.size(); i++){
        if(tab[i]==n)
            return true;
    }
    return false;
}