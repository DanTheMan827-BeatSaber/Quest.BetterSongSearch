#pragma once

#include "main.hpp"
#include "uri.hh"
#include "web-utils/shared/WebUtils.hpp"
#include "logging.hpp"
#include <future>

using namespace WebUtils;
class BeatSaverRegionManager {
    public:
        static inline const std::string mapDownloadUrlFallback = "https://cdn.beatsaver.com";
        static inline const std::string detailsDownloadUrl = "https://api.beatsaver.com/maps/id/";

        static inline std::string mapDownloadUrl = "https://r2cdn.beatsaver.com";
        static inline std::string coverDownloadUrl = "https://cdn.beatsaver.com";
        static inline std::string previewDownloadUrl  = "https://cdn.beatsaver.com";

        static inline bool didTheThing = false;


    static void GetSongDescription(std::string key, std::function<void(std::string)> finished) {
        std::thread([key, finished]() mutable {
            auto result = Get<JsonResponse>(URLOptions(detailsDownloadUrl + key));

            if (result.IsSuccessful()) {
                if (result.responseData.has_value()) {
                    auto& value = result.responseData.value();
                    std::string description = value["description"].GetString();
                    return finished(description);
                }
            }
        }).detach();
    }

    static void RegionLookup(bool force = false) {
            if(didTheThing && !force)
                return;

            
            didTheThing = true;
            std::thread([]() {
                auto response = Get<JsonResponse>(URLOptions(detailsDownloadUrl + "225eb"));

                if (response.IsSuccessful()) {
                    if (response.responseData.has_value()) {
                        auto& value = response.responseData.value();
                        std::string joe = value["versions"].GetArray()[0]["coverURL"].GetString();
                        if(joe.length() > 0) {
                            uri u(joe);
                            coverDownloadUrl = previewDownloadUrl = fmt::format("{}://{}", u.get_scheme(), u.get_host());
                            return;
                        }
                    }
                }
            }).detach();
            
        }
};


