#include "GettingTxT.h"
String SpecialCharacters = ",;.():_-+*\"='[]|{}¿?¡!/«»~@#&";

/*
 * Constructors
 */
GettingTxT::GettingTxT(String pathTo): _pathTo(pathTo){
}


/*
 * Get Articles
 * ------------
 */
void GettingTxT::createFiles(){
    std::vector<std::string> files;
    std::string line;

    getdir(_pathTo,files);

    // Loop for files
    for(uint i=0; i<files.size(); ++i){
    //
    //- Get lines
    //  ---------
        if( files[i].size() > 5){
            std::cout << _pathTo + "/" +files[i] << std::endl; 
            _file.open(_pathTo + "/" +files[i]);
            while ( this->createArticleFiles() ){ }
            _file.close();
        }
    }
}


/*
 * Get Articles
 * ------------
 */
void GettingTxT::analyzeArticles(){
    std::vector<std::string> files;
    std::string line;

    getdir(_pathTo,files);

    // Loop for files
    for(uint i=0; i<files.size(); ++i){
    //
    //- Get lines
    //  ---------
        if( files[i].size() > 5){
            std::cout << _pathTo + "/" +files[i] << std::endl; 
            _file.open(_pathTo + "/" +files[i]);
            while ( this->getArticles() ){ }
            _file.close();
        }
    }
}


/*
 * Get Articles
 * ------------
 */
bool GettingTxT::getArticles(){
    std::string line,word,
                title;
    std::size_t found, _endID,_startTitle,_endTitle;

    //
    // Title
    // =====

    // Busca la cabecera de la forma:
    // <doc id="32436" title="Ampolla" nonfiltered="4884" processed="4830" dbindex="14995">
    if( getline(_file,line) ){
        found = line.find("<doc id=");
        if( found != 0){
            return this->getArticles();
        }
    }
    else return false;
    _endID      = line.find("\"",9,1); // Ultima comilla
    _startTitle = line.find("title=") + 7;
    _endTitle   = line.find("\"",_startTitle+1,1);

    // Get id
    _id = line.substr(9,_endID-9);

    // Get title
    title = line.substr(_startTitle,_endTitle-_startTitle);

    // Get URL
    _url = title;
    std::replace( _url.begin(), _url.end(), ' ', '_');
    _url = "https://en.wikipedia.org/wiki/" + _url;

    // Create article
    TxT article( std::stoi( _id ), _url );

    // Word per word (title)
    std::istringstream iss(title);
    while (std::getline(iss, word,' ')){
        article.add(word,true);
    }

    //
    // Content
    // =======
    bool isgood = false;

    // Line per line
    while( !isEndOfArticle( line ) ){
        isgood = true;
        
        // Clean Special characters
        removeCharsFromString(line,SpecialCharacters);

        // Reemplace tab with space
        std::replace( line.begin(), line.end(), '\t', ' ');

        // Word per word (content)
        std::istringstream iss(line);
        while (std::getline(iss, word,' ')){
            article.add(word);
        }
    }

    article.runPurge    ();
    article.analyzeWords();

    // Add to vector
    _articles.push_back( article );
    
    return isgood;
}


/*
 * Is the end of article?
 * ----------------------
 */
bool GettingTxT::isEndOfArticle( std::string &line ){
    // Normal getLine
    getline(_file,line);

    // Find the end
    if( line.size() < 20 ){
        std::size_t pos;

        // True end: ENDOFARTICLE
        pos = line.find("ENDOFARTICLE");
        if( pos == 0 ){
            getline(_file,line);
            return true;
        }

        // Véase también.
        pos = line.find("ase tambi");
        if( 1<pos && pos < 5 ){
            while( line.find("ENDOFARTICLE") !=0 )
                getline(_file,line);
            return true;
        }

        // Bibliografía.
        pos = line.find("Bibliograf");
        if( 0<=pos && pos < 4 ){
            while( line.find("ENDOFARTICLE") !=0 )
                getline(_file,line);
            return true;
        }

        // Enlaces externos.
        pos = line.find("Enlaces externos");
        if( 0<=pos && pos < 4 ){
            while( line.find("ENDOFARTICLE") !=0 )
                getline(_file,line);
            return true;
        }
        
        // Referencias.
        pos = line.find("Referencias");
        if( 0<=pos && pos < 4 ){
            while( line.find("ENDOFARTICLE") !=0 )
                getline(_file,line);
            return true;
        }
    }
    return false;
}


/*
 * Create Article Files
 * --------------------
 */
