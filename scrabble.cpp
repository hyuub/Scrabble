#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <map>

#include <fstream>

size_t utf8Len(std::string s)
{
    return std::count_if(s.begin(),s.end(),[](char c) 
    { return (static_cast<unsigned char>(c) & 0xC0) != 0x80; } );
}

int main(void)
{
    std::ifstream input("slowa.txt");
    std::string line;

    std::vector<int> i;
    //std::vector<std::string> dict;
    std::multimap<std::string, std::string> dict;
    
    auto t1 = std::chrono::high_resolution_clock::now();
    
    std::cout<<"Loading dictionary"<<std::endl;

    while(std::getline(input,line))
    {
       line.erase(std::remove(line.begin(),line.end(),'\r'),line.end());
        //std::cout << line << std::endl;

        if(line.size() == utf8Len(line))
        {
            std::string sorted = line;
            std::sort(sorted.begin(), sorted.end());
            dict.insert(std::pair<std::string,std::string>(sorted,line));
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
    std::cout << "Time: " << (double)(dt.count())/1000000.0 << " seconds" << std::endl;

    std::string in;
    std::string one;

    std::cin >> one;

    while(in.size()!=7)
    {
        std::cin >> in;
        std::cout << "Musisz podac 7 liter wpisales: " << in.size() << std::endl;
    }

    if (in.find(one) != std::string::npos)
    {
        in+=one;
    } else 
    {
        std::cout << "Nie mozna znaleźć takiego słowa" << std::endl;
        return -1;
    }

    std::cout << "Szukamy z liter:" << in << std::endl;
    

    std::sort(in.begin(), in.end());

    t1 = std::chrono::high_resolution_clock::now();

    std::string sample;

    std::cout << "Dostepne hasla:" << std::endl;
    for(int i = 0; i < in.size(); i++) 
    {
        std::string sorted1 = sample;
        std::sort(sorted1.begin(), sorted1.end());
        auto result = dict.equal_range(sorted1);
        for (auto itr = result.first; itr != result.second; ++itr) {
            std::cout << itr->second << std::endl;
        }
        
        sample += in[i];
    }

    t2 = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
    std::cout << "Time: " << dt.count() << " microseconds" << std::endl;

    return 0;
}