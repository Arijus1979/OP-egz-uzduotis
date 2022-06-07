#include "functions.h"

int main()
{
    multiset <pair<string, int>> data;
    stringstream buffer;
    read_file(buffer);
    analyse(data, buffer);
    print_words(data);
    search_url(buffer);

    return 0;
    
    

    


}

