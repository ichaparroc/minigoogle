#include<string.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void purgeSpecialCharacters(string &txt){
    char _char;
    uint     c;

    c = 0;
    while( c < txt.size()){
        _char = txt.at(c);

        // Is Special Characters?
        if( (47<_char && _char< 58) ||
            (64<_char && _char< 91) ||
            (96<_char && _char<123)  ){
            // Es bueno
        }else{
            // a: char([131-134,142,143,160])
            if( _char=='\340' || _char=='\341' || _char=='\342'  || _char=='\343'  || _char=='\344' || _char=='\345' || _char=='\346' ||
                _char=='\300' || _char=='\301' || _char=='\302'  || _char=='\303'  || _char=='\304' || _char=='\305' || _char=='\306' )
            //(130<_char && _char<135) || _char==142 || _char==143 || _char==160  || _char==181 )
                txt.at(c) = 'a';

            // e: char([136-138,130,144])
            else if( _char=='\350' || _char=='\351' || _char=='\352' || _char=='\353' ||
                     _char=='\310' || _char=='\311' || _char=='\312' || _char=='\313' )
            //(135<_char && _char<139) || _char==130 || _char==144 || _char==-23 )
                txt.at(c) = 'e';

            // i: char([139-141,161])
            else if( _char=='\354' || _char=='\355' || _char=='\356' || _char=='\357' ||
                     _char=='\314' || _char=='\315' || _char=='\316' || _char=='\317')
            //(138<_char && _char<142) || _char==161 || _char==214 )
                txt.at(c) = 'i';

            // o: char([147-149,153,162])
            else if( _char=='\362' || _char=='\363' || _char=='\364' || _char=='\365' || _char=='\366' ||
                     _char=='\322' || _char=='\323' || _char=='\324' || _char=='\325' || _char=='\326')
            // (146<_char && _char<150) || _char==153 || _char==162  || _char==224 )
                txt.at(c) = 'o';

            // u: char([129,150,151,154,163])
            else if( _char=='\371' || _char=='\372' || _char=='\373' || _char=='\374' ||
                     _char=='\331' || _char=='\332' || _char=='\333' || _char=='\334')
            //_char==129 || _char==150 || _char==151 || _char==154 || _char==163 || _char==23)
                txt.at(c) = 'u';

            // n: char([164,165])
            else if( _char=='\361' || _char=='\321' )
            //_char==164 || _char==165)
                txt.at(c) = 'n';

            else if( _char=='\t' )
            //_char==164 || _char==165)
                txt.at(c) = ' ';
        }
        ++c;
    }
}

void purgeUppercase(string &txt){
    uint c;

    c = 0;
    while( c < txt.size() ){
        // Is Uppercase?
        if(  txt.at(c) < 91   ){
            if(  txt.at(c) > 64   ) txt.at(c) += 32;
        }
        ++c;
    }
}

bool purgeLittleWords(std::string &txt){
    if( txt.size()<3 ) return true;
    else               return false;
}


