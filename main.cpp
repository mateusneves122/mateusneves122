#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <sstream>

#include "artista.h"
#include "track.h"

using namespace std;

bool verificaCaractere(string word);
void leArtistaCsv(ifstream &fileIn, ofstream &binFileOut, Artista &art1);
void geraVectorArtista(ifstream &binFile, int repeticoes,vector<Artista> &artistas, int tam);
void leTrackCsv(ifstream &trackCsv, ofstream &trackBin, Track &track);
void geraVectorTrack(ifstream &trackIn, int repeticoes, vector<Track> &tracks, int tam);
void geraArquivoFinal(string artistaCsvHeader, vector<Artista> artistas, string trackCsvHeader, vector<Track> tracks, int tam);
void imprime_Terminal(vector<Artista> artistas, vector<Track> tracks);

int main(int argc, char* argv[]){

    if(argc < 2){ // ./main ./input
        cout << "Informe um diretorio existente" << endl;
        return 0;
    }

    srand(time(NULL));

    string dir = argv[1];
    string artistaCsv = dir + "/artists.csv";
    string artistaBin = dir + "/artists.bin";
    string trackCsv = dir + "/tracks.csv"; 
    string trackBin = dir + "/tracks.bin";  
    
    ifstream fileIn, trackIn;
    fileIn.open(artistaCsv);
    trackIn.open(trackCsv);

    ofstream binFileOut, binTrackOut;
    binFileOut.open(artistaBin, ios::out | ios::binary);
    binTrackOut.open(trackBin, ios::out | ios::binary);

    Artista art1;
    vector<Artista> artV;
    
    Track track;
    vector <Track> tracks;
    int sizeTrackBin = 0;

    ifstream binFileIn, binTrackIn;

    string tmp;
    string aux = "";
    string artistaCsvHeader, trackCsvHeader;

    int qtdLinhas;

    //Parte comentada a baixa precisa ser implementada
    char res; //descomentar quando for implementar parte de gerar arquivo/imprimir no terminal
    cout << "Pressione a tecla c para exibir os resultados no console." << endl;
    cout << "Pressione a tecla a para gerar um arquivo com os resultados." << endl;
    cin >> res;
    if(res == 'c'){
        qtdLinhas = 10;
    }
    else if(res == 'a'){
        qtdLinhas = 100;
    }
    else{
        //lidar com erro
    }

    //pega dados de artistas.csv e salva em objeto art1 da struct Artista
    //depois salva em binário em artistas.bin 

    if(fileIn.is_open() && binFileOut.is_open()){
        getline(fileIn,artistaCsvHeader,'\n');
        leArtistaCsv(fileIn,binFileOut,art1);
        binFileOut.close();
        fileIn.close();
    }
    else{
        cout << "Erro ao abrir Artistas.csv" << endl;
        exit(1);
    } 

    //pega dados de track.csv e salva em objeto track da struct Track
    //depois salva em binário em track.bin

    binTrackIn.open(trackBin, ios::in | ios::binary);

    if(trackIn.is_open() && binTrackOut.is_open()){
        getline(trackIn,trackCsvHeader,'\n');
        leTrackCsv(trackIn,binTrackOut,track);
        trackIn.close();
        binTrackOut.close();
    }
    else{
        cout << "Erro ao abrir track.csv" << endl;
        exit(1);
    }

    //A partir daqui que o valor de res tem impacto

    binFileIn.open(artistaBin, ios::in | ios::binary);

    //lê dados aleatórios em artistas.bin e coloca em vetor para leitura

    if(binFileIn.is_open()){
        if(res == 'c'){
             geraVectorArtista(binFileIn,qtdLinhas,artV,artista_Size());
        }
        else{
            geraVectorArtista(binFileIn,qtdLinhas,artV,artista_Size());
        }
        binFileIn.close();
        
        // imprime_ArtistaV(artV);
    }
    else{
        cout << "Erro ao abrir arquivo artitstas.bin";
        exit(2);
    }

    if(binTrackIn.is_open()){
        if(res == 'c'){
            geraVectorTrack(binTrackIn,qtdLinhas,tracks, track_Size());

        }
        else{
            geraVectorTrack(binTrackIn,qtdLinhas,tracks, track_Size());

        }
        binTrackIn.close();
        
        // imprime_TrackV(tracks);
    }
    else{
        cout << "Erro ao abrir arquivo track.bin" << endl;
        exit(2);
    }

    if(res == 'a'){
        // geraArquivoFinal(artistaCsvHeader,artV,trackCsvHeader,tracks, qtdLinhas);
    }
    else{
        imprime_Terminal(artV,tracks);
    }

    return 0;
}

