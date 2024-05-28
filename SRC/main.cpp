#include "weatherapp.h"
#include "JSONParser.h"
#include <curl/curl.h>



Json::Value getJsonResponse(std::string apiUrl);
size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);



int main()
{
    WeatherApp app;
    app.homePage();

//    IntermediateUser app1;
//    app1.homePage();
}



Json::Value getJsonResponse(std::string apiUrl) {

  CURL* curl = curl_easy_init();
  if(curl) {
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);

    if(result == CURLE_OK) {
      // Parse JSON response
        JSONParser parser;
        Json::Value root = parser.parseJSON(response);
        std::cout << "Data fetched successfully." << std::endl;
      return root;
    }else {
        std::cout << "Error fetching data: " << curl_easy_strerror(result) << std::endl;
    }

    curl_easy_cleanup(curl);
  }

  return "Unknown";
}



  size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