bool purgeBadWords(std::string &text){
    //
    // Define Bad words
    // ----------------
    std::vector<std::string> bad2,bad3,bad4,bad5,bad6,bad7;
    unsigned int j;
    // Palabra de dos letras
    if( text.size() == 2 ){
        bad2.push_back("in"); bad2.push_back("si"); bad2.push_back("ya");
        bad2.push_back("of"); bad2.push_back("ha"); bad2.push_back("le");
        bad2.push_back("lo"); bad2.push_back("no"); bad2.push_back("al");
        bad2.push_back("es"); bad2.push_back("su"); bad2.push_back("un");
        bad2.push_back("se"); bad2.push_back("el"); bad2.push_back("en");
        bad2.push_back("la"); bad2.push_back("de"); bad2.push_back("at");

        for(j=0; j<bad2.size(); ++j)
            if(text.compare(bad2[j]) == 0) return true;
    }

    // Palabra de tres letras
    else if( text.size() == 3 ){
        bad3.push_back("ese"); bad3.push_back("and"); bad3.push_back("han");
        bad3.push_back("vez"); bad3.push_back("asi"); bad3.push_back("muy");
        bad3.push_back("era"); bad3.push_back("sin"); bad3.push_back("ser");
        bad3.push_back("dos"); bad3.push_back("son"); bad3.push_back("the");
        bad3.push_back("sus"); bad3.push_back("mas"); bad3.push_back("fue");
        bad3.push_back("una"); bad3.push_back("las"); bad3.push_back("con");
        bad3.push_back("por"); bad3.push_back("del"); bad3.push_back("los");
        bad3.push_back("que");

        for(j=0; j<bad3.size(); ++j)
            if(text.compare(bad3[j]) == 0) return true;
    }

    // Palabra de cuatro letras
    else if( text.size() == 4 ){
        bad4.push_back("esto"); bad4.push_back("sido");
        bad4.push_back("cada"); bad4.push_back("tras");
        bad4.push_back("cual"); bad4.push_back("pero");
        bad4.push_back("este"); bad4.push_back("esta");
        bad4.push_back("para"); bad4.push_back("como");

        for(j=0; j<bad4.size(); ++j)
            if(text.compare(bad4[j]) == 0) return true;
    }

    // Palabra de cinco letras
    else if( text.size() == 5 ){
        bad5.push_back("tiene"); bad5.push_back("donde");
        bad5.push_back("estos"); bad5.push_back("hasta");
        bad5.push_back("desde"); bad5.push_back("sobre");
        bad5.push_back("entre");

        for(j=0; j<bad5.size(); ++j)
           if(text.compare(bad5[j]) == 0)  return true;
    }

    // Palabra de siete letras
    else if( text.size() == 7 ){
        bad7.push_back("tambien");

        for(j=0; j<bad7.size(); ++j)
            if(text.compare(bad7[j]) == 0) return true;
    }

    return false;
}

void getTitle(int &id, string &title){
    string _pathTo = "database/" + to_string(id) + ".txt";
    ifstream _file;
    _file.open(_pathTo);
    getline(_file,title); // Jala una linea
    _file.close();
}

void getContent_c(int id)
{
	string _pathTo = "database/" + to_string(id) + ".txt";
	ifstream _file;
	string value;
	_file.open(_pathTo);

  while(getline(_file,value)) {
		cout<<value<< endl;
  }
  //printf("Leído...\n");
	_file.close();
}

string getContent(int &id)
{
	string _pathTo = "database/" + to_string(id) + ".txt";
	ifstream _file;
	string value;
  string Resu;
	_file.open(_pathTo);

  while(getline(_file,value)) {
		Resu+=value;
  }
  //printf("Leído...\n");
	_file.close();
  return Resu;
}

int	compare_word(string word_node,string word_insert)
{
	unsigned int i;
	for(i=0 ; i < word_node.size() ; ++i)
		if(word_node[i] != word_insert[i])
			break;
	return i;
}

class radix_trie_index
{
	public:
	vector<int> id_file;
	vector<float> relevance;
	int elements=0;

	void print_radix_trie_index()
	{
		cout<<"{";
		for(int i=0 ; i < this->elements ; ++i)
			cout<< this->id_file[i] << ":" << this->relevance[i] << endl;
		cout << "}";
	}

	void insert(int id_file, float relevance)
	{
		if(this->elements!=0) //insertar y mantener orden
		{
			int pos=0;
			while(id_file >= this->id_file[pos] && pos < this->elements) //busqueda de posicion
			{
				pos++;
			}

			this->id_file.push_back(this->id_file.back());
			this->relevance.push_back(this->relevance.back());

			for(int i=this->elements-2 ; i >= pos ; i--) //recorrer a la derecha
			{
				this->id_file[i+1]=this->id_file[i];
				this->relevance[i+1]=this->relevance[i];
			}

			this->id_file[pos] = id_file;
			this->relevance[pos] = relevance;
		}
		else
		{
			this->id_file.push_back(id_file);
			this->relevance.push_back(relevance);
		}
		this->elements++;
	}
};

