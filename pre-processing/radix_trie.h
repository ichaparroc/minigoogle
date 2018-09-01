#include<string.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>

using namespace std;

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
	else
		return result_vector[0];
}

