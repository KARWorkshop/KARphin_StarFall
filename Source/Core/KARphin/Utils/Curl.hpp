#pragma once

#include <curl/curl.h>

#include <filesystem>

#include <Common/Logging/Log.h>

 namespace KAR::Networking::Curl
{
	// Callback for writing data to a file
	size_t CurlCallbackFunc_WriteToFile(void* ptr, size_t size, size_t nmemb, FILE* stream)
	{
		return fwrite(ptr, size, nmemb, stream);
	}


	// Progress callback (new interface)
	int CurlCallbackFunc_ProgressCallback(void*,
		curl_off_t dltotal, curl_off_t dlnow,
		curl_off_t ultotal, curl_off_t ulnow)
	{
		if (dltotal > 0) {
			double percentage = (double)dlnow / (double)dltotal * 100.0;
			fmt::print("\rDownload progress: {}%\n", percentage);
		}
		return 0; // return non-zero to abort transfer
	}

	//defines a curl instance
	struct Curl
	{
		bool isInited = false; //is curl inited

		CURL* instance = nullptr;

		//inits curl as a whole
		inline void Init() { curl_global_init(CURL_GLOBAL_DEFAULT); isInited = true; }

		//creates a CURL instance
		inline CURL* CreateInstance() { instance = curl_easy_init(); return instance; }

		//destroys a CURL instance
		inline void DestroyInstance() { curl_easy_cleanup(instance); instance = nullptr; }

		//shutsdown curl as a whole
		inline void Shutdown()
		{
			if (instance) //destroys the instance if it exists
				DestroyInstance();

			curl_global_cleanup();
		}

		//performs a download
		inline bool PerformDownload(const std::filesystem::path& outputFilepath, const std::string&
URL)
		{
			//downloads the latest one for a specific track
			if (instance)
			{
				FILE* fp;
				CURLcode res;
				fp = fopen(outputFilepath.string().c_str(), "wb");
				if (!fp)
				{
					fclose(fp);
					fmt::print("Failed to write binary data as zip at \"{}\"\n", outputFilepath.string());
					return false;
				}

				//download file
				curl_easy_setopt(instance, CURLOPT_URL, URL.c_str());
				curl_easy_setopt(instance, CURLOPT_WRITEFUNCTION,
				CurlCallbackFunc_WriteToFile); 				curl_easy_setopt(instance,
CURLOPT_WRITEDATA, fp);

				// Enable progress
				//curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
				//curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION,
				//CurlCallbackFunc_ProgressCallback);
				//curl_easy_setopt(curl, CURLOPT_XFERINFODATA, NULL);

				// Optional: Follow redirects
				curl_easy_setopt(instance, CURLOPT_FOLLOWLOCATION, 1L);

				// Perform download
				res = curl_easy_perform(instance);
				if (res != CURLE_OK)
				{
					fclose(fp);
					fmt::print("curl_easy_perform() failed: {}\n", curl_easy_strerror(res));
					return false;
				}

				fclose(fp);
				return true;
			}
		}
	};
 }