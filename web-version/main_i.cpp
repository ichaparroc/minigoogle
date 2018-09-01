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

	int create_socket;
	socklen_t addrlen;
	struct sockaddr_in address;

	if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
		cout<<"The socket was created\n";
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(4000);
	cout<<"\nworking";

	if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
		cout<<"Binding Socket\n";

	// convert the socket to listen for incoming connections
	if (listen(create_socket, 0) < 0) {
		perror("listen");
		exit(-1);
	}

	puts("Listening to connection...");

	// allocate buffer
	int buflen, nread;
	char *buf;
	int indd2;
	//buflen = 1024;
	//buf = new char[buflen+1];
	string query,resultado;
	// loop to handle all requests
	//cout<<"> … Loading index done!"<<endl;
	while (1)
	{
  	//cout<<"> Enter your query:";
		buflen = 102400;
		buf = new char[buflen+1];
		unsigned int client = accept(create_socket,(struct sockaddr *)&address,&addrlen);

		// read a request
		memset(buf, 0, buflen);
		nread = recv(client, buf, buflen, 0); //recibe

		query=buf; //string luis alvaro
		bool match_gen=false;
		vector<string> query2;
		vector<string> query3;

		size_t pos = query.find(' ');
		size_t initialPos = 0;
		query2.clear();
		query3.clear();
		while( pos != std::string::npos )
		{
		    query2.push_back(query.substr( initialPos, pos - initialPos ) );
		    initialPos = pos + 1;

		    pos = query.find(' ', initialPos );
		}
		query2.push_back( query.substr( initialPos, std::min( pos, query.size() ) - initialPos + 1 ) );



		vector<radix_trie_index*> result_vector;
		radix_trie_index *result_index;
			double start_time = omp_get_wtime();
			for(unsigned int i = 0; i < query2.size(); i++)
			{
				cout<<query2[i];
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

			string title;
			resultado="Tiempo de busqueda: "+to_string(t_time)+" para: ";
			for(unsigned int i = 0; i < query3.size(); i++)
			{
				resultado+=query3[i]+" ";
			}

				if(result_index!=NULL){
			int found_count=result_index->id_file.size();
			int list_size=min(found_count,20);
					printf("\nNumero de resultados: %u\n\n", found_count);
					//printf("\nTiempo12: %s\n\n", resultado.c_str());


					for (int i = 0; i < list_size; i++) {
						getTitle(result_index->id_file[i], title);
						resultado+="@"+title;
						cout<<title<<endl;
					}
					cout<<endl;
					////////////////////////////////////////////////////

				/////////////////////////////////////////////////////
			}
			else{
				cout<<"No result found.";
			}
/*
			for (int indd = 0; indd < list_size; indd++) {
				indd2=result_index->id_file[indd];
				resultado+=";"+getContent(indd2);
				cout<<indd<<endl;
				cout<<resultado<<endl;
			}
*/
		printf("\nClient says: %s\n\n", resultado.c_str());

		memset(buf, 0, buflen);
		strcpy(buf, resultado.c_str());

		// echo back to the client
		send(client, buf, resultado.size(), 0);


		close(client);
		delete(buf);
	}

	close(create_socket);
	return 0;
}
