#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/algorithm/cxx11/copy_if.hpp>

#include <string>
#include <vector>
#include <iostream>

void TextSearch()
{
    std::string text = "Hello World this is a World!";
    std::string search;

    std::cout << "Text is: " << text << std::endl;
    std::cout << "Search: ";
    std::getline(std::cin, search);

    auto textIt = boost::algorithm::boyer_moore_search(
        text.begin(), text.end(), 
        search.begin(), search.end()
    );

    if (textIt.first != text.end())
    {
        std::cout << "Text found!" << std::endl;
        std::cout 
            << "Offset: " 
            << textIt.first - text.begin() 
            << " (Length: " 
            << textIt.second - textIt.first
            << ")" << std::endl
            ;
        std::cout << std::string(textIt.first, textIt.second) << std::endl;
    }
    else
    {
        std::cout << "Text NOT found!" << std::endl;
    }

}

int main()
{
    // TextSearch();

    std::vector<int> seq = { 0, 1, 2, 0, 1, 1, 0, 3 };
    std::vector<int> search = { 1, 1, 0 };

    auto find = boost::algorithm::boyer_moore_search(seq.begin(), seq.end(), search.begin(), search.end());
    std::cout << "Search at pos " << find.first - seq.begin() << " of seq" << std::endl;

    std::cout
        << "Seq all under 3: "
        << (boost::algorithm::all_of(seq.begin(), seq.end(), [](int i) { return i < 3; }) ? "true" : "false")
        << std::endl
        ;
    std::cout
        << "Search all under 3: "
        << (boost::algorithm::all_of(search.begin(), search.end(), [](int i) { return i < 3; }) ? "true" : "false")
        << std::endl
        ;

    std::vector<int> numbers = { 0, 2, 3, 4, 1, 2, 0, 5 };

    auto endIt = boost::algorithm::copy_if(
        numbers.begin(), numbers.end(),
        numbers.begin(),
        [](int n) { return n < 3; }
    );
    numbers.resize(endIt - numbers.begin());
}
