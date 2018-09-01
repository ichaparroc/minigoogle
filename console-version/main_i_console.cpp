#include<string.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include <omp.h>
#include"radix_trie.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/un.h>
#include<unistd.h>
#include<signal.h>
#include<algorithm>


using namespace std;

int main(void)
{
	radix_trie_node * master = new radix_trie_node;

	ifstream file;
	string line;
	string word;

	string palabra;
	int      id;
	float value;

	int i = 0;

	file.open("foodForTrie.txt");
	//while ( getline(file,line)){
	while ( getline(file,line)){
		istringstream iss(line);
		getline(iss, word,'\t');
        palabra = word;
		getline(iss, word,'\t');
		id = stoi(word);
		getline(iss, word,'\t');
		value = stof(word);

		if( i%1000000 == 0) cout << i << endl ;
		++i;
		master->insert(palabra,id,value);
	}
	file.close();

//////////////////////////////////////

	string query,query1,resultado;
	// loop to handle all requests
	cout<<"> … Loading index done!"<<endl;
	purgeUppercase(query1);
	cout<<"-----------------------------";
	cout<<query1;
	while (1)
	{

		cout<<"> Enter your query:";
	  	getline(cin, query);

		vector<string> query2;
		vector<string> query3;

		size_t pos = query.find(' ');
		size_t initialPos = 0;
		query2.clear();
		query3.clear();
		while( pos != std::string::npos )
		{
			query1=query.substr( initialPos, pos - initialPos ) ;
			//purgeUppercase(query1);
		    query2.push_back(query1);
		    initialPos = pos + 1;

		    pos = query.find(' ', initialPos );
		}
		query1=query.substr( initialPos, std::min( pos, query.size() ) - initialPos + 1 );
		//purgeUppercase(query1);
		query2.push_back(query1);

		vector<radix_trie_index*> result_vector;
		radix_trie_index *result_index;

		double start_time = omp_get_wtime();
		for(unsigned int i = 0; i < query2.size(); i++)
		{
			result_index=master->search(query2[i]);
			if(result_index!=NULL)
			{
				query3.push_back(query2[i]);
				result_vector.push_back(result_index);
			}
			else
			{
				query2[i]=similar(query2[i],master);
				i--;
			}
		}
		result_index=AND_results(result_vector);
		double t_time = omp_get_wtime() - start_time;

		cout<<"\nResultados para: ";
		for(unsigned int i = 0; i < query3.size(); i++)
		{
			cout<<query3[i]<<" ";
		}
		cout<<endl;
		string title;
		printf("\nTiempo %f\n\n", t_time);
		if(result_index!=NULL){
			int found_count=result_index->id_file.size();
			printf("\nNumero de resultados: %u\n\n", found_count);
			resultado=to_string(t_time);
			//printf("\nTiempo12: %s\n\n", resultado.c_str());
			int list_size=result_index->id_file.size();
			list_size=min(list_size,20);
			for (int i = 0; i < list_size; i++) {
				getTitle(result_index->id_file[i], title);
				cout<<"["<<i<<"] "<<title<<endl;
			}
			string ind;
			cout<<"Do you want to open any result [n or result number]? ";
			getline (cin, ind);
			//cout<<(int)ind[0]-48<<endl;
			if(ind[0]!='n' && ind[0]!='N'){
				int indd=stoi(ind);
				if (indd<=found_count) {
					indd=result_index->id_file[indd];
					getContent_c(indd);
				}
				else{
					cout<<"Invalid request.";
				}
			//cout<<"reconoce"<<endl
		}
		else{
			cout<<"Don search for content"<<endl;
		}
	}
	else{
		cout<<"No result found.";
	}
	}

	return 0;
}
