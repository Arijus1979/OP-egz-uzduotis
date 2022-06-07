#include "functions.h"

void SkipBOM(std::ifstream& in)
{
    char test[3] = { 0 };
    in.read(test, 3);
    if ((unsigned char)test[0] == 0xEF &&
        (unsigned char)test[1] == 0xBB &&
        (unsigned char)test[2] == 0xBF)
    {
        return;
    }
    in.seekg(0);
}

void read_file(stringstream &buffer)
{
    ifstream in("tekstas.txt");
    SkipBOM(in);
    buffer << in.rdbuf();
    in.close();
    
}

void analyse(multiset <pair<string, int>> &data, stringstream& buffer)
{
    
    int line_num = 0;
    string line = "", word = "";
    const string puncts = "%()[];',./{}:\"?><`~!-_1234567890";
    string output;
    
    while (!buffer.eof())
    {
        line_num++;
        getline(buffer, line);

        for (const auto& ch : line)
        {
            bool found = false;

            for (const auto& p : puncts)
            {
                if (ch == p)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                output += ch;
        }
        //cout << output << endl;

        stringstream eilute;
        eilute << output;
        output = "";
        //cout << line << endl;
        while (!eilute.eof())
        {
            eilute >> word;

            if (word.size() > 0)
            {
                data.insert({ word, line_num });
            }

            word = "";
        }
    }
}

void print_words(multiset <pair<string, int>> &data)
{
    set<string> result;
    multiset<string>result1;
    for (auto item : data) {
        result.insert(result.end(), item.first);
        result1.insert(result1.end(), item.first);
    }
    ofstream out("rezultatai.txt");
    for (auto t : result)
    {
        //out << pora.first << pora.second << endl;
        if (result1.count(t) >= 2)
        {
            out << left << setw(20) << setfill(' ') << t << " pasikartojo " << left << setw(3) << result1.count(t) << " kartus/u ";
            for (auto q : data)
            {
                if (q.first == t)
                {
                    out << setfill(' ') << right << setw(10) << q.second << " ";
                }
            }
            out << endl;
        }
    }
    out.close();
}

void search_url(stringstream& buffer)
{
    buffer.clear();
    buffer.seekg(0, std::ios::beg);
    ofstream out1("url.txt");
    string url_test, line;
    regex url(".*\\..*\\..*");
    while (!buffer.eof())
    {
        getline(buffer, line);
        stringstream eilute;
        eilute << line;
        while (!eilute.eof())
        {
            eilute >> url_test;
            if (regex_match(url_test, url))
            {
                out1 << url_test << endl;
            }
            url_test = "";
        }
        line = "";
    }
    out1.close();
   
}
