#include <iostream>
#include <string.h>
#include <curl/curl.h>
#include <vector>

#define ERASE_INDEX 0
#define ERASE_LENGHT 12

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((std::string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

void getDigitsOfPi(std::vector<int> vec, long long int n)
{
    CURL *curl;
    CURLcode res;

    curl= curl_easy_init();
    if (curl) 
    {
        std::string URL;
        URL.assign("https://api.pi.delivery/v1/pi?start=" + std::to_string(n * 1000) + "&numberOfDigits=1000&radix=10");
    
        //std::cout << URL << "\n";

        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);

        //std::cout << "\nRESPONSE: \n" << response;

        response.erase(ERASE_INDEX, ERASE_LENGHT);
        response.erase(response.end()-3, response.end());

        std::cout << "\nNEW RESPONSE: \n" << response << "\n";

         for(int i = 0; i < response.size(); ++i)
             vec.push_back((response[i] - '0'));

        curl_easy_cleanup(curl);
    }
}


int main()
{
    std::vector<int> digits;
    for(long long int i = 0; true; ++i)
        getDigitsOfPi(digits, i);
    return 0;
}