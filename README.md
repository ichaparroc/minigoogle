# minigoogle-console version
Mini Google Implementation in Console

### Prerequisites

Install make to run MakeFile if you need
Download the pre-processed data: http://212.8.251.77/foodForTrie.zip
And the pre-processed database: http://212.8.251.77/database.zip
and unzip in the folder mini-google-console

### CLONE
Clone repository
* [minigoogle repository](https://github.com/ichaparroc/minigoogle.git) link 'https://github.com/ichaparroc/minigoogle.git'

Enter to folder minigoogle
```
 cd minigoogle/console-version
```

### COMPILE C++ API
If you use MakeFile just run
```
make build
```
Or
```
g++ -g -Wall -fopenmp -std=c++11 -o -O3 main_i_console main_i_console.cpp 
```

### EXCUTE C++ API
Run comand
```
./main_i_console
```
Or
```
make run
```

# minigoogle-web version
Mini Google Implementation in Web

### Prerequisites

We need have http server, php and module for connect http-server with php. (Common LAMP server, but we only need php and http server). HTTP SERVER EXAMPLE: APACHE2.
We need clone the repository into a "www" folder, for use php. For example, "/var/html/www" in linux.
Install make to run MakeFile if you need
Download the pre-processed data: http://212.8.251.77/foodForTrie.zip
And the pre-processed database: http://212.8.251.77/database.zip
and unzip in the folder mini-google-web

### CLONE
Clone repository
* [minigoogle repository](https://github.com/ichaparroc/minigoogle.git) link 'https://github.com/ichaparroc/minigoogle.git'

Enter to folder minigoogle
```
 cd minigoogle/web-version
```

### COMPILE C++ API
If you use MakeFile just run
```
make build
```
Or
```
g++ -Wall -o3 -fopenmp -std=c++11 -o main_i main_i.cpp

```

### EXCUTE C++ API
Run comand
```
./main_i
```
Or
```
make run
```
