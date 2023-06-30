//Copyright 2023 Julien CAUBET
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "CreateFilmstripThread.h"
#include "BinaryData.h"

class MainComponent  : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    const juce::Label &getAppNameLanel() const;

    const juce::Label &getInputFilesLabel() const;

    const juce::Label &getOutputFolderLabel() const;

    const juce::TextButton &getProceedButton() const;

    const juce::TextButton &getSupportUsButton() const;

    const juce::ImageButton &getLogoOpenWebBrowser() const;

    const juce::ImageButton &getInputBrowserButton() const;

    const juce::ImageButton &getOutputBrowserButton() const;

    const juce::Label &getInputTextEditor() const;

    const juce::Label &getOutputTextEditor() const;

    const juce::File &getFileToLoad() const;

    const juce::File &getFileToSave() const;

    const std::unique_ptr<juce::FileChooser> &getMyChooser() const;

private:
    juce::Colour backgroundColour = juce::Colour::fromRGB(0, 68, 85);
    juce::Colour browserBackgroundColour = juce::Colours::darkgrey;
    juce::Colour appNameColour = juce::Colours::darkturquoise;
    juce::Colour browserLabelColour = juce::Colours::beige;

    juce::Label appNameLanel, inputFilesLabel, outputFolderLabel;
    juce::TextButton proceedButton, supportUsButton;
    juce::ImageButton logoOpenWebBrowser, inputBrowserButton, outputBrowserButton;
    juce::Label inputTextEditor, outputTextEditor;

    juce::File fileToLoad{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("/PNGToFilmstrip/pngToConvert") };
    juce::File fileToSave{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("/PNGToFilmstrip/exportedPngFilmstrip/Output.png") };

    std::unique_ptr<juce::FileChooser> myChooser;
    std::function<void()> function = [this]{proceed();};
    CreateFilmstripThread createFilmstripThread{function};

    void launchInputBrowser();
    void launchOutputBrowser();
    void proceed();
    void initializeImageButtons();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};