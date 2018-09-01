#ifndef GETTINGTXT_H
#define GETTINGTXT_H

#include "includes.h"
#include "utils.h"
#include "txt.h"

class GettingTxT
{
private:
    // Parameters
    std::vector<TxT> _articles;
    String _pathTo;

    // Temporal
    std::ifstream _file;
    String _url, _id;

    bool getArticles();
    bool isEndOfArticle( std::string &line );

    bool createArticleFiles();
    
public:
    GettingTxT(){}
    GettingTxT(String pathTo);
    
    // Basic
    void createFiles();
    void analyzeArticles();

    // To trie
    void feedTrie( String pathTo );

    // Histogram
    void histogram();

};

#endif // GETTINGTXT_H