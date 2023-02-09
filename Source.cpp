#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <nlohmann/json.hpp>
#include <urlmon.h>

#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "Winmm.lib")

using json = nlohmann::json;

//const wchar_t* eqAPI = L"https://earthquake.usgs.gov/fdsnws/event/1/query?format=geojson&starttime=NOW&minmagnitude=5";
//const wchar_t* eqAPI = L"https://earthquake.usgs.gov/fdsnws/event/1/query?format=geojson&starttime=2018-01-01&endtime=2018-01-05&minmagnitude=4.5";
const wchar_t* eqAPI = L"https://earthquake.usgs.gov/fdsnws/event/1/query?format=geojson&starttime=NOW&minmagnitude=5&latitude=55.75&longitude=12.25&maxradiuskm=600";
const wchar_t* jsonF = L"eqFile.json";

int main()
{
	if (S_OK != URLDownloadToFile(NULL, eqAPI, jsonF, 0, NULL))
		std::cerr << "Failed to download file.\n";

	std::ifstream f(jsonF);
	json data = json::parse(f);

	std::string cleanedUp;
	cleanedUp = to_string(data["features"]);

	if (data["features"].size() > 0)
	{
		PlaySound(TEXT("C:\\Windows\\Media\\Speech On.wav"), NULL, SND_SYNC);

		for (int i = 0; i < data["features"].size(); i++)
		{
			for (int j = 0; j < data["features"][i].size(); j++)
			{
				std::cout << "[EARTHQUAKE DETECTED]\nMagnitude: " << data["features"][j]["properties"]["mag"] << "\n Place: " << data["features"][j]["properties"]["place"] << "\n Coords: " << data["features"][j]["geometry"]["coordinates"] << "\n\n";
			}
		}
	}
	else
		std::cout << "Calm\n";

	return 0;
}