// RadixTrie
class radix_trie_node
{
	public:
	radix_trie_index *index=NULL;
	short int elements=0;

	vector<string> words;
	vector<radix_trie_node*> pointers;

	void insert(string word , int id_file, float relevance)
	{
		if(word != "") //no encontro donde aun
		{
			if(this->elements>0) //si tiene hijos
			{
				unsigned int equals;
				bool match=0;
				short int pos=0;

				while(pos < this->elements && word[0] >= this->words[pos][0]) //busqueda en orden
				{
					equals = compare_word(this->words[pos] , word);
					if(equals == 0) {}
					else if(equals < this->words[pos].size()) //SPLIT
					{
						match=1;

						radix_trie_node *father = new radix_trie_node;
						father->words.push_back(this->words[pos].substr(equals));
						father->pointers.push_back(this->pointers[pos]);
						father->elements++;

						this->words[pos]=this->words[pos].substr(0,equals);
						this->pointers[pos]=father;

						this->pointers[pos]->insert(word.substr(equals) , id_file , relevance); //seguimos buscando

						break;
					}
					else //equals == node->words[i].size() //EXACTO
					{
						match=1;
						this->pointers[pos]->insert(word.substr(equals) , id_file , relevance); //seguimos buscando
						break;
					}
					pos++;
				}
				if(match==0)  //tiene hijos y no hay match, inserta
				{
					this->words.push_back(this->words.back());
					this->pointers.push_back(this->pointers.back());
					this->elements++;

					for(short int i=this->elements-2 ; i >= pos ; i--)
					{
						this->words[i+1]=this->words[i];
						this->pointers[i+1]=this->pointers[i];
					}

					radix_trie_node *child = new radix_trie_node;
					radix_trie_index *index = new radix_trie_index;
					child->index=index;

					child->index->insert(id_file,relevance);

					this->words[pos] = word;
					this->pointers[pos] = child;
				}
			}
			else //si no tiene hijos
			{
				radix_trie_node *child = new radix_trie_node;
				radix_trie_index *index = new radix_trie_index;
				child->index=index;

				child->index->insert(id_file,relevance);

				this->words.push_back(word);
				this->pointers.push_back(child);
				this->elements++;
			}
		}
		else // word==""
		{
			if(this->index==NULL)
			{
				radix_trie_index *index = new radix_trie_index;
				this->index=index;
			}
			this->index->insert(id_file,relevance);
		}
	}

	radix_trie_index *search(string word)
	{
		if(word != "")
		{
			short int left=0;
			short int right=this->elements-1;
			short int pos=(left+right)/2;
			while(left <= right) //busqueda binaria
			{
				if(word[0] < this->words[pos][0])
					right=pos-1;
				else if(word[0] > this->words[pos][0])
					left=pos+1;
				else
				{
					int equals = compare_word(this->words[pos] , word);
					return this->pointers[pos]->search(word.substr(equals));
				}
				pos=(left+right)/2;
			}
			return NULL;
		}
		else
			return this->index;
	}

	void print_radix_trie_node()
	{
		cout << endl << "(" << this->elements << ")";
		if(this->index != NULL)
			this->index->print_radix_trie_index();
		for(int i=0 ; i < this->elements ; ++i)
		{
			cout << endl << this->words[i]  << endl;
			this->pointers[i]->print_radix_trie_node();
		}
	}

};


