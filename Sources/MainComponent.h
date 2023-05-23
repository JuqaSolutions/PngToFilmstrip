#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "CreateFilmstripThread.h"


class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //For Windows Clion Debugging
    void printToLog(juce::String message){std::cout<<message<<std::endl;}

private:
    juce::Label brandLabel, appNameLanel, inputFilesLabel, outputFolderLabel;
    juce::TextButton proceedButton, supportUsButton;
    juce::ImageButton logoOpenWebBrowser, inputBrowserButton, outputBrowserButton;
    juce::Label inputTextEditor, outputTextEditor;

    juce::File fileToLoad{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("/PNGToFilmstrip/pngToConvert") };
    juce::File fileToSave{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("/PNGToFilmstrip/exportedPngFilmstrip/Output.png") };

    std::unique_ptr<juce::FileChooser> myChooser;
    std::function<void()> function = [this]{proceed();};
    CreateFilmstripThread createFilmstripThread{function};

    void launchBrowser(juce::String browserText, juce::Label& textEditor);
    void proceed();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};