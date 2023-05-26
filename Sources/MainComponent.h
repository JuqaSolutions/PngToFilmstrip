#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "CreateFilmstripThread.h"
#include "BinaryData.h"

class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void initializeImageButtons();

private:
    juce::Colour backgroundColour = juce::Colour::fromRGB(0, 68, 85);
    juce::Colour browserBackgroundColour = juce::Colours::darkgrey;
    juce::Colour appNameColour = juce::Colours::lightgrey;

    juce::Label brandLabel, appNameLanel, inputFilesLabel, outputFolderLabel;
    juce::TextButton proceedButton, supportUsButton;
    juce::ImageButton logoOpenWebBrowser, inputBrowserButton, outputBrowserButton;
    juce::Label inputTextEditor, outputTextEditor;

    juce::File fileToLoad{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("/PNGToFilmstrip/pngToConvert") };
    juce::File fileToSave{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("/PNGToFilmstrip/exportedPngFilmstrip/Output.png") };

    std::unique_ptr<juce::FileChooser> myChooser;
    std::function<void()> function = [this]{proceed();};
    CreateFilmstripThread createFilmstripThread{function};

    void launchBrowser(juce::String browserText, juce::Label& textEditor, juce::File& fileToCopy);
    void proceed();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};