radix_trie_index *AND_results(vector<radix_trie_index*> &result_vector)
{
	if(result_vector.size()>1)
	{
		int min=0;

		radix_trie_index *result = new radix_trie_index;
		radix_trie_index *aux;

		for(unsigned int i=1 ; i < result_vector.size() ; ++i)
			if(result_vector[i]->elements < result_vector[min]->elements)
				min=i;

		aux=result_vector[0];
		result_vector[0]=result_vector[min];
		result_vector[min]=aux;

		vector<int> bases(result_vector.size(),0);

		for(int i=0 ; i < result_vector[0]->elements ; ++i) // I=recorre elementos minimos
		{
			bool match1=1;
			float sum_relevance=result_vector[0]->relevance[i];
			for(unsigned int j=1 ; j < result_vector.size(); ++j) // J=recorre vectores
			{
				bool match2=1;
				for(int k=bases[j] ; k < result_vector[j]->elements ; k++) // K=recorre posiciones en el vector
				{
					if(result_vector[j]->id_file[k] < result_vector[0]->id_file[i]) {}
					else if(result_vector[j]->id_file[k] > result_vector[0]->id_file[i])
					{
						bases[j]=k;
						match2=0;
						break;
					}
					else //igual
					{
						bases[j]=k+1;
						sum_relevance+=result_vector[j]->relevance[k];
						break;
					}
				}
				if(match2 == 0)
				{
					match1 = 0;
					break;
				}
			}
			if(match1 == 1)
			{
				result->insert(result_vector[0]->id_file[i],sum_relevance);
			}
		}
		if(result->elements == 0)
		{
			delete result;
			return NULL;
		}

		//sort results
		int h=result->elements-1;
		int l=0;
		int stack [h-l+1],i,j,p;
	   	int top=-1;

		float pivot;
		bool flag;
		int aux_id;
		float aux_rel;

	   	stack[++top]=l;
	   	stack[++top]=h;

		while(top>=0)
		{
			h=stack[top--];
			l=stack[top--];

			//partition hoare
			pivot=result->relevance[l];
			i=l-1;
			j=h+1;
			flag=1;
			while(flag)
			{
				do
				{
					i++;
				}
				while(result->relevance[i]>pivot);
				do
				{
					j--;
				}
				while(result->relevance[j]<pivot);
				if(i>=j)
				{
					p=j;
					flag=0;
				}
				else
				{
					aux_id=result->id_file[i];
					result->id_file[i]=result->id_file[j];
					result->id_file[j]=aux_id;
					aux_rel=result->relevance[i];
					result->relevance[i]=result->relevance[j];
					result->relevance[j]=aux_rel;
				}
			}
			if(p>l)
			{
				stack[++top]=l;
				stack[++top]=p;
			}
			if(p+1<h)
			{
				stack[++top]=p+1;
				stack[++top]=h;
			}
		}
		return result;
	}
	else if(result_vector.size()==1)
	{
		radix_trie_index *result;
		result=result_vector[0];
		//sort results
		int h=result->elements-1;
		int l=0;
		int stack [h-l+1],i,j,p;
	   	int top=-1;

		float pivot;
		bool flag;
		int aux_id;
		float aux_rel;

	   	stack[++top]=l;
	   	stack[++top]=h;

		while(top>=0)
		{
			h=stack[top--];
			l=stack[top--];

			//partition hoare
			pivot=result->relevance[l];
			i=l-1;
			j=h+1;
			flag=1;
			while(flag)
			{
				do
				{
					i++;
				}
				while(result->relevance[i]>pivot);
				do
				{
					j--;
				}
				while(result->relevance[j]<pivot);
				if(i>=j)
				{
					p=j;
					flag=0;
				}
				else
				{
					aux_id=result->id_file[i];
					result->id_file[i]=result->id_file[j];
					result->id_file[j]=aux_id;
					aux_rel=result->relevance[i];
					result->relevance[i]=result->relevance[j];
					result->relevance[j]=aux_rel;
				}
			}
			if(p>l)
			{
				stack[++top]=l;
				stack[++top]=p;
			}
			if(p+1<h)
			{
				stack[++top]=p+1;
				stack[++top]=h;
			}
		}
		return result;
	}
	else
		return NULL;
}

//vitto code

void editDist(string &,string &, int &);

void editDist2(string &,string &, int &);

void similaridad(string &s,int tolerancia, int dis_actual, string word, radix_trie_node* nodo, vector<string> &lista);//!!!

string similar(string &s,radix_trie_node* root);

