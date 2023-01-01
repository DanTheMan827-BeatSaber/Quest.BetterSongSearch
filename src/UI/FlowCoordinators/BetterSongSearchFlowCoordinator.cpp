#include "UI/FlowCoordinators/BetterSongSearchFlowCoordinator.hpp"

#include "System/Action.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace QuestUI;

DEFINE_TYPE(BetterSongSearch::UI::FlowCoordinators, BetterSongSearchFlowCoordinator);



void BetterSongSearch::UI::FlowCoordinators::BetterSongSearchFlowCoordinator::Awake() {
    fcInstance = this;
    if (!SongListController || !SongListController->m_CachedPtr.m_value) {
        SongListController = BeatSaberUI::CreateViewController<ViewControllers::SongListController*>();
    }
    if (!FilterViewController ||  !FilterViewController->m_CachedPtr.m_value) {
        FilterViewController = BeatSaberUI::CreateViewController<ViewControllers::FilterViewController*>();
    }
    if (!DownloadHistoryViewController ||  !DownloadHistoryViewController->m_CachedPtr.m_value) {
        DownloadHistoryViewController = BeatSaberUI::CreateViewController<ViewControllers::DownloadHistoryViewController*>();
    }
}

void BetterSongSearch::UI::FlowCoordinators::BetterSongSearchFlowCoordinator::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    SetTitle(il2cpp_utils::newcsstr("Better Song Search"), HMUI::ViewController::AnimationType::In);
    showBackButton = true;
    ProvideInitialViewControllers(SongListController, FilterViewController, DownloadHistoryViewController, nullptr, nullptr);
}

void BetterSongSearch::UI::FlowCoordinators::BetterSongSearchFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
    this->Close();
    
}

//  std::function<void(int)> cancelConfirmCallback; 
void BetterSongSearch::UI::FlowCoordinators::BetterSongSearchFlowCoordinator::Close(bool immediately, bool downloadAbortConfim){
    if(downloadAbortConfim && ConfirmCancelOfPending([this, immediately](){this->Close(immediately, false);}))
		return;

    cancelConfirmCallback = nullptr;
    
    // Trigger refresh of songs only if needed
    if (DownloadHistoryViewController->hasUnloadedDownloads) {
        RuntimeSongLoader::API::RefreshSongs(false);
        DownloadHistoryViewController->hasUnloadedDownloads = false;
    }


    // Hide all modals
    for(auto modal: SongListController->GetComponentsInChildren<HMUI::ModalView*>()) {
        modal->Hide(false, nullptr);
    }

    
    this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, immediately);
};
bool BetterSongSearch::UI::FlowCoordinators::BetterSongSearchFlowCoordinator::ConfirmCancelOfPending(std::function<void()> callback){
    if (DownloadHistoryViewController->HasPendingDownloads()) {
        cancelConfirmCallback = callback;
        SongListController->ShowCloseConfirmation();
        return true;
    } else {
        return false;
    }
};

void BetterSongSearch::UI::FlowCoordinators::BetterSongSearchFlowCoordinator::ConfirmCancelCallback(bool doCancel){
    if(doCancel) {
        // Fail all dls
        for (auto entry : DownloadHistoryViewController->downloadEntryList)
        {
            if (entry->IsInAnyOfStates((DownloadHistoryEntry::DownloadStatus)(DownloadHistoryEntry::DownloadStatus::Downloading | DownloadHistoryEntry::DownloadStatus::Queued)))
            {
                entry->retries = 69;
                entry->status = DownloadHistoryEntry::DownloadStatus::Failed;
            }
        }

        // closeCancelSource?.Cancel();
        cancelConfirmCallback();
    }

    cancelConfirmCallback = nullptr;
}