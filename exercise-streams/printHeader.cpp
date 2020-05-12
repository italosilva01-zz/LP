#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
//Exercicio um
//printa o cabecalho da tabela
void printRow(char separator, char complete, int size){
    //generalização para printar a linha
    //size+3 pois irei reconpensar os espaços vazios(espaços de respiração) do conteudo
    // da tabela 
    cout<< setw(size+3) << left<<setfill(complete)<<separator;
    
}
void printContent(char separator, char complete,std::string nome,int size){
    //printo o cabeçalho da tabela
    cout<<separator<<' ';
    //size+1 para ter espaço de respiração entre o conteudo e os delimitadores
    //da tabela
    cout<< setw(size+1)<< setfill(complete)<<nome;

}
void printHeader(const std::vector <std::string> &fields_){
   //função principal do exercicio Um
   
    //percorro o vetor para saber o tamanho de cada item
    //que vai entrar, assim fazendo as linhas da forma que
    //a atividade propoe.
   for(auto elements :fields_){
       int size = elements.length();
       printRow('+','-',size);
   }
   //fechamento do lado direito da tabela
   cout<<"+";
   cout<< endl;

   for(auto items : fields_){
       int size = items.length();
       printContent('|',' ',items,size);
   }
   cout<<"|";
   cout<<endl;
    for(auto elements :fields_){
       int size = elements.length();
       printRow('+','-',size);
   }
   cout<<"+";
   cout<< endl;
   

    
};

//Exercicio dois
bool fileValid(ifstream & file){
    //verifica se o arquivo de leitura existe
    
    if(file.fail()){
            /*Caso o arquivo não exista ou não foi encontrado
            esse while pede para escrever o nome de outro arquivo*/
            cout<<"arquivo não encontrado\nDigite novamente: "<<endl;
            file.clear();//limpa o fail
            return true;
        }else{
            return false;
        }
}
void impress(){
/* Função ler de um arquivo e escreve em outro arquivo*/

    string directory;//nome|diretório do arquivo que o cliente irá digitar
    ifstream fileName;// arquivo de leitura 
    vector<char> input; /*vector que irá armazenar nossos valores
                                temporáriamente antes do arquivo de saida*/

    bool status = true;//condicional para o prox. while.

    cout << "Digite o nome do arquivo: "<<endl;
    while(status){

        cin >> directory;//recebendo nome|diretório do arquivo
        fileName.open(directory.c_str());//abrindo arquivo.
        status = fileValid(fileName);
            

    }
    char number;
    while (fileName.get(number)){
        //Exercuta enquanto o arquivo não chegar ao fim.
        if(!(number==' ')){
            input.push_back(number);//adicionando elementos no vector
        };       
        
        
    }
    fileName.close();//fechando arquivo de leitura.
    
    int size = input.size();//quantidade de elementos de vector;
    ofstream output;//arquivo de saida.
    
    output.open("invertido.txt");

    for(int pos = size-1; pos>=0; --pos){
        //gravanda na ordem inversa no arquivo 'invertido.txt'.
        output<<input[pos]<<" ";
    }

    output.close();
    cout<<endl<<"feito";
     
}

//Exercicio Três

int getInteger(string msg_){
    //Converte uma string para um inteiro.
    bool condition = false;//condição que vai respeitar o while
    int integer{0};//inteiro que irá receber o valor da string
    
    cout<<msg_<<endl;
    while(!condition){
        //irá executar até que o condition seja verdade.
        getline(cin,msg_);
        istringstream fluxo(msg_);
        fluxo >> integer>>ws;//retirando os espaços em branco.
        
        if(fluxo.fail() or !fluxo.eof()){
            cout<<"erro"<<endl;
            condition= false;
        
        }else{
            condition = true;
        }
    }
    
    return integer;
}

//Exercicio quatro
void printTable( vector<string> & value, int * point){
    //imprimi linha por linha.
    //o point é para a o vetor sizes, no qual guarda o tamanho de cada coluna.
        
    for(int pos = 0; pos<value.size();pos+=3){
        cout<<"|"<<setw(*point+2)<<setfill(' ')<<right <<value[pos];
        cout<<"|"<<setw(*(point+1)+2)<<setfill(' ')<<right <<value[pos+1];
        cout<<"|"<<setw(*(point+2)+2)<<setfill(' ')<<right <<value[pos+2]<<"|"<<endl;
        
    }
};


void ultraTable(){
    string argc, argv;//nome dos arquivos
    ifstream file1,file2 ;//
    
    vector<string>headerTable;//cabeçalho da tabela
    vector<string >bodyTable;//corpo da tabela
    int sizes[3];
    string phs;
    
    bool condition1,condition2;
    condition1 =  condition2= true; 

    while(condition1){
        //Vai avaliar se a primeira entrada do usuário é válida.
        cout<<"Digite o nome do primeiro arquivo"<<endl;
        cin >> argc;

        file1.open(argc.c_str());
        condition1 = fileValid(file1);

    }
    while(getline(file1,phs)){
        //lendo do arquivo 1 e adicionando no vector header
        headerTable.push_back(phs);
    }
    for(int pos = 0;pos<headerTable.size();++pos){
        sizes[pos]=headerTable[pos].length(); // pegando tamanhos dos vectores
    }

    file1.close();//Não vamos mais usar esse arquivo;   
    while(condition2){
        cout<<"Digite o nome do segundo arquivo"<<endl;
        cin >> argv;
        
        file2.open(argv.c_str());
        condition2 = fileValid(file2);
    }
    phs= "";//'zerando' a string
    char c;//variável auxiliar
    while(file2.get(c)){
        
        if(c!=' '&& c!='\n'){
        phs+=c;//acumulo o numero aqui
        }else{
            /*Quando c for igual a espaço em branco
            . Adiciono o numero acumulado no vector*/
            bodyTable.push_back(phs);
            phs = "";//reinicio o phs
        }
    }    

    file2.close();
    
    printHeader(headerTable);
    printTable(bodyTable,sizes);
}
int main(){
    std::vector< std::string > fieldNames = {"ITEM","QUANTIDADE","VALOR UNITARIO"};
    
   // printHeader(fieldNames); 
   // impress();
   // int t =  getInteger("Diigite um inteiro");
   ultraTable();
    return 0;
}