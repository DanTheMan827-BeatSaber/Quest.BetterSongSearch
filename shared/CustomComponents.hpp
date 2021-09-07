#pragma once

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/RectOffset.hpp"

#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "questui_components/shared/components/layouts/VerticalLayoutGroup.hpp"
#include "questui_components/shared/components/layouts/HorizontalLayoutGroup.hpp"
#include "questui_components/shared/components/settings/StringSetting.hpp"
#include "questui_components/shared/components/settings/DropdownSetting.hpp"
#include "questui_components/shared/components/Text.hpp"


namespace BetterSongSearch::UI {
    class SongListVerticalLayoutGroup : public QuestUI_Components::VerticalLayoutGroup {
    public:
        explicit SongListVerticalLayoutGroup(std::initializer_list<QuestUI_Components::ComponentWrapper> children) : VerticalLayoutGroup(children) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            VerticalLayoutGroup::render(parentTransform);

            auto verticalLayoutGroup = getTransform()->get_gameObject()->GetComponent<UnityEngine::UI::VerticalLayoutGroup*>();
            verticalLayoutGroup->set_childAlignment(UnityEngine::TextAnchor::UpperLeft);
            verticalLayoutGroup->set_childControlWidth(true);
            verticalLayoutGroup->set_childControlHeight(false);
            verticalLayoutGroup->set_childForceExpandHeight(false);
            verticalLayoutGroup->set_childForceExpandWidth(false);

            auto element = getTransform()->get_gameObject()->AddComponent<UnityEngine::UI::LayoutElement*>();
            element->set_preferredWidth(120);
            auto background = getTransform()->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            background->ApplyBackground(il2cpp_utils::newcsstr("round-rect-panel"));
            return this;
        }
    };

    class SongListHorizontalFilterBar : public QuestUI_Components::HorizontalLayoutGroup {
    public:
        explicit SongListHorizontalFilterBar(std::initializer_list<QuestUI_Components::ComponentWrapper> children) : HorizontalLayoutGroup(children) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            HorizontalLayoutGroup::render(parentTransform);

            auto horizontalLayoutGroup = getTransform()->get_gameObject()->GetComponent<UnityEngine::UI::HorizontalLayoutGroup*>();
            horizontalLayoutGroup->set_childAlignment(UnityEngine::TextAnchor::MiddleCenter);
            horizontalLayoutGroup->set_childForceExpandWidth(false);
            horizontalLayoutGroup->set_childControlWidth(true);
            horizontalLayoutGroup->set_childControlHeight(true);
            horizontalLayoutGroup->set_childForceExpandHeight(false);
            horizontalLayoutGroup->set_childScaleWidth(false);

            auto element = getTransform()->get_gameObject()->AddComponent<UnityEngine::UI::LayoutElement*>();
            element->set_preferredHeight(10);
            auto background = getTransform()->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            background->ApplyBackground(il2cpp_utils::newcsstr("round-rect-panel"));
            return this;
        }
    };

    class SongListHorizontalLayout : public QuestUI_Components::HorizontalLayoutGroup {
    public:
        explicit SongListHorizontalLayout(std::initializer_list<QuestUI_Components::ComponentWrapper> children) : HorizontalLayoutGroup(children) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            HorizontalLayoutGroup::render(parentTransform);

            auto horizontalLayoutGroup = getTransform()->get_gameObject()->GetComponent<UnityEngine::UI::HorizontalLayoutGroup*>();

            auto element = getTransform()->get_gameObject()->AddComponent<UnityEngine::UI::LayoutElement*>();
            element->set_preferredHeight(70);
            element->set_preferredWidth(80);
            auto background = getTransform()->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            //background->ApplyBackground(il2cpp_utils::newcsstr("round-rect-panel"));
            return this;
        }
    };

    class SongVerticalGroup : public QuestUI_Components::VerticalLayoutGroup {
    public:
        explicit SongVerticalGroup(std::initializer_list<QuestUI_Components::ComponentWrapper> children) : VerticalLayoutGroup(children) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            VerticalLayoutGroup::render(parentTransform);

            auto verticalLayoutGroup = getTransform()->get_gameObject()->GetComponent<UnityEngine::UI::VerticalLayoutGroup*>();

            verticalLayoutGroup->set_padding(UnityEngine::RectOffset::New_ctor(1,1,1,2));

            auto element = getTransform()->get_gameObject()->AddComponent<UnityEngine::UI::LayoutElement*>();
            //element->set_preferredWidth(40);

            auto fitter = getTransform()->get_gameObject()->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
            fitter->set_horizontalFit(UnityEngine::UI::ContentSizeFitter::FitMode::Unconstrained);

            auto background = getTransform()->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            background->ApplyBackgroundWithAlpha(il2cpp_utils::newcsstr("round-rect-panel"), 1);
            return this;
        }
    };

    class SongHorizontalTitleTimeText : public QuestUI_Components::HorizontalLayoutGroup {
    public:
        explicit SongHorizontalTitleTimeText(std::initializer_list<QuestUI_Components::ComponentWrapper> children) : HorizontalLayoutGroup(children) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            HorizontalLayoutGroup::render(parentTransform);

            auto horizontalLayoutGroup = getTransform()->get_gameObject()->GetComponent<UnityEngine::UI::HorizontalLayoutGroup*>();
            horizontalLayoutGroup->set_spacing(3);

            return this;
        }
    };

    class SongHorizontalAuthorRatingText : public QuestUI_Components::HorizontalLayoutGroup {
    public:
        explicit SongHorizontalAuthorRatingText(std::initializer_list<QuestUI_Components::ComponentWrapper> children) : HorizontalLayoutGroup(children) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            HorizontalLayoutGroup::render(parentTransform);

            auto horizontalLayoutGroup = getTransform()->get_gameObject()->GetComponent<UnityEngine::UI::HorizontalLayoutGroup*>();
            horizontalLayoutGroup->set_spacing(2);
            horizontalLayoutGroup->set_padding(UnityEngine::RectOffset::New_ctor(0,0,1,2));

            return this;
        }
    };

    class TitleTimeText : public QuestUI_Components::Text {
    public:
        explicit TitleTimeText(std::string_view text, std::optional<InitialTextData> textData = std::nullopt) : QuestUI_Components::Text(text, textData) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            QuestUI_Components::Text::render(parentTransform);

            auto textMeshProUGUI = getTransform()->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
            textMeshProUGUI->set_fontSize(2.7);
            textMeshProUGUI->set_overflowMode(TMPro::TextOverflowModes::Ellipsis);
            textMeshProUGUI->set_enableWordWrapping(false);
            textMeshProUGUI->set_alignment(TMPro::TextAlignmentOptions::MidlineLeft);

            return this;
        }
    };

    class AuthorRatingText : public QuestUI_Components::Text {
    public:
        explicit AuthorRatingText(std::string_view text, std::optional<InitialTextData> textData = std::nullopt) : QuestUI_Components::Text(text, textData) {}

    protected:
        virtual Component *render(UnityEngine::Transform *parentTransform) override {
            QuestUI_Components::Text::render(parentTransform);

            auto textMeshProUGUI = getTransform()->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
            textMeshProUGUI->set_fontSize(2.4);
            textMeshProUGUI->set_overflowMode(TMPro::TextOverflowModes::Ellipsis);
            textMeshProUGUI->set_enableWordWrapping(false);
            textMeshProUGUI->set_alignment(TMPro::TextAlignmentOptions::MidlineLeft);

            return this;
        }
    };
}