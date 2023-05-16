#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void printToLog(juce::String message);

private:
    juce::Label brandLabel, appNameLanel, inputFilesLabel, outputFolderLabel;
    juce::TextButton proceedButton;
    juce::ImageButton inputBrowserButton, outputBrowserButton;
    juce::TextEditor inputTextEditor, outputTextEditor;

    juce::File fileToLoad{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("PNGToFilmstrip/pngToConvert") };
    juce::File fileToSave{ juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName() + ("PNGToFilmstrip/exportedPngFilmstrip/Output.png") };

    std::unique_ptr<juce::FileChooser> myChooser;

    void launchBrowser(juce::String browserText, juce::TextEditor& textEditor);
    void proceed();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};