void leArtistaCsv(ifstream &fileIn, ofstream &binFileOut, Artista &art1){
    // cout << "Lendo do arquivo Artista.csv" << endl;
    string line;
    string tmp;
    string aux = "";
    while(getline(fileIn, line)){
            stringstream sstr(line);

            getline(sstr, tmp, ',');
            strcpy(art1.id, tmp.c_str());

            getline(sstr, tmp, ',');
            art1.followers = atof(tmp.c_str());

            getline(sstr, tmp, ',');     


            while(!verificaCaractere(tmp)){
                aux += tmp + ',';
                getline(sstr, tmp, ',');  
            }
            aux += tmp;
            strcpy(art1.genres, aux.c_str());
            aux = "";


            getline(sstr, tmp, ',');  
            strcpy(art1.name, tmp.c_str());

            getline(sstr, tmp, ',');
            art1.popularity = atoi(tmp.c_str());

            // cout << "\n\nImprimindo a leitura de artista.csv: " << endl << endl;
            // imprime_Artista(art1);
            artista_Save(art1,binFileOut);
        }
}

void geraVectorArtista(ifstream &binFile, int repeticoes,vector<Artista> &artistas, int tam){
    int n;
    artistas.resize(repeticoes); 
    // cout << "Preenchendo vetor de artistas" << endl;
    for(int i = 0; i < repeticoes; i++){
            n = rand()%repeticoes;
            artista_Read(artistas[i], binFile, n, tam);
    }
}

void leTrackCsv(ifstream &trackCsv, ofstream &trackBin, Track &track){
    string line;
    string tmp;
    string aux = "";
    while(getline(trackCsv, line)){
        stringstream sstr(line);

        getline(sstr,tmp,',');
        strcpy(track.id, tmp.c_str());

        getline(sstr,tmp,',');
        strcpy(track.name, tmp.c_str());

        getline(sstr,tmp,',');
        track.popularity = atoi(tmp.c_str());

        getline(sstr,tmp,',');
        track.duration = atoi(tmp.c_str());

        getline(sstr,tmp,',');
        track.explicitt = atoi(tmp.c_str());


        getline(sstr,tmp,',');

        while(!verificaCaractere(tmp)){
            aux += tmp + ',';
            getline(sstr,tmp,',');
        }
        aux += tmp;
        strcpy(track.artist, aux.c_str());
        aux = "";


        getline(sstr,tmp,',');

        while(!verificaCaractere(tmp)){
            aux += tmp + ',';
            getline(sstr,tmp,',');
        }
        aux += tmp;
        strcpy(track.idArtist, aux.c_str());
        aux = "";


        getline(sstr,tmp,',');
        strcpy(track.releaseDate, tmp.c_str());

        getline(sstr,tmp,',');
        track.danceability = atof(tmp.c_str());

        getline(sstr,tmp,',');
        track.energy = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.key = atoi(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.loudness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.mode = atoi(tmp.c_str());

        getline(sstr,tmp,',');
        track.speechiness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.acousticness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.instrumentalness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.liveness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.valence = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.tempo = atof(tmp.c_str());
    
        getline(sstr,tmp,'\n');
        track.timeSignature = atoi(tmp.c_str());

        // cout << "\nImprimindo track depois de ler track.csv: " << endl ;
        // imprime_Track(track);
        // cout << endl;
        track_Save(track,trackBin);
        // sizeTrackBin++; O que isso faz?
    }
}

void geraVectorTrack(ifstream &trackIn, int repeticoes, vector<Track> &tracks, int tam){
    int n;
    tracks.resize(repeticoes); 
    // cout << "Preenchendo vetor de tracks" << endl;
    for(int i = 0; i < repeticoes; i++){
            n = rand()%repeticoes;
            track_Read(tracks[i], trackIn, n, tam);
    }
}

bool verificaCaractere(string word){
    return word[word.size()-1] == ']' || word[word.size()-1] == '"';
}

void imprime_Terminal(vector<Artista> artistas, vector<Track> tracks){
    cout << "\nImprimindo dados dos artistas:" << endl;
    imprime_ArtistaV(artistas);
    cout << "\nImprimindo dados de tracks:" << endl;
    imprime_TrackV(tracks);
}