void editDist(string &s1,string &s2, int &dist){
	int n=s1.size()+1;
	int m=s2.size()+1;
	int mem[n][m];
	int i,j,x,q,temp,temp1;
	
	for(j=0;j<m;j++){
		mem[0][j]=j;
	}

	for(i=1;i<n;i++){
		mem[i][0]=i;
	}

	x=1;
	q=(n<m)?n:m;
	while(x<q){
		for(i=x;i<n;i++){
			temp=mem[i-1][x]+1;
			temp1=mem[i][x-1]+1;
			if(temp1<temp){
				temp=temp1;
			}
			temp1=mem[i-1][x-1];
			if(s2[x-1]!=s1[i-1]){
				++temp1;
			}
			if(temp1<temp){
				temp=temp1;
			}
			mem[i][x]=temp;
		}

		for(j=x+1;j<m;j++){
			temp=mem[x][j-1]+1;
			temp1=mem[x-1][j]+1;
			if(temp1<temp){
				temp=temp1;
			}
			temp1=mem[x-1][j-1];
			if(s2[j-1]!=s1[x-1]){
				++temp1;
			}
			if(temp1<temp){
				temp=temp1;
			}
			mem[x][j]=temp;

		}
		++x;

	}

	dist=mem[n-1][m-1];
}

void editDist2(string &s1,string &s2, int &dist){
	int n=s1.size()+1;
	int m=s2.size()+1;
	int mem[n][m];
	int i,j,x,q,temp,temp1;
	
	for(j=0;j<m;j++){
		mem[0][j]=j;
	}

	for(i=1;i<n;i++){
		mem[i][0]=i;
	}

	x=1;
	q=(n<m)?n:m;
	while(x<q){
		for(i=x;i<n;i++){
			temp=mem[i-1][x]+1;
			temp1=mem[i][x-1]+1;
			if(temp1<temp){
				temp=temp1;
			}
			temp1=mem[i-1][x-1];
			if(s2[x-1]!=s1[i-1]){
				++temp1;
			}
			if(temp1<temp){
				temp=temp1;
			}
			mem[i][x]=temp;
		}

		for(j=x+1;j<m;j++){
			temp=mem[x][j-1]+1;
			temp1=mem[x-1][j]+1;
			if(temp1<temp){
				temp=temp1;
			}
			temp1=mem[x-1][j-1];
			if(s2[j-1]!=s1[x-1]){
				++temp1;
			}
			if(temp1<temp){
				temp=temp1;
			}
			mem[x][j]=temp;

		}
		++x;
	}

	temp=mem[n-1][m-1];
	for(i=0;i<n-1;i++){
		if(mem[i][m-1]<temp){
			temp=mem[i][m-1];
		}
	}

	for(i=0;i<n-1;i++){
		if(mem[n-1][i]<temp){
			temp=mem[n-1][i];
		}
	}
	dist=temp;
}

void similaridad(string &s,int tolerancia, int dis_actual, string palabra, radix_trie_node* nodo, vector<string> &lista){
	int dist;
	string texto;
	if(!lista.size()){
		for(int i=0;i<(nodo->elements);i++){
			texto=palabra+nodo->words[i];
			if((nodo->pointers[i])->index!=NULL || nodo->pointers[i]==NULL){
				editDist(texto,s,dist);
				if(dist<=tolerancia){
					lista.push_back(texto);
				}
			}
			
			if(lista.size()==0 && nodo->pointers[i]!=NULL){
				editDist2(texto,s,dist);
				if(dist<=tolerancia){
					similaridad(s,tolerancia, dist, texto, nodo->pointers[i], lista);
				}
			}		
		}
	}
}

string similar(string &s,radix_trie_node* root){
	int tolerancia=1;
	vector<string> lista;
	while(lista.size()==0||tolerancia<(int)s.size()){
		similaridad(s,tolerancia,0,"",root,lista);
		tolerancia++;
	}
	if(lista.size()){
		return lista[lista.size()-1];
	}else{
		return "";//return random?
	}
}

