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
    proceedButton.onClick = [this] {createFilmstripThread.launchThread();};
    //TODO Put Patreon link
}

MainComponent::~MainComponent()
{
    if(createFilmstripThread.isThreadRunning())
        createFilmstripThread.stopThread(10);
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

void MainComponent::proceed() {
    DBG("Proceed!");

    /**
    Verifications:

        input:
            folder contains .png files and not empty - height and width identical on all files - files are Bitmap type - ...
        thread:
            for processing

            ////loadFiles(pathForLoad);
            //verifyFiles();
            //assembleFiles();
    */

    DBG("is loaded: " << fileToLoad.getFullPathName());

    if (!fileToLoad.exists()) {
        fileToLoad.createDirectory();
    }

    if (!fileToSave.exists()) {
        fileToSave.create();
    }

    if (fileToLoad.isDirectory()) {
        DBG("is directory");

        auto result = juce::Array<juce::File>();

        if (fileToLoad.findChildFiles(
                result,
                2,
                false,
                "*.png")) {
            DBG("contains of the directory: " << result.size());
            std::cout<<result.size()<<std::endl;

            juce::PNGImageFormat imageFileFormat;
            juce::Array<juce::Image> imageArray{};
            int width = 0;
            int height = 0;
            int outputHeight = 0;

            //TODO !!!!! Create a THREAD !!!!!!!!!!!
            for (juce::File file: result)
            {
                juce::Image tempImage;
                int tempWidth{123};
                int tempHeight{123};

                //juce::FileInputStream fileInputStream = juce::FileInputStream(file);

//                if (!imageFileFormat.canUnderstand(fileInputStream))
//                        DBG("Wrong file type, need png file format");
//                else
//                {
                    tempImage = juce::ImageFileFormat::loadFrom(file);//imageFileFormat.decodeImage(fileInputStream);
                //}
                //std::cout<<fileInputStream.getTotalLength()<<std::endl;
                std::cout<<tempImage.isValid()<<std::endl;

                tempWidth = tempImage.getWidth();
                tempHeight = tempImage.getHeight();

                DBG(tempHeight << " + " << tempWidth);
                std::cout<<tempHeight << " + " << tempWidth<<std::endl;

                imageArray.add(tempImage);//.decodeImage(fileInputStream));
                width = tempWidth;
                height = tempHeight;

                /* if ((tempWidth != 0 || tempWidth != width)
                     &&
                     (tempHeight != 0 || tempHeight != height))
                 {
                     DBG("The Image size doesn't match with the others");
                 }
                 else {
                     imageArray.add(imageFileFormat.decodeImage(juce::FileInputStream(file)));
                 }*/
            }

            outputHeight = height * imageArray.size();

            juce::Image outputImage{juce::Image::ARGB, width, outputHeight, true};

            int arrayIndex = 0;
            int heightForLoop = 0;

            while (arrayIndex < imageArray.size()) {
                for (int h = 0; h < height; ++h) {
                    for (int w = 0; w < width; ++w) {
                        outputImage.setPixelAt(w, heightForLoop, imageArray.getReference(arrayIndex).getPixelAt(w, h));
                    }
                    ++heightForLoop;
                }
                ++arrayIndex;
            }

            juce::FileOutputStream outputStream{fileToSave};
            imageFileFormat.writeImageToStream(outputImage, outputStream);
        }
        else
        {
            juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon, "Empty folder", "The folder containing the .png files is empty.");
        }
    }
}