bool GettingTxT::createArticleFiles(){
    std::string line,word,
                id,title;
    std::size_t found, _endID,_startTitle,_endTitle;

    //
    // Title
    // =====

    // Busca la cabecera de la forma:
    // <doc id="32436" title="Ampolla" nonfiltered="4884" processed="4830" dbindex="14995">
    if( getline(_file,line) ){
        found = line.find("<doc id=");
        if( found != 0){
            return this->getArticles();
        }
    }
    else return false;
    _endID      = line.find("\"",9,1); // Ultima comilla
    _startTitle = line.find("title=") + 7;
    _endTitle   = line.find("\"",_startTitle+1,1);

    // Get id
    id = line.substr(9,_endID-9);

    // Get title
    title = line.substr(_startTitle,_endTitle-_startTitle);

    // Create file
    std::ofstream outfile ("database/"+id+".txt");
    cureString(title);
    outfile << title << std::endl;

    //
    // Content
    // =======
    bool isgood = false;

    // Line per line
    while( !isEndOfArticle( line ) ){
        isgood = true;
        if( line.size()>0 ){
            cureString(line);
            outfile << line << std::endl;
        } 
    }

    outfile.close();
    return isgood;
}


void GettingTxT::feedTrie( String pathTo ){
    uint  id;
    Words _w;
    
    std::cout << "Execute Feed Trie!" << std::endl;

    std::vector<std::size_t> index_vec;
    for (std::size_t i = 0; i != _articles.size(); ++i) { index_vec.push_back(i); }

    std::sort(index_vec.begin(), index_vec.end(),
              [&](std::size_t a, std::size_t b) { return _articles[a].getDocumentID() <  _articles[b].getDocumentID(); });
    /*
    std::vector<std::size_t> index_vec;
    for (std::size_t i = 0; i != wordList.size(); ++i) { index_vec.push_back(i); }

    std::sort(index_vec.begin(), index_vec.end(),
              [&](std::size_t a, std::size_t b) { return wordCount[a] < wordCount[b]; });
    */
    std::ofstream myfile (pathTo);
    if (myfile.is_open()){
        for(unsigned a = 0; a < _articles.size(); ++a){
            _w = _articles[index_vec[a]].getWords();
            id = _articles[index_vec[a]].getDocumentID();

            std::cout << "\t - " << a+1 <<  " de " << _articles.size() << std::endl;

            for( unsigned i = 0; i< _w.size(); ++i){
                myfile << _w[i].text  << "\t";
                myfile <<     id      << "\t";
                myfile << _w[i].value << "\n";
            }
        }
    }
    else std::cout << "Unable to open file" << std::endl;
}


/*
 * Create histogram
 * --------------------
 */
void GettingTxT::histogram(){
    std::vector<String> wordList ;
    std::vector< uint > wordCount;
    std::vector<String>::iterator it;
    uint sizeArt;
    uint     idx;
    Words     _w; 
    double value;

    std::cout << "Execute Histogram!" << std::endl;

    // Calculate
    for ( unsigned a=0; a<_articles.size(); ++a){
        sizeArt = _articles[a].getSize();
        _w      = _articles[a].getWords();

        // Print
        std::cout << "\t - " << a <<  " de " << _articles.size() << std::endl;

        for( unsigned i=0; i<_w.size(); ++i){
            it = find (wordList.begin(), wordList.end(), _w[i].text);

            // Value
            value = _w[i].value;
            if( value < 1.0 ) value = ceil(  value      * ((double)sizeArt) );
            else              value = ceil( (value - 1) * ((double)sizeArt) );

            // Palabra nueva
            if(it == wordList.end()){
                wordList .push_back( _w[i].text );
                wordCount.push_back( ((uint)value) ); 
            }
            // No es palabra nueva: Actualizar!
            else{
                idx = it - wordList.begin();
                wordCount[idx] += ((uint)value);
            }
        }
    }
    
    std::vector<std::size_t> index_vec;
    for (std::size_t i = 0; i != wordList.size(); ++i) { index_vec.push_back(i); }

    std::sort(index_vec.begin(), index_vec.end(),
              [&](std::size_t a, std::size_t b) { return wordCount[a] < wordCount[b]; });

    // Save
    std::ofstream myfile ("histoWords.txt");
    if (myfile.is_open()){
        
        for( unsigned i=0; i<index_vec.size(); ++i){
             myfile << wordList [index_vec[i]] << "\t";
             myfile << wordCount[index_vec[i]] << "\n";
        }
        myfile.close();
    }
    else std::cout << "Unable to open file" << std::endl;

}


