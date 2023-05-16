#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    addAndMakeVisible(brandLabel);
    addAndMakeVisible(appNameLanel);

    addAndMakeVisible(inputFilesLabel);
    addAndMakeVisible(inputTextEditor);
    addAndMakeVisible(inputBrowserButton);

    addAndMakeVisible(outputFolderLabel);
    addAndMakeVisible(outputTextEditor);
    addAndMakeVisible(outputBrowserButton);

    addAndMakeVisible(proceedButton);

    brandLabel.setText("Juqa.Solutions", juce::dontSendNotification);
    appNameLanel.setText("PNG TO FILMSTRIP", juce::dontSendNotification);
    inputFilesLabel.setText("Select the folder containing the .png files:", juce::dontSendNotification);
    inputTextEditor.setText(fileToLoad.getFullPathName());
    outputFolderLabel.setText("Select the output folder:", juce::dontSendNotification);
    outputTextEditor.setText(fileToSave.getFullPathName());
    proceedButton.setButtonText("Let's go!");

    inputBrowserButton.onClick = [&] {launchBrowser("Select the folder containing the .png files:", inputTextEditor); };
    outputBrowserButton.onClick = [&] {launchBrowser("Select the output folder:", outputTextEditor); };
    proceedButton.onClick = [&] {proceed();};

    //TODO Put Patreon link
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    auto height = bounds.getHeight() / 4;

    auto headerBounds = bounds.removeFromTop(height);
    auto inputBounds = bounds.removeFromTop(height);
    auto outputBounds = bounds.removeFromTop(height);
    auto footerBounds = bounds.removeFromTop(height);

    brandLabel.setBounds(headerBounds.removeFromLeft(headerBounds.getWidth() / 2));
    appNameLanel.setBounds(headerBounds);

    inputFilesLabel.setBounds(inputBounds.removeFromTop(inputBounds.getHeight() / 2));
    inputTextEditor.setBounds(inputBounds.removeFromLeft(inputBounds.getWidth() * 0.9f));
    inputBrowserButton.setBounds(inputBounds);

    outputFolderLabel.setBounds(outputBounds.removeFromTop(outputBounds.getHeight() / 2));
    outputTextEditor.setBounds(outputBounds.removeFromLeft(outputBounds.getWidth() * 0.9f));
    outputBrowserButton.setBounds(outputBounds);

    proceedButton.setBounds(footerBounds.removeFromRight(footerBounds.getWidth() / 2));
}

void MainComponent::launchBrowser(juce::String browserText, juce::TextEditor& textEditor)
{
    myChooser = std::make_unique<juce::FileChooser>(browserText,
                                                    juce::File::getSpecialLocation(juce::File::userHomeDirectory),
                                                    "*.png");

    myChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
            [&](const juce::FileChooser& chooser)
            {
                juce::File returnedFile(chooser.getResult());
                textEditor.setText(returnedFile.getFullPathName());
            });
}

void MainComponent::proceed()
{
    DBG("Poceed!");

    /**
    Verifications:

        input:
            folder contains .png files - height and width identical on all files - files are Bitmap type - ...
